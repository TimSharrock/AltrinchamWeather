#include "pch.h"
#include <cmath>
#include <sstream>
#include "DaySeries.h"
#include "XsvReader.h"
#include <immintrin.h>


std::vector<TjsWeather::DayAndValue>::const_iterator TjsWeather::DaySeries::begin() const
{
	return myData.cbegin();
}

std::vector<TjsWeather::DayAndValue>::const_iterator TjsWeather::DaySeries::end() const
{
	return myData.cend();
}

bool TjsWeather::DaySeries::coordinateIsIn5kmBlock(int const coordinate, std::string const& blockCentreCoordinateAsString)
{
	// assume numbers are in metres, on the block-boundary accept either
	std::istringstream stream(blockCentreCoordinateAsString);
	auto const halfBlockSize{2500};
	auto blockCentreCoordinate{coordinate+halfBlockSize*4};  // initial value too far away
	stream >> blockCentreCoordinate;
	return std::abs(coordinate - blockCentreCoordinate) <= halfBlockSize;
}

void TjsWeather::DaySeries::load(std::istream& stream, int const easting, int const northing)
{
	XsvReader reader(stream);
	// read the header, and find the appropriate column
	auto eastingLine = reader.readLine();
	if(eastingLine.size()<2u){throw std::invalid_argument("First line has too few fields (should start 'easting,')");}
	if(eastingLine[0]!="easting"){throw std::invalid_argument("Missing 'easting' line, found: "+eastingLine[0]);}
	auto northingLine = reader. readLine();
	if(northingLine.size()<2u){throw std::invalid_argument("First line has too few fields (should start 'northing,')");}
	if(northingLine[0]!="northing"){throw std::invalid_argument("Missing 'northing' line, found: "+northingLine[0]);}

	size_t localColumnIndex{0};
	for(size_t i=1; i<std::min(eastingLine.size(),northingLine.size());++i)
	{
		if(coordinateIsIn5kmBlock(easting,eastingLine[i])&&coordinateIsIn5kmBlock(northing,northingLine[i]))
		{
			localColumnIndex=i;
			break;
		}
	}

	if(localColumnIndex==0){throw std::invalid_argument("No matching grid-cell found");}

	while(stream)
	{
		auto dataLine=reader.readLine();
		if(dataLine.size()>localColumnIndex)
		{
			myData.emplace_back(dataLine[0],dataLine[localColumnIndex]);
		}
		else if(!dataLine.empty())
		{
			throw std::invalid_argument("Incomplete data line for: "+dataLine[0]);
		}
	}
}

size_t TjsWeather::DaySeries::size() const
{
	return myData.size();
}

