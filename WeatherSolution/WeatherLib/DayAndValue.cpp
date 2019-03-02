#include "pch.h"
#include "DayAndValue.h"
#include <sstream>


TjsWeather::DayAndValue::DayAndValue(date::year_month_day const& aDate, double aValue)
	:myDate(aDate),myValue(aValue)
{
}

TjsWeather::DayAndValue::DayAndValue(std::string const& dateAsString, std::string const& valueAsString)
{
	std::istringstream dateStream(dateAsString);
	int year, month, day;
	char separator1, separator2;
	dateStream >> year >> separator1 >> month >> separator2 >> day;
	myDate = date::year_month_day(date::year(year), date::month(month), date::day(day));
	if (!myDate.ok()) { throw std::invalid_argument("Invalid date string: " + dateAsString); }

	std::istringstream valueStream(valueAsString);
	valueStream >> myValue;
	if(!valueStream) { throw std::invalid_argument("Invalid value string: " + valueAsString); }
}

date::year TjsWeather::DayAndValue::year() const
{
	return myDate.year();
}

date::month TjsWeather::DayAndValue::month() const
{
	return myDate.month();
}

date::day TjsWeather::DayAndValue::day() const
{
	return myDate.day();
}

double TjsWeather::DayAndValue::value() const
{
	return myValue;
}

date::year_month_day TjsWeather::DayAndValue::date() const
{
	return myDate;
}


