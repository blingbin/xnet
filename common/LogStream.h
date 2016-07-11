#ifndef _XNET_COMMON_LOGSTREAM_H_
#define _XNET_COMMON_LOGSTREAM_H_

#include "StringPiece.h"

#include <assert.h>
#include <string.h> // memcpy
#include <string>

#include <boost/noncopyable.hpp>
#include<boost/implicit_cast.hpp>

namespace xnet
{

namespace detail
{

const int kSmallBuffer = 4000;
const int kLargeBuffer = 4000 * 1000;

template<int SIZE>
class FixedBuffer: boost::noncopyable
{
public:
	FixedBuffer() :
					cur_(data_)
	{
		setCookie(cookieStart);
	}

	~FixedBuffer()
	{
		setCookie(cookieEnd);
	}

	void append(const char* /*restrict*/buf, size_t len)
	{
		if (boost::implicit_cast<size_t>(avail()) > len)
		{
			memcpy(cur_, buf, len);
			cur_ += len;
		}
	}

	const char* data() const
	{
		return data_;
	}
	int length() const
	{
		return static_cast<int>(cur_ - data_);
	}

	// write to data_ directly
	char* current()
	{
		return cur_;
	}
	int avail() const
	{
		return static_cast<int>(end() - cur_);
	}
	void add(size_t len)
	{
		cur_ += len;
	}

	void reset()
	{
		cur_ = data_;
	}
	void bzero()
	{
		::bzero(data_, sizeof data_);
	}

	// for used by GDB
	const char* debugString();
	void setCookie(void (*cookie)())
	{
		cookie_ = cookie;
	}
	// for used by unit test
	std::string asString() const
	{
		return std::string(data_, length());
	}

private:
	const char* end() const
	{
		return data_ + sizeof data_;
	}
	// Must be outline function for cookies.
	static void cookieStart();
	static void cookieEnd();

	void (*cookie_)();
	char data_[SIZE];
	char* cur_;
};

}

class LogStream: boost::noncopyable
{
public:
	typedef detail::FixedBuffer<detail::kSmallBuffer> Buffer;

	LogStream& operator<<(bool v)
	{
		buffer_.append(v ? "1" : "0", 1);
		return *this;
	}

	LogStream& operator<<(short);
	LogStream& operator<<(unsigned short);
	LogStream& operator<<(int);
	LogStream& operator<<(unsigned int);
	LogStream& operator<<(long);
	LogStream& operator<<(unsigned long);
	LogStream& operator<<(long long);
	LogStream& operator<<(unsigned long long);

	LogStream& operator<<(const void*);

	LogStream& operator<<(float v)
	{
		*this << static_cast<double>(v);
		return *this;
	}
	LogStream& operator<<(double);

	LogStream& operator<<(char v)
	{
		buffer_.append(&v, 1);
		return *this;
	}

	// LogStream& operator<<(signed char);
	// LogStream& operator<<(unsigned char);

	LogStream& operator<<(const char* v)
	{
		buffer_.append(v, strlen(v));
		return *this;
	}

	LogStream& operator<<(const std::string& v)
	{
		buffer_.append(v.c_str(), v.size());
		return *this;
	}

	LogStream& operator<<(const StringPiece& v)
	{
		buffer_.append(v.data(), v.size());
		return *this;
	}

	void append(const char* data, int len)
	{
		buffer_.append(data, len);
	}
	const Buffer& buffer() const
	{
		return buffer_;
	}
	void resetBuffer()
	{
		buffer_.reset();
	}

private:
	void staticCheck();

	template<typename T>
	void formatInteger(T);

	Buffer buffer_;

	static const int kMaxNumericSize = 32;
};

class Fmt // : boost::noncopyable
{
public:
	template<typename T>
	Fmt(const char* fmt, T val);

	const char* data() const
	{
		return buf_;
	}
	int length() const
	{
		return length_;
	}

private:
	char buf_[32];
	int length_;
};

inline LogStream& operator<<(LogStream& s, const Fmt& fmt)
{
	s.append(fmt.data(), fmt.length());
	return s;
}

}
#endif  // _XNET_COMMON_LOGSTREAM_H_

