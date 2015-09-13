//===-- ParseDifferentialCorrectionAge_Test.cpp -----------------*- C++ -*-===//
//
// This file is distributed uner the MIT license. See LICENSE.txt for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// Unit tests for ParseDifferentialCorrectionAge(std::string CorrectionAge)
///
//===----------------------------------------------------------------------===//
#include "NMEAParser.h"
#include "gtest/gtest.h"

#include <cmath>

#if 0
Test cases
| N | CorrectionAge |
|---+---------------|
| 1 | Valid         |
| 2 | Invalid       |
| 3 | Empty         |
#endif

namespace NMEA {
TEST(ParseDifferentialCorrectionAge, Valid_CorrectionAge) {
  const std::string CorrectionAge = "48.0";
  const float Expected = 48.0f;

  auto Parser = NMEAParser{};

  EXPECT_FLOAT_EQ(Expected,
                  Parser.ParseDifferentialCorrectionAge(CorrectionAge));
}

TEST(ParseDifferentialCorrectionAge, Invalid_CorrectionAge) {
  const std::string CorrectionAge = "ertyhgf";

  auto Parser = NMEAParser{};

  EXPECT_TRUE(isnan(Parser.ParseDifferentialCorrectionAge(CorrectionAge)));
}

TEST(ParseDifferentialCorrectionAge, Empty_CorrectionAge) {
  const std::string CorrectionAge = "";

  auto Parser = NMEAParser{};

  EXPECT_TRUE(isnan(Parser.ParseDifferentialCorrectionAge(CorrectionAge)));
}
}
