//===-- ParseCOGT_Test.cpp --------------------------------------*- C++ -*-===//
//
// This file is distributed uner the MIT license. See LICENSE.txt for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// Unit tests for ParseCOGT(std::string COGT)
///
//===----------------------------------------------------------------------===//
#include "NMEAParser.cpp"
#include "gtest/gtest.h"

#include <cmath>

#if 0
Test cases
| N | COGT    |
|---+---------|
| 1 | Valid   |
| 2 | Invalid |
| 3 | Empty   |
#endif

namespace NMEA {
TEST(ParseCOGT, Valid_COGT) {
  const std::string COGT = "77.52";
  const float Expected = 77.52f;

  EXPECT_FLOAT_EQ(Expected, ParseCOGT(COGT));
}

TEST(ParseCOGT, Invalid_COGT) {
  const std::string COGT = "ertyhgf";

  EXPECT_TRUE(isnan(ParseCOGT(COGT)));
}

TEST(ParseCOGT, Empty_COGT) {
  const std::string COGT = "";
  const int Expected = 0;

  EXPECT_TRUE(isnan(ParseCOGT(COGT)));
}
}
