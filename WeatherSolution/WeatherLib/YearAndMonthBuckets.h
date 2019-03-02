#pragma once
#include <array>
#include <vector>
#include <date/date.h>

namespace TjsWeather
{

	class YearAndMonthBuckets
	{
	public:
		YearAndMonthBuckets() = default;
		double value(date::year const& aYear, date::month aMonth) const;
		double& value(date::year const& aYear, date::month aMonth);

		auto yearCount() const { return myBuckets.size(); }
		auto firstYear() const { return myStartYear; }
		auto lastYear() const { return myStartYear + date::years(myBuckets.size()-1); }
	private:
		auto yearIndex(date::year aYear) const { return (aYear - myStartYear).count(); }
		static auto monthIndex(date::month aMonth) { return unsigned(aMonth) - 1; }

		date::year myStartYear = {};
		static unsigned constexpr monthsPerYear = 12;
		using MonthValuesT= std::array<double, monthsPerYear>;
		struct YearData
		{
			date::year year;
			MonthValuesT values;
		};
		std::vector<YearData> myBuckets;
	};

}
