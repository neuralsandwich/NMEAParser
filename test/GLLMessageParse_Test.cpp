//===-- GLLMessageParse_Test.cpp --------------------------------*- C++ -*-===//
//
// This file is distributed uner the MIT license. See LICENSE.txt for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// Functional tests for Parsing GLL messages
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
TEST(GLLMessageParse, Valid_Message) {
  const std::string RawMessage =
      "$GPGLL,4717.11364,N,00833.91565,E,092321.00,A,A*60";

  time_t ExpectedTimestamp = 0;
  struct tm *TimeInfo;

  std::time(&ExpectedTimestamp);
  TimeInfo = gmtime(&ExpectedTimestamp);
  TimeInfo->tm_hour = 9;
  TimeInfo->tm_min = 23;
  TimeInfo->tm_sec = 21;
  ExpectedTimestamp = mktime(TimeInfo);

  GPGLL Message{4717.11364f, 833.91565f, ExpectedTimestamp, true, 'A'};

  NMEAMessage Expected{NMEA_TALKER_ID::GPS, NMEA_MESSAGE_TYPE::GLL, 1,
                       .GLL = &Message};

  auto Parser = NMEAParser{};
  auto Result = Parser.Parse(RawMessage);

  // Compare Headers
  EXPECT_EQ(Expected.ID, Result->ID) << "Talker ID is incorrect";
  EXPECT_EQ(Expected.Type, Result->Type) << "Message type is incorrect";
  EXPECT_EQ(Expected.Valid, Result->Valid)
      << "Message valid status is incorrect";

  // Compate Messages
  EXPECT_FLOAT_EQ(Expected.GLL->Latitude, Result->GLL->Latitude);
  EXPECT_FLOAT_EQ(Expected.GLL->Longitude, Result->GLL->Longitude);
  EXPECT_EQ(Expected.GLL->TimeStamp, Result->GLL->TimeStamp);
  EXPECT_EQ(Expected.GLL->Status, Result->GLL->Status);
  EXPECT_EQ(Expected.GLL->PositioningMode, Result->GLL->PositioningMode);
}

TEST(GLLMessageParse, Invalid_Message) {
  const std::string RawMessage = "$iouf8f8j,6,345,dsdfsf*8R";
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
  EXPECT_EQ(Expected.GLL, Result->GLL);
}

TEST(GLLMessageParse, Empty_Message) {
  const std::string RawMessage = "";
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
  EXPECT_EQ(Expected.GLL, Result->GLL);
}
}
