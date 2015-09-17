//===-- ParseHDOP_Test.cpp --------------------------------------*- C++ -*-===//
//
// This file is distributed uner the MIT license. See LICENSE.txt for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// Unit tests for ParseHDOP(std::string HDOP)
///
//===----------------------------------------------------------------------===//
#include "NMEAParser.cpp"
#include "gtest/gtest.h"

#include <cmath>

#if 0
Test cases
| N | HDOP      |
|---+-----------|
| 1 | Valid     |
| 2 | Invalid   |
| 3 | Empty     |
#endif

namespace NMEA {
TEST(ParseHDOP, Valid_Fixes) {
  const std::string Fixes = "1.01";
  const float Expected = 1.01f;

  EXPECT_FLOAT_EQ(Expected, ParseHDOP(Fixes));
}

TEST(ParseHDOP, Invalid_Fixes) {
  const std::string Fixes = "ertyhgf";

  EXPECT_TRUE(isnan(ParseHDOP(Fixes)));
}

TEST(ParseHDOP, Empty_Fixes) {
  const std::string Fixes = "";

  EXPECT_TRUE(isnan(ParseHDOP(Fixes)));
}
}
