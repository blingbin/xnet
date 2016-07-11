#include <sys/time.h>
#include <stdio.h>

#include <boost/static_assert.hpp>
#include "Timestamp.h"

using namespace xnet;

//static assert(assert at compile)
BOOST_STATIC_ASSERT(sizeof(Timestamp) == sizeof(int64_t));

Timestamp::Timestamp(int64_t microseconds) :
		microSecondsSinceEpoch_(microseconds)
{
}

std::string Timestamp::toString() const
{
	char buf[32] = { 0 };
	int64_t seconds = microSecondsSinceEpoch_ / kmicroSeconds_PerSecond;
	int64_t microseconds = microSecondsSinceEpoch_ % kmicroSeconds_PerSecond;
	snprintf(buf, sizeof(buf)-1, "%" PRId64 ".%06" PRId64 "", seconds, microseconds);
	return buf;   //pass by value
}

std::string Timestamp::toFormattedString() const
{
	char buf[32] = { 0 };
	time_t seconds = static_cast<time_t>(microSecondsSinceEpoch_ / kmicroSeconds_PerSecond);
	int microseconds = static_cast<int>(microSecondsSinceEpoch_ % kmicroSeconds_PerSecond);
	struct tm tm_time;
	gmtime_r(&seconds, &tm_time);

	snprintf(buf, sizeof(buf), "%4d%02d%02d %02d:%02d:%02d.%06d", tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday, tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec, microseconds);
	return buf;
}

Timestamp Timestamp::now()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	int64_t seconds = tv.tv_sec;
	return Timestamp(seconds * kmicroSeconds_PerSecond + tv.tv_usec);
}

Timestamp Timestamp::invalid()
{
	return Timestamp();
}

