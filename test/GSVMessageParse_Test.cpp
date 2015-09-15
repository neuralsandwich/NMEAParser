//===-- GSVMessageParse_Test.cpp --------------------------------*- C++ -*-===//
//
// This file is distributed uner the MIT license. See LICENSE.txt for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// Functional tests for Parsing GSV messages
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
TEST(GSVMessageParse, Valid_Message) {
  const std::string RawMessage = "$GPGSV,3,1,10,23,38,230,44,29,71,156,47,"
                                 "07,29,116,41,08,09,081,36*7F";

  NMEAHeader Header = {
      .ID = NMEA_TALKER_ID::GPS, .Type = NMEA_MESSAGE_TYPE::GSV, .Valid = 1};

  int SVs[4] = {23, 29, 7, 8};
  int Elvs[4] = {38, 71, 29, 9};
  int Azs[4] = {230, 156, 116, 81};
  int Cnos[4] = {44, 47, 41, 36};

  GPGSV Message = {.NoMSG = 3,
                   .MSGNo = 1,
                   .NoSV = 10,
                   .sv = SVs,
                   .elv = Elvs,
                   .az = Azs,
                   .cno = Cnos,
                   .DataFieldsInMessage = 16};

  NMEAMessage Expected = {.Header = &Header, .GSV = &Message};

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
  EXPECT_EQ(Expected.GSV->NoMSG, Result->GSV->NoMSG);
  EXPECT_EQ(Expected.GSV->MSGNo, Result->GSV->MSGNo);
  for (int i = 0; i < 4; i++) {
    EXPECT_EQ(Expected.GSV->sv[i], Result->GSV->sv[i]);
  }
  for (int i = 0; i < 4; i++) {
    EXPECT_EQ(Expected.GSV->elv[i], Result->GSV->elv[i]);
  }
  for (int i = 0; i < 4; i++) {
    EXPECT_EQ(Expected.GSV->az[i], Result->GSV->az[i]);
  }
  for (int i = 0; i < 4; i++) {
    EXPECT_EQ(Expected.GSV->cno[i], Result->GSV->cno[i]);
  }
}

TEST(GSAMessageParse, Invalid_Message) {
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
  EXPECT_EQ(Expected.GSV, Result->GSV);
}

TEST(GSAMessageParse, Empty_Message) {
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
  EXPECT_EQ(Expected.GSV, Result->GSV);
}
}
