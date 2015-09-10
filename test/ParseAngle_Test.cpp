 /**
 * @file: ParseAngle_Test.cpp
 * @brief: Unit tests for ParseAngle(const std::string &Angle)
 */
#include "NMEAParser.h"
#include "gtest/gtest.h"

#include <cmath>

namespace NMEA {
TEST(ParseAngle, Valid_Angle) {
  const std::string Angle = "77.52";
  const float Expected = 77.52f;

  auto Parser = NMEAParser{};

  EXPECT_FLOAT_EQ(Expected, Parser.ParseAngle(Angle));
}

TEST(ParseAngle, Invalid_Angle) {
  const std::string Angle = "asdf";

  auto Parser = NMEAParser{};

  EXPECT_TRUE(isnan(Parser.ParseAngle(Angle)));
}

TEST(ParseAngle, Empty_Angle) {
  const std::string Angle = "";

  auto Parser = NMEAParser{};

  EXPECT_TRUE(isnan(Parser.ParseAngle(Angle)));
}
}
