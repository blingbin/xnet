#include "BlockingQueue.h"
#include "CountDownLatch.h"
#include "Thread.h"
#include "Timestamp.h"

#include <boost/bind.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <map>
#include <string>
#include <stdio.h>

class Bench
{
 public:
  Bench(int numThreads)
    : latch_(numThreads),
      threads_(numThreads)
  {
    for (int i = 0; i < numThreads; ++i)
    {
      char name[32];
      snprintf(name, sizeof name, "work thread %d", i);
      threads_.push_back(new xnet::Thread(
            boost::bind(&Bench::threadFunc, this), std::string(name)));
    }
    for_each(threads_.begin(), threads_.end(), boost::bind(&xnet::Thread::start, _1));
  }

  void run(int times)
  {
    printf("waiting for count down latch\n");
    latch_.wait();
    printf("all threads started\n");
    for (int i = 0; i < times; ++i)
    {
      xnet::Timestamp now(xnet::Timestamp::now());
      queue_.put(now);
      usleep(1000);
    }
  }

  void joinAll()
  {
    for (size_t i = 0; i < threads_.size(); ++i)
    {
      queue_.put(xnet::Timestamp::invalid());
    }

    for_each(threads_.begin(), threads_.end(), boost::bind(&xnet::Thread::join, _1));
  }

 private:

  void threadFunc()
  {
    printf("tid=%d, %s started\n",
           xnet::CurrentThread::tid(),
           xnet::CurrentThread::name());

    std::map<int, int> delays;
    latch_.countDown();
    bool running = true;
    while (running)
    {
      xnet::Timestamp t(queue_.take());
      xnet::Timestamp now(xnet::Timestamp::now());
      if (t.valid())
      {
        int delay = static_cast<int>(timeDifference(now, t) * 1000000);
        // printf("tid=%d, latency = %d us\n",
        //        xnet::CurrentThread::tid(), delay);
        ++delays[delay];
      }
      running = t.valid();
    }

    printf("tid=%d, %s stopped\n",
           xnet::CurrentThread::tid(),
           xnet::CurrentThread::name());
    for (std::map<int, int>::iterator it = delays.begin();
        it != delays.end(); ++it)
    {
      printf("tid = %d, delay = %d, count = %d\n",
             xnet::CurrentThread::tid(),
             it->first, it->second);
    }
  }

  xnet::BlockingQueue<xnet::Timestamp> queue_;
  xnet::CountDownLatch latch_;
  boost::ptr_vector<xnet::Thread> threads_;
};

int main(int argc, char* argv[])
{
  int threads = argc > 1 ? atoi(argv[1]) : 1;

  Bench t(threads);
  t.run(10000);
  t.joinAll();
}
