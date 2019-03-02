#include "pch.h"
#include "YearAndMonthBuckets.h"



double TjsWeather::YearAndMonthBuckets::value(date::year const& aYear, date::month aMonth) const
{
	auto const yIndex = yearIndex(aYear);
	if((yIndex<0)||(yIndex>=myBuckets.size())){return 0.0;} // out of range - no value
	auto const mIndex = monthIndex(aMonth);
	if((mIndex<0)||(mIndex>=monthsPerYear)){return 0.0;} // out of range - no value
	return myBuckets[yIndex].values[mIndex];
}

double& TjsWeather::YearAndMonthBuckets::value(date::year const& aYear, date::month aMonth)
{
	if(myBuckets.empty()){myStartYear=aYear;}

	auto const  yIndex = yearIndex(aYear);
	if(yIndex<0){throw std::invalid_argument("year before start of YearAndMonthBuckets");}
	auto const mIndex = monthIndex(aMonth);
	if((mIndex<0)||(mIndex>=monthsPerYear)){throw std::invalid_argument("invalid month for  YearAndMonthBuckets");}
	while(myBuckets.size()<=yIndex)
    {
		date::year const nextYear{myStartYear+date::years(myBuckets.size())};
		myBuckets.emplace_back();
		myBuckets.back().year=nextYear;
    } 
	return myBuckets[yIndex].values[mIndex];
}


