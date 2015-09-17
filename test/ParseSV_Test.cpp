//===-- ParseSV_Test.cpp ----------------------------------------*- C++ -*-===//
//
// This file is distributed uner the MIT license. See LICENSE.txt for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// Unit tests for ParseSV(std::vector<std::string>::iterator Start,
///                        std::vector<std::string>::iterator End)
///
//===----------------------------------------------------------------------===//
#include "NMEAParser.cpp"
#include "gtest/gtest.h"

#if 0
Test Cases
| N | Case    |
|---+---------|
|   | Valid   |
|   | Invalid |
|   | Mixed   |
|   | Empty   |
#endif

namespace NMEA {
TEST(ParseSV, Valid_Array) {
  std::vector<std::string> SVs = {"3",  "23", "29", "07", "08",
                                  "09", "18", "26", "28"};
  std::vector<int> Expected = {3, 23, 29, 7, 8, 9, 18, 26, 28};

  int *Result = ParseSV(SVs.begin(), SVs.end());

  for (unsigned int i = 0; i < SVs.size(); i++) {
    EXPECT_EQ(Expected[i], Result[i]);
  }
}

TEST(ParseSV, Invalid_Array) {
  std::vector<std::string> SVs = {"b", "gr", "[]"};
  std::vector<int> Expected = {0, 0, 0};

  int *Result = ParseSV(SVs.begin(), SVs.end());

  for (unsigned int i = 0; i < SVs.size(); i++) {
    EXPECT_EQ(Expected[i], Result[i]);
  }
}

TEST(ParseSV, Mixed_Array) {
  std::vector<std::string> SVs = {"b", "7", "gr", "[]", "100"};
  std::vector<int> Expected = {0, 7, 0, 0, 100};

  int *Result = ParseSV(SVs.begin(), SVs.end());

  for (unsigned int i = 0; i < SVs.size(); i++) {
    EXPECT_EQ(Expected[i], Result[i]);
  }
}

TEST(ParseSV, Empty_Array) {
  std::vector<std::string> SVs = {};
  std::vector<int> Expected = {};

  int *Result = ParseSV(SVs.begin(), SVs.end());

  for (unsigned int i = 0; i < SVs.size(); i++) {
    EXPECT_EQ(Expected[i], Result[i]);
  }
}
}
