/**
 * @file: ParseMagneticVariation_Test.cpp
 * @brief: Unit tests for
 *         ParseMagneticVariation(const std::string &MagneticVariation,
 *                                const std::string &MagneticVariationDirection)
 */

#include "NMEAParser.h"
#include "gtest/gtest.h"

#include <cmath>

/*
 * N | Variation | Direction
 * --|-----------|----------
 * 1 | Valid     | Valid
 * 2 | Invalid   | Valid
 * 3 | Valid     | Invalid
 * 4 | Invalid   | Invalid
 * 5 | Empty     | Valid
 * 6 | Valid     | Empty
 * 7 | Empty     | Empty
 */

namespace NMEA {
TEST(ParseMagneticVariation, Valid_Variable_Valid_North_Direction) {
  const std::string Variation = "0.001";
  const std::string Direction = "E";
  const float Expected = 0.001f;

  auto Parser = NMEAParser{};

  EXPECT_FLOAT_EQ(Expected,
                  Parser.ParseMagneticVariation(Variation, Direction));
}

TEST(ParseMagneticVariation, Valid_Variable_Valid_South_Direction) {
  const std::string Variation = "0.001";
  const std::string Direction = "W";
  const float Expected = -0.001f;

  auto Parser = NMEAParser{};

  EXPECT_FLOAT_EQ(Expected,
                  Parser.ParseMagneticVariation(Variation, Direction));
}

TEST(ParseMagneticVariation, Invalid_Variable_Valid_Direction) {
  const std::string Variation = "asdf";
  const std::string Direction = "E";

  auto Parser = NMEAParser{};

  EXPECT_TRUE(isnan(Parser.ParseMagneticVariation(Variation, Direction)));
}

TEST(ParseMagneticVariation, Valid_Variable_Invalid_Direction) {
  const std::string Variation = "0.001";
  const std::string Direction = "J";

  auto Parser = NMEAParser{};

  EXPECT_TRUE(isnan(Parser.ParseMagneticVariation(Variation, Direction)));
}

TEST(ParseMagneticVariation, Invalid_Variable_Invalid_Direction) {
  const std::string Variation = "sdfg";
  const std::string Direction = "J";

  auto Parser = NMEAParser{};

  EXPECT_TRUE(isnan(Parser.ParseMagneticVariation(Variation, Direction)));
}

TEST(ParseMagneticVariation, Empty_Variable_Valid_Direction) {
  const std::string Variation = "";
  const std::string Direction = "W";

  auto Parser = NMEAParser{};

  EXPECT_TRUE(isnan(Parser.ParseMagneticVariation(Variation, Direction)));
}

#if 0
TEST(ParseMagneticVariation, Valid_Variable_Empty_Direction) {

}

TEST(ParseMagneticVariation, Empty_Variable_EmptyDirection) {

}
#endif
}
