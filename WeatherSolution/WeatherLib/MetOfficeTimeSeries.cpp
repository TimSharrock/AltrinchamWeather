#include "pch.h"
#include <cmath>
#include <sstream>
#include "MetOfficeTimeSeries.h"
#include "CsvReader.h"


bool TjsWeather::MetOfficeTimeSeries::coordinateIsIn5kmBlock(int const coordinate, std::string const& blockCentreCoordinateAsString)
{
	// assume numbers are in metres, on the block-boundary accept either
	std::istringstream stream(blockCentreCoordinateAsString);
	auto const halfBlockSize{2500};
	auto blockCentreCoordinate{coordinate+halfBlockSize*4};  // initial value too far away
	stream >> blockCentreCoordinate;
	return std::abs(coordinate - blockCentreCoordinate) <= halfBlockSize;
}

void TjsWeather::MetOfficeTimeSeries::load(std::istream& stream, int const easting, int const northing)
{
	CsvReader reader(stream);
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

size_t TjsWeather::MetOfficeTimeSeries::size() const
{
	return myData.size();
}

void TjsWeather::MetOfficeTimeSeries::printStatistics(std::ostream& stream)
{
	if(myData.empty()){return;}
	// boring fortran style

	size_t startIndex=0;
	size_t coldestInYearIndex=0;
	auto lastFrostIndex=myData.size()+1;
	auto firstFrostIndex=myData.size()+1;
	size_t frostCount=0;

	// print the header
	stream << "Year\t"
		   << "Coldest-T\tColdest-D\t"
		   << "Frosts\t"
		   << "Gap\t"
		   << "Last-T\tLast-D\tLast-O\t"
		   << "First-T\tFirst-D\tFirst-O\n";


	for(size_t i=0;i<=myData.size();++i)
	{
		if((i==myData.size()) || (myData[i].year()!=myData[startIndex].year()))
		{
			// a year finished, print and reset values
			stream << myData[startIndex].year() << "\t"
				   << myData[coldestInYearIndex].value() << "\t" << myData[coldestInYearIndex].date() << "\t"
				   << frostCount << "\t";
			if((lastFrostIndex<myData.size())&&(firstFrostIndex<myData.size()))
			{
				stream << (date::sys_days(myData[firstFrostIndex].date())-date::sys_days(myData[lastFrostIndex].date())).count() << "\t";
			}
			else
			{
				stream << "\t"; // gap not valid, i could do one-ended I suppose, but there are no examples here
			}

			if(lastFrostIndex<myData.size())
			{
				auto const lastFrost = myData[lastFrostIndex];
				auto const orderingDate = date::year(2104)/lastFrost.month()/lastFrost.day();
				stream << lastFrost.value() << "\t" << lastFrost.date() << "\t" << orderingDate << "\t";
			}
			else
			{
				stream << "\t\t\t";
			}
			if(firstFrostIndex<myData.size())
			{
				auto const firstFrost = myData[firstFrostIndex];
				auto const orderingDate = date::year(2104)/firstFrost.month()/firstFrost.day();
				stream << firstFrost.value() << "\t" << firstFrost.date()  << "\t" << orderingDate << "\n";
			}
			else
			{
				stream << "\t\t\n";
			}
			startIndex=i;
			coldestInYearIndex=i;
			lastFrostIndex=myData.size()+1;
			firstFrostIndex=myData.size()+1;
			frostCount=0;
		}
		if(i<myData.size())
		{
			auto const temperature=myData[i].value();
			if(myData[coldestInYearIndex].value()>temperature){coldestInYearIndex=i;}
			if(temperature<0.0)
			{
				++frostCount;
				if(myData[i].month()<date::July)
				{
					lastFrostIndex=i;
				}
				else
				{
					if(firstFrostIndex>myData.size()){firstFrostIndex=i;}
				}
			}
		}
	}
}
