/**
 * File: ParseTimeStamp_String_String_Test.cpp
 * Description: Unit tests for
 * NMEA::NMEAParser::ParseTimeStamp(const std::string *TimeStamp,
 *                                  const std::string *DateStamp)
 */
#include "NMEAParser.h"
#include "gtest/gtest.h"

#include <iostream>
#include <ctime>

namespace NMEA {
TEST(ParseTimeStamp_String_String, Valid_TimeStamp_Valid_DateStamp) {
  const std::string TimeStamp = "092725.00";
  const std::string DateStamp = "01012000";

  time_t Expected = 0;
  struct tm *TimeInfo;

  std::time(&Expected);
  TimeInfo = gmtime(&Expected);
  TimeInfo->tm_hour = 9;
  TimeInfo->tm_min = 27;
  TimeInfo->tm_sec = 25;
  TimeInfo->tm_mday = 1;
  TimeInfo->tm_mon = 0;
  TimeInfo->tm_year = 100;
  Expected = mktime(TimeInfo);

  auto Parser = NMEA::NMEAParser();

  EXPECT_EQ(Expected, Parser.ParseTimeStamp(&TimeStamp, &DateStamp));
}

TEST(ParseTimeStamp_String_String, Invalid_TimeStamp_Valid_DateStamp) {
  const std::string TimeStamp = "asdfasdff";
  const std::string DateStamp = "01012000";

  time_t Expected = -1;

  auto Parser = NMEA::NMEAParser();

  EXPECT_EQ(Expected, Parser.ParseTimeStamp(&TimeStamp, &DateStamp));
}

TEST(ParseTimeStamp_String_String, Valid_TimeStamp_Invalid_DateStamp) {
  const std::string TimeStamp = "232323.00";
  const std::string DateStamp = "asdfasdf";

  time_t Expected = -1;

  auto Parser = NMEA::NMEAParser();

  EXPECT_EQ(Expected, Parser.ParseTimeStamp(&TimeStamp, &DateStamp));
}

TEST(ParseTimeStamp_String_String, Invalid_TimeStamp_Invalid_DateStamp) {
  const std::string TimeStamp = "opiigjgjg";
  const std::string DateStamp = "asdfasdf";

  time_t Expected = -1;

  auto Parser = NMEA::NMEAParser();

  EXPECT_EQ(Expected, Parser.ParseTimeStamp(&TimeStamp, &DateStamp));
}

TEST(ParseTimeStamp_String_String,
     Invalid_Long_Range_TimeStamp_Valid_DateStamp) {
  const std::string TimeStamp = "0123456789789789";
  const std::string DateStamp = "02022002";

  time_t Expected = -1;

  auto Parser = NMEA::NMEAParser();

  EXPECT_EQ(Expected, Parser.ParseTimeStamp(&TimeStamp, &DateStamp));
}

TEST(ParseTimeStamp_String_String,
     Invalid_Short_Range_TimeStamp_Valid_DateStamp) {
  const std::string TimeStamp = "01023";
  const std::string DateStamp = "03032003";

  time_t Expected = -1;

  auto Parser = NMEA::NMEAParser();

  EXPECT_EQ(Expected, Parser.ParseTimeStamp(&TimeStamp, &DateStamp));
}

TEST(ParseTimeStamp_String_String,
     Valid_TimeStamp_Invalid_Long_Range_DateStamp) {
  const std::string TimeStamp = "010230.00";
  const std::string DateStamp = "040420040";

  time_t Expected = -1;

  auto Parser = NMEA::NMEAParser();

  EXPECT_EQ(Expected, Parser.ParseTimeStamp(&TimeStamp, &DateStamp));
}

TEST(ParseTimeStamp_String_String,
     Valid_TimeStamp_Invalid_Short_Range_DateStamp) {
  const std::string TimeStamp = "010230.00";
  const std::string DateStamp = "0404200";

  time_t Expected = -1;

  auto Parser = NMEA::NMEAParser();

  EXPECT_EQ(Expected, Parser.ParseTimeStamp(&TimeStamp, &DateStamp));
}

TEST(ParseTimeStamp_String_String,
     Invalid_Short_Range_TimeStamp_Invalid_Short_Range_DateStamp) {
  const std::string TimeStamp = "01.00";
  const std::string DateStamp = "0404200";

  time_t Expected = -1;

  auto Parser = NMEA::NMEAParser();

  EXPECT_EQ(Expected, Parser.ParseTimeStamp(&TimeStamp, &DateStamp));
}

TEST(ParseTimeStamp_String_String,
     Invalid_Long_Range_TimeStamp_Invalid_Long_Range_DateStamp) {
  const std::string TimeStamp = "060606.06006060";
  const std::string DateStamp = "0404200400000";

  time_t Expected = -1;

  auto Parser = NMEA::NMEAParser();

  EXPECT_EQ(Expected, Parser.ParseTimeStamp(&TimeStamp, &DateStamp));
}

TEST(ParseTimeStamp_String_String, Invalid_Before_Epoch) {
  const std::string TimeStamp = "235959.00";
  const std::string DateStamp = "31121969";

  time_t Expected = -1;

  auto Parser = NMEA::NMEAParser();

  EXPECT_EQ(Expected, Parser.ParseTimeStamp(&TimeStamp, &DateStamp));
}
}
