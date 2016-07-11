#ifndef XNET_NET_POLLER_H
#define XNET_NET_POLLER_H

#include <vector>
#include <boost/noncopyable.hpp>

#include "Timestamp.h"
#include "EventLoop.h"

namespace xnet
{
namespace net
{

class Channel;


class Poller: boost::noncopyable
{
public:
	typedef std::vector<Channel*> ChannelList;

	Poller(EventLoop* loop);
	virtual ~Poller();

	/// Polls the I/O events.
	/// Must be called in the loop thread.
	virtual Timestamp poll(int timeoutMs, ChannelList* activeChannels) = 0;

	/// Changes the interested I/O events.
	/// Must be called in the loop thread.
	virtual void updateChannel(Channel* channel) = 0;

	/// Remove the channel, when it destructs.
	/// Must be called in the loop thread.
	virtual void removeChannel(Channel* channel) = 0;

	static Poller* newDefaultPoller(EventLoop* loop);

	void assertInLoopThread()
	{
		ownerLoop_->assertInLoopThread();
	}

private:
	EventLoop* ownerLoop_;	// Poller所属EventLoop
};

}
}
#endif  // XNET_NET_POLLER_H
