 /**
 * @file: ParseAngle_Test.cpp
 * @brief: Unit tests for ParseAngle(const std::string &Angle)
 */
#include "NMEAParser.cpp"
#include "gtest/gtest.h"

#include <cmath>

namespace NMEA {
TEST(ParseAngle, Valid_Angle) {
  const std::string Angle = "77.52";
  const float Expected = 77.52f;

  EXPECT_FLOAT_EQ(Expected, ParseAngle(Angle));
}

TEST(ParseAngle, Invalid_Angle) {
  const std::string Angle = "asdf";

  EXPECT_TRUE(isnan(ParseAngle(Angle)));
}

TEST(ParseAngle, Empty_Angle) {
  const std::string Angle = "";

  EXPECT_TRUE(isnan(ParseAngle(Angle)));
}
}
