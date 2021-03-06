#include <gtest/gtest.h>
#include <marnav/nmea/gns.hpp>
#include <marnav/nmea/nmea.hpp>

namespace
{

using namespace marnav;

class Test_nmea_gns : public ::testing::Test
{
};

TEST_F(Test_nmea_gns, contruction) { nmea::gns gns; }

TEST_F(Test_nmea_gns, parse)
{
	auto s = nmea::make_sentence(
		"$GNGNS,122310.0,3722.42567,N,12258.856215,W,AA,15,0.9,1005.54,6.5,,*75");
	ASSERT_NE(nullptr, s);

	auto gns = nmea::sentence_cast<nmea::gns>(s);
	ASSERT_NE(nullptr, gns);
}

TEST_F(Test_nmea_gns, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(nmea::gns::parse("@@", {11, "@"}));
	EXPECT_ANY_THROW(nmea::gns::parse("@@", {13, "@"}));
}

TEST_F(Test_nmea_gns, empty_to_string)
{
	nmea::gns gns;

	EXPECT_STREQ("$GPGNS,,,,,,,,,,,,*4D", nmea::to_string(gns).c_str());
}

TEST_F(Test_nmea_gns, set_lat)
{
	nmea::gns gns;
	gns.set_lat(geo::latitude{12.34});

	EXPECT_STREQ("$GPGNS,,1220.4000,N,,,,,,,,,*28", nmea::to_string(gns).c_str());
}

TEST_F(Test_nmea_gns, set_lon)
{
	nmea::gns gns;
	gns.set_lon(geo::longitude{123.45});

	EXPECT_STREQ("$GPGNS,,,,12327.0000,W,,,,,,,*01", nmea::to_string(gns).c_str());
}

TEST_F(Test_nmea_gns, set_mode_indicator)
{
	nmea::gns gns;
	gns.set_mode_indicator("AA");

	EXPECT_STREQ("$GPGNS,,,,,,AA,,,,,,*4D", nmea::to_string(gns).c_str());
}
}
