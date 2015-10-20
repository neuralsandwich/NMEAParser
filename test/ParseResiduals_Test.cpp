//===-- ParseResiduals_Test.cpp ---------------------------------*- C++ -*-===//
//
// This file is distributed uner the MIT license. See LICENSE.txt for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// Unit test for ParseResiduals function
///
//===----------------------------------------------------------------------===//
#include "NMEAParser.cpp"
#include "gtest/gtest.h"

#include <cmath>

namespace NMEA {
TEST(ParseResiduals, Valid_Residuals) {
  const std::vector<std::string> Residuals{"0.54",  "0.83",  "1.00",
                                           "1.02",  "-2.12", "2.64",
                                           "-0.71", "-1.18", "0.25"};
  const std::vector<float> Expected{0.54f,  0.83f,  1.00f, 1.02f, -2.12f, 2.64f,
                                    -0.71f, -1.18f, 0.25f, 0.0f,  0.0f,   0.0f};

  auto Start = Residuals.begin();
  auto End = Residuals.end();

  auto Actual = ParseResiduals(Start, End);

  for (size_t i = 0; i < Expected.size(); ++i) {
    EXPECT_FLOAT_EQ(Expected[i], Actual[i]);
  }
}

TEST(ParseResiduals, Invalid_Residuals) {
  const std::vector<std::string> Residuals{"a", "b", "asd", "ten"};

  auto Start = Residuals.begin();
  auto End = Residuals.end();

  auto Actual = ParseResiduals(Start, End);

  for (size_t i = 0; i < Residuals.size(); ++i) {
    EXPECT_TRUE(isnan(Actual[i]));
  }
}

TEST(ParseResiduals, Empty_Residuals) {
  const std::vector<std::string> Residuals{"", ""};

  auto Start = Residuals.begin();
  auto End = Residuals.end();

  auto Actual = ParseResiduals(Start, End);

  for (size_t i = 0; i < Residuals.size(); ++i) {
    EXPECT_TRUE(isnan(Actual[i]));
  }
}
};
