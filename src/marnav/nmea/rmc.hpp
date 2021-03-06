#ifndef __NMEA__RMC__HPP__
#define __NMEA__RMC__HPP__

#include "sentence.hpp"
#include "date.hpp"
#include "time.hpp"
#include "angle.hpp"
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{


/// @brief RMC - Recommended Minimum Navigation Information
///
/// @code
///                                                            12
///        1         2 3       4 5        6  7   8   9    10 11|
///        |         | |       | |        |  |   |   |    |  | |
/// $--RMC,hhmmss.ss,A,llll.ll,a,yyyyy.yy,a,x.x,x.x,xxxx,x.x,a,m,*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1.  UTC Time
/// 2.  Status, V=Navigation receiver warning A=Valid
/// 3.  Latitude
/// 4.  Latitude hemisphere
///     - N = North
///     - S = South
/// 5.  Longitude
/// 6.  Longitude hemisphere
///     - E = East
///     - W = West
/// 7.  Speed over ground, knots
/// 8.  Track made good, degrees true
/// 9.  Date, ddmmyy
/// 10. Magnetic Variation, degrees
/// 11. Magnetic Variation, degrees, direction
///     - E = East
///     - W = West
/// 12. FAA mode indicator (NMEA 2.3 and later)
///
/// A status of V means the GPS has a valid fix that is below an internal quality
/// threshold, e.g. because the dilution of precision is too high or an elevation
/// mask test failed.
///
class rmc : public sentence
{
public:
	constexpr static const sentence_id ID = sentence_id::RMC;
	constexpr static const char * TAG = "RMC";

	rmc();
	rmc(const rmc &) = default;
	rmc & operator=(const rmc &) = default;

	static std::unique_ptr<sentence> parse(const std::string & talker,
		const std::vector<std::string> & fields) throw(std::invalid_argument);

protected:
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<nmea::time> time_utc;
	utils::optional<char> status;
	utils::optional<geo::latitude> lat;
	utils::optional<char> lat_hem;
	utils::optional<geo::longitude> lon;
	utils::optional<char> lon_hem;
	utils::optional<double> sog;
	utils::optional<double> heading;
	utils::optional<nmea::date> date;
	utils::optional<double> mag;
	utils::optional<char> mag_hem;
	utils::optional<char> faa_mode_indicator;

public:
	decltype(time_utc) get_time_utc() const { return time_utc; }
	decltype(status) get_status() const { return status; }
	decltype(lat) get_lat() const { return lat; }
	decltype(lat_hem) get_lat_hem() const { return lat_hem; }
	decltype(lon) get_lon() const { return lon; }
	decltype(lon_hem) get_lon_hem() const { return lon_hem; }
	decltype(sog) get_sog() const { return sog; }
	decltype(heading) get_heading() const { return heading; }
	decltype(date) get_date() const { return date; }
	decltype(mag) get_mag() const { return mag; }
	decltype(mag_hem) get_mag_hem() const { return mag_hem; }
	decltype(faa_mode_indicator) get_faa_mode_indicator() const { return faa_mode_indicator; }

	void set_time_utc(const time & t) { time_utc = t; }
	void set_status(char t) { status = t; }
	void set_lat(const geo::latitude & t);
	void set_lon(const geo::longitude & t);
	void set_sog(double t) { sog = t; }
	void set_heading(double t) { heading = t; }
	void set_date(const nmea::date & t) { date = t; }
	void set_mag(double t, char h)
	{
		mag = t;
		mag_hem = h;
	}
	void set_mode_indicator(char t) { faa_mode_indicator = t; }
};
}
}

#endif
