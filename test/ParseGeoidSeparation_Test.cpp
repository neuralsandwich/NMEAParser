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
#include "NMEAParser.h"
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

  auto Parser = NMEAParser{};

  EXPECT_FLOAT_EQ(Expected, Parser.ParseGeoidSeparation(GeoidSeparation));
}

TEST(ParseGeoidSeparation, Invalid_GeoidSeparation) {
  const std::string GeoidSeparation = "ertyhgf";

  auto Parser = NMEAParser{};

  EXPECT_TRUE(isnan(Parser.ParseGeoidSeparation(GeoidSeparation)));
}

TEST(ParseGeoidSeparation, Empty_GeoidSeparation) {
  const std::string GeoidSeparation = "";

  auto Parser = NMEAParser{};

  EXPECT_TRUE(isnan(Parser.ParseGeoidSeparation(GeoidSeparation)));
}
}
