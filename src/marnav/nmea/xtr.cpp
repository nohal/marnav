#include "xtr.hpp"
#include "io.hpp"
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * xtr::TAG;

xtr::xtr()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

std::unique_ptr<sentence> xtr::parse(const std::string & talker,
	const std::vector<std::string> & fields) throw(std::invalid_argument)
{
	if (fields.size() != 3)
		throw std::invalid_argument{"invalid number of fields in xtr::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<xtr>();
	result->set_talker(talker);
	xtr & detail = static_cast<xtr &>(*result);

	read(fields[0], detail.cross_track_error_magnitude);
	read(fields[1], detail.direction_to_steer);
	read(fields[2], detail.cross_track_units);

	return result;
}

std::vector<std::string> xtr::get_data() const
{
	return {to_string(cross_track_error_magnitude), to_string(direction_to_steer),
		to_string(cross_track_units)};
}
}
}

