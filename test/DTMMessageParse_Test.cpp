//===-- DTMMessageParse_Test.cpp --------------------------------*- C++ -*-===//
//
// This file is distributed uner the MIT license. See LICENSE.txt for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// Functional tests for parseing DTM Messages
///
//===----------------------------------------------------------------------===//
#include "NMEAParser.h"
#include "gtest/gtest.h"

#include <cstring>
#include <cmath>
#include <iostream>

#if 0
| N | Message     |
|---+-------------|
| 1 | W84 Valid   |
| 2 | W72 Invalid |
| 3 | Empty       |
#endif

namespace NMEA {
TEST(DTMMessageParse, Valid_W84_Message) {
  const std::string RawMessage = "$GPDTM,W84,,0.0,N,0.0,E,0.0,W84*6F";

  NMEAHeader Header = {
      .ID = NMEA_TALKER_ID::GPS, .Type = NMEA_MESSAGE_TYPE::DTM, .Valid = 1};

  GPDTM Message = {.LLL = "W84",
                   .LSD = "",
                   .lat = 0.0f,
                   .lon = 0.0f,
                   .alt = 0.0f,
                   .RRR = "W84"};

  NMEAMessage Expected = {.Header = &Header, .DTM = &Message};

  auto Parser = NMEAParser{};
  auto Result = Parser.Parse(RawMessage);

  // Compare Header
  EXPECT_EQ(Expected.Header->ID, Result->Header->ID);
  EXPECT_EQ(Expected.Header->Type, Result->Header->Type);
  EXPECT_EQ(Expected.Header->Valid, Result->Header->Valid);

  // Compare Message
  EXPECT_TRUE(strncmp(Expected.DTM->LLL, Result->DTM->LLL, 3) == 0);
  EXPECT_EQ(Expected.DTM->LSD[0], Result->DTM->LSD[0]);
  EXPECT_EQ(Expected.DTM->lat, Result->DTM->lat);
  EXPECT_EQ(Expected.DTM->lon, Result->DTM->lon);
  EXPECT_EQ(Expected.DTM->alt, Result->DTM->alt);
  EXPECT_TRUE(strncmp(Expected.DTM->RRR, Result->DTM->RRR, 3) == 0);
};

TEST(DTMMessageParse, Valid_W72_Message) {
  const std::string RawMessage = "$GPDTM,W72,,0.00,S,0.01,W,-2.8,W84*4F";

  NMEAHeader Header = {
      .ID = NMEA_TALKER_ID::GPS, .Type = NMEA_MESSAGE_TYPE::DTM, .Valid = 1};

  GPDTM Message = {.LLL = "W72",
                   .LSD = "",
                   .lat = 0.0f,
                   .lon = -0.01f,
                   .alt = -2.8f,
                   .RRR = "W84"};

  NMEAMessage Expected = {.Header = &Header, .DTM = &Message};

  auto Parser = NMEAParser{};
  auto Result = Parser.Parse(RawMessage);

  // Compare Header
  EXPECT_EQ(Expected.Header->ID, Result->Header->ID);
  EXPECT_EQ(Expected.Header->Type, Result->Header->Type);
  EXPECT_EQ(Expected.Header->Valid, Result->Header->Valid);

  // Compare Message
  EXPECT_TRUE(strncmp(Expected.DTM->LLL, Result->DTM->LLL, 3) == 0);
  EXPECT_EQ(Expected.DTM->LSD[0], Result->DTM->LSD[0]);
  EXPECT_EQ(Expected.DTM->lat, Result->DTM->lat);
  EXPECT_EQ(Expected.DTM->lon, Result->DTM->lon);
  EXPECT_EQ(Expected.DTM->alt, Result->DTM->alt);
  EXPECT_TRUE(strncmp(Expected.DTM->RRR, Result->DTM->RRR, 3) == 0);
};

TEST(DTMMessageParse, Valid_999_Message) {
  const std::string RawMessage = "$GPDTM,999,CH95,0.08,N,0.07,E,-47.7,W84*1C";

  NMEAHeader Header = {
      .ID = NMEA_TALKER_ID::GPS, .Type = NMEA_MESSAGE_TYPE::DTM, .Valid = 1};

  GPDTM Message = {.LLL = "999",
                   .LSD = "CH95",
                   .lat = 0.08f,
                   .lon = 0.07f,
                   .alt = -47.7f,
                   .RRR = "W84"};

  NMEAMessage Expected = {.Header = &Header, .DTM = &Message};

  auto Parser = NMEAParser{};
  auto Result = Parser.Parse(RawMessage);

  // Compare Header
  EXPECT_EQ(Expected.Header->ID, Result->Header->ID);
  EXPECT_EQ(Expected.Header->Type, Result->Header->Type);
  EXPECT_EQ(Expected.Header->Valid, Result->Header->Valid);

  // Compare Message
  EXPECT_TRUE(strncmp(Expected.DTM->LLL, Result->DTM->LLL, 3) == 0);
  EXPECT_EQ(Expected.DTM->LSD[0], Result->DTM->LSD[0]);
  EXPECT_EQ(Expected.DTM->lat, Result->DTM->lat);
  EXPECT_EQ(Expected.DTM->lon, Result->DTM->lon);
  EXPECT_EQ(Expected.DTM->alt, Result->DTM->alt);
  EXPECT_TRUE(strncmp(Expected.DTM->RRR, Result->DTM->RRR, 3) == 0);
};

TEST(DTMMessageParse, Invalid_Message) {
  const std::string RawMessage = "asdfliouieniifioewufyshdfj";

  NMEAHeader Header = {.ID = NMEA_TALKER_ID::UNKNOWN_TALKER_ID,
                       .Type = NMEA_MESSAGE_TYPE::UNKNOWN_MESSAGE,
                       .Valid = 0};

  NMEAMessage Expected = {.Header = &Header, 0};

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
  EXPECT_EQ(Expected.DTM, Result->DTM);
}

TEST(DTMMessageParse, Empty_Message) {
  const std::string RawMessage = "";

  NMEAHeader Header = {.ID = NMEA_TALKER_ID::UNKNOWN_TALKER_ID,
                       .Type = NMEA_MESSAGE_TYPE::UNKNOWN_MESSAGE,
                       .Valid = 0};

  NMEAMessage Expected = {.Header = &Header, 0};

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
  EXPECT_EQ(Expected.DTM, Result->DTM);
}
}
