//===-- ParseStatus_Test.cpp ------------------------------------*- C++ -*-===//
//
// This file is distributed uner the MIT license. See LICENSE.txt for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// Unit tests for ParseStatus(const std::string &String)
///
//===----------------------------------------------------------------------===//
#include "NMEAParser.cpp"
#include "gtest/gtest.h"

#if 0
Test Cases
| N | Message      |
|---+--------------|
| 1 | Valid active |
| 2 | Valid void   |
| 3 | Invalid      |
| 4 | Empty        |
#endif

namespace NMEA {
TEST(ParseStatus, Valid_Active_Status) {
  const std::string Status = "A";
  const bool Expected = true;

  EXPECT_EQ(Expected, ParseStatus(Status));
}

TEST(ParseStatus, Valid_Void_Status) {
  const std::string Status = "V";
  const bool Expected = false;

  EXPECT_EQ(Expected, ParseStatus(Status));
}

TEST(ParseStatus, Invalid_Status) {
  const std::string Status = "Q";
  const bool Expected = false;

  EXPECT_EQ(Expected, ParseStatus(Status));
}

TEST(ParseStatus, Empty_Status) {
  const std::string Status = "";
  const bool Expected = false;

  EXPECT_EQ(Expected, ParseStatus(Status));
}
}
