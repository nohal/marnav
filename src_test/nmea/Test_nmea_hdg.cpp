#include <gtest/gtest.h>
#include <marnav/nmea/hdg.hpp>
#include <marnav/nmea/nmea.hpp>

namespace
{

using namespace marnav;

class Test_nmea_hdg : public ::testing::Test
{
};

TEST_F(Test_nmea_hdg, contruction) { nmea::hdg hdg; }

TEST_F(Test_nmea_hdg, parse)
{
	auto s = nmea::make_sentence("$HCHDG,45.8,,,0.6,E*16");
	ASSERT_NE(nullptr, s);

	auto hdg = nmea::sentence_cast<nmea::hdg>(s);
	ASSERT_NE(nullptr, hdg);

	auto heading = hdg->get_heading();
	EXPECT_TRUE(heading.available());
	EXPECT_EQ(45.8, heading.value());
}

TEST_F(Test_nmea_hdg, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(nmea::hdg::parse("@@", {4, "@"}));
	EXPECT_ANY_THROW(nmea::hdg::parse("@@", {6, "@"}));
}

TEST_F(Test_nmea_hdg, empty_to_string)
{
	nmea::hdg hdg;

	EXPECT_STREQ("$HCHDG,,,,,*6C", nmea::to_string(hdg).c_str());
}

TEST_F(Test_nmea_hdg, set_heading)
{
	nmea::hdg hdg;
	hdg.set_heading(45.8);

	EXPECT_STREQ("$HCHDG,45.8,,,,*7B", nmea::to_string(hdg).c_str());
}

TEST_F(Test_nmea_hdg, set_magn_dev)
{
	nmea::hdg hdg;
	hdg.set_magn_dev(5.8, nmea::direction::WEST);

	EXPECT_STREQ("$HCHDG,,5.8,W,,*18", nmea::to_string(hdg).c_str());
}

TEST_F(Test_nmea_hdg, set_magn_var)
{
	nmea::hdg hdg;
	hdg.set_magn_var(5.8, nmea::direction::WEST);

	EXPECT_STREQ("$HCHDG,,,,5.8,W*18", nmea::to_string(hdg).c_str());
}

TEST_F(Test_nmea_hdg, set_magn_dev_wrong_hemisphere)
{
	nmea::hdg hdg;

	EXPECT_ANY_THROW(hdg.set_magn_dev(5.8, nmea::direction::NORTH));
	EXPECT_ANY_THROW(hdg.set_magn_dev(5.8, nmea::direction::SOUTH));
}
}

