//===-- ZDAMessageParse_Test.cpp --------------------------------*- C++ -*-===//
//
// This file is distributed uner the MIT license. See LICENSE.txt for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// Functional tests for Parsing ZDA Messages
///
//===----------------------------------------------------------------------===//
#include "NMEAParser.h"
#include "gtest/gtest.h"

namespace NMEA {
TEST(ZDAMessageParse, Valid_Message) {
  const std::string RawMessage = "$GPZDA,082710.00,16,09,2002,00,00*64";

  NMEAHeader Header = {
      .ID = NMEA_TALKER_ID::GPS, .Type = NMEA_MESSAGE_TYPE::ZDA, .Valid = 1};

  time_t ExpectedTimestamp = 0;
  struct tm *TimeInfo;

  std::time(&ExpectedTimestamp);
  TimeInfo = gmtime(&ExpectedTimestamp);
  TimeInfo->tm_hour = 8;
  TimeInfo->tm_min = 27;
  TimeInfo->tm_sec = 10;
  TimeInfo->tm_mday = 16;
  TimeInfo->tm_mon = 8;
  TimeInfo->tm_year = 102;
  ExpectedTimestamp = mktime(TimeInfo);

  GPZDA Message = {
      .TimeStamp = ExpectedTimestamp, .LocalHours = 0, .LocalMinutes = 0};

  NMEAMessage Expected = {.Header = &Header, .ZDA = &Message};

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
  EXPECT_EQ(Expected.ZDA->TimeStamp, Result->ZDA->TimeStamp);
  EXPECT_EQ(Expected.ZDA->LocalHours, Result->ZDA->LocalHours);
  EXPECT_EQ(Expected.ZDA->LocalMinutes, Result->ZDA->LocalMinutes);
}

TEST(ZDAMessageParse, Invalid_Message) {
  const std::string RawMessage =
      "$GPZDA,082710.00,16,09,,12,4,123401924,00,00*64";

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
  EXPECT_EQ(Expected.ZDA, Result->ZDA);
}

TEST(ZDAMessageParse, Empty_Message) {
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
  EXPECT_EQ(Expected.ZDA, Result->ZDA);
}
};
