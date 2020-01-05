#include <catch.hpp>

#pragma warning(push)
#pragma warning(disable:4251 4275 4996)
#include <yaml-cpp/yaml.h>
#pragma warning(pop)

TEST_CASE("yaml-cpp availability")
{
    SECTION("We can create a YAML node")
    {
        REQUIRE_NOTHROW(YAML::Node{});
    }
    
    SECTION("We can load a Sequence")
    {
        YAML::Node node = YAML::Load("[1, 2, 3]");
        CHECK(node.Type() == YAML::NodeType::Sequence);
        CHECK(node.IsSequence());  // a shortcut!
        REQUIRE(node.size()==3);
    }

    SECTION("We can navigate a multi-level map")
    {
        YAML::Node node = YAML::Load(
R"(# comment
# File and Geographic Locations for Altrincham
---
   Tag: Altrincham 
   Easting: 377000
   Northing: 387000
   OutputFolder: <XXXXX>\AltrinchamWeather\Run\Output
   MetOfficeFiles: 
      MaximumTemperature: <YYYYY>\TimeSeries\maximum-temperature\ukcp09_gridded-land-obs-daily_timeseries_maximum-temperature_350000E_350000N_19600101-20161231.csv
      MinimumTemperature: <YYYYY>\TimeSeries\minimum-temperature\ukcp09_gridded-land-obs-daily_timeseries_minimum-temperature_350000E_350000N_19600101-20161231.csv
      Rainfall: <YYYYY>\TimeSeries\rainfall\ukcp09_gridded-land-obs-daily_timeseries_rainfall_350000E_350000N_19580101-20161231.csv
   WeatherHubFolders:
      GreenHouseA: 
         Type: Thermometer
         Folder: <XXXXX>\AltrinchamWeather\HomeWeatherData\GreenHouseA
      BackGardenB:
         Type: Thermometer
         Folder: <XXXXX>\AltrinchamWeather\HomeWeatherData\BackGardenB
      FrontGardenC:
         Type: Thermometer
         Folder: <XXXXX>\AltrinchamWeather\HomeWeatherData\FrontGardenC
      VictoriaRoad:
         Type: WeatherStation
         Folder: <XXXXX>\AltrinchamWeather\HomeWeatherData\WeatherStation
...
)"
        );
        CHECK(node.Type() == YAML::NodeType::Map);
        CHECK(node.IsMap());  // a shortcut!
        CHECK(node.size() == 6);
        CHECK(node["Tag"].as<std::string>() == "Altrincham");
        CHECK(node["WeatherHubFolders"]["FrontGardenC"]["Type"].as<std::string>() == "Thermometer");
        CHECK_THROWS(node["WeatherHubFolders"]["XXXXX"]["Type"].as<std::string>());
        CHECK_FALSE(node["WeatherHubFolders"]["XXXXX"]["Type"]);
        CHECK_FALSE(node["WeatherHubFolders"]["XXXXX"]);
    }

}