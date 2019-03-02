#include "pch.h"
#include "date/date.h"
#include "../WeatherLib/YearAndMonthBuckets.h"

TEST(YearAndMonthBucketsTest, DefaultConstructedIsOk)
{
	TjsWeather::YearAndMonthBuckets const buckets;
	EXPECT_EQ(0, buckets.yearCount());
	EXPECT_EQ(0,buckets.value(date::year(1666), date::January));
	EXPECT_EQ(date::year(0), buckets.firstYear());
}

TEST(YearAndMonthBucketsTest, CanAddData)
{
	TjsWeather::YearAndMonthBuckets buckets;
	buckets.value(date::year(1666), date::January)=666;
	EXPECT_EQ(666,buckets.value(date::year(1666), date::January));
	EXPECT_ANY_THROW(buckets.value(date::year(1665), date::January)=665);
	buckets.value(date::year(1668), date::December)=668;
	EXPECT_EQ(666,buckets.value(date::year(1666), date::January));
	EXPECT_EQ(0,buckets.value(date::year(1667), date::August));
	EXPECT_EQ(668,buckets.value(date::year(1668), date::December));
	EXPECT_EQ(date::year(1666), buckets.firstYear());
	EXPECT_EQ(date::year(1668), buckets.lastYear());
}