//===-- ParseNavMode_Test.cpp ---------------------------------*- C++ -*-===//
//
// This file is distributed uner the MIT license. See LICENSE.txt for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// Unit tests for ParseNavMode(std::string String)
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
TEST(ParseNavMode, Valid_Status) {
  const std::string Status = "2";
  const int Expected = 2;

  auto Parser = NMEAParser{};

  EXPECT_EQ(Expected, Parser.ParseNavMode(Status));
}

TEST(ParseNavMode, Under_Status) {
  const std::string Status = "0";
  const int Expected = 1;

  auto Parser = NMEAParser{};

  EXPECT_EQ(Expected, Parser.ParseNavMode(Status));
}

TEST(ParseNavMode, Over_Status) {
  const std::string Status = "4";
  const int Expected = 1;

  auto Parser = NMEAParser{};

  EXPECT_EQ(Expected, Parser.ParseNavMode(Status));
}

TEST(ParseNavMode, Empty_Status) {
  const std::string Status = "";
  const int Expected = 1;

  auto Parser = NMEAParser{};

  EXPECT_EQ(Expected, Parser.ParseNavMode(Status));
}
}
