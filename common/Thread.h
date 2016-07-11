#ifndef _XNET_COMMON_THREAD_H_
#define _XNET_COMMON_THREAD_H_

#include "Atomic.h"

#include <string>
#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
#include <pthread.h>

namespace xnet
{

class Thread: boost::noncopyable
{
public:
	typedef boost::function<void()> ThreadFunc;

	explicit Thread(const ThreadFunc&, const std::string& name = std::string());
	~Thread();

	void start();
	int join(); // return pthread_join()

	bool isStarted() const
	{
		return started_;
	}

	pid_t tid() const
	{
		return tid_;
	}
	const std::string& name() const
	{
		return name_;
	}

	static int numCreated()
	{
		return numCreated_.get();
	}

private:
	static void* startThread(void* thread);
	void runInThread();

	bool started_;
	pthread_t pthreadId_;
	pid_t tid_;
	ThreadFunc func_;
	std::string name_;

	static AtomicInt32 numCreated_;
};

}
#endif
