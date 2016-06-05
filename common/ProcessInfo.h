
#ifndef _XNET_COMMON_PROCESSINFO_H_
#define _XNET_COMMON_PROCESSINFO_H_


#include "Timestamp.h"
#include <vector>

namespace xnet
{

namespace ProcessInfo
{
  pid_t pid();
  std::string pidString();
  uid_t uid();
  std::string username();
  uid_t euid();
  Timestamp startTime();

  std::string hostname();

  /// read /proc/self/status
  std::string procStatus();

  int openedFiles();
  int maxOpenFiles();

  int numThreads();
  std::vector<pid_t> threads();
}

}

#endif  // _XNET_COMMON_PROCESSINFO_H_
