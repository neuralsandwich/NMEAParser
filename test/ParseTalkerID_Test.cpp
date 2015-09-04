/**
 * File: ParseTimeStamp_String_String_Test.cpp
 * Description: Unit tests for
 * NMEA::NMEAParser::ParseTimeStamp(const std::string *TimeStamp,
 *                                  const std::string *DateStamp)
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
  
}
