//===-- GGAMessageParse_Test.cpp --------------------------------*- C++ -*-===//
//
// This file is distributed uner the MIT license. See LICENSE.txt for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// Functional tests for Parsing GGA Messages
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
TEST(GGAMessageParse, Valid_Message) {
  const std::string RawMessage =
      "$GPGGA,092725.00,4717.11399,N,00833.91590,E,1,8,"
      "1.01,499.6,M,48.0,M,,0*5B";

  time_t ExpectedTimestamp = 0;
  struct tm *TimeInfo;

  std::time(&ExpectedTimestamp);
  TimeInfo = gmtime(&ExpectedTimestamp);
  TimeInfo->tm_hour = 9;
  TimeInfo->tm_min = 27;
  TimeInfo->tm_sec = 25;
  ExpectedTimestamp = mktime(TimeInfo);

  NMEAMessage Expected{
      NMEA_TALKER_ID::GPS, NMEA_MESSAGE_TYPE::GGA, 1,
      .GGA = {new GPGGA{ExpectedTimestamp, 4717.11399f, 833.9159f, 1, 8, 1.01f,
                        499.6f, 'M', 48.0f, 'M', NAN, 0}}};

  auto Parser = NMEAParser{};
  auto Result = Parser.Parse(RawMessage);

  // Compare Headers
  EXPECT_EQ(Expected.ID, Result->ID) << "Talker ID is incorrect";
  EXPECT_EQ(Expected.Type, Result->Type) << "Message type is incorrect";
  EXPECT_EQ(Expected.Valid, Result->Valid)
      << "Message valid status is incorrect";

  // Compare Message
  EXPECT_EQ(Expected.GGA->TimeStamp, Result->GGA->TimeStamp)
      << "Timestamps are incorrect";
  EXPECT_FLOAT_EQ(Expected.GGA->Latitude, Result->GGA->Latitude)
      << "Latitude is incorrect";
  EXPECT_FLOAT_EQ(Expected.GGA->Longitude, Result->GGA->Longitude)
      << "Longitude is incorrect";
  EXPECT_EQ(Expected.GGA->Status, Result->GGA->Status) << "Status is incorrect";
  EXPECT_EQ(Expected.GGA->SatelliteFixes, Result->GGA->SatelliteFixes)
      << "Number of Satellite fixes are incorrect";
  EXPECT_FLOAT_EQ(Expected.GGA->HDOP, Result->GGA->HDOP)
      << "Horizontal dilution of Precision is incorrect";
  EXPECT_FLOAT_EQ(Expected.GGA->MSL, Result->GGA->MSL)
      << "MSL Altitude is incorrect";
  EXPECT_EQ(Expected.GGA->uMSL, Result->GGA->uMSL)
      << "MSL Units are incorrect, this should always be M";
  EXPECT_FLOAT_EQ(Expected.GGA->GeoidSeparation, Result->GGA->GeoidSeparation)
      << "Geoid Separation is incorrect";
  EXPECT_EQ(Expected.GGA->uSep, Result->GGA->uSep)
      << "Geoid separation unit is incorrect. This should always be M";
  EXPECT_EQ(isnan(Expected.GGA->DifferentialCorrectionAge),
            isnan(Result->GGA->DifferentialCorrectionAge))
      << "Differential Correction Age is incorrect";
  EXPECT_EQ(Expected.GGA->DifferentialStationID,
            Result->GGA->DifferentialStationID)
      << "Differential Station ID is incorrect";
}

TEST(GGAMessageParse, Invalid_Message) {
  const std::string RawMessage = "lajsdlkfjasdf";
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
  EXPECT_EQ(Expected.GGA, Result->GGA);
}

TEST(GGAMessageParse, Empty_Message) {
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
  EXPECT_EQ(Expected.GGA, Result->GGA);
}
}
