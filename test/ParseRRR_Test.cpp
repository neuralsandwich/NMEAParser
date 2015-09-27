//===-- ParseRRR_Test.cpp ---------------------------------------*- C++ -*-===//
//
// This file is distributed uner the MIT license. See LICENSE.txt for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// Unit tests for ParseRRR(const std::string)
///
//===----------------------------------------------------------------------===//
#include "NMEAParser.cpp"
#include "gtest/gtest.h"

namespace NMEA {
TEST(ParseRRR, Valid_Datum) {
  const std::string Datum = "W84";
  const char Expected[4] = "W84";

  EXPECT_EQ(*Expected, *ParseRRR(Datum));
}

TEST(ParseRRR, Invalid_Datum) {
  const std::string Datum = "I*U";
  const char Expected[4] = "999";

  EXPECT_EQ(*Expected, *ParseRRR(Datum));
}
  
TEST(ParseRRR, Empty_Datum) {
  const std::string Datum = "";
  const char Expected[4] = "999";

  EXPECT_EQ(*Expected, *ParseRRR(Datum));
}
}
