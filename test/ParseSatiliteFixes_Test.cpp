//===-- ParseSatiliteFixes_Test.cpp -----------------------------*- C++ -*-===//
//
// This file is distributed uner the MIT license. See LICENSE.txt for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// Unit tests for ParseSatiliteFixes(std::string Fixes)
///
//===----------------------------------------------------------------------===//
#include "NMEAParser.cpp"
#include "gtest/gtest.h"

#if 0
Test cases
| N | Fixes     |
|---+-----------|
| 1 | Valid     |
| 2 | Invalid   |
| 3 | Empty     |
#endif

namespace NMEA {
TEST(ParseSatiliteFixes, Valid_Fixes) {
  const std::string Fixes = "10";
  const int Expected = 10;

  EXPECT_EQ(Expected, ParseSatiliteFixes(Fixes));
}

TEST(ParseSatiliteFixes, Invalid_Fixes) {
  const std::string Fixes = "ertyhgf";
  const int Expected = 0;

  EXPECT_EQ(Expected, ParseSatiliteFixes(Fixes));
}

TEST(ParseSatiliteFixes, Empty_Fixes) {
  const std::string Fixes = "";
  const int Expected = 0;

  EXPECT_EQ(Expected, ParseSatiliteFixes(Fixes));
}
}
