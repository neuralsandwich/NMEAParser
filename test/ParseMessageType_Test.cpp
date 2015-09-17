//===-- ParseMessageType_Test.cpp -------------------------------*- C++ -*-===//
//
// This file is distributed uner the MIT license. See LICENSE.txt for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// Unit tests for ParseMessageType(const std::string &Message)
///
//===----------------------------------------------------------------------===//
#include "NMEAParser.cpp"
#include "gtest/gtest.h"

namespace NMEA {
TEST(ParseMessageType, Valid_Message_Type) {
  const std::string Message =
      "GPRMC,083559.00,A,4717.11437,N,00833.91522,E,0.004,77.52,091202,,,A*57";
  const enum NMEA_MESSAGE_TYPE Expected = RMC;

  EXPECT_EQ(Expected, ParseMessageType(Message));
}

TEST(ParseMessageType, Invalid_Message_Type) {
  const std::string Message = "PUBX,05,,*cs";
  const enum NMEA_MESSAGE_TYPE Expected = UNKNOWN_MESSAGE;

  EXPECT_EQ(Expected, ParseMessageType(Message));
}

TEST(ParseMessageType, Invalid_Empty_Message_Type) {
  const std::string Message = "";
  const enum NMEA_MESSAGE_TYPE Expected = UNKNOWN_MESSAGE;

  EXPECT_EQ(Expected, ParseMessageType(Message));
}
}
