//===-- ParseFixStatus_Test.cpp ---------------------------------*- C++ -*-===//
//
// This file is distributed uner the MIT license. See LICENSE.txt for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// Unit tests for ParseFixStatus(std::string String)
///
//===----------------------------------------------------------------------===//
#include "NMEAParser.h"
#include "gtest/gtest.h"

#if 0
| N | Status |
|---+--------|
| 1 | Valid  |
| 2 | Under  |
| 3 | Over   |
| 4 | Empty  |
#endif

namespace NMEA {
TEST(ParseFixStatus, Valid_Status) {
  const std::string Status = "2";
  const int Expected = 2;

  auto Parser = NMEAParser{};

  EXPECT_EQ(Expected, Parser.ParseFixStatus(Status));
}

TEST(ParseFixStatus, Under_Status) {
  const std::string Status = "0";
  const int Expected = 1;

  auto Parser = NMEAParser{};

  EXPECT_EQ(Expected, Parser.ParseFixStatus(Status));
}

TEST(ParseFixStatus, Over_Status) {
  const std::string Status = "4";
  const int Expected = 1;

  auto Parser = NMEAParser{};

  EXPECT_EQ(Expected, Parser.ParseFixStatus(Status));
}

TEST(ParseFixStatus, Empty_Status) {
  const std::string Status = "";
  const int Expected = 1;

  auto Parser = NMEAParser{};

  EXPECT_EQ(Expected, Parser.ParseFixStatus(Status));
}
}
