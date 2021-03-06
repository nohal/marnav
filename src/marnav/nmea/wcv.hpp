#ifndef __NMEA__WCV__HPP__
#define __NMEA__WCV__HPP__

#include "sentence.hpp"
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{

/// @brief WCV - Waypoint Closure Velocity
///
/// @code
///        1   2 3
///        |   | |
/// $--WCV,x.x,N,c--c*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Velocity
/// 2. Velocity unit
///    - N = knots
/// 3. Waypoint ID
///
class wcv : public sentence
{
public:
	constexpr static const sentence_id ID = sentence_id::WCV;
	constexpr static const char * TAG = "WCV";

	wcv();
	wcv(const wcv &) = default;
	wcv & operator=(const wcv &) = default;

	static std::unique_ptr<sentence> parse(const std::string & talker,
		const std::vector<std::string> & fields) throw(std::invalid_argument);

protected:
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<double> speed;
	utils::optional<char> speed_unit;
	utils::optional<std::string> waypoint_id;

public:
	decltype(speed) get_speed() const { return speed; }
	decltype(speed_unit) get_speed_unit() const { return speed_unit; }
	decltype(waypoint_id) get_waypoint_id() const { return waypoint_id; }

	void set_speed(double t);
	void set_waypoint(const std::string & id);
};
}
}

#endif
