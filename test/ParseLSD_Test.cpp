//===-- ParseLSD_Test.cpp ---------------------------------------*- C++ -*-===//
//
// This file is distributed uner the MIT license. See LICENSE.txt for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// Unit tests for ParseLSD(const std::string)
///
//===----------------------------------------------------------------------===//
#include "NMEAParser.cpp"
#include "gtest/gtest.h"

namespace NMEA {
TEST(ParseLSD, Valid_Datum) {
  const std::string Datum = "???";
  const char Expected[4] = "???";

  EXPECT_EQ(*Expected, *ParseLSD(Datum));
}

TEST(ParseLLL, Invalid_Datum) {
  const std::string Datum = "11111111111111111111111111111111111111111111111111111";
  const char Expected[4] = "";

  EXPECT_EQ(Expected[0], ParseLSD(Datum)[0]);
  EXPECT_EQ(Expected[1], ParseLSD(Datum)[1]);
}
  
TEST(ParseLLL, Empty_Datum) {
  const std::string Datum = "";
  const char Expected[4] = "";

  EXPECT_EQ(Expected[0], ParseLSD(Datum)[0]);
  EXPECT_EQ(Expected[1], ParseLSD(Datum)[1]);
}
}
