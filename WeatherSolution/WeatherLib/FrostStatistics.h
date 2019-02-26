#pragma once
#include <ostream>


namespace TjsWeather
{
	template <typename Iterator>
	void printFrostStatistics(Iterator const& startIterator, Iterator const& endIterator, std::ostream& stream)
	{
		if (startIterator == endIterator) { return; }

		auto yearStartIterator = startIterator;
		auto coldestInYearIterator = startIterator;
		auto lastFrostIterator = endIterator;
		auto firstFrostIterator = endIterator;
		size_t frostCount = 0;

		// print the header
		stream << "Year\t"
			<< "Coldest-T\tColdest-D\t"
			<< "Frosts\t"
			<< "Gap\t"
			<< "Last-T\tLast-D\tLast-O\t"
			<< "First-T\tFirst-D\tFirst-O\n";

		auto i = startIterator;
		while (true)
		{
			if ((i == endIterator) || (i->year() != yearStartIterator->year()))
			{
				// a year finished, print and reset values
				stream << yearStartIterator->year() << "\t"
					<< coldestInYearIterator->value() << "\t" << coldestInYearIterator->date() << "\t"
					<< frostCount << "\t";
				if ((lastFrostIterator != endIterator) && (firstFrostIterator != endIterator))
				{
					stream << (date::sys_days(firstFrostIterator->date()) - date::sys_days(lastFrostIterator->date())).count() << "\t";
				}
				else
				{
					stream << "\t"; // gap not valid, i could do one-ended I suppose, but there are no examples here
				}

				if (lastFrostIterator != endIterator)
				{
					auto const orderingDate = date::year(2104) / lastFrostIterator->month() / lastFrostIterator->day();
					stream << lastFrostIterator->value() << "\t" << lastFrostIterator->date() << "\t" << orderingDate << "\t";
				}
				else
				{
					stream << "\t\t\t";
				}
				if (firstFrostIterator != endIterator)
				{
					auto const orderingDate = date::year(2104) / firstFrostIterator->month() / firstFrostIterator->day();
					stream << firstFrostIterator->value() << "\t" << firstFrostIterator->date() << "\t" << orderingDate << "\n";
				}
				else
				{
					stream << "\t\t\n";
				}
				yearStartIterator = i;
				coldestInYearIterator = i;
				lastFrostIterator = endIterator;
				firstFrostIterator = endIterator;
				frostCount = 0;
			}
			if (i == endIterator) { break; }

			auto const temperature = i->value();
			if (coldestInYearIterator->value() > temperature) { coldestInYearIterator = i; }
			if (temperature < 0.0)
			{
				++frostCount;
				if (i->month() < date::July)
				{
					lastFrostIterator = i;
				}
				else
				{
					if (firstFrostIterator == endIterator) { firstFrostIterator = i; }
				}
			}
			++i;

		}
	}
}


