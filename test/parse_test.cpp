#include "NMEAParser.h"
#include "gtest/gtest.h"

#include <iostream>

namespace NMEA {
TEST(FieldParseTests, Valid_ParseTimeStamp_String) {
  const std::string TimeStamp = "092725.00";
  const time_t Expected = 1439454445;

  auto Parser = NMEA::NMEAParser();

  EXPECT_EQ(Expected, Parser.ParseTimeStamp(&TimeStamp));
}

TEST(FieldParseTests, Invalid_ParseTimeStamp_String) {
  const std::string TimeStamp = "asdfkjasd=234";
  const time_t Expected = 0;

  auto Parser = NMEA::NMEAParser();

  EXPECT_EQ(Expected, Parser.ParseTimeStamp(&TimeStamp));
}

TEST(FieldParseTests, Invalid_Range_ParseTimeStamp_String) {
  const std::string TimeStamp = "444294967297";
  const time_t Expected = 0;

  auto Parser = NMEA::NMEAParser();

  EXPECT_EQ(Expected, Parser.ParseTimeStamp(&TimeStamp));
}
}
