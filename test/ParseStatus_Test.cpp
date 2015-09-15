//===-- ParseStatus_Test.cpp ------------------------------------*- C++ -*-===//
//
// This file is distributed uner the MIT license. See LICENSE.txt for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// Unit tests for ParseStatus(const std::string &String)
///
//===----------------------------------------------------------------------===//
#include "NMEAParser.h"
#include "gtest/gtest.h"

#if 0
Test Cases
| N | Message          |
|---+------------------|
|   | RMC Valid active |
|   | RMC Valid void   |
|   | RMC Invalid      |
|   | GLL Valid active |
|   | GLL Valid void   |
|   | GLL Invalid      |

#endif

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

TEST(ParseStatus, Invalid_RMC_Status) {
  const std::string Status = "Q";
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

TEST(ParseStatus, Invalid_GLL_Status) {
  const std::string Status = "Q";
  const bool Expected = false;

  auto Parser = NMEAParser{};

  EXPECT_EQ(Expected, Parser.ParseStatus(NMEA_MESSAGE_TYPE::GLL, Status));
}
}
