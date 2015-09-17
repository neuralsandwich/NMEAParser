//===-- ParseVDOP_Test.cpp --------------------------------------*- C++ -*-===//
//
// This file is distributed uner the MIT license. See LICENSE.txt for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// Unit tests for ParseVDOP()
///
//===----------------------------------------------------------------------===//
#include "NMEAParser.cpp"
#include "gtest/gtest.h"

#include <cmath>

#if 0
Test cases
| N | VDOP    |
|---+---------|
| 1 | Valid   |
| 2 | Invalid |
| 3 | Empty   |
#endif

namespace NMEA {
TEST(ParseVDOP, Valid_VDOP) {
  const std::string VDOP = "1.54";
  const float Expected = 1.54f;

  EXPECT_FLOAT_EQ(Expected, ParseVDOP(VDOP));
}

TEST(ParseVDOP, Invalid_VDOP) {
  const std::string VDOP = "ertyhgf";

  EXPECT_TRUE(isnan(ParseVDOP(VDOP)));
}

TEST(ParseVDOP, Empty_VDOP) {
  const std::string VDOP = "";

  EXPECT_TRUE(isnan(ParseVDOP(VDOP)));
}
}
