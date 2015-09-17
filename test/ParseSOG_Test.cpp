//===-- ParseSOG_Test.cpp --------------------------------------*- C++ -*-===//
//
// This file is distributed uner the MIT license. See LICENSE.txt for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// Unit tests for ParseSOG(std::string SOG)
///
//===----------------------------------------------------------------------===//
#include "NMEAParser.cpp"
#include "gtest/gtest.h"

#include <cmath>

#if 0
Test cases
| N | SOG    |
|---+---------|
| 1 | Valid   |
| 2 | Invalid |
| 3 | Empty   |
#endif

namespace NMEA {
TEST(ParseSOG, Valid_SOG) {
  const std::string SOG = "77.52";
  const float Expected = 77.52f;

  EXPECT_FLOAT_EQ(Expected, ParseSOG(SOG));
}

TEST(ParseSOG, Invalid_SOG) {
  const std::string SOG = "ertyhgf";

  EXPECT_TRUE(isnan(ParseSOG(SOG)));
}

TEST(ParseSOG, Empty_SOG) {
  const std::string SOG = "";

  EXPECT_TRUE(isnan(ParseSOG(SOG)));
}
}
