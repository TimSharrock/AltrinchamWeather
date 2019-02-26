#include "pch.h"
#include "../WeatherLib/MetOfficeTimeSeries.h"

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
		    "1960-01-02,   2.13,   2.08,   1.97\n"))
	{
	}
protected:
	std::istringstream csvStream;
};

TEST_F(LittleTimeSeriesTest, CanReadSomeValues)
{
    TjsWeather::MetOfficeTimeSeries series;
	series.load(csvStream,17400,37900);
	EXPECT_EQ(2u,series.size());
}
