#include "Singleton.h"
#include "CurrentThread.h"
#include "Thread.h"

#include <boost/noncopyable.hpp>
#include <stdio.h>
#include <string>

class Test: boost::noncopyable
{
public:
	Test()
	{
		printf("tid=%d, constructing %p\n", xnet::CurrentThread::tid(), this);
	}

	~Test()
	{
		printf("tid=%d, destructing %p %s\n", xnet::CurrentThread::tid(), this, name_.c_str());
	}

	const std::string& name() const
	{
		return name_;
	}
	void setName(const std::string& n)
	{
		name_ = n;
	}

private:
	std::string name_;
};

void threadFunc()
{
	printf("tid=%d, %p name=%s\n", xnet::CurrentThread::tid(), &xnet::Singleton<Test>::instance(), xnet::Singleton<Test>::instance().name().c_str());
	xnet::Singleton<Test>::instance().setName("only one, changed");
}

int main()
{
	xnet::Singleton<Test>::instance().setName("only one");
	xnet::Thread t1(threadFunc);
	t1.start();
	t1.join();
	printf("tid=%d, %p name=%s\n", xnet::CurrentThread::tid(), &xnet::Singleton<Test>::instance(), xnet::Singleton<Test>::instance().name().c_str());
}
