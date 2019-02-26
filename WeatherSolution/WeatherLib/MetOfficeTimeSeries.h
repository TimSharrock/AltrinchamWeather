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
		std::vector<DayAndValue>::const_iterator begin() const;
		std::vector<DayAndValue>::const_iterator end() const;
		MetOfficeTimeSeries(MetOfficeTimeSeries const&)=delete;
		MetOfficeTimeSeries& operator=(MetOfficeTimeSeries const&)=delete;
		MetOfficeTimeSeries(MetOfficeTimeSeries const&&)=delete;
		MetOfficeTimeSeries& operator=(MetOfficeTimeSeries const&&)=delete;

		static bool coordinateIsIn5kmBlock(int coordinate, std::string const& blockCentreCoordinateAsString);

		void load(std::istream& stream, int easting, int northing);
		size_t size() const;

	private:
		std::vector<DayAndValue> myData;
	};

}
