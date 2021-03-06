#include <gtest/gtest.h>
#include <marnav/nmea/xtr.hpp>
#include <marnav/nmea/nmea.hpp>

namespace
{

using namespace marnav;

class Test_nmea_xtr : public ::testing::Test
{
};

TEST_F(Test_nmea_xtr, contruction) { nmea::xtr xtr; }

TEST_F(Test_nmea_xtr, parse)
{
	auto s = nmea::make_sentence("$GPXTR,,,*65");
	ASSERT_NE(nullptr, s);

	auto xtr = nmea::sentence_cast<nmea::xtr>(s);
	ASSERT_NE(nullptr, xtr);
}

TEST_F(Test_nmea_xtr, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(nmea::xtr::parse("@@", {2, "@"}));
	EXPECT_ANY_THROW(nmea::xtr::parse("@@", {4, "@"}));
}

TEST_F(Test_nmea_xtr, empty_to_string)
{
	nmea::xtr xtr;

	EXPECT_STREQ("$GPXTR,,,*65", nmea::to_string(xtr).c_str());
}

TEST_F(Test_nmea_xtr, set_cross_track_error_magnitude)
{
	nmea::xtr xtr;
	xtr.set_cross_track_error_magnitude(1.2);

	EXPECT_STREQ("$GPXTR,1.2,,*48", nmea::to_string(xtr).c_str());
}

TEST_F(Test_nmea_xtr, set_direction_to_steer)
{
	nmea::xtr xtr;
	xtr.set_direction_to_steer(nmea::side::LEFT);

	EXPECT_STREQ("$GPXTR,,L,*29", nmea::to_string(xtr).c_str());
}

TEST_F(Test_nmea_xtr, set_cross_track_units)
{
	nmea::xtr xtr;
	xtr.set_cross_track_units(nmea::unit::NM);

	EXPECT_STREQ("$GPXTR,,,N*2B", nmea::to_string(xtr).c_str());
}

}

