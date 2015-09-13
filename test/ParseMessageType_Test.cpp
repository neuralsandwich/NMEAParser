/**
 * File: ParseMessageType_Test.cpp
 * Description: Unit tests for
 * NMEA::NMEAParser::ParseMessageType(const std::string &Message) const;
 */
#include "NMEAParser.h"
#include "gtest/gtest.h"

namespace NMEA {
TEST(ParseMessageType, Valid_Message_Type) {
  const std::string Message =
      "GPRMC,083559.00,A,4717.11437,N,00833.91522,E,0.004,77.52,091202,,,A*57";
  const enum NMEA_MESSAGE_TYPE Expected = RMC;

  auto Parser = NMEAParser{};

  EXPECT_EQ(Expected, Parser.ParseMessageType(Message));
}

TEST(ParseMessageType, Invalid_Message_Type) {
  const std::string Message = "PUBX,05,,*cs";
  const enum NMEA_MESSAGE_TYPE Expected = UNKNOWN_MESSAGE;

  auto Parser = NMEAParser{};

  EXPECT_EQ(Expected, Parser.ParseMessageType(Message));
}

TEST(ParseMessageType, Invalid_Empty_Message_Type) {
  const std::string Message = "";
  const enum NMEA_MESSAGE_TYPE Expected = UNKNOWN_MESSAGE;

  auto Parser = NMEAParser{};

  EXPECT_EQ(Expected, Parser.ParseMessageType(Message));
}
}
