#pragma once
#include <istream>
#include <vector>

namespace TjsWeather
{
	class CsvReader
	{
	public:
		explicit CsvReader(std::istream& stream);
		auto readLine() const -> std::vector<std::string>;
	private:
		std::istream& myStream;
	};

}
