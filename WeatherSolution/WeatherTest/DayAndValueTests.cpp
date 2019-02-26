#include "pch.h"
#include "../WeatherLib/DayAndValue.h"

TEST(DayAndValueTests,validDayAndValues)
{
   TjsWeather::DayAndValue aDayAndValue("1958-01-01","5.78");
   EXPECT_EQ(date::year(1958), aDayAndValue.year());
   EXPECT_EQ(date::month(1), aDayAndValue.month());
   EXPECT_EQ(date::day(1), aDayAndValue.day());
   EXPECT_EQ(5.78, aDayAndValue.value());
   TjsWeather::DayAndValue anotherDayAndValue("1960-02-29", "-5.78E3");
   EXPECT_EQ(-5.78E3, anotherDayAndValue.value());
}

TEST(DayAndValueTests, invalidDays)
{
	EXPECT_THROW(TjsWeather::DayAndValue aDayAndValue("1958-02-29", "5.78"), std::invalid_argument);
	EXPECT_THROW(TjsWeather::DayAndValue aDayAndValue("1958-22-29", "5.78"), std::invalid_argument);
	EXPECT_THROW(TjsWeather::DayAndValue aDayAndValue("bananas", "5.78"), std::invalid_argument);
}

TEST(DayAndValueTests, invalidvalues)
{
	EXPECT_THROW(TjsWeather::DayAndValue aDayAndValue("1958-01-01", "bananas"), std::invalid_argument);
	EXPECT_THROW(TjsWeather::DayAndValue aDayAndValue("1958-01-01", "3Elephants"), std::invalid_argument);
	EXPECT_THROW(TjsWeather::DayAndValue aDayAndValue("1958-01-01", "--1"), std::invalid_argument);
}

