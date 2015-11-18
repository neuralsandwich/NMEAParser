//===-- GSTMessageParse_Test.cpp --------------------------------*- C++ -*-===//
//
// This file is distributed uner the MIT license. See LICENSE.txt for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// Functional tests for Parsing GST messages
///
//===----------------------------------------------------------------------===//
#include "NMEAParser.h"
#include "gtest/gtest.h"

#include <cmath>

#if 0
Test Cases
| N | Message |
|---+---------|
| 1 | Valid   |
| 2 | Invalid |
| 3 | Empty   |
#endif

namespace NMEA {
TEST(GSTMessageParse, Valid_Message) {
  const std::string RawMessage{"$GPGST,082356.00,1.8,,,,1.7,1.3,2.2*7E"};

  time_t ExpectedTimestamp = 0;
  struct tm *TimeInfo;

  std::time(&ExpectedTimestamp);
  TimeInfo = gmtime(&ExpectedTimestamp);
  TimeInfo->tm_hour = 8;
  TimeInfo->tm_min = 23;
  TimeInfo->tm_sec = 56;
  ExpectedTimestamp = mktime(TimeInfo);

  GPGST Message{ExpectedTimestamp, 1.8f, NAN, NAN, NAN, 1.7f, 1.3f, 2.2f};
  NMEAMessage Expected{NMEA_TALKER_ID::GPS, NMEA_MESSAGE_TYPE::GST, 1,
                       .GST = &Message};

  auto Parser = NMEAParser{};
  auto Result = Parser.Parse(RawMessage);

  // Compare Headers
  EXPECT_EQ(Expected.ID, Result->ID) << "Talker ID is incorrect";
  EXPECT_EQ(Expected.Type, Result->Type) << "Message type is incorrect";
  EXPECT_EQ(Expected.Valid, Result->Valid)
      << "Message valid status is incorrect";

  // Compate Messages
  EXPECT_EQ(Expected.GST->TimeStamp, Result->GST->TimeStamp);
  EXPECT_FLOAT_EQ(Expected.GST->range_rms, Result->GST->range_rms);
  EXPECT_TRUE(isnan(Result->GST->std_major));
  EXPECT_TRUE(isnan(Result->GST->std_minor));
  EXPECT_TRUE(isnan(Result->GST->hdg));
  EXPECT_FLOAT_EQ(Expected.GST->std_lat, Result->GST->std_lat);
  EXPECT_FLOAT_EQ(Expected.GST->std_long, Result->GST->std_long);
  EXPECT_FLOAT_EQ(Expected.GST->std_alt, Result->GST->std_alt);
}

TEST(GSTMessageParse, Invalid_Message) {
  const std::string RawMessage = "$(_+R,er,3,4,?>P#@$,fsd,,4,t,g,g,,*8R";
  NMEAMessage Expected{NMEA_TALKER_ID::UNKNOWN_TALKER_ID,
                       NMEA_MESSAGE_TYPE::UNKNOWN_MESSAGE,
                       0,
                       {}};

  auto Parser = NMEAParser{};
  auto Result = Parser.Parse(RawMessage);

  // Compare Headers
  EXPECT_EQ(Expected.ID, Result->ID) << "Talker ID is incorrect";
  EXPECT_EQ(Expected.Type, Result->Type) << "Message type is incorrect";
  EXPECT_EQ(Expected.Valid, Result->Valid)
      << "Message valid status is incorrect";

  // Compare Message
  EXPECT_EQ(Expected.GST, Result->GST);
}

TEST(GSTMessageParse, Empty_Message) {
  const std::string RawMessage{""};
  NMEAMessage Expected{NMEA_TALKER_ID::UNKNOWN_TALKER_ID,
                       NMEA_MESSAGE_TYPE::UNKNOWN_MESSAGE,
                       0,
                       {}};

  auto Parser = NMEAParser{};
  auto Result = Parser.Parse(RawMessage);

  // Compare Headers
  EXPECT_EQ(Expected.ID, Result->ID) << "Talker ID is incorrect";
  EXPECT_EQ(Expected.Type, Result->Type) << "Message type is incorrect";
  EXPECT_EQ(Expected.Valid, Result->Valid)
      << "Message valid status is incorrect";

  // Compare Message
  EXPECT_EQ(Expected.GST, Result->GST);
}
}
