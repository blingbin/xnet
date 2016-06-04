// Use of this source code is governed by a BSD-style license
// that can be found in the License file.


#ifndef _XNET_COMMON_COUNTDOWNLATCH_H_
#define _XNET_COMMON_COUNTDOWNLATCH_H_

#include "Condition.h"
#include "Mutex.h"

#include <boost/noncopyable.hpp>

namespace xnet
{

class CountDownLatch : boost::noncopyable
{
 public:

  explicit CountDownLatch(int count);

  void wait();

  void countDown();

  int getCount() const;

 private:
  mutable MutexLock mutex_;
  Condition condition_;
  int count_;
};

}
#endif  // _XNET_COMMON_COUNTDOWNLATCH_H_
