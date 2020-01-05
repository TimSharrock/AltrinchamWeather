#pragma once
#include "YearAndMonthBuckets.h"
#include "DaySeries.h"

namespace TjsWeather
{
	void accumulate(YearAndMonthBuckets& buckets, DaySeries const& series);
	void accumulateCumulativeForYear(YearAndMonthBuckets& buckets, DaySeries const& series);
	void printBuckets(const YearAndMonthBuckets& yearAndMonthBuckets, std::string const& title, std::ostream& stream);


	template <typename Combiner>
	DaySeries combine(DaySeries const& seriesA, DaySeries const& seriesB,
		Combiner combiner)
	{
		if (seriesA.size() != seriesB.size()) { throw std::invalid_argument("non-matching series lengths"); }
		DaySeries result;
		result.reserve(seriesA.size());
		auto aIterator = seriesA.begin();
		auto bIterator = seriesB.begin();
		while ((aIterator != seriesA.end()) && (bIterator != seriesB.end()))
		{
			if (aIterator->date() != bIterator->date())
			{
				throw std::invalid_argument("Mismatched dates");
			}
			result.emplace_back(aIterator->date(), combiner(aIterator->value(), bIterator->value()));
			++aIterator;
			++bIterator;
		}
		return result;
	}
}


