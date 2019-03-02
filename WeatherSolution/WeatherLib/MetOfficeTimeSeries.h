#pragma once
#include <iosfwd>
#include "DayAndValue.h"
#include <vector>

namespace TjsWeather
{
	class MetOfficeTimeSeries
	{
	public:
		MetOfficeTimeSeries()=default;
		~MetOfficeTimeSeries()=default;
		MetOfficeTimeSeries(MetOfficeTimeSeries const&)=delete;
		MetOfficeTimeSeries& operator=(MetOfficeTimeSeries const&)=delete;
		MetOfficeTimeSeries(MetOfficeTimeSeries const&&)=delete;
		MetOfficeTimeSeries& operator=(MetOfficeTimeSeries const&&)=delete;

		template<typename Combiner>
		MetOfficeTimeSeries(MetOfficeTimeSeries const& seriesA, MetOfficeTimeSeries const& seriesB, Combiner combiner);


		std::vector<DayAndValue>::const_iterator begin() const;
		std::vector<DayAndValue>::const_iterator end() const;

		static bool coordinateIsIn5kmBlock(int coordinate, std::string const& blockCentreCoordinateAsString);

		void load(std::istream& stream, int easting, int northing);
		size_t size() const;

	private:
		std::vector<DayAndValue> myData;
	};

	template <typename Combiner>
	MetOfficeTimeSeries::MetOfficeTimeSeries(MetOfficeTimeSeries const& seriesA, MetOfficeTimeSeries const& seriesB,
		Combiner combiner)
	{
		if(seriesA.size()!=seriesB.size()){throw std::invalid_argument("non-matching series lengths");}
		myData.reserve(seriesA.size());
		auto aIterator=seriesA.begin();
		auto bIterator=seriesB.begin();
		while((aIterator!=seriesA.end()) && (bIterator!=seriesB.end()))
		{
			if(aIterator->date() != bIterator->date())
			{
				throw std::invalid_argument("Mismatched dates");
			}
			myData.emplace_back(aIterator->date(),combiner(aIterator->value(),bIterator->value()));
			++aIterator;
			++bIterator;
		}

	}
}
