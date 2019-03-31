#include <catch.hpp>
#include "../WeatherLib/DayAndValue.h"
using namespace Catch::literals;

TEST_CASE("A DayAndValue accepts")
{
	SECTION("dates in 1958-01-30 format")
	{
		TjsWeather::DayAndValue aDayAndValue("1958-01-30", "5.78");
		CHECK(date::year(1958) == aDayAndValue.year());
		CHECK(date::month(1) == aDayAndValue.month());
		REQUIRE(date::day(30) == aDayAndValue.day());
	}

	SECTION("real values")
	{
		TjsWeather::DayAndValue aDayAndValue("1958-01-30", "5.78");
		REQUIRE(5.78_a == aDayAndValue.value());
	}

	SECTION("real values using exponents")
	{
		TjsWeather::DayAndValue anotherDayAndValue("1960-02-29", "-5.78E3");
		REQUIRE(-5.78E3_a == anotherDayAndValue.value());
	}
}

TEST_CASE("A DayAndValue rejects")
{
	SECTION("invalid dates")
	{
		SECTION("with an invalid day")
		{
			REQUIRE_THROWS(TjsWeather::DayAndValue("1958-02-29", "5.78"));
		}
		SECTION("with an invalid month")
		{
			REQUIRE_THROWS(TjsWeather::DayAndValue("1958-22-29", "5.78"));
		}
		SECTION("with an invalid year")
		{
			REQUIRE_THROWS(TjsWeather::DayAndValue("bananas", "5.78"));
		}
	}

	SECTION("values that are not numbers")
	{
		CHECK_THROWS(TjsWeather::DayAndValue("1958-01-01", "bananas"));
		CHECK_THROWS(TjsWeather::DayAndValue("1958-01-01", "3Elephants"));
		REQUIRE_THROWS(TjsWeather::DayAndValue("1958-01-01", "--1"));
	}
}
