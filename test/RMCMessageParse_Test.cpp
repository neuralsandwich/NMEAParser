//===-- RMCMessageParse_Test.cpp --------------------------------*- C++ -*-===//
//
// This file is distributed uner the MIT license. See LICENSE.txt for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// Functional tests for Parsing RMC messages
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
TEST(RMCMessageParse, Valid_Message) {
  const std::string RawMessage =
      "$GPRMC,083559.00,A,4717.11437,N,00833.91522,E,0.004,77.52,091202,,,A*57";

  NMEAHeader Header = {
      .ID = NMEA_TALKER_ID::GPS, .Type = NMEA_MESSAGE_TYPE::RMC, .Valid = 1};

  time_t ExpectedTimestamp = 0;
  struct tm *TimeInfo;

  std::time(&ExpectedTimestamp);
  TimeInfo = gmtime(&ExpectedTimestamp);
  TimeInfo->tm_hour = 8;
  TimeInfo->tm_min = 35;
  TimeInfo->tm_sec = 59;
  TimeInfo->tm_mday = 9;
  TimeInfo->tm_mon = 11;
  TimeInfo->tm_year = 102;
  ExpectedTimestamp = mktime(TimeInfo);

  GPRMC Message = {.TimeStamp = ExpectedTimestamp,
                   .Status = true,
                   .Latitude = 4717.11437f,
                   .Longitude = 833.91522f,
                   .Speed = 0.004f,
                   .Angle = 77.52f,
                   .MagneticVariation = NAN};

  NMEAMessage Expected = {.Header = &Header, .RMC = &Message};

  auto Parser = NMEAParser{};
  auto Result = Parser.Parse(RawMessage);

  // Compare Headers
  EXPECT_EQ(Expected.Header->ID, Result->Header->ID)
      << "Talker ID is incorrect";
  EXPECT_EQ(Expected.Header->Type, Result->Header->Type)
      << "Message type is incorrect";
  EXPECT_EQ(Expected.Header->Valid, Result->Header->Valid)
      << "Message valid status is incorrect";

  // Compate Messages
  EXPECT_EQ(Expected.RMC->TimeStamp, Result->RMC->TimeStamp);
  EXPECT_EQ(Expected.RMC->Status, Result->RMC->Status);
  EXPECT_FLOAT_EQ(Expected.RMC->Latitude, Result->RMC->Latitude);
  EXPECT_FLOAT_EQ(Expected.RMC->Longitude, Result->RMC->Longitude);
  EXPECT_FLOAT_EQ(Expected.RMC->Speed, Result->RMC->Speed);
  EXPECT_FLOAT_EQ(Expected.RMC->Angle, Result->RMC->Angle);
  EXPECT_EQ(isnan(Expected.RMC->MagneticVariation),
            isnan(Result->RMC->MagneticVariation));
}

TEST(RMCMessageParse, Invalid_Message) {
  const std::string RawMessage = "$ZZR,er,3,4,rwe,r,fsd,,4,t,g,g,,*8R";
  NMEAHeader Header = {.ID = NMEA_TALKER_ID::UNKNOWN_TALKER_ID,
                       .Type = NMEA_MESSAGE_TYPE::UNKNOWN_MESSAGE,
                       .Valid = 0};

  NMEAMessage Expected = {.Header = &Header, {}};

  auto Parser = NMEAParser{};
  auto Result = Parser.Parse(RawMessage);

  // Compare Headers
  EXPECT_EQ(Expected.Header->ID, Result->Header->ID)
      << "Talker ID is incorrect";
  EXPECT_EQ(Expected.Header->Type, Result->Header->Type)
      << "Message type is incorrect";
  EXPECT_EQ(Expected.Header->Valid, Result->Header->Valid)
      << "Message valid status is incorrect";

  // Compare Message
  EXPECT_EQ(Expected.RMC, Result->RMC);
}

TEST(RMCMessageParse, Empty_Message) {
  const std::string RawMessage = "";
  NMEAHeader Header = {.ID = NMEA_TALKER_ID::UNKNOWN_TALKER_ID,
                       .Type = NMEA_MESSAGE_TYPE::UNKNOWN_MESSAGE,
                       .Valid = 0};

  NMEAMessage Expected = {.Header = &Header, {}};

  auto Parser = NMEAParser{};
  auto Result = Parser.Parse(RawMessage);

  // Compare Headers
  EXPECT_EQ(Expected.Header->ID, Result->Header->ID)
      << "Talker ID is incorrect";
  EXPECT_EQ(Expected.Header->Type, Result->Header->Type)
      << "Message type is incorrect";
  EXPECT_EQ(Expected.Header->Valid, Result->Header->Valid)
      << "Message valid status is incorrect";

  // Compare Message
  EXPECT_EQ(Expected.RMC, Result->RMC);
}
}
