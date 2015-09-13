/**
 * File: ParseTalkerID_Test.cpp
 * Description: Unit tests for
 * NMEA::NMEAParser::ParseTalkerID(const std::string& ID) const;
 */
#include "NMEAParser.h"
#include "gtest/gtest.h"

namespace NMEA {

TEST(ParseTalkerID, Valid_GPS_TalkerID) {
  const std::string TalkerID = "GPGGA";
  const NMEA_TALKER_ID Expected = NMEA_TALKER_ID::GPS;

  auto Parser = NMEAParser{};

  EXPECT_EQ(Expected, Parser.ParseTalkerID(TalkerID));
}

TEST(ParseTalkerID, Valid_GLONASS_TalkerID) {
  const std::string TalkerID = "GLSOM";
  const NMEA_TALKER_ID Expected = NMEA_TALKER_ID::GLONASS;

  auto Parser = NMEAParser{};

  EXPECT_EQ(Expected, Parser.ParseTalkerID(TalkerID));
}

TEST(ParseTalkerID, Invalid_First_Check_TalkerID) {
  const std::string TalkerID = "XX";
  const NMEA_TALKER_ID Expected = NMEA_TALKER_ID::UNKNOWN_TALKER_ID;

  auto Parser = NMEAParser{};

  EXPECT_EQ(Expected, Parser.ParseTalkerID(TalkerID));
}

TEST(ParseTalkerID, Invalid_Second_Check_TalkerID) {
  const std::string TalkerID = "GX";
  const NMEA_TALKER_ID Expected = NMEA_TALKER_ID::UNKNOWN_TALKER_ID;

  auto Parser = NMEAParser{};

  EXPECT_EQ(Expected, Parser.ParseTalkerID(TalkerID));
}

TEST(ParseTalkerID, Invalid_Empty_TalkerID) {
  const std::string TalkerID = "";
  const NMEA_TALKER_ID Expected = NMEA_TALKER_ID::UNKNOWN_TALKER_ID;

  auto Parser = NMEAParser{};

  EXPECT_EQ(Expected, Parser.ParseTalkerID(TalkerID));
}
}
