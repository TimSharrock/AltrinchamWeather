#include "pch.h"
#include "../WeatherLib/MetOfficeTimeSeries.h"
#include "../WeatherLib/DegreeDayCalculator.h"
#include "../WeatherLib/YearAndMonthBuckets.h"
#include "../WeatherLib/WeatherAlgorithms.h"

TEST(MetOfficeTimeSeriesTests, defaultConstructed)
{
	TjsWeather::MetOfficeTimeSeries series;
	EXPECT_EQ(0u,series.size());
}

class LittleTimeSeriesTest: public testing::Test
{
public:
	LittleTimeSeriesTest() :
		csvStream(std::string(
			"easting,12500,17500,22500\n"
			"northing,32500,37500,42500\n"
			"1960-01-01,   8.32,   8.30,   8.32\n"
		    "1960-01-02,   2.13,   2.08,   1.97\n")),
		csvStreamDifferentValues(std::string(
			"easting,12500,17500,22500\n"
			"northing,32500,37500,42500\n"
			"1960-01-01,   18.32,   18.30,   18.32\n"
		    "1960-01-02,   12.13,   12.08,   11.97\n")),
		csvStreamDifferentDates(std::string(
			"easting,12500,17500,22500\n"
			"northing,32500,37500,42500\n"
			"1961-01-01,   8.32,   8.30,   8.32\n"
		    "1961-01-02,   2.13,   2.08,   1.97\n"))

	{
	}
protected:
	std::istringstream csvStream;
	std::istringstream csvStreamDifferentValues;
	std::istringstream csvStreamDifferentDates;
};

TEST_F(LittleTimeSeriesTest, CanReadSomeValues)
{
    TjsWeather::MetOfficeTimeSeries series;
	series.load(csvStream,17400,37900);
	EXPECT_EQ(2u,series.size());
}

TEST_F(LittleTimeSeriesTest, CombiningThrowsIfLengthsAreDifferent)
{
    TjsWeather::MetOfficeTimeSeries seriesA;
	seriesA.load(csvStream,17400,37900);
    TjsWeather::MetOfficeTimeSeries seriesB;
	EXPECT_ANY_THROW(
		TjsWeather::MetOfficeTimeSeries combined(seriesA,seriesB,
			TjsWeather::DegreeDayCalculator(TjsWeather::DegreeDayCalculator::Direction::Above,5.5)));
}

TEST_F(LittleTimeSeriesTest, CombiningThrowsIfDatesAreDifferent)
{
    TjsWeather::MetOfficeTimeSeries seriesA;
	seriesA.load(csvStream,17400,37900);
    TjsWeather::MetOfficeTimeSeries seriesB;
	seriesB.load(csvStreamDifferentDates,17400,37900);
	EXPECT_ANY_THROW(
		TjsWeather::MetOfficeTimeSeries combined(seriesA,seriesB,
			TjsWeather::DegreeDayCalculator(TjsWeather::DegreeDayCalculator::Direction::Above,5.5)));
}

TEST_F(LittleTimeSeriesTest, CombiningProducesSameLengthAsInputAndPlausibleResults)
{
    TjsWeather::MetOfficeTimeSeries seriesA;
	seriesA.load(csvStream,17400,37900);
    TjsWeather::MetOfficeTimeSeries seriesB;
	seriesB.load(csvStreamDifferentValues,17400,37900);
	TjsWeather::DegreeDayCalculator calculator(TjsWeather::DegreeDayCalculator::Direction::Above,5.5);
	TjsWeather::MetOfficeTimeSeries combined(seriesA,seriesB,TjsWeather::GrowingDegreeDays);
	EXPECT_EQ(seriesA.size(),combined.size());
	EXPECT_EQ(seriesA.begin()->date(),combined.begin()->date());
	EXPECT_EQ(TjsWeather::GrowingDegreeDays(seriesA.begin()->value(),seriesB.begin()->value()),combined.begin()->value());
}

TEST_F(LittleTimeSeriesTest, CanAccumulateIntoMonthBuckets)
{
    TjsWeather::MetOfficeTimeSeries seriesA;
	seriesA.load(csvStream,17400,37900);
	TjsWeather::YearAndMonthBuckets buckets;
	TjsWeather::accumulate(buckets,seriesA);
	EXPECT_EQ(8.30+2.08,buckets.value(date::year(1960),date::January));
}