#include "Exception.h"
#include <stdio.h>

class Trace
{
public:
	void test()
	{
		throw xnet::Exception("oops");
	}
};

void A()
{
	Trace t;
	t.test();
}


void B()
{
	A();
}

void C()
{
	B();
}

int main()
{
	try
	{
		C();
	}
	catch (const xnet::Exception& ex)
	{
		printf("reason: %s\n", ex.what());
		printf("stack trace: %s\n", ex.stackTrace());
	}
}
