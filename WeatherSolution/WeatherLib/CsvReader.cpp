#include "pch.h"
#include "XsvReader.h"


TjsWeather::XsvReader::XsvReader(std::istream& stream)
	:myStream(stream)
{
}

std::vector<std::string> TjsWeather::XsvReader::readLine() const
{
	std::vector<std::string> result;
	std::string aField;
	auto lineIsJustWhiteSpace = true;

	// do a very simplified subset of csv reading
	// ignore whitespace and any quoting/escaping

	auto c = ' ';
	while(myStream.get(c))
	{
		switch (c)
		{
		case '\n':
			// end of line, take the last field
			result.push_back(aField);
			return result;
		case ',':
			// end of field
			result.push_back(aField);
			aField.clear();
			lineIsJustWhiteSpace = false;
			break;
		case ' ':
		case '\t':
			// simple whitespace, ignore
			break;
		default:
			aField += c;
			lineIsJustWhiteSpace = false;
		}
	}
	// end of file or other error, treat as a return
	if (!lineIsJustWhiteSpace) { result.push_back(aField); }
	return result;
}

