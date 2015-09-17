//===-- ParseLLL_Test.cpp ---------------------------------------*- C++ -*-===//
//
// This file is distributed uner the MIT license. See LICENSE.txt for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// Unit tests for ParseLLL(const std::string)
///
//===----------------------------------------------------------------------===//
#include "NMEAParser.cpp"
#include "gtest/gtest.h"

namespace NMEA {
TEST(ParseLLL, Valid_Datum) {
  const std::string Datum = "W84";
  const char Expected[4] = "W84";

  EXPECT_EQ(*Expected, *ParseLLL(Datum));
}

TEST(ParseLLL, Invalid_Datum) {
  const std::string Datum = "I*U";
  const char Expected[4] = "999";

  EXPECT_EQ(*Expected, *ParseLLL(Datum));
}
  
TEST(ParseLLL, Empty_Datum) {
  const std::string Datum = "";
  const char Expected[4] = "999";

  EXPECT_EQ(*Expected, *ParseLLL(Datum));
}
}
