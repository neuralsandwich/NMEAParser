//===-- ParseSatiliteFixes_Test.cpp -----------------------------*- C++ -*-===//
//
// This file is distributed uner the MIT license. See LICENSE.txt for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// Unit test for ParseSatiliteFixes
///
//===----------------------------------------------------------------------===//

#include "NMEAParser.h"
#include "gtest/gtest.h"

#include <cmath>

#if 0
Test cases
| N | Variation |
|---+-----------|
| 1 | Valid     |
| 2 | Invalid   |
| 3 | Empty     |
#endif

namespace NMEA {
TEST(ParseSatiliteFixes, Valid_Fixes) {
  const std::string Fixes = "10";
  const int Expected = 10;

  auto Parser = NMEAParser{};

  EXPECT_EQ(Expected, Parser.ParseSatiliteFixes(Fixes));
}

TEST(ParseSatiliteFixes, Invalid_Fixes) {
  const std::string Fixes = "ertyhgf";
  const int Expected = 0;

  auto Parser = NMEAParser{};

  EXPECT_EQ(Expected, Parser.ParseSatiliteFixes(Fixes));
}

TEST(ParseSatiliteFixes, Empty_Fixes) {
  const std::string Fixes = "";
  const int Expected = 0;

  auto Parser = NMEAParser{};

  EXPECT_EQ(Expected, Parser.ParseSatiliteFixes(Fixes));
}
}
