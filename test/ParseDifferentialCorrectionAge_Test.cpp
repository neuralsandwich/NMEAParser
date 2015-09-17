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
#include "NMEAParser.cpp"
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

  EXPECT_FLOAT_EQ(Expected,
                  ParseDifferentialCorrectionAge(CorrectionAge));
}

TEST(ParseDifferentialCorrectionAge, Invalid_CorrectionAge) {
  const std::string CorrectionAge = "ertyhgf";

  EXPECT_TRUE(isnan(ParseDifferentialCorrectionAge(CorrectionAge)));
}

TEST(ParseDifferentialCorrectionAge, Empty_CorrectionAge) {
  const std::string CorrectionAge = "";

  EXPECT_TRUE(isnan(ParseDifferentialCorrectionAge(CorrectionAge)));
}
}
