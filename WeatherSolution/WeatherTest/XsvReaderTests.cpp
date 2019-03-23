#include "pch.h"
#include "../WeatherLib/XsvReader.h"


class LittleXsvStreamTest: public testing::Test
{
public:
	LittleXsvStreamTest() :
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

TEST_F(LittleXsvStreamTest, CanBeConstructedFromAStream)
{
	TjsWeather::XsvReader aReader(csvStream);
	EXPECT_TRUE(true);
}

TEST_F(LittleXsvStreamTest, CanReadSomeValues)
{
	TjsWeather::XsvReader aReader(csvStream);
	auto someFields = aReader.readLine();
	EXPECT_GT(someFields.size(), 0u);
	EXPECT_EQ(someFields[0], std::string("easting"));
	EXPECT_EQ(someFields[1], std::string("12500"));
	aReader.readLine();
	auto someMoreFields = aReader.readLine();
	EXPECT_EQ(someMoreFields[0], std::string("1960-01-01"));
	EXPECT_EQ(someMoreFields[1], std::string("8.32"));
}

TEST(XsvStreamLimitationsTest, simpleFields)
{
	std::istringstream aStream(std::string(" ignores spaces\t, no \",\" quote handling,\n"));
    TjsWeather::XsvReader aReader(aStream);
	auto const someFields = aReader.readLine();
	EXPECT_EQ(someFields.size(), 4u);
	EXPECT_EQ(someFields[0], std::string("ignoresspaces"));
	EXPECT_EQ(someFields[1], std::string("no\""));
	EXPECT_EQ(someFields[2], std::string("\"quotehandling"));
	EXPECT_EQ(someFields[3], std::string());
}

TEST(XsvStreamLimitationsTest, missingFinalNewLine)
{
	std::istringstream aStream(std::string("missing,new,line,"));
	TjsWeather::XsvReader aReader(aStream);
	auto const someFields = aReader.readLine();
	EXPECT_EQ(someFields.size(), 4u); // treated as if new line is there
	EXPECT_EQ(someFields[2], std::string("line"));
	EXPECT_EQ(someFields[3], std::string());
}

TEST(XsvStreamLimitationsTest, unfinishedWhitespaceOnly)
{
	std::istringstream aStream(std::string(" \t"));
	TjsWeather::XsvReader aReader(aStream);
	auto const someFields = aReader.readLine();
	EXPECT_EQ(someFields.size(), 0u); // treated as if nothing at all there
}

class LittleSemiColonSvStreamTest: public testing::Test
{
public:
	LittleSemiColonSvStreamTest() :
		ssvStream(std::string(
			"easting;12500;17500;22500\n"
			"northing;32500;37500 ;42500\n"
			"1960-01-01;   8.32;   8.30;   8.32\n"
		    "1960-01-02;   2.13;   2.08;   1.97\n"))
	{
	}
protected:
	std::istringstream ssvStream;
};

TEST_F(LittleSemiColonSvStreamTest, CanReadSomeValuesSemiColon)
{
	TjsWeather::XsvReader aReader(ssvStream,';');
	auto someFields = aReader.readLine();
	EXPECT_GT(someFields.size(), 0u);
	EXPECT_EQ(someFields[0], std::string("easting"));
	EXPECT_EQ(someFields[1], std::string("12500"));
	aReader.readLine();
	auto someMoreFields = aReader.readLine();
	EXPECT_EQ(someMoreFields[0], std::string("1960-01-01"));
	EXPECT_EQ(someMoreFields[1], std::string("8.32"));
}
