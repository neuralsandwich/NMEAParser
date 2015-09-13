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

#include "NMEAParser.h"
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

  auto Parser = NMEAParser{};

  EXPECT_FLOAT_EQ(Expected, Parser.ParsePDOP(PDOP));
}

TEST(ParsePDOP, Invalid_PDOP) {
  const std::string PDOP = "ertyhgf";

  auto Parser = NMEAParser{};

  EXPECT_TRUE(isnan(Parser.ParsePDOP(PDOP)));
}

TEST(ParsePDOP, Empty_PDOP) {
  const std::string PDOP = "";

  auto Parser = NMEAParser{};

  EXPECT_TRUE(isnan(Parser.ParsePDOP(PDOP)));
}
}
