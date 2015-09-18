//===-- ParseAltitude_Test.cpp ----------------------------------*- C++ -*-===//
//
// This file is distributed uner the MIT license. See LICENSE.txt for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// Unit tests for ParseAltitude(const std::string &String,
///                              const std::string &Direction
///
//===----------------------------------------------------------------------===//
#include "NMEAParser.cpp"
#include "gtest/gtest.h"

#include <cmath>

namespace NMEA {
TEST(ParseAltitude, Valid_Altitude) {
  const std::string Altitude = "-2.8";
  const float Expected = -2.8f;

  EXPECT_FLOAT_EQ(Expected, ParseAltitude(Altitude));
}

TEST(ParseAltitude, Invalid_Altitude) {
  const std::string Altitude = "asdf";

  EXPECT_TRUE(isnan(ParseAltitude(Altitude)));
}

TEST(ParseAltitude, Empty_Altitude) {
  const std::string Altitude = "";

  EXPECT_TRUE(isnan(ParseAltitude(Altitude)));
}
}
