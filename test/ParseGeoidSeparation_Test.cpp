//===-- ParseGeoidSeparation_Test.cpp ---------------------------*- C++ -*-===//
//
// This file is distributed uner the MIT license. See LICENSE.txt for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// Unit tests for ParseGeoidSeparation(std::string GeoidSeparation)
///
//===----------------------------------------------------------------------===//
#include "NMEAParser.cpp"
#include "gtest/gtest.h"

#include <cmath>

#if 0
Test cases
| N | GeoidSeparation |
|---+-----------------|
| 1 | Valid           |
| 2 | Invalid         |
| 3 | Empty           |
#endif

namespace NMEA {
TEST(ParseGeoidSeparation, Valid_GeoidSeparation) {
  const std::string GeoidSeparation = "48.0";
  const float Expected = 48.0f;

  EXPECT_FLOAT_EQ(Expected, ParseGeoidSeparation(GeoidSeparation));
}

TEST(ParseGeoidSeparation, Invalid_GeoidSeparation) {
  const std::string GeoidSeparation = "ertyhgf";

  EXPECT_TRUE(isnan(ParseGeoidSeparation(GeoidSeparation)));
}

TEST(ParseGeoidSeparation, Empty_GeoidSeparation) {
  const std::string GeoidSeparation = "";

  EXPECT_TRUE(isnan(ParseGeoidSeparation(GeoidSeparation)));
}
}
