/**
 * File: ParseInteger_Test.cpp
 * Description: Unit tests for
 * ParseInteger(const std::string &String)
 */
#include "NMEAParser.cpp"
#include "gtest/gtest.h"

#include <cmath>

namespace NMEA {
TEST(ParseInteger, Valid_Float) {
  const std::string String = "128";
  const int Expected = 128;

  EXPECT_EQ(Expected, ParseInteger(String));
}

TEST(ParseInteger, Invalid_Integer) {
  const std::string String = "ASDF";
  const int Expected = 0;
  
  EXPECT_EQ(Expected, ParseInteger(String));
}

TEST(ParseInteger, Invalid_Empty_Integer) {
  const std::string String = "";
  const float Expected = 0;

  EXPECT_EQ(Expected, ParseInteger(String));
}
}
