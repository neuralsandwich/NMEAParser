//===-- ParseMSL_Test.cpp ---------------------------------------*- C++ -*-===//
//
// This file is distributed uner the MIT license. See LICENSE.txt for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// Unit tests for ParseMSL(std::string MSL)
///
//===----------------------------------------------------------------------===//
#include "NMEAParser.h"
#include "gtest/gtest.h"

#include <cmath>

#if 0
Test cases
| N | MSL       |
|---+-----------|
| 1 | Valid     |
| 2 | Invalid   |
| 3 | Empty     |
#endif

namespace NMEA {
TEST(ParseMSL, Valid_MSL) {
  const std::string MSL = "499.6";
  const float Expected = 499.6f;

  auto Parser = NMEAParser{};

  EXPECT_FLOAT_EQ(Expected, Parser.ParseMSL(MSL));
}

TEST(ParseMSL, Invalid_MSL) {
  const std::string MSL = "ertyhgf";

  auto Parser = NMEAParser{};

  EXPECT_TRUE(isnan(Parser.ParseMSL(MSL)));
}

TEST(ParseMSL, Empty_MSL) {
  const std::string MSL = "";

  auto Parser = NMEAParser{};

  EXPECT_TRUE(isnan(Parser.ParseMSL(MSL)));
}
}
