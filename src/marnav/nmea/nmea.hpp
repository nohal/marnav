#ifndef __NMEA__NMEA__HPP__
#define __NMEA__NMEA__HPP__

#include <stdexcept>
#include "sentence.hpp"

namespace marnav
{
namespace nmea
{

/// Exception for cases where the checksum is wrong.
///
/// This exception carries the actual as well as the expected
/// checksum and will provide this information in the explanation.
class checksum_error : public std::exception
{
public:
	checksum_error(uint8_t expected, uint8_t actual);

	virtual const char * what() const noexcept override { return text.c_str(); }

public:
	const uint8_t expected;
	const uint8_t actual;
	std::string text;
};

/// Exception to be thrown if a NMEA sentence is not known/supported.
class unknown_sentence : public std::logic_error
{
public:
	using logic_error::logic_error;
};

std::unique_ptr<sentence> make_sentence(const std::string & s) throw(
	std::invalid_argument, checksum_error, unknown_sentence);

std::vector<std::string> get_supported_sentences_str();
std::vector<sentence_id> get_supported_sentences_id();
const char * id_to_tag(sentence_id id) throw(unknown_sentence);
sentence_id tag_to_id(const std::string & tag) throw(unknown_sentence);
}
}

#endif
