#ifndef _XNET_COMMON_TIMESTAMP_H_
#define _XNET_COMMON_TIMESTAMP_H_

#include <boost/operators.hpp>
#include <string>

#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#undef __STDC_FORMAT_MACROS

namespace xnet
{

class Timestamp
{
public:

	Timestamp() :
			microSecondsSinceEpoch_(0)
	{
	}


	explicit Timestamp(int64_t microSeconds);


	void swap(Timestamp& that)
	{
		std::swap(microSecondsSinceEpoch_, that.microSecondsSinceEpoch_);
	}

	std::string toString() const;
	std::string toFormattedString() const;

	bool valid() const
	{
		return microSecondsSinceEpoch_ > 0;
	}

	int64_t microSeconds() const
	{
		return microSecondsSinceEpoch_;
	}
	int64_t microSecondsSinceEpoch() const { return microSecondsSinceEpoch_; }
	time_t secondsSinceEpoch() const   //microSecondsSinceEpoch
	{
		return static_cast<time_t>(microSecondsSinceEpoch_ / kmicroSeconds_PerSecond);
	}


	static Timestamp now();
	static Timestamp invalid();
	static const int kmicroSeconds_PerSecond = 1000 * 1000;

private:
	int64_t microSecondsSinceEpoch_;
};

inline bool operator<(Timestamp left, Timestamp right)
{
	return left.microSeconds() < right.microSeconds();
}

inline bool operator==(Timestamp left, Timestamp right)
{
	return left.microSeconds() == right.microSeconds();
}

inline double timeDifference(Timestamp high, Timestamp low)
{
	int64_t diff = high.microSeconds() - low.microSeconds();
	return static_cast<double>(diff) / Timestamp::kmicroSeconds_PerSecond;
}

inline Timestamp addTime(Timestamp timestamp, double seconds)
{
	int64_t delta = static_cast<int64_t>(seconds * Timestamp::kmicroSeconds_PerSecond);
	return Timestamp(timestamp.microSeconds() + delta);
}

}
#endif  // _XNET_COMMON_TIMESTAMP_H_
