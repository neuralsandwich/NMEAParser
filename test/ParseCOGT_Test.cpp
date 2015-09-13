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

#include "NMEAParser.h"
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

  auto Parser = NMEAParser{};

  EXPECT_FLOAT_EQ(Expected, Parser.ParseCOGT(COGT));
}

TEST(ParseCOGT, Invalid_COGT) {
  const std::string COGT = "ertyhgf";

  auto Parser = NMEAParser{};

  EXPECT_TRUE(isnan(Parser.ParseCOGT(COGT)));
}

TEST(ParseCOGT, Empty_COGT) {
  const std::string COGT = "";
  const int Expected = 0;

  auto Parser = NMEAParser{};

  EXPECT_TRUE(isnan(Parser.ParseCOGT(COGT)));
}
}
