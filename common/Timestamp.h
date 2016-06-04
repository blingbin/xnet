#ifndef _XNET_COMMON_TIMESTAMP_H_
#define _XNET_COMMON_TIMESTAMP_H_

#include <boost/operators.hpp>
#include <string>

#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#undef __STDC_FORMAT_MACROS

namespace xnet
{

// Time notes in UTC, in micro Seconds

// This class is immutable.
// It's recommended to pass it by value, since it's passed in register on x64.

class Timestamp
{
public:

	// Constucts an invalid Timestamp.
	Timestamp() :
			microSeconds_(0)
	{
	}

	///
	/// Constucts a Timestamp at specific time
	///
	/// @param micro Seconds Since 1970-01-01 00:00:00
	explicit Timestamp(int64_t microSeconds);

	void swap(Timestamp& that)
	{
		std::swap(microSeconds_, that.microSeconds_);
	}


	std::string toString() const;
	std::string toFormattedString() const;

	bool valid() const
	{
		return microSeconds_ > 0;
	}

	// for internal usage.
	int64_t microSeconds() const
	{
		return microSeconds_;
	}
	time_t secondsSinceEpoch() const
	{
		return static_cast<time_t>(microSeconds_ / kmicroSeconds_PerSecond);
	}


	// Get time of now.
	static Timestamp now();
	static Timestamp invalid();
	static const int kmicroSeconds_PerSecond = 1000 * 1000;

private:
	int64_t microSeconds_;
};

inline bool operator<(Timestamp left, Timestamp right)
{
	return left.microSeconds() < right.microSeconds();
}

inline bool operator==(Timestamp left, Timestamp right)
{
	return left.microSeconds() == right.microSeconds();
}


// Gets time slot between two Timestamp, result in seconds.
// @param high, low
// @return (high-low) in seconds
inline double timeDifference(Timestamp high, Timestamp low)
{
	int64_t diff = high.microSeconds() - low.microSeconds();
	return static_cast<double>(diff) / Timestamp::kmicroSeconds_PerSecond;
}

///
/// Add @c seconds to given Timestamp.
///
/// @return Timestamp+seconds as Timestamp
///
inline Timestamp addTime(Timestamp timestamp, double seconds)
{
	int64_t delta = static_cast<int64_t>(seconds * Timestamp::kmicroSeconds_PerSecond);
	return Timestamp(timestamp.microSeconds() + delta);
}

}
#endif  // _XNET_COMMON_TIMESTAMP_H_
