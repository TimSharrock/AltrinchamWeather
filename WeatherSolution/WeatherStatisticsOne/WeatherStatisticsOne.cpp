// WeatherStatisticsOne.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>

#pragma warning(push)
#pragma warning(disable:4251 4275 4996)
#include <yaml-cpp/yaml.h>
#pragma warning(pop)

#include "../WeatherLib/MetOfficeTimeSeries.h"
#include "../WeatherLib/FrostStatistics.h"
#include "../WeatherLib/DegreeDayCalculator.h"
#include "../WeatherLib/YearAndMonthBuckets.h"
#include "../WeatherLib/WeatherAlgorithms.h"

template<typename T>
T getConfigValue(const YAML::Node& node, const char* key)
{
   if(node[key])
   {
      return node[key].as<T>();
   }
   std::cerr << "No configuration value for " << key << " found\n";
   exit(1);
}

int main(int argc, char *argv[])
{
   std::cout << "Hello Weather World!\n";
   if(argc!=2)
   {
      std::cerr << "One argument expected: a yaml configuration file\n";
      exit(1);
   }

   try
   {
      std::string configurationYamlFileName{ argv[1] };
      std::cout << "Loading configuration file: " << configurationYamlFileName << std::endl;
      YAML::Node configurationNode = YAML::LoadFile(configurationYamlFileName);

      auto locationTag{ getConfigValue<YAML::Node>(configurationNode,"Tag") };
      auto easting{ getConfigValue<int>(configurationNode,"Easting") };
      auto northing{ getConfigValue<int>(configurationNode,"Northing") };
      std::cout << "Location: " << locationTag << " (E" << easting << " N" << northing << ")\n";
      auto outputFolder{ getConfigValue<std::string>(configurationNode,"OutputFolder") };

      auto metOfficeNode{ getConfigValue<YAML::Node>(configurationNode,"MetOfficeFiles") };
      auto minimumTemperatureCsvPath{ getConfigValue<std::string>(metOfficeNode,"MinimumTemperature") };
      auto maximumTemperatureCsvPath{ getConfigValue<std::string>(metOfficeNode,"MaximumTemperature") };
      auto rainfallCsvPath{ getConfigValue<std::string>(metOfficeNode,"Rainfall") };

      std::ifstream minimumTemperatureStream{minimumTemperatureCsvPath };
      TjsWeather::MetOfficeTimeSeries minimumSeries;
      minimumSeries.load(minimumTemperatureStream, easting, northing);
      std::cout << "Minimum temperature records found: " << minimumSeries.size() << "\n";

      std::ofstream outputStream(outputFolder + "\\statisticsOne.txt");
      TjsWeather::printFrostStatistics(minimumSeries.begin(), minimumSeries.end(), outputStream);
      std::cout << "Frost Statistics Processed.\n\n";

      std::ifstream maximumTemperatureStream{ maximumTemperatureCsvPath };
      TjsWeather::MetOfficeTimeSeries maximumSeries;
      maximumSeries.load(maximumTemperatureStream, easting, northing);
      std::cout << "Maximum temperature records found: " << maximumSeries.size() << "\n";

      TjsWeather::MetOfficeTimeSeries growingDegreeDaysSeries(minimumSeries, maximumSeries, TjsWeather::GrowingDegreeDays);
      TjsWeather::YearAndMonthBuckets growingDegreeDaysByMonth;
      TjsWeather::accumulate(growingDegreeDaysByMonth, growingDegreeDaysSeries);
      std::ofstream degreeDaysByMonthOutputStream(outputFolder + "\\degreeDaysByMonth.txt");
      TjsWeather::printBuckets(growingDegreeDaysByMonth, "Year", degreeDaysByMonthOutputStream);

      TjsWeather::YearAndMonthBuckets cumulativeGrowingDegreeDaysByMonth;
      TjsWeather::accumulateCumulativeForYear(cumulativeGrowingDegreeDaysByMonth, growingDegreeDaysSeries);
      std::ofstream cumulativeDegreeDaysByMonthOutputStream(outputFolder + "\\cumulativeDegreeDaysByMonth.txt");
      TjsWeather::printBuckets(cumulativeGrowingDegreeDaysByMonth, "Year", cumulativeDegreeDaysByMonthOutputStream);
      std::cout << "Growing Degree Days Processed: " << growingDegreeDaysSeries.size() << "\n\n";

      std::ifstream rainfallStream{ rainfallCsvPath };
      TjsWeather::MetOfficeTimeSeries rainfallSeries;
      rainfallSeries.load(rainfallStream, easting, northing);
      std::cout << "Rainfall temperature records found: " << rainfallSeries.size() << "\n";

      TjsWeather::YearAndMonthBuckets rainfallByMonth;
      TjsWeather::accumulate(rainfallByMonth, rainfallSeries);
      std::ofstream rainfallByMonthOutputStream{ outputFolder + "\\rainfallByMonth.txt" };
      TjsWeather::printBuckets(rainfallByMonth, "Year", rainfallByMonthOutputStream);
      std::cout << "rainfall Processed:\n\n";
   }
   catch (std::exception const& e)
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
