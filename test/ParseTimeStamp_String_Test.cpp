/**
 * File: ParseTimeStamp_String_Test.cpp
 * Description: Unit tests for
 * NMEA::NMEAParser::ParseTimeStamp(const std::string *TimeStamp)
 */
#include "NMEAParser.h"
#include "gtest/gtest.h"

#include <iostream>
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

  auto Parser = NMEA::NMEAParser();

  EXPECT_EQ(Expected, Parser.ParseTimeStamp(&TimeStamp));
}

TEST(FieldParseTests, Invalid_ParseTimeStamp_String) {
  const std::string TimeStamp = "asdfkjasd=234";
  const time_t Expected = -1;

  auto Parser = NMEA::NMEAParser();

  EXPECT_EQ(Expected, Parser.ParseTimeStamp(&TimeStamp));
}

TEST(FieldParseTests, Invalid_Range_ParseTimeStamp_String) {
  const std::string TimeStamp = "444294967297";
  const time_t Expected = -1;

  auto Parser = NMEA::NMEAParser();

  EXPECT_EQ(Expected, Parser.ParseTimeStamp(&TimeStamp));
}

TEST(FieldParseTests, Invalid_Empty_String_ParseTimeStamp_String) {
  const std::string TimeStamp = "";
  const time_t Expected = -1;

  auto Parser = NMEA::NMEAParser();

  EXPECT_EQ(Expected, Parser.ParseTimeStamp(&TimeStamp));
}
}
