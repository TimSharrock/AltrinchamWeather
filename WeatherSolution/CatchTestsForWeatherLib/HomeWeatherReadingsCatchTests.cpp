#include <catch.hpp>
#include "../WeatherLib/HomeWeatherReadings.h"
#include <date/date.h>
using namespace date::literals;

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
      CHECK(ymd.year() == 1970_y); // unix Epoch???
      auto time = date::make_time(readings.timeStamp - dayPoint);
      CHECK(time.hours().count() == 0);
   }

   //Timestamp; Temperature; Temperature Probe
   //07.04.2018 15:14:21; 22.1; 22.9
}