/**
 * @file: ParseStatus_Test.cpp
 * @brief: Unit tests for ParseStatus(const std::string &String)
 */
#include "NMEAParser.h"
#include "gtest/gtest.h"

namespace NMEA {
TEST(ParseStatus, Valid_Active_RMC_Status) {
  const std::string Status = "A";
  const bool Expected = true;

  auto Parser = NMEAParser{};

  EXPECT_EQ(Expected, Parser.ParseStatus(NMEA_MESSAGE_TYPE::RMC, Status));
}

TEST(ParseStatus, Valid_Void_RMC_Status) {
  const std::string Status = "V";
  const bool Expected = false;

  auto Parser = NMEAParser{};

  EXPECT_EQ(Expected, Parser.ParseStatus(NMEA_MESSAGE_TYPE::RMC, Status));
}

TEST(ParseStatus, Valid_Active_GLL_Status) {
  const std::string Status = "A";
  const bool Expected = true;

  auto Parser = NMEAParser{};

  EXPECT_EQ(Expected, Parser.ParseStatus(NMEA_MESSAGE_TYPE::GLL, Status));
}

TEST(ParseStatus, Valid_Void_GLL_Status) {
  const std::string Status = "V";
  const bool Expected = false;

  auto Parser = NMEAParser{};

  EXPECT_EQ(Expected, Parser.ParseStatus(NMEA_MESSAGE_TYPE::GLL, Status));
}

TEST(ParseStatus, Valid_Fix_GGA_Status) {
  const std::string Status = "2";
  const bool Expected = true;

  auto Parser = NMEAParser{};

  EXPECT_EQ(Expected, Parser.ParseStatus(NMEA_MESSAGE_TYPE::GGA, Status));
}

TEST(ParseStatus, Valid_No_Fix_GGA_Status) {
  const std::string Status = "0";
  const bool Expected = false;

  auto Parser = NMEAParser{};

  EXPECT_EQ(Expected, Parser.ParseStatus(NMEA_MESSAGE_TYPE::GGA, Status));
}

TEST(ParseStatus, Valid_Fix_GSA_Status) {
  const std::string Status = "3";
  const bool Expected = true;

  auto Parser = NMEAParser{};

  EXPECT_EQ(Expected, Parser.ParseStatus(NMEA_MESSAGE_TYPE::GSA, Status));
}

TEST(ParseStatus, Valid_No_Fix_GSA_Status) {
  const std::string Status = "1";
  const bool Expected = false;

  auto Parser = NMEAParser{};

  EXPECT_EQ(Expected, Parser.ParseStatus(NMEA_MESSAGE_TYPE::GSA, Status));
}

TEST(ParseStatus, Invalid_Empty_Status) {
  const std::string Status = "";
  const bool Expected = false;

  auto Parser = NMEAParser{};

  EXPECT_EQ(Expected, Parser.ParseStatus(NMEA_MESSAGE_TYPE::RMC, Status));
}
}
