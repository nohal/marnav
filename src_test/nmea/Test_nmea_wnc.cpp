#include <gtest/gtest.h>
#include <marnav/nmea/wnc.hpp>
#include <marnav/nmea/nmea.hpp>

namespace
{

using namespace marnav;

class Test_nmea_wnc : public ::testing::Test
{
};

TEST_F(Test_nmea_wnc, contruction) { nmea::wnc wnc; }

TEST_F(Test_nmea_wnc, parse)
{
	auto s = nmea::make_sentence("$GPWNC,12.3,N,5.6,K,POINT1,POINT2*78");
	ASSERT_NE(nullptr, s);

	auto wnc = nmea::sentence_cast<nmea::wnc>(s);
	ASSERT_NE(nullptr, wnc);
}

TEST_F(Test_nmea_wnc, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(nmea::wnc::parse("@@", {5, "@"}));
	EXPECT_ANY_THROW(nmea::wnc::parse("@@", {7, "@"}));
}

TEST_F(Test_nmea_wnc, empty_to_string)
{
	nmea::wnc wnc;

	EXPECT_STREQ("$GPWNC,,,,,,*4D", nmea::to_string(wnc).c_str());
}

TEST_F(Test_nmea_wnc, set_distance_nm)
{
	nmea::wnc wnc;
	wnc.set_distance_nm(12.5);

	EXPECT_STREQ("$GPWNC,12.5,N,,,,*1B", nmea::to_string(wnc).c_str());
}

TEST_F(Test_nmea_wnc, set_distance_km)
{
	nmea::wnc wnc;
	wnc.set_distance_km(12.5);

	EXPECT_STREQ("$GPWNC,,,12.5,K,,*1E", nmea::to_string(wnc).c_str());
}

TEST_F(Test_nmea_wnc, set_waypoint_to)
{
	nmea::wnc wnc;
	wnc.set_waypoint_to("wpt1");

	EXPECT_STREQ("$GPWNC,,,,,wpt1,*0F", nmea::to_string(wnc).c_str());
}

TEST_F(Test_nmea_wnc, set_waypoint_to_string_to_large)
{
	nmea::wnc wnc;

	EXPECT_ANY_THROW(wnc.set_waypoint_to("123456789"));
}

TEST_F(Test_nmea_wnc, set_waypoint_from)
{
	nmea::wnc wnc;
	wnc.set_waypoint_from("wpt1");

	EXPECT_STREQ("$GPWNC,,,,,,wpt1*0F", nmea::to_string(wnc).c_str());
}

TEST_F(Test_nmea_wnc, set_waypoint_from_string_to_large)
{
	nmea::wnc wnc;

	EXPECT_ANY_THROW(wnc.set_waypoint_from("123456789"));
}
}

