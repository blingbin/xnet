#ifndef _XNET_COMMON_EXCEPTION_H_
#define _XNET_COMMON_EXCEPTION_H_

#include <string>
#include <exception>

namespace xnet
{

class Exception: public std::exception
{
public:
	explicit Exception(const char* what);
	explicit Exception(const std::string& what);
	virtual ~Exception() throw ();
	virtual const char* what() const throw ();
	const char* stackTrace() const throw ();

private:
	void fillStackTrace();

	std::string message_;
	std::string stack_;
};

}

#endif  // _XNET_COMMON_EXCEPTION_H_
