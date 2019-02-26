#pragma once

#include <string>
#include "date/date.h"  // Howard Hinnant's http://howardhinnant.github.io/date/date.html 

namespace TjsWeather
{

	class DayAndValue
	{
	public:
		DayAndValue(std::string const& dateAsString, std::string const& valueAsString);
		date::year year() const;
		date::month month() const;
		date::day day() const;
		double value() const;
		date::year_month_day date() const;
	private:
		date::year_month_day myDate{};
		double myValue{};
	};

}
