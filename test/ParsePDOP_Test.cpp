//===-- ParsePDOP_Test.cpp --------------------------------------*- C++ -*-===//
//
// This file is distributed uner the MIT license. See LICENSE.txt for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// Unit tests for ParsePDOP()
///
//===----------------------------------------------------------------------===//
#include "NMEAParser.cpp"
#include "gtest/gtest.h"

#include <cmath>

#if 0
Test cases
| N | PDOP    |
|---+---------|
| 1 | Valid   |
| 2 | Invalid |
| 3 | Empty   |
#endif

namespace NMEA {
TEST(ParsePDOP, Valid_PDOP) {
  const std::string PDOP = "1.54";
  const float Expected = 1.54f;

  EXPECT_FLOAT_EQ(Expected, ParsePDOP(PDOP));
}

TEST(ParsePDOP, Invalid_PDOP) {
  const std::string PDOP = "ertyhgf";

  EXPECT_TRUE(isnan(ParsePDOP(PDOP)));
}

TEST(ParsePDOP, Empty_PDOP) {
  const std::string PDOP = "";

  EXPECT_TRUE(isnan(ParsePDOP(PDOP)));
}
}
