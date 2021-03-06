#include "default_seatalk_reader.hpp"

namespace marnav
{
namespace io
{

default_seatalk_reader::default_seatalk_reader(std::unique_ptr<device> && dev)
	: seatalk_reader(std::move(dev))
	, message_received(false)
{
}

/// Reads synchronously messages from the device.
///
/// @param[out] data The received message.
/// @retval true  Success.
/// @retval false End of file.
/// @exception std::runtime_error
bool default_seatalk_reader::read_message(seatalk::raw & data)
{
	// reads as long as the message is not complete.
	while (read()) {
		// the message was received, return it and reset the 'semaphore'.
		// please note: this works only in single threaded environment,
		// since the 'semaphore' isn't really one.
		if (message_received) {
			data = message;
			message_received = false;
			return true;
		}
	}
	return false;
}

/// Processes the received message. Uses the data member 'message_received'
/// as poor-mans semaphore to signal the receipt.
///
/// After the reception, the message will be stored temporarily.
void default_seatalk_reader::process_message(const seatalk::raw & msg)
{
	message = msg;
	message_received = true;
}
}
}
