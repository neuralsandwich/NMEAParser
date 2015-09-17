//===-- ParseLongitude_Test.cpp ---------------------------------*- C++ -*-===//
//
// This file is distributed uner the MIT license. See LICENSE.txt for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// Unit tests for ParseLongitude(const std::string &String,
///                               const std::string &Direction)
///
//===----------------------------------------------------------------------===//
#include "NMEAParser.cpp"
#include "gtest/gtest.h"

#include <cmath>

namespace NMEA {
TEST(ParseLongitude, Valid_Longitude_Valid_East) {
  const std::string Longitude = "00833.91522";
  const std::string Direction = "E";
  const float Expected = 833.91522f;

  EXPECT_FLOAT_EQ(Expected, ParseLongitude(Longitude, Direction));
}

TEST(ParseLongitude, Valid_Longitude_Valid_West) {
  const std::string Longitude = "00833.91522";
  const std::string Direction = "W";
  const float Expected = -833.91522;

  EXPECT_FLOAT_EQ(Expected, ParseLongitude(Longitude, Direction));
}

TEST(ParseLongitude, Valid_Longitude_Invalid_Direction) {
  const std::string Longitude = "00833.91522";
  const std::string Direction = "I";

  EXPECT_TRUE(isnan(ParseLongitude(Longitude, Direction)));
}

TEST(ParseLongitude, Invalid_Longitude_Valid_Direction) {
  const std::string Longitude = "asdf";
  const std::string Direction = "W";

  EXPECT_TRUE(isnan(ParseLongitude(Longitude, Direction)));
}

TEST(ParseLongitude, Invalid_Longitude_Invalid_Direction) {
  const std::string Longitude = "asdf";
  const std::string Direction = "Z";

  EXPECT_TRUE(isnan(ParseLongitude(Longitude, Direction)));
}

TEST(ParseLongitude, Empty_Longitude_Valid_Direction) {
  const std::string Longitude = "";
  const std::string Direction = "W";

  EXPECT_TRUE(isnan(ParseLongitude(Longitude, Direction)));
}

TEST(ParseLongitude, Empty_Longitude_Invalid_Direction) {
  const std::string Longitude = "";
  const std::string Direction = "B";

  EXPECT_TRUE(isnan(ParseLongitude(Longitude, Direction)));
}

TEST(ParseLongitude, Empty_Longitude_Empty_Direction) {
  const std::string Longitude = "";
  const std::string Direction = "";

  EXPECT_TRUE(isnan(ParseLongitude(Longitude, Direction)));
}
}
