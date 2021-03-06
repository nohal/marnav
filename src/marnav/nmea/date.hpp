#ifndef __NMEA__DATE__HPP__
#define __NMEA__DATE__HPP__

#include <string>
#include <stdexcept>

namespace marnav
{
namespace nmea
{

enum class month : uint32_t {january = 1, february, march, april, may, june, july, august,
	september, october, november, december};

class date
{
public:
	date();
	date(uint32_t y, month m, uint32_t d) throw(std::invalid_argument);

	/// Returns the year component.
	uint32_t year() const noexcept;

	/// Returns the month component.
	month mon() const noexcept;

	/// Returns the day component.
	uint32_t day() const noexcept;

	friend bool operator==(const date & a, const date & b) noexcept;

	/// Parses the date within the specified string.
	/// The date to be parsed must be in the form: "DDMMYY"
	static date parse(const std::string & str) throw(std::invalid_argument);

	/// Returns true if the specified year is a leap year. This function
	/// does not work for dates before 17?? (only for julian calendar).
	///
	/// Every fourth year is a leap year except for every 100 years,
	/// except every 400 years.
	static constexpr bool is_leap_year(uint32_t year) noexcept
	{
		return ((year % 4) == 0) && (((year % 100) != 0) || ((year % 400) == 0));
	}

private:
	bool check() const noexcept;

	uint32_t y; // year
	month m;
	uint32_t d; // day: 1..31
};

bool operator==(const date & a, const date & b) noexcept;
std::string to_string(const date & d);
std::ostream & operator<<(std::ostream & os, const date & d);
std::istream & operator>>(std::istream & is, date & d);
}
}

#endif
