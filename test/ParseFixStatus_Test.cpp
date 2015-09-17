//===-- ParseNavMode_Test.cpp ---------------------------------*- C++ -*-===//
//
// This file is distributed uner the MIT license. See LICENSE.txt for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// Unit tests for ParseNavMode(std::string String)
///
//===----------------------------------------------------------------------===//
#include "NMEAParser.cpp"
#include "gtest/gtest.h"

#if 0
| N | Status |
|---+--------|
| 1 | Valid  |
| 2 | Under  |
| 3 | Over   |
| 4 | Empty  |
#endif

namespace NMEA {
TEST(ParseFixStatus, Valid_No_Fix_Status) {
  const std::string Status = "0";
  const int Expected = 0;

  EXPECT_EQ(Expected, ParseFixStatus(Status));
}

TEST(ParseFixStatus, Valid_Standard_Fix_Status) {
  const std::string Status = "1";
  const int Expected = 1;

  EXPECT_EQ(Expected, ParseFixStatus(Status));
}

TEST(ParseFixStatus, Valid_Differential_Fix_Status) {
  const std::string Status = "2";
  const int Expected = 2;

  EXPECT_EQ(Expected, ParseFixStatus(Status));
}

TEST(ParseFixStatus, Valid_Estimated_DR_Fix_Status) {
  const std::string Status = "6";
  const int Expected = 6;

  EXPECT_EQ(Expected, ParseFixStatus(Status));
}

TEST(ParseFixStatus, Invalid_Fix_Status) {
  const std::string Status = "asdf";
  const int Expected = 0;

  EXPECT_EQ(Expected, ParseFixStatus(Status));
}

TEST(ParseFixStatus, Empty_Fix_Status) {
  const std::string Status = "";
  const int Expected = 0;

  EXPECT_EQ(Expected, ParseFixStatus(Status));
}
}
