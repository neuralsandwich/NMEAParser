//===-- ParseCOGM_Test.cpp --------------------------------------*- C++ -*-===//
//
// This file is distributed uner the MIT license. See LICENSE.txt for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// Unit tests for ParseCOGM(std::string COGM)
///
//===----------------------------------------------------------------------===//
#include "NMEAParser.cpp"
#include "gtest/gtest.h"

#include <cmath>

#if 0
Test cases
| N | COGM    |
|---+---------|
| 1 | Valid   |
| 2 | Invalid |
| 3 | Empty   |
#endif

namespace NMEA {
TEST(ParseCOGM, Valid_COGM) {
  const std::string COGM = "77.52";
  const float Expected = 77.52f;

  EXPECT_FLOAT_EQ(Expected, ParseCOGM(COGM));
}

TEST(ParseCOGM, Invalid_COGM) {
  const std::string COGM = "ertyhgf";

  EXPECT_TRUE(isnan(ParseCOGM(COGM)));
}

TEST(ParseCOGM, Empty_COGM) {
  const std::string COGM = "";

  EXPECT_TRUE(isnan(ParseCOGM(COGM)));
}
}
