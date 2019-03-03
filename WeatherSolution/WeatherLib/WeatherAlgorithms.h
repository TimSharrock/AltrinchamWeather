#pragma once
#include "YearAndMonthBuckets.h"
#include "MetOfficeTimeSeries.h"

namespace TjsWeather
{
	void accumulate(YearAndMonthBuckets& buckets, MetOfficeTimeSeries const& series);
	void accumulateCumulativeForYear(YearAndMonthBuckets& buckets, MetOfficeTimeSeries const& series);
	void printBuckets(const YearAndMonthBuckets& yearAndMonthBuckets, std::string const& title, std::ostream& stream);
}

