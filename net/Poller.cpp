
#include "Poller.h"

using namespace xnet;
using namespace xnet::net;

Poller::Poller(EventLoop* loop)
  : ownerLoop_(loop)
{
}

Poller::~Poller()
{
}

