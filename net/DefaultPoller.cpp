#include "Poller.h"
#include "PollPoller.h"
#include "EPollPoller.h"

#include <stdlib.h>

using namespace xnet::net;

Poller* Poller::newDefaultPoller(EventLoop* loop)
{
	if (::getenv("XNET_USE_POLL"))
	{
		return new PollPoller(loop);
	}
	else
	{
		return new EPollPoller(loop);
	}
}
