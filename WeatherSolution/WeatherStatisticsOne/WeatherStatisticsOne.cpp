// WeatherStatisticsOne.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include "../WeatherLib/MetOfficeTimeSeries.h"
#include "../WeatherLib/FrostStatistics.h"
#include "../WeatherLib/DegreeDayCalculator.h"
#include "../WeatherLib/YearAndMonthBuckets.h"
#include "../WeatherLib/WeatherAlgorithms.h"


int main()
{
    std::cout << "Hello Weather World!\n";

	try
	{
	std::string timeSeriesFolder{"E:\\Tim\\Documents\\weather\\MetOffice\\TimeSeries"};
	std::string minimumTemperatureCsv{"\\minimum-temperature\\ukcp09_gridded-land-obs-daily_timeseries_minimum-temperature_350000E_350000N_19600101-20161231.csv"};

	std::ifstream minimumTemperatureStream{timeSeriesFolder+minimumTemperatureCsv};
    TjsWeather::MetOfficeTimeSeries minimumSeries;
	minimumSeries.load(minimumTemperatureStream,377020,387175);
    std::cout << "Minimum temperature records found: " << minimumSeries.size() << "\n";

	std::ofstream outputStream("E:\\Tim\\Documents\\weather\\statisticsOne.txt");
	TjsWeather::printFrostStatistics(minimumSeries.begin(),minimumSeries.end(), outputStream);
	std::cout << "Frost Statistics Processed.\n\n";

	std::string maximumTemperatureCsv{"\\maximum-temperature\\ukcp09_gridded-land-obs-daily_timeseries_maximum-temperature_350000E_350000N_19600101-20161231.csv"};
	std::ifstream maximumTemperatureStream{timeSeriesFolder+maximumTemperatureCsv};
    TjsWeather::MetOfficeTimeSeries maximumSeries;
	maximumSeries.load(maximumTemperatureStream,377020,387175);
    std::cout << "Maximum temperature records found: " << maximumSeries.size() << "\n";

    TjsWeather::MetOfficeTimeSeries growingDegreeDaysSeries(minimumSeries,maximumSeries,TjsWeather::GrowingDegreeDays);
	TjsWeather::YearAndMonthBuckets growingDegreeDaysByMonth;
	TjsWeather::accumulate(growingDegreeDaysByMonth,growingDegreeDaysSeries);	
	std::ofstream degreeDaysByMonthOutputStream("E:\\Tim\\Documents\\weather\\degreeDaysByMonth.txt");
	TjsWeather::printBuckets(growingDegreeDaysByMonth,"Year", degreeDaysByMonthOutputStream);

	TjsWeather::YearAndMonthBuckets cumulativeGrowingDegreeDaysByMonth;
	TjsWeather::accumulateCumulativeForYear(cumulativeGrowingDegreeDaysByMonth,growingDegreeDaysSeries);	
	std::ofstream cumulativeDegreeDaysByMonthOutputStream("E:\\Tim\\Documents\\weather\\cumulativeDegreeDaysByMonth.txt");
	TjsWeather::printBuckets(cumulativeGrowingDegreeDaysByMonth,"Year", cumulativeDegreeDaysByMonthOutputStream);
    std::cout << "Growing Degree Days Processed: " << growingDegreeDaysSeries.size() << "\n\n";

	std::string rainfallCsv{"\\rainfall\\ukcp09_gridded-land-obs-daily_timeseries_rainfall_350000E_350000N_19580101-20161231.csv"};
	std::string rainfallPath{timeSeriesFolder+rainfallCsv};
	std::ifstream rainfallStream{rainfallPath};
    TjsWeather::MetOfficeTimeSeries rainfallSeries;
	rainfallSeries.load(rainfallStream,377020,387175);
    std::cout << "Rainfall temperature records found: " << rainfallSeries.size() << "\n";

	TjsWeather::YearAndMonthBuckets rainfallByMonth;
	TjsWeather::accumulate(rainfallByMonth,rainfallSeries);	
	std::ofstream rainfallByMonthOutputStream("E:\\Tim\\Documents\\weather\\rainfallByMonth.txt");
	TjsWeather::printBuckets(rainfallByMonth,"Year", rainfallByMonthOutputStream);
    std::cout << "rainfall Processed:\n\n";
	}
	catch(std::exception e)
	{
		std::cout << "### Exception caught: " << e.what() << "\n";
	}

    std::cout << "Farewell Weather World!\n";

 }

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
