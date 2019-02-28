#pragma once

namespace TjsWeather
{
	class DegreeDayCalculator
	{
	public:
		enum class Direction{Above,Below};
		DegreeDayCalculator(Direction direction, double threshold) 
		: myDirection(direction),myThreshold(threshold)
		{}
		double operator()(double aValue, double anotherValue);
	private:
		Direction myDirection;
		double myThreshold;
	};
}
