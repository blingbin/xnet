
#ifndef _XNET_COMMON_THREADPOOL_H_
#define _XNET_COMMON_THREADPOOL_H_

#include "Condition.h"
#include "Mutex.h"
#include "Thread.h"

#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

#include <deque>
#include <string>

namespace xnet
{

	class ThreadPool: boost::noncopyable
	{
	public:
		typedef boost::function<void()> Task;

		explicit ThreadPool(const std::string& name = std::string());
		~ThreadPool();

		void start(int numThreads);
		void stop();

		void run(const Task& f);

	private:
		void runInThread();
		Task take();

		MutexLock mutex_;
		Condition cond_;
		std::string name_;
		boost::ptr_vector<xnet::Thread> threads_;
		std::deque<Task> queue_;
		bool running_;
	};

}

#endif   //_XNET_COMMON_THREADPOOL_H_
