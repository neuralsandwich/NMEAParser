//===-- ParseSpeed_Test.cpp -------------------------------------*- C++ -*-===//
//
// This file is distributed uner the MIT license. See LICENSE.txt for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// Unit tests for ParseString(const std::string &Speed)
///
//===----------------------------------------------------------------------===//
#include "NMEAParser.cpp"
#include "gtest/gtest.h"

#include <cmath>

namespace NMEA {
TEST(ParseSpeed, Valid_Speed) {
  const std::string Speed = "0.004";
  const float Expected = 0.004f;

  EXPECT_FLOAT_EQ(Expected, ParseSpeed(Speed));
}

TEST(ParseSpeed, Invalid_Speed) {
  const std::string Speed = "asdf";

  EXPECT_TRUE(isnan(ParseSpeed(Speed)));
}

TEST(ParseSpeed, Empty_Speed) {
  const std::string Speed = "";

  EXPECT_TRUE(isnan(ParseSpeed(Speed)));
}
}
