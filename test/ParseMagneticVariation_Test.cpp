//===-- ParseMagneticVariation_Test.cpp -------------------------*- C++ -*-===//
//
// This file is distributed uner the MIT license. See LICENSE.txt for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
///
/// Unit tests for ParseMagenetic Variation (const std::string
///                                          &MagneticVaration,
///                                          const std::string
///                                          &MagneticVariationDirection)
///
//===----------------------------------------------------------------------===//
#include "NMEAParser.cpp"
#include "gtest/gtest.h"

#include <cmath>

#if 0
Test cases
| N | Variation | Direction |
|---+-----------+-----------|
| 1 | Valid     | Valid     |
| 2 | Invalid   | Valid     |
| 3 | Valid     | Invalid   |
| 4 | Invalid   | Invalid   |
| 5 | Empty     | Valid     |
| 6 | Valid     | Empty     |
| 7 | Empty     | Empty     |
#endif

namespace NMEA {
TEST(ParseMagneticVariation, Valid_Variable_Valid_North_Direction) {
  const std::string Variation = "0.001";
  const std::string Direction = "E";
  const float Expected = 0.001f;

  EXPECT_FLOAT_EQ(Expected,
                  ParseMagneticVariation(Variation, Direction));
}

TEST(ParseMagneticVariation, Valid_Variable_Valid_South_Direction) {
  const std::string Variation = "0.001";
  const std::string Direction = "W";
  const float Expected = -0.001f;

  EXPECT_FLOAT_EQ(Expected,
                  ParseMagneticVariation(Variation, Direction));
}

TEST(ParseMagneticVariation, Invalid_Variable_Valid_Direction) {
  const std::string Variation = "asdf";
  const std::string Direction = "E";

  EXPECT_TRUE(isnan(ParseMagneticVariation(Variation, Direction)));
}

TEST(ParseMagneticVariation, Valid_Variable_Invalid_Direction) {
  const std::string Variation = "0.001";
  const std::string Direction = "J";

  EXPECT_TRUE(isnan(ParseMagneticVariation(Variation, Direction)));
}

TEST(ParseMagneticVariation, Invalid_Variable_Invalid_Direction) {
  const std::string Variation = "sdfg";
  const std::string Direction = "J";

  EXPECT_TRUE(isnan(ParseMagneticVariation(Variation, Direction)));
}

TEST(ParseMagneticVariation, Empty_Variable_Valid_Direction) {
  const std::string Variation = "";
  const std::string Direction = "W";

  EXPECT_TRUE(isnan(ParseMagneticVariation(Variation, Direction)));
}

TEST(ParseMagneticVariation, Valid_Variable_Empty_Direction) {
  const std::string Variation = "0.001";
  const std::string Direction = "";

  EXPECT_TRUE(isnan(ParseMagneticVariation(Variation, Direction)));
}

TEST(ParseMagneticVariation, Empty_Variable_EmptyDirection) {
  const std::string Variation = "";
  const std::string Direction = "";

  EXPECT_TRUE(isnan(ParseMagneticVariation(Variation, Direction)));
}
}
