#ifndef __NMEA__FSI__HPP__
#define __NMEA__FSI__HPP__

#include "sentence.hpp"
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{

/// @brief FSI - Frequency Set Information
///
/// @code
///         1      2      3 4 5
///         |      |      | | |
///  $--FSI,xxxxxx,xxxxxx,c,x,a*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Transmitting Frequency in 100Hz increments
/// 2. Receiving Frequency in 100Hz increments
/// 3. Mode of operation
/// 4. Power Level
///    - 0 = standby
///    - 1..9 = intensity (1=lowest, 9=highest)
/// 5. Sentence Status Flag
///    - R = Report of current settings
///    - C = Configuration command to change settings
///
class fsi : public sentence
{
public:
	constexpr static const sentence_id ID = sentence_id::FSI;
	constexpr static const char * TAG = "FSI";

	fsi();
	fsi(const fsi &) = default;
	fsi & operator=(const fsi &) = default;

	static std::unique_ptr<sentence> parse(const std::string & talker,
		const std::vector<std::string> & fields) throw(std::invalid_argument);

protected:
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<uint32_t> tx_frequency;
	utils::optional<uint32_t> rx_frequency;
	utils::optional<char> communications_mode;
	utils::optional<uint32_t> power_level;
	utils::optional<char> sentence_status;

public:
	decltype(tx_frequency) get_tx_frequency() const { return tx_frequency; }
	decltype(rx_frequency) get_rx_frequency() const { return rx_frequency; }
	decltype(communications_mode) get_communications_mode() const
	{
		return communications_mode;
	}
	decltype(power_level) get_power_level() const { return power_level; }
	decltype(sentence_status) get_sentence_status() const { return sentence_status; }

	void set_tx_frequency(uint32_t t) { tx_frequency = t; }
	void set_rx_frequency(uint32_t t) { rx_frequency = t; }
	void set_communications_mode(char t) { communications_mode = t; }
	void set_power_level(uint32_t t) { power_level = t; }
	void set_sentence_status(char t) { sentence_status = t; }
};
}
}

#endif
