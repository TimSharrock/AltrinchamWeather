// WeatherStatisticsOne.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include "../WeatherLib/MetOfficeTimeSeries.h"


int main()
{
    std::cout << "Hello Weather World!\n";
	std::string timeSeriesFolder{"E:\\Tim\\Documents\\weather\\MetOffice\\TimeSeries"};
	std::string minimumTemperatureCsv{"\\minimum-temperature\\ukcp09_gridded-land-obs-daily_timeseries_minimum-temperature_350000E_350000N_19600101-20161231.csv"};

	std::ifstream minimumTemperatureStream{timeSeriesFolder+minimumTemperatureCsv};
    TjsWeather::MetOfficeTimeSeries minimumSeries;
	minimumSeries.load(minimumTemperatureStream,377020,387175);
    std::cout << "Minimum temperature records found: " << minimumSeries.size() << "\n\n";
	std::ofstream outputStream("E:\\Tim\\Documents\\weather\\statisticsOne.txt");
	minimumSeries.printStatistics(outputStream);
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
