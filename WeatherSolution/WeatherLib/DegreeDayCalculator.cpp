#include "pch.h"
#include "DegreeDayCalculator.h"
#include <algorithm>

double TjsWeather::DegreeDayCalculator::operator()(double aValue, double anotherValue) const
{
	auto const maxValue{std::max(aValue,anotherValue)};
	auto const minValue{std::min(aValue,anotherValue)};
	auto const meanValue{(aValue+anotherValue)*0.5};

	if(myDirection==Direction::Above)
	{
		if(maxValue<=myThreshold){return 0.0;}
		if(minValue>=myThreshold){return meanValue-myThreshold;}
		if(meanValue>=myThreshold){return 0.5*(maxValue-myThreshold)-0.25*(myThreshold-minValue);}
		return 0.25*(maxValue-myThreshold);
	}
    // else Below...
	if(minValue>=myThreshold){return 0.0;}
	if(maxValue<=myThreshold){return myThreshold-meanValue;}
	if(meanValue<=myThreshold){return 0.5*(myThreshold-minValue)-0.25*(maxValue-myThreshold);}
	return 0.25*(myThreshold-minValue);

}
