#include "NMEAParser.h"

extern "C" {
#include "NMEA.h"
}

// HNMEAParser
HNMEAParser *HNMEAParser_Create() {
  try {
    return reinterpret_cast<HNMEAParser *>(new NMEAParser());
  } catch (...) {
    return NULL;
  }
} // HNMEAParser_Create

NMEAData *HNMEAParser_Parse(const HNMEAParser *Parser, const char *String) {
  try {
    NMEAData *Result = 0;

    Result = Parser->parse(String);

    return Result;
  } catch (...) {
    return 0;
  }
} // HNMEAParser_Parse
