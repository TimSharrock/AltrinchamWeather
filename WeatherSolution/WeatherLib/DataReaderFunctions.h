#pragma once
#include "DaySeries.h"

namespace TjsWeather
{
   bool coordinateIsIn5kmBlock(int const coordinate, std::string const& blockCentreCoordinateAsString);
   DaySeries loadFromMetOfficeGriddedData(std::istream& stream, int const easting, int const northing);
}

