#include <gtest/gtest.h>
#include <marnav/nmea/dbk.hpp>
#include <marnav/nmea/nmea.hpp>

namespace
{

using namespace marnav;

class Test_nmea_dbk : public ::testing::Test
{
};

TEST_F(Test_nmea_dbk, contruction) { nmea::dbk dbk; }

TEST_F(Test_nmea_dbk, parse)
{
	auto s = nmea::make_sentence("$IIDBK,9.3,f,1.2,M,3.4,F*00");
	ASSERT_NE(nullptr, s);

	auto dbk = nmea::sentence_cast<nmea::dbk>(s);
	ASSERT_NE(nullptr, dbk);
}

TEST_F(Test_nmea_dbk, parse_invalid_number_of_arguments)
{
	EXPECT_ANY_THROW(nmea::dbk::parse("@@", {5, "@"}));
	EXPECT_ANY_THROW(nmea::dbk::parse("@@", {7, "@"}));
}

TEST_F(Test_nmea_dbk, empty_to_string)
{
	nmea::dbk dbk;

	EXPECT_STREQ("$IIDBK,,,,,,*4D", nmea::to_string(dbk).c_str());
}

TEST_F(Test_nmea_dbk, set_depth_feet)
{
	nmea::dbk dbk;
	dbk.set_depth_feet(12.5);

	EXPECT_STREQ("$IIDBK,12.5,f,,,,*33", nmea::to_string(dbk).c_str());
}

TEST_F(Test_nmea_dbk, set_depth_meter)
{
	nmea::dbk dbk;
	dbk.set_depth_meter(12.5);

	EXPECT_STREQ("$IIDBK,,,12.5,M,,*18", nmea::to_string(dbk).c_str());
}

TEST_F(Test_nmea_dbk, set_depth_fathom)
{
	nmea::dbk dbk;
	dbk.set_depth_fathom(12.5);

	EXPECT_STREQ("$IIDBK,,,,,12.5,F*13", nmea::to_string(dbk).c_str());
}
}


