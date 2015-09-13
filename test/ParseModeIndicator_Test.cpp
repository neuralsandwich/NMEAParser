//===-- ParseModeIndicator_Test.cpp -----------------------------*- C++ -*-===//
//
// This file is distributed uner the MIT license. See LICENSE.txt for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// Unit tests for ParseModeIndicator(std::string ModeIndicator)
///
//===----------------------------------------------------------------------===//
#include "NMEAParser.h"
#include "gtest/gtest.h"

#if 0
|  N | Type | ModeIndicator |
|----+------+---------------|
|  1 | RMC  | Valid         |
|  2 | RMC  | Valid_No_Fix  |
|  3 | RMC  | Invalid       |
|  4 | RMC  | Empty         |
|  5 | GLL  | Valid         |
|  6 | GLL  | Valid_No_Fix  |
|  7 | GLL  | Invalid       |
|  8 | GLL  | Empty         |
|  9 | VTG  | Valid         |
| 10 | VTG  | Valid_No_Fix  |
| 11 | VTG  | Invalid       |
| 12 | VTG  | Empty         |
#endif

namespace NMEA {
TEST(ParseModeIndicator, Valid_Fix_Mode_RMC) {
  const std::string Mode = "A";
  const char Expected = 'A';

  auto Parser = NMEAParser{};

  EXPECT_EQ(Expected, Parser.ParseModeIndicator(NMEA_MESSAGE_TYPE::RMC, Mode));
}

TEST(ParseModeIndicator, Valid_No_Fix_Mode_RMC) {
  const std::string Mode = "N";
  const char Expected = 'N';

  auto Parser = NMEAParser{};

  EXPECT_EQ(Expected, Parser.ParseModeIndicator(NMEA_MESSAGE_TYPE::RMC, Mode));
}

TEST(ParseModeIndicator, Invalid_Mode_RMC) {
  const std::string Mode = "P";
  const char Expected = 'N';

  auto Parser = NMEAParser{};

  EXPECT_EQ(Expected, Parser.ParseModeIndicator(NMEA_MESSAGE_TYPE::RMC, Mode));
}

TEST(ParseModeIndicator, Empty_Mode_RMC) {
  const std::string Mode = "";
  const char Expected = 'N';

  auto Parser = NMEAParser{};

  EXPECT_EQ(Expected, Parser.ParseModeIndicator(NMEA_MESSAGE_TYPE::RMC, Mode));
}

TEST(ParseModeIndicator, Valid_Fix_Mode_GLL) {
  const std::string Mode = "A";
  const char Expected = 'A';

  auto Parser = NMEAParser{};

  EXPECT_EQ(Expected, Parser.ParseModeIndicator(NMEA_MESSAGE_TYPE::GLL, Mode));
}

TEST(ParseModeIndicator, Valid_No_Fix_Mode_GLL) {
  const std::string Mode = "N";
  const char Expected = 'N';

  auto Parser = NMEAParser{};

  EXPECT_EQ(Expected, Parser.ParseModeIndicator(NMEA_MESSAGE_TYPE::GLL, Mode));
}

TEST(ParseModeIndicator, Invalid_Mode_GLL) {
  const std::string Mode = "Z";
  const char Expected = 'N';

  auto Parser = NMEAParser{};

  EXPECT_EQ(Expected, Parser.ParseModeIndicator(NMEA_MESSAGE_TYPE::GLL, Mode));
}

TEST(ParseModeIndicator, Empty_Mode_GLL) {
  const std::string Mode = "";
  const char Expected = 'N';

  auto Parser = NMEAParser{};

  EXPECT_EQ(Expected, Parser.ParseModeIndicator(NMEA_MESSAGE_TYPE::GLL, Mode));
}

TEST(ParseModeIndicator, Valid_Fix_Mode_VTG) {
  const std::string Mode = "A";
  const char Expected = 'A';

  auto Parser = NMEAParser{};

  EXPECT_EQ(Expected, Parser.ParseModeIndicator(NMEA_MESSAGE_TYPE::VTG, Mode));
}

TEST(ParseModeIndicator, Valid_No_Fix_Mode_VTG) {
  const std::string Mode = "N";
  const char Expected = 'N';

  auto Parser = NMEAParser{};

  EXPECT_EQ(Expected, Parser.ParseModeIndicator(NMEA_MESSAGE_TYPE::VTG, Mode));
}

TEST(ParseModeIndicator, Invalid_Mode_VTG) {
  const std::string Mode = "G";
  const char Expected = 'N';

  auto Parser = NMEAParser{};

  EXPECT_EQ(Expected, Parser.ParseModeIndicator(NMEA_MESSAGE_TYPE::VTG, Mode));
}

TEST(ParseModeIndicator, Empty_Mode_VTG) {
  const std::string Mode = "";
  const char Expected = 'N';

  auto Parser = NMEAParser{};

  EXPECT_EQ(Expected, Parser.ParseModeIndicator(NMEA_MESSAGE_TYPE::VTG, Mode));
}
}
