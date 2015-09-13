//===-- ParseSmode_Test.cpp -------------------------------------*- C++ -*-===//
//
// This file is distributed uner the MIT license. See LICENSE.txt for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// Unit tests for ParseSmode(std::string ModeIndicator)
///
//===----------------------------------------------------------------------===//
#include "NMEAParser.h"
#include "gtest/gtest.h"

#if 0
| N | Smode     |
|---+-----------|
| 1 | Manual    |
| 2 | Automatic |
| 3 | Empty     |
#endif

namespace NMEA {
TEST(ParseSmode, Manual) {
  const std::string Smode = "M";
  const char Expected = 'M';

  auto Parser = NMEAParser{};

  EXPECT_EQ(Expected, Parser.ParseSmode(Smode));
}

TEST(ParseSmode, Automatic) {
  const std::string Smode = "A";
  const char Expected = 'A';

  auto Parser = NMEAParser{};

  EXPECT_EQ(Expected, Parser.ParseSmode(Smode));
}

TEST(ParseSmode, Empty) {
  const std::string Smode = "";
  const char Expected = 'M';

  auto Parser = NMEAParser{};

  EXPECT_EQ(Expected, Parser.ParseSmode(Smode));
}
}
