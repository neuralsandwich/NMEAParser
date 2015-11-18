//===-- VTGMessageParse_Test.cpp --------------------------------*- C++ -*-===//
//
// This file is distributed uner the MIT license. See LICENSE.txt for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// Functional tests for Parsing VTG messages
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
TEST(VTGMessageParse, Valid_Message) {
  const std::string RawMessage = "$GPVTG,77.52,T,,M,0.004,N,0.008,K,A*06";

  GPVTG Message = {.cogt = 77.52f,
                   .T = 'T',
                   .cogm = NAN,
                   .M = 'M',
                   .sog = 0.004f,
                   .N = 'N',
                   .kph = 0.008,
                   .K = 'K',
                   .mode = 'A'};

  NMEAMessage Expected = {NMEA_TALKER_ID::GPS, NMEA_MESSAGE_TYPE::VTG, 1,
                          .VTG = &Message};

  auto Parser = NMEAParser{};
  auto Result = Parser.Parse(RawMessage);

  // Compare Headers
  EXPECT_EQ(Expected.ID, Result->ID) << "Talker ID is incorrect";
  EXPECT_EQ(Expected.Type, Result->Type) << "Message type is incorrect";
  EXPECT_EQ(Expected.Valid, Result->Valid)
      << "Message valid status is incorrect";

  // Compate Messages
  EXPECT_FLOAT_EQ(Expected.VTG->cogt, Result->VTG->cogt);
  EXPECT_EQ(Expected.VTG->T, Result->VTG->T);
  EXPECT_FLOAT_EQ(isnan(Expected.VTG->cogm), isnan(Result->VTG->cogm));
  EXPECT_EQ(Expected.VTG->M, Result->VTG->M);
  EXPECT_FLOAT_EQ(Expected.VTG->sog, Result->VTG->sog);
  EXPECT_EQ(Expected.VTG->N, Result->VTG->N);
  EXPECT_FLOAT_EQ(Expected.VTG->kph, Result->VTG->kph);
  EXPECT_EQ(Expected.VTG->K, Result->VTG->K);
  EXPECT_EQ(Expected.VTG->mode, Result->VTG->mode);
}

TEST(VTGMessageParse, Invalid_Message) {
  const std::string RawMessage = "$ZZR,er,3,4,rwe,r,fsd,,4,t,g,g,,*8R";
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
  EXPECT_EQ(Expected.VTG, Result->VTG);
}

TEST(VTGMessageParse, Empty_Message) {
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
  EXPECT_EQ(Expected.VTG, Result->VTG);
}
}
