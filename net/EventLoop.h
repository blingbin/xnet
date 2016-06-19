

#ifndef XNET_NET_EVENTLOOP_H
#define XNET_NET_EVENTLOOP_H

#include <vector>

#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>

#include "CurrentThread.h"
#include "Thread.h"
#include "Timestamp.h"

namespace xnet
{
namespace net
{

class Channel;
class Poller;
///
/// Reactor, at most one per thread.
///
/// This is an interface class, so don't expose too much details.
class EventLoop : boost::noncopyable
{
 public:
  EventLoop();
  ~EventLoop();  // force out-line dtor, for scoped_ptr members.

  ///
  /// Loops forever.
  ///
  /// Must be called in the same thread as creation of the object.
  ///
  void loop();

  void quit();

  ///
  /// Time when poll returns, usually means data arrivial.
  ///
  Timestamp pollReturnTime() const { return pollReturnTime_; }

  // internal usage
  void updateChannel(Channel* channel);		// 在Poller中添加或者更新通道
  void removeChannel(Channel* channel);		// 从Poller中移除通道

  void assertInLoopThread()
  {
    if (!isInLoopThread())
    {
      abortNotInLoopThread();
    }
  }
  bool isInLoopThread() const { return threadId_ == CurrentThread::tid(); }

  static EventLoop* getEventLoopOfCurrentThread();

 private:
  void abortNotInLoopThread();

  void printActiveChannels() const; // DEBUG

  typedef std::vector<Channel*> ChannelList;
  
  bool looping_; /* atomic */
  bool quit_; /* atomic */
  bool eventHandling_; /* atomic */
  const pid_t threadId_;		// 当前对象所属线程ID
  Timestamp pollReturnTime_;
  boost::scoped_ptr<Poller> poller_;
  ChannelList activeChannels_;		// Poller返回的活动通道
  Channel* currentActiveChannel_;	// 当前正在处理的活动通道
};

}
}
#endif  // XNET_NET_EVENTLOOP_H
