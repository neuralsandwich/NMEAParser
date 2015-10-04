//===-- GBSMessageParse_Test.cpp --------------------------------*- C++ -*-===//
//
// This file is distributed uner the MIT license. See LICENSE.txt for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
///
///
//===----------------------------------------------------------------------===//
#include "NMEAParser.h"
#include "gtest/gtest.h"

#include <cstring>
#include <cmath>
#include <iostream>

#if 0
| N | Message |
|---+---------|
| 1 | Valid   |
| 2 | Invalid |
| 3 | Empty   |
#endif

namespace NMEA {
TEST(GBSMessageParse, Valid_Message) {
  const std::string RawMessage =
      "$GPGBS,235458.00,1.4,1.3,3.1,03,,-21.4,3.8*5B";

  NMEAHeader Header = {NMEA_TALKER_ID::GPS, NMEA_MESSAGE_TYPE::GBS, 1};

  time_t ExpectedTimestamp = 0;
  struct tm *TimeInfo;

  std::time(&ExpectedTimestamp);
  TimeInfo = gmtime(&ExpectedTimestamp);
  TimeInfo->tm_hour = 23;
  TimeInfo->tm_min = 54;
  TimeInfo->tm_sec = 58;
  ExpectedTimestamp = mktime(TimeInfo);

  GPGBS Message = {ExpectedTimestamp, 1.4f, 1.3f, 3.1f, 3, NAN, -21.4f, 3.8f};

  NMEAMessage Expected = {.Header = &Header, .GBS = &Message};

  auto Parser = NMEAParser{};
  auto Result = Parser.Parse(RawMessage);

  // Compare Header
  EXPECT_EQ(Expected.Header->ID, Result->Header->ID);
  EXPECT_EQ(Expected.Header->Type, Result->Header->Type);
  EXPECT_EQ(Expected.Header->Valid, Result->Header->Valid);

  // Compare Message
  EXPECT_EQ(Expected.GBS->TimeStamp, Result->GBS->TimeStamp);
  EXPECT_FLOAT_EQ(Expected.GBS->errlat, Result->GBS->errlat);
  EXPECT_FLOAT_EQ(Expected.GBS->errlon, Result->GBS->errlon);
  EXPECT_FLOAT_EQ(Expected.GBS->erralt, Result->GBS->erralt);
  EXPECT_EQ(Expected.GBS->svid, Result->GBS->svid);
  EXPECT_EQ(isnan(Expected.GBS->prob), isnan(Result->GBS->prob));
  EXPECT_FLOAT_EQ(Expected.GBS->bias, Result->GBS->bias);
  EXPECT_FLOAT_EQ(Expected.GBS->stddev, Result->GBS->stddev);
}
};
