/**
 * File: ParseTimeStamp_String_String_Test.cpp
 * Description: Unit tests for
 * NMEA::NMEAParser::ParseTimeStamp(const std::string *TimeStamp,
 *                                  const std::string *DateStamp)
 */
#include "NMEAParser.h"
#include "gtest/gtest.h"

#include <iostream>

namespace NMEA {

TEST(ValidateChecksum, Valid_Checksum) {
  const std::string Message = "$GPGGA,092725.00,4717.11399,N,00833.91590,E,1,8,"
                              "1.01,499.6,M,48.0,M,,0*5B";
  const std::string Checksum = "5B";
  const bool Expected = true;

  auto Parser = NMEA::NMEAParser{};

  EXPECT_EQ(Expected, Parser.ValidateChecksum(&Message, &Checksum));
}

TEST(ValidateChecksum, Invalid_Checksum) {
  const std::string Message = "$GPGGA,092725.00,4717.11399,N,00833.91590,E,1,8,"
                              "1.01,499.6,M,48.0,M,,0*5B";
  const std::string Checksum = "AB";
  const bool Expected = false;

  auto Parser = NMEA::NMEAParser{};

  EXPECT_EQ(Expected, Parser.ValidateChecksum(&Message, &Checksum));
}

TEST(ValidateChecksum, Invalid_Empty_Message) {
  const std::string Message = "";
  const std::string Checksum = "AB";
  const bool Expected = false;

  auto Parser = NMEA::NMEAParser{};

  EXPECT_EQ(Expected, Parser.ValidateChecksum(&Message, &Checksum));
}

TEST(ValidateChecksum, Invalid_Short_Range_Checksum) {
  const std::string Message = "$GPGGA,092725.00,4717.11399,N,00833.91590,E,1,8,"
                              "1.01,499.6,M,48.0,M,,0*5B";
  const std::string Checksum = "5";
  const bool Expected = false;

  auto Parser = NMEA::NMEAParser{};

  EXPECT_EQ(Expected, Parser.ValidateChecksum(&Message, &Checksum));
}

TEST(ValidateChecksum, Invalid_Long_Range_Checksum) {
  const std::string Message = "$GPGGA,092725.00,4717.11399,N,00833.91590,E,1,8,"
                              "1.01,499.6,M,48.0,M,,0*5BB";
  const std::string Checksum = "5BB";
  const bool Expected = false;

  auto Parser = NMEA::NMEAParser{};

  EXPECT_EQ(Expected, Parser.ValidateChecksum(&Message, &Checksum));
}
}
