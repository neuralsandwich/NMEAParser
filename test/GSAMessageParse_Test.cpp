//===-- GSAMessageParse_Test.cpp --------------------------------*- C++ -*-===//
//
// This file is distributed uner the MIT license. See LICENSE.txt for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// Functional tests for Parsing GSA messages
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
TEST(GSAMessageParse, Valid_Message) {
  const std::string RawMessage =
      "$GPGSA,A,3,23,29,07,08,09,18,26,28,,,,,1.94,1.18,1.54*0D";

  int SVs[8] = {23, 29, 7, 8, 9, 18, 26, 28};

  GPGSA Message{'A', 3, SVs, 1.94f, 1.18f, 1.54f};

  NMEAMessage Expected{NMEA_TALKER_ID::GPS, NMEA_MESSAGE_TYPE::GSA, 1,
                       .GSA = &Message};

  auto Parser = NMEAParser{};
  auto Result = Parser.Parse(RawMessage);

  // Compare Headers
  EXPECT_EQ(Expected.ID, Result->ID) << "Talker ID is incorrect";
  EXPECT_EQ(Expected.Type, Result->Type) << "Message type is incorrect";
  EXPECT_EQ(Expected.Valid, Result->Valid)
      << "Message valid status is incorrect";

  // Compate Messages
  EXPECT_EQ(Expected.GSA->Smode, Result->GSA->Smode);
  EXPECT_EQ(Expected.GSA->FixStatus, Result->GSA->FixStatus);
  for (int i = 0; i < 8; i++) {
    EXPECT_EQ(Expected.GSA->sv[i], Result->GSA->sv[i]);
  }
  EXPECT_EQ(Expected.GSA->pdop, Result->GSA->pdop);
  EXPECT_EQ(Expected.GSA->hdop, Result->GSA->hdop);
  EXPECT_EQ(Expected.GSA->vdop, Result->GSA->vdop);
}

TEST(GSAMessageParse, Invalid_Message) {
  const std::string RawMessage = "$ZZR,er,3,4,rwe,r,fsd,,4,t,g,g,,*8R";
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
  EXPECT_EQ(Expected.GSA, Result->GSA);
}

TEST(GSAMessageParse, Empty_Message) {
  const std::string RawMessage = "";
  NMEAMessage Expected = {NMEA_TALKER_ID::UNKNOWN_TALKER_ID,
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
  EXPECT_EQ(Expected.GSA, Result->GSA);
}
}
