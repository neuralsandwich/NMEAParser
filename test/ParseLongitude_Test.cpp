/**
 * @file: ParseLongitude_Test.cpp
 * @brief: Unit tests for ParseLongitude(const std::string &String,
 *                                       const std::string &Direction)
 */

#include "NMEAParser.h"
#include "gtest/gtest.h"

#include <cmath>

namespace NMEA {
TEST(ParseLongitude, Valid_Longitude_Valid_East) {
  const std::string Longitude = "00833.91522";
  const std::string Direction = "E";
  const float Expected = 833.91522f;

  auto Parser = NMEAParser{};

  EXPECT_FLOAT_EQ(Expected, Parser.ParseLongitude(Longitude, Direction));
}

TEST(ParseLongitude, Valid_Longitude_Valid_West) {
  const std::string Longitude = "00833.91522";
  const std::string Direction = "W";
  const float Expected = -833.91522;

  auto Parser = NMEAParser{};

  EXPECT_FLOAT_EQ(Expected, Parser.ParseLongitude(Longitude, Direction));
}

TEST(ParseLongitude, Valid_Longitude_Invalid_Direction) {
  const std::string Longitude = "00833.91522";
  const std::string Direction = "I";

  auto Parser = NMEAParser{};

  EXPECT_TRUE(isnan(Parser.ParseLongitude(Longitude, Direction)));
}

TEST(ParseLongitude, Invalid_Longitude_Valid_Direction) {
  const std::string Longitude = "asdf";
  const std::string Direction = "W";

  auto Parser = NMEAParser{};

  EXPECT_TRUE(isnan(Parser.ParseLongitude(Longitude, Direction)));
}

TEST(ParseLongitude, Invalid_Longitude_Invalid_Direction) {
  const std::string Longitude = "asdf";
  const std::string Direction = "Z";

  auto Parser = NMEAParser{};

  EXPECT_TRUE(isnan(Parser.ParseLongitude(Longitude, Direction)));
}

TEST(ParseLongitude, Empty_Longitude_Valid_Direction) {
  const std::string Longitude = "";
  const std::string Direction = "W";

  auto Parser = NMEAParser{};

  EXPECT_TRUE(isnan(Parser.ParseLongitude(Longitude, Direction)));
}

TEST(ParseLongitude, Empty_Longitude_Invalid_Direction) {
  const std::string Longitude = "";
  const std::string Direction = "B";

  auto Parser = NMEAParser{};

  EXPECT_TRUE(isnan(Parser.ParseLongitude(Longitude, Direction)));
}

TEST(ParseLongitude, Empty_Longitude_Empty_Direction) {
  const std::string Longitude = "";
  const std::string Direction = "";

  auto Parser = NMEAParser{};

  EXPECT_TRUE(isnan(Parser.ParseLongitude(Longitude, Direction)));
}
}
