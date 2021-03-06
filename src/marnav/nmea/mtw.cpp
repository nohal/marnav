#include "mtw.hpp"
#include "io.hpp"
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * mtw::TAG;

mtw::mtw()
	: sentence(ID, TAG, talker_id::integrated_instrumentation)
{
}

std::unique_ptr<sentence> mtw::parse(const std::string & talker,
	const std::vector<std::string> & fields) throw(std::invalid_argument)
{
	if (fields.size() != 2)
		throw std::invalid_argument{"invalid number of fields in mtw::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<mtw>();
	result->set_talker(talker);
	mtw & detail = static_cast<mtw &>(*result);

	read(fields[0], detail.temperature);
	read(fields[1], detail.unit);

	return result;
}

std::vector<std::string> mtw::get_data() const
{
	return {to_string(temperature), to_string(unit)};
}
}
}
