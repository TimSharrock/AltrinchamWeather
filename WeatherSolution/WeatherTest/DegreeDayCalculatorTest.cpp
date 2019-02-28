#include "pch.h"
#include "../WeatherLib/DegreeDayCalculator.h"

using namespace TjsWeather;

TEST(DegreeDayCalculatorTests, BothTemperaturesBelowThreshold)
{
	DegreeDayCalculator ddc(DegreeDayCalculator::Direction::Above,4.0);
	EXPECT_EQ(0.0,ddc(0.0,0.0));
}

TEST(DegreeDayCalculatorTests, BothTemperaturesAboveThreshold)
{
	DegreeDayCalculator ddc(DegreeDayCalculator::Direction::Above,4.0);
	EXPECT_EQ((6.0+7.0)*0.5 - 4.0,ddc(6.0,7.0));
}

TEST(DegreeDayCalculatorTests, MeanTemperatureAboveThreshold)
{
	DegreeDayCalculator ddc(DegreeDayCalculator::Direction::Above,4.0);
	EXPECT_EQ((7.0-4.0)*0.5 - (4.0-3.0)*0.25,ddc(3.0,7.0));
}

TEST(DegreeDayCalculatorTests, MeanTemperatureAboveThresholdReversedArgs)
{
	DegreeDayCalculator ddc(DegreeDayCalculator::Direction::Above,4.0);
	EXPECT_EQ((7.0-4.0)*0.5 - (4.0-3.0)*0.25,ddc(7.0,3.0));
}
TEST(DegreeDayCalculatorTests, MeanTemperatureBelowThreshold)
{
	DegreeDayCalculator ddc(DegreeDayCalculator::Direction::Above,6.0);
	EXPECT_EQ((7.0-6.0)*0.25,ddc(3.0,7.0));
}

TEST(DegreeDayCalculatorTests, BothTemperaturesBelowABelowThreshold)
{
	DegreeDayCalculator ddc(DegreeDayCalculator::Direction::Below,4.0);
	EXPECT_EQ(4.0-(0.0+2.0)*0.5,ddc(0.0,2.0));
}

TEST(DegreeDayCalculatorTests, BothTemperaturesAboveABelowThreshold)
{
	DegreeDayCalculator ddc(DegreeDayCalculator::Direction::Below,4.0);
	EXPECT_EQ(0.0,ddc(6.0,7.0));
}

TEST(DegreeDayCalculatorTests, MeanTemperatureAboveABelowThreshold)
{
	DegreeDayCalculator ddc(DegreeDayCalculator::Direction::Below,4.0);
	EXPECT_EQ((4.0-3.0)*0.25,ddc(3.0,7.0));
}

TEST(DegreeDayCalculatorTests, MeanTemperatureAboveABelowThresholdReversedArgs)
{
	DegreeDayCalculator ddc(DegreeDayCalculator::Direction::Below,4.0);
	EXPECT_EQ((4.0-3.0)*0.25,ddc(7.0,3.0));
}
TEST(DegreeDayCalculatorTests, MeanTemperatureBelowABelowThreshold)
{
	DegreeDayCalculator ddc(DegreeDayCalculator::Direction::Below,6.0);
	EXPECT_EQ((6.0-3.0)*0.5 - (7.0-6.0)*0.25,ddc(3.0,7.0));
}