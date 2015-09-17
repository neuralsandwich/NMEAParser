//===-- ParseTimeStamp_String_Test.cpp --------------------------*- C++ -*-===//
//
// This file is distributed uner the MIT license. See LICENSE.txt for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// Unit tests for ParseTimeStamp(const std::string *TimeStamp)
///
//===----------------------------------------------------------------------===//
#include "NMEAParser.cpp"
#include "gtest/gtest.h"

#include <ctime>

namespace NMEA {
TEST(FieldParseTests, Valid_ParseTimeStamp_String) {
  const std::string TimeStamp = "092725.00";

  time_t Expected = 0;
  struct tm *TimeInfo;

  std::time(&Expected);
  TimeInfo = gmtime(&Expected);
  TimeInfo->tm_hour = 9;
  TimeInfo->tm_min = 27;
  TimeInfo->tm_sec = 25;
  Expected = mktime(TimeInfo);

  EXPECT_EQ(Expected, ParseTimeStamp(TimeStamp));
}

TEST(FieldParseTests, Invalid_ParseTimeStamp_String) {
  const std::string TimeStamp = "asdfkjasd=234";
  const time_t Expected = -1;

  EXPECT_EQ(Expected, ParseTimeStamp(TimeStamp));
}

TEST(FieldParseTests, Invalid_Range_ParseTimeStamp_String) {
  const std::string TimeStamp = "444294967297";
  const time_t Expected = -1;

  EXPECT_EQ(Expected, ParseTimeStamp(TimeStamp));
}

TEST(FieldParseTests, Invalid_Empty_String_ParseTimeStamp_String) {
  const std::string TimeStamp = "";
  const time_t Expected = -1;

  EXPECT_EQ(Expected, ParseTimeStamp(TimeStamp));
}
}
