/**
 * @file: ParseSpeed_Test.cpp
 * @brief: Unit tests for ParseString(const std::string &Speed)
 */
#include "NMEAParser.h"
#include "gtest/gtest.h"

#include <cmath>

namespace NMEA {
TEST(ParseSpeed, Valid_Speed) {
  const std::string Speed = "0.004";
  const float Expected = 0.004f;

  auto Parser = NMEAParser{};

  EXPECT_FLOAT_EQ(Expected, Parser.ParseSpeed(Speed));
}

TEST(ParseSpeed, Invalid_Speed) {
  const std::string Speed = "asdf";

  auto Parser = NMEAParser{};

  EXPECT_TRUE(isnan(Parser.ParseSpeed(Speed)));
}

TEST(ParseSpeed, Empty_Speed) {
  const std::string Speed = "";

  auto Parser = NMEAParser{};

  EXPECT_TRUE(isnan(Parser.ParseSpeed(Speed)));
}
}
