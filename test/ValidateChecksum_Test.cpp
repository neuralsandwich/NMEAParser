//===-- ValidateChecksum_Test.cpp -------------------------------*- C++ -*-===//
//
// This file is distributed uner the MIT license. See LICENSE.txt for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// Unit tests for ValidateChecksum(const std::string &Message)
///
//===----------------------------------------------------------------------===//
#include "NMEAParser.cpp"
#include "gtest/gtest.h"

namespace NMEA {

TEST(ValidateChecksum, Valid_Checksum) {
  const std::string Message = "$GPGGA,092725.00,4717.11399,N,00833.91590,E,1,8,"
                              "1.01,499.6,M,48.0,M,,0*5B";
  const std::string Checksum = "5B";
  const bool Expected = true;

  EXPECT_EQ(Expected, ValidateChecksum(Message, Checksum));
}

TEST(ValidateChecksum, Invalid_Checksum) {
  const std::string Message = "$GPGGA,092725.00,4717.11399,N,00833.91590,E,1,8,"
                              "1.01,499.6,M,48.0,M,,0*5B";
  const std::string Checksum = "AB";
  const bool Expected = false;

  EXPECT_EQ(Expected, ValidateChecksum(Message, Checksum));
}

TEST(ValidateChecksum, Invalid_Empty_Message) {
  const std::string Message = "";
  const std::string Checksum = "AB";
  const bool Expected = false;

  EXPECT_EQ(Expected, ValidateChecksum(Message, Checksum));
}

TEST(ValidateChecksum, Invalid_Empty_Checksum) {
  const std::string Message = "$GPGGA,092725.00,4717.11399,N,00833.91590,E,1,8,"
                              "1.01,499.6,M,48.0,M,,0*5B";
  const std::string Checksum = "";
  const bool Expected = false;

  EXPECT_EQ(Expected, ValidateChecksum(Message, Checksum));
}

TEST(ValidateChecksum, Invalid_Short_Range_Checksum) {
  const std::string Message = "$GPGGA,092725.00,4717.11399,N,00833.91590,E,1,8,"
                              "1.01,499.6,M,48.0,M,,0*5B";
  const std::string Checksum = "5";
  const bool Expected = false;

  EXPECT_EQ(Expected, ValidateChecksum(Message, Checksum));
}

TEST(ValidateChecksum, Invalid_Long_Range_Checksum) {
  const std::string Message = "$GPGGA,092725.00,4717.11399,N,00833.91590,E,1,8,"
                              "1.01,499.6,M,48.0,M,,0*5BB";
  const std::string Checksum = "5BB";
  const bool Expected = false;

  EXPECT_EQ(Expected, ValidateChecksum(Message, Checksum));
}
}
