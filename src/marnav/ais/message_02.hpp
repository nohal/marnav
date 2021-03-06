#ifndef __AIS__MESSAGE_02__HPP__
#define __AIS__MESSAGE_02__HPP__

#include "message_01.hpp"

namespace marnav
{
namespace ais
{

class message_02 : public message_01
{
public:
	constexpr static const message_id ID
		= message_id::position_report_class_a_assigned_schedule;

	message_02();
	message_02(const message_02 &) = default;
	message_02 & operator=(const message_02 &) = default;

	static std::unique_ptr<message> parse(const raw & bits) throw(std::invalid_argument);
};
}
}

#endif
