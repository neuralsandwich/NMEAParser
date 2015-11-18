//===-- THSMessageParse_Test.cpp --------------------------------*- C++ -*-===//
//
// This file is distributed uner the MIT license. See LICENSE.txt for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// Functional tests for Parsing THS Messages
///
//===----------------------------------------------------------------------===//
#include "NMEAParser.h"
#include "gtest/gtest.h"

#include <cmath>

namespace NMEA {
TEST(THSMessageParse, Valid_Message) {
  const std::string RawMessage{"$GPTHS,77.52,E*34"};

  GPTHS Message{77.52f, 'E'};
  NMEAMessage Expected{NMEA_TALKER_ID::GPS, NMEA_MESSAGE_TYPE::THS, 1,
                       .THS = &Message};

  auto Parser = NMEAParser{};
  auto Result = Parser.Parse(RawMessage);

  // Compare Headers
  EXPECT_EQ(Expected.ID, Result->ID) << "Talker ID is incorrect";
  EXPECT_EQ(Expected.Type, Result->Type) << "Message type is incorrect";
  EXPECT_EQ(Expected.Valid, Result->Valid)
      << "Message valid status is incorrect";

  EXPECT_FLOAT_EQ(Expected.THS->headt, Result->THS->headt);
  EXPECT_EQ(Expected.THS->mi, Result->THS->mi);
}

TEST(THSMessageParse, Invalid_Message) {
  const std::string RawMessage{"*ASDflaksdjflkasjdflaksdjf"};

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
}

TEST(THSMessageParse, Empty_Message) {
  const std::string RawMessage{""};

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
}
}
