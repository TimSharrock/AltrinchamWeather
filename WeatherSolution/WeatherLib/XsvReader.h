#pragma once
#include <istream>
#include <vector>

namespace TjsWeather
{
	class XsvReader
	{
	public:
		explicit XsvReader(std::istream& stream, char aSeparator=',');
		auto readLine() const -> std::vector<std::string>;
	private:
		std::istream& myStream;
		char const mySeparator=',';
	};

}
