#include <catch.hpp>
#include "../WeatherLib/HomeWeatherReadings.h"
#include <date/date.h>

TEST_CASE("C++ language version verification (for <optional>)")
{
   SECTION("_ MSC_VER macro")
   {
      REQUIRE(_MSC_VER >= 1920);
   }
   SECTION("__ cplusplus macro")
   {
      REQUIRE(__cplusplus >= 201700L);
   }
}

TEST_CASE("Can create and access HomeWeatherReadings")
{
   SECTION("Can default construct a HomeWeatherReadings")
   {
      HomeWeatherReadings readings{};
      CHECK_FALSE(readings.frontGardenSoilTemperature);
      CHECK_FALSE(readings.frontGardenTemperature);
      auto dayPoint = floor<date::days>(readings.timeStamp);
      auto ymd = date::year_month_day{ dayPoint };
      CHECK(ymd.year() == date::year(1970)); // unix Epoch???
   }
}