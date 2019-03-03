#include "pch.h"
#include "WeatherAlgorithms.h"

void TjsWeather::accumulate(YearAndMonthBuckets& buckets, MetOfficeTimeSeries const& series)
{
	for (auto iter = series.begin(); iter != series.end(); ++iter)
	{
		buckets.value(iter->year(), iter->month()) += iter->value();
	}
}

void TjsWeather::accumulateCumulativeForYear(YearAndMonthBuckets& buckets, MetOfficeTimeSeries const& series)
{
	for (auto iter = series.begin(); iter != series.end(); ++iter)
	{
		auto month = iter->month();
		do
		{
			buckets.value(iter->year(), month) += iter->value();
			++month;
		}
		while(month != date::January);  // ie month has wrapped round....
	}
}


void TjsWeather::printBuckets(const YearAndMonthBuckets& yearAndMonthBuckets, std::string const& title, std::ostream& stream)
{
	stream << "# " << title;
	for (auto monthNumber = 1u; monthNumber <= 12u; ++monthNumber)
	{
		stream << "\t" << date::month(monthNumber);
	}
	stream << "\n";
	for (auto year = yearAndMonthBuckets.firstYear(); year <= yearAndMonthBuckets.lastYear(); ++year)
	{
		stream << year;
		for (auto monthNumber = 1u; monthNumber <= 12u; ++monthNumber)
		{
			stream << "\t" << yearAndMonthBuckets.value(year, date::month(monthNumber));
		}
		stream << "\n";
	}
}
