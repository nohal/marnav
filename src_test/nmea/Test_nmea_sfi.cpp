#include <gtest/gtest.h>
#include <marnav/nmea/sfi.hpp>
#include <marnav/nmea/nmea.hpp>

namespace
{

using namespace marnav;

class Test_nmea_sfi : public ::testing::Test
{
};

TEST_F(Test_nmea_sfi, contruction) { nmea::sfi sfi; }

TEST_F(Test_nmea_sfi, parse)
{
	auto s = nmea::make_sentence("$GPSFI,1,1,156025,M*03");
	ASSERT_NE(nullptr, s);

	auto sfi = nmea::sentence_cast<nmea::sfi>(s);
	ASSERT_NE(nullptr, sfi);
}

TEST_F(Test_nmea_sfi, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(nmea::sfi::parse("@@", {1, "@"}));
	EXPECT_ANY_THROW(nmea::sfi::parse("@@", {3, "@"}));
	EXPECT_ANY_THROW(nmea::sfi::parse("@@", {23, "@"}));
	EXPECT_ANY_THROW(nmea::sfi::parse("@@", {24, "@"}));
}

TEST_F(Test_nmea_sfi, empty_to_string)
{
	nmea::sfi sfi;

	EXPECT_STREQ("$GPSFI,0,0*4B", nmea::to_string(sfi).c_str());
}
}

