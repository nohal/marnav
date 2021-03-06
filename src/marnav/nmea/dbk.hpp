#ifndef __NMEA__DBK__HPP__
#define __NMEA__DBK__HPP__

#include "sentence.hpp"
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{

/// @brief DBK - Depth Below Keel
///
/// @note This sentence appears to be deprected, use @ref marnav::nmea::dpt "DPT" instead.
///
/// @code
///        1   2 3   4 5   6
///        |   | |   | |   |
/// $--DBK,x.x,f,x.x,M,x.x,F*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Depth feet
/// 2. Depth feet unit
///    - f = feet
/// 3. Depth meters
/// 4. Depth meters unit
///    - M = meters
/// 5. Depth Fathoms
/// 6. Depth Fathoms
///    - F = Fathoms
///
class dbk : public sentence
{
public:
	constexpr static const sentence_id ID = sentence_id::DBK;
	constexpr static const char * TAG = "DBK";

	dbk();
	dbk(const dbk &) = default;
	dbk & operator=(const dbk &) = default;

	static std::unique_ptr<sentence> parse(const std::string & talker,
		const std::vector<std::string> & fields) throw(std::invalid_argument);

protected:
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<double> depth_feet;
	utils::optional<char> depth_feet_unit;
	utils::optional<double> depth_meter;
	utils::optional<char> depth_meter_unit;
	utils::optional<double> depth_fathom;
	utils::optional<char> depth_fathom_unit;

public:
	decltype(depth_feet) get_depth_feet() const { return depth_feet; }
	decltype(depth_feet_unit) get_depth_feet_unit() const { return depth_feet_unit; }
	decltype(depth_meter) get_depth_meter() const { return depth_meter; }
	decltype(depth_meter_unit) get_depth_meter_unit() const { return depth_meter_unit; }
	decltype(depth_fathom) get_depth_fathom() const { return depth_fathom; }
	decltype(depth_fathom_unit) get_depth_fathom_unit() const { return depth_fathom_unit; }

	void set_depth_feet(double t) { depth_feet = t; depth_feet_unit = unit::FEET; }
	void set_depth_meter(double t) { depth_meter = t; depth_meter_unit = unit::METER; }
	void set_depth_fathom(double t) { depth_fathom = t; depth_fathom_unit = unit::FATHOM; }
};
}
}

#endif
