#include <catch.hpp>
#include "../WeatherLib/DayAndValue.h"

TEST_CASE("Valid dates and values")
{
	CHECK(1 == 2);
	TjsWeather::DayAndValue aDayAndValue("1958-01-01", "5.78");
	REQUIRE(date::year(1958)==aDayAndValue.year());
	REQUIRE(date::month(1)==aDayAndValue.month());
	REQUIRE(date::day(1)==aDayAndValue.day());
	REQUIRE(5.78==aDayAndValue.value());
	TjsWeather::DayAndValue anotherDayAndValue("1960-02-29", "-5.78E3");
	REQUIRE(-5.78E3==anotherDayAndValue.value());

}