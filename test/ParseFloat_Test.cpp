/**
 * File: ParseFloat_Test.cpp
 * Description: Unit tests for
 * Parse(const std::string &String)
 */
#include "NMEAParser.cpp"
#include "gtest/gtest.h"

#include <cmath>

namespace NMEA {
TEST(ParseFloat, Valid_Float) {
  const std::string String = "3.0";
  const float Expected = 3.0f;

  EXPECT_EQ(Expected, ParseFloat(String));
}

TEST(ParseFloat, Invalid_Float) {
  const std::string String = "ASDF";

  EXPECT_TRUE(isnan(ParseFloat(String)));
}

TEST(ParseFloat, Invalid_Empty_Float) {
  const std::string String = "";
  const float Expected = NAN;

  EXPECT_TRUE(isnan(ParseFloat(String)));
}
}
