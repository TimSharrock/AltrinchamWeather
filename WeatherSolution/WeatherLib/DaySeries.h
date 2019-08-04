#pragma once
#include <iosfwd>
#include "DayAndValue.h"
#include <vector>

namespace TjsWeather
{
	class DaySeries
	{
	public:
		DaySeries() = default;
		~DaySeries() = default;
		DaySeries(DaySeries const&) = default;
		DaySeries& operator=(DaySeries const&) = default;

		void reserve(size_t size);

		template<typename When, typename Value>
		void emplace_back(When when, Value value)
		{
			myData.emplace_back(when, value);
		}
		std::vector<DayAndValue>::const_iterator begin() const;
		std::vector<DayAndValue>::const_iterator end() const;

		size_t size() const;

	private:
		std::vector<DayAndValue> myData;
	};
}
