//===-- ParseDifferentialStationID_Test.cpp ---------------------*- C++ -*-===//
//
// This file is distributed uner the MIT license. See LICENSE.txt for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// Unit tests for ParseDifferentialStationID(std::string CorrectionAge)
///
//===----------------------------------------------------------------------===//
#include "NMEAParser.cpp"
#include "gtest/gtest.h"

#include <cmath>

#if 0
Test cases
| N | StationID |
|---+-----------|
| 1 | Valid     |
| 2 | Invalid   |
| 3 | Empty     |
#endif

namespace NMEA {
TEST(ParseDifferentialStationID, Valid_StationID) {
  const std::string StationID = "0";
  const int Expected = 0;

  EXPECT_EQ(Expected, ParseDifferentialStationID(StationID));
}

TEST(ParseDifferentialStationID, Invalid_StationID) {
  const std::string StationID = "ertyhgf";
  const int Expected = 0;

  EXPECT_EQ(Expected, ParseDifferentialStationID(StationID));
}

TEST(ParseDifferentialStationID, Empty_StationID) {
  const std::string StationID = "";
  const int Expected = 0;

  EXPECT_EQ(Expected, ParseDifferentialStationID(StationID));
}
}
