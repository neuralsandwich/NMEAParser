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
| N | Type | ModeIndicator |
|---+------+---------------|
| 1 | RMC  | Valid         |
| 2 | RMC  | Valid_No_Fix  |
| 3 | RMC  | Invalid       |
| 4 | GLL  | Valid         |
| 5 | GLL  | Valid_No_Fix  |
| 6 | GLL  | Invalid       |
| 7 | VTG  | Valid         |
| 8 | VTG  | Valid_No_Fix  |
| 9 | VTG  | Invalid       |
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
  const std::string Mode = "N";
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
  const std::string Mode = "N";
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
  const std::string Mode = "N";
  const char Expected = 'N';

  auto Parser = NMEAParser{};

  EXPECT_EQ(Expected, Parser.ParseModeIndicator(NMEA_MESSAGE_TYPE::VTG, Mode));
}
}
