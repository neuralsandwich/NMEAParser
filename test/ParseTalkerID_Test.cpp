//===-- ParseTalkerID_Test.cpp ----------------------------------*- C++ -*-===//
//
// This file is distributed uner the MIT license. See LICENSE.txt for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// Unit tests for ParseTalkerID(const std::string& ID)
///
//===----------------------------------------------------------------------===//
#include "NMEAParser.cpp"
#include "gtest/gtest.h"

namespace NMEA {

TEST(ParseTalkerID, Valid_GPS_TalkerID) {
  const std::string TalkerID = "GPGGA";
  const NMEA_TALKER_ID Expected = NMEA_TALKER_ID::GPS;

  EXPECT_EQ(Expected, ParseTalkerID(TalkerID));
}

TEST(ParseTalkerID, Valid_GLONASS_TalkerID) {
  const std::string TalkerID = "GLSOM";
  const NMEA_TALKER_ID Expected = NMEA_TALKER_ID::GLONASS;

  EXPECT_EQ(Expected, ParseTalkerID(TalkerID));
}

TEST(ParseTalkerID, Invalid_First_Check_TalkerID) {
  const std::string TalkerID = "XX";
  const NMEA_TALKER_ID Expected = NMEA_TALKER_ID::UNKNOWN_TALKER_ID;

  EXPECT_EQ(Expected, ParseTalkerID(TalkerID));
}

TEST(ParseTalkerID, Invalid_Second_Check_TalkerID) {
  const std::string TalkerID = "GX";
  const NMEA_TALKER_ID Expected = NMEA_TALKER_ID::UNKNOWN_TALKER_ID;

  EXPECT_EQ(Expected, ParseTalkerID(TalkerID));
}

TEST(ParseTalkerID, Invalid_Empty_TalkerID) {
  const std::string TalkerID = "";
  const NMEA_TALKER_ID Expected = NMEA_TALKER_ID::UNKNOWN_TALKER_ID;

  EXPECT_EQ(Expected, ParseTalkerID(TalkerID));
}
}
