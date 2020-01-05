#include "pch.h"
#include <cmath>
#include <sstream>
#include "DaySeries.h"
#include "XsvReader.h"
#include <immintrin.h>


void TjsWeather::DaySeries::reserve(size_t size)
{
	myData.reserve(size);
}

std::vector<TjsWeather::DayAndValue>::const_iterator TjsWeather::DaySeries::begin() const
{
	return myData.cbegin();
}

std::vector<TjsWeather::DayAndValue>::const_iterator TjsWeather::DaySeries::end() const
{
	return myData.cend();
}


size_t TjsWeather::DaySeries::size() const
{
	return myData.size();
}

