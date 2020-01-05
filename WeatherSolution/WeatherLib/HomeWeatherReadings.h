#pragma once
#include <optional>
#include <chrono>

struct HomeWeatherReadings
{
   std::chrono::system_clock::time_point timeStamp;
   std::optional<double> frontGardenTemperature;
   std::optional<double> frontGardenSoilTemperature;
};

