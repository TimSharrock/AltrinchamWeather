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
		double operator()(double aValue, double anotherValue) const;

	private:
		Direction myDirection;
		double myThreshold;
	};

	static DegreeDayCalculator GrowingDegreeDays={DegreeDayCalculator::Direction::Above,5.5};
	static DegreeDayCalculator HeatingDegreeDays={DegreeDayCalculator::Direction::Below,15.5};
	static DegreeDayCalculator CoolingDegreeDays={DegreeDayCalculator::Direction::Above,22};
	static DegreeDayCalculator FreezingDegreeDays={DegreeDayCalculator::Direction::Below,0};
}
