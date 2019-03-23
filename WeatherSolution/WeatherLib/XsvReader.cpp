#include "pch.h"
#include "XsvReader.h"


TjsWeather::XsvReader::XsvReader(std::istream& stream, char aSeparator)
	:myStream(stream),mySeparator(aSeparator)
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
		if(c=='\n')
		{
			// end of line, take the last field
			result.push_back(aField);
			return result;
		}
		else if(c==mySeparator)
		{
			// end of field
			result.push_back(aField);
			aField.clear();
			lineIsJustWhiteSpace = false;
		}
		else if((c==' ')||(c=='\t'))
		{
			// simple whitespace, ignore
		}
		else
		{
			aField += c;
			lineIsJustWhiteSpace = false;
		}
	}
	// end of file or other error, treat as a return
	if (!lineIsJustWhiteSpace) { result.push_back(aField); }
	return result;
}

