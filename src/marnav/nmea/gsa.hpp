#ifndef __NMEA__GSA__HPP__
#define __NMEA__GSA__HPP__

#include "sentence.hpp"
#include <marnav/utils/optional.hpp>
#include <array>

namespace marnav
{
namespace nmea
{

/// @brief GSA - GPS DOP and active satellites
///
/// @code
///        1 2 3                        14 15  16  17
///        | | |                         |  |   |   |
/// $--GSA,a,a,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x.x,x.x,x.x*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1.  Selection mode: M=Manual, forced to operate in 2D or 3D, A=Automatic, 3D/2D
/// 2.  Mode (1 = no fix, 2 = 2D fix, 3 = 3D fix)
/// 3.  ID of 1st satellite used for fix
/// 4.  ID of 2nd satellite used for fix
/// 5.  ID of 3rd satellite used for fix
/// 6.  ID of 4th satellite used for fix
/// 7.  ID of 5th satellite used for fix
/// 8.  ID of 6th satellite used for fix
/// 9.  ID of 7th satellite used for fix
/// 10. ID of 8th satellite used for fix
/// 11. ID of 9th satellite used for fix
/// 12. ID of 10th satellite used for fix
/// 13. ID of 11th satellite used for fix
/// 14. ID of 12th satellite used for fix
/// 15. PDOP
/// 16. HDOP
/// 17. VDOP
///
class gsa : public sentence
{
public:
	constexpr static const sentence_id ID = sentence_id::GSA;
	constexpr static const char * TAG = "GSA";

	gsa();
	gsa(const gsa &) = default;
	gsa & operator=(const gsa &) = default;

	static std::unique_ptr<sentence> parse(const std::string & talker,
		const std::vector<std::string> & fields) throw(std::invalid_argument);

protected:
	virtual std::vector<std::string> get_data() const override;

private:
	constexpr static const int MAX_SATELLITE_IDS = 12;

	utils::optional<char> selection_mode; // A:automatic 2D/3D, M:manual
	utils::optional<uint32_t> mode; // 1 = no fix, 2 = 2D fix, 3 = 3D fix
	std::array<utils::optional<uint32_t>, MAX_SATELLITE_IDS> satellite_id;
	utils::optional<double> pdop;
	utils::optional<double> hdop;
	utils::optional<double> vdop;

	void check_index(int index) const throw(std::out_of_range);

public:
	decltype(selection_mode) get_selection_mode() const { return selection_mode; }
	decltype(mode) get_mode() const { return mode; }
	utils::optional<uint32_t> get_satellite_id(int index) const throw(std::out_of_range);
	decltype(pdop) get_pdop() const { return pdop; }
	decltype(hdop) get_hdop() const { return hdop; }
	decltype(vdop) get_vdop() const { return vdop; }

	void set_selection_mode(char t) { selection_mode = t; }
	void set_mode(uint32_t t) { mode = t; }
	void set_satellite_id(int index, uint32_t t) throw(std::out_of_range);
	void set_pdop(double t) { pdop = t; }
	void set_hdop(double t) { hdop = t; }
	void set_vdop(double t) { vdop = t; }
};
}
}

#endif
