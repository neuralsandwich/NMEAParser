/**
 * @file: ParseLatitude_Test.cpp
 * @brief: Unit tests for ParseLatitue(const std::string &String,
 *                                      const std::string &Direction)
 */

#include "NMEAParser.h"
#include "gtest/gtest.h"

#include <cmath>

namespace NMEA {
TEST(ParseLatitude, Valid_Latitude_Valid_North) {
  const std::string Latitude = "4717.11437";
  const std::string Direction = "N";
  const float Expected = 4717.11437f;

  auto Parser = NMEAParser{};

  EXPECT_FLOAT_EQ(Expected, Parser.ParseLatitude(Latitude, Direction));
}

TEST(ParseLatitude, Valid_Latitude_Valid_South) {
  const std::string Latitude = "4717.11437";
  const std::string Direction = "S";
  const float Expected = -4717.11437f;

  auto Parser = NMEAParser{};

  EXPECT_FLOAT_EQ(Expected, Parser.ParseLatitude(Latitude, Direction));
}

TEST(ParseLatitude, Valid_Latitude_Invalid_Direction) {
  const std::string Latitude = "4717.11364";
  const std::string Direction = "K";

  auto Parser = NMEAParser{};

  EXPECT_TRUE(isnan(Parser.ParseLatitude(Latitude, Direction)));
}

TEST(ParseLatitude, Invalid_Latitude_Valid_Direction) {
  const std::string Latitude = "asdf";
  const std::string Direction = "N";

  auto Parser = NMEAParser{};

  EXPECT_TRUE(isnan(Parser.ParseLatitude(Latitude, Direction)));
}

TEST(ParseLatitude, Invalid_Latitude_Invalid_Direction) {
  const std::string Latitude = "asdf";
  const std::string Direction = "Z";

  auto Parser = NMEAParser{};

  EXPECT_TRUE(isnan(Parser.ParseLatitude(Latitude, Direction)));
}

TEST(ParseLatitude, Empty_Latitude_Valid_Direction) {
  const std::string Latitude = "";
  const std::string Direction = "N";

  auto Parser = NMEAParser{};

  EXPECT_TRUE(isnan(Parser.ParseLatitude(Latitude, Direction)));
}

TEST(ParseLatitude, Empty_Latitude_Invalid_Direction) {
  const std::string Latitude = "";
  const std::string Direction = "B";

  auto Parser = NMEAParser{};

  EXPECT_TRUE(isnan(Parser.ParseLatitude(Latitude, Direction)));
}

TEST(ParseLatitude, Empty_Latitude_Empty_Direction) {
  const std::string Latitude = "";
  const std::string Direction = "";

  auto Parser = NMEAParser{};

  EXPECT_TRUE(isnan(Parser.ParseLatitude(Latitude, Direction)));
}
}
