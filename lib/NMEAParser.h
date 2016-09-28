//===-- NMEAParser.h - NMEA Message definitions -----------------*- C++ -*-===//
//
//                                NMEAParser
//
// This file is distributed under the MIT license. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains the declaration of the NMEAParser. The parser is based
/// on different internet sources. In theory it should be able to parse NMEA
//  0183 Version 2.3.
///
//===----------------------------------------------------------------------===//
#ifndef NMEA_PARSER_HPP
#define NMEA_PARSER_HPP

extern "C" {
#include "NMEA.h"
}

#ifndef DEBUG
#else
#include "gtest/gtest_prod.h"
#endif

#include <string>
#include <vector>

namespace NMEA {
// Printable strings for Talker IDs
constexpr char NMEATalkerIDName[NMEA_TALKER_ID_NUM][8] = {
    "Unknown", "GPS", "GLONASS"}; // NMEATalkerIDName

struct NMEAGPSMessageName {
  enum NMEA_MESSAGE_TYPE Type;
  const char String[4];
};

// Printable strings for Message types
constexpr NMEAGPSMessageName NMEAGPSMessageNames[NMEA_GPS_MESSAGE_NUM] = {
    {NMEA_MESSAGE_TYPE::UNKNOWN_MESSAGE, "???"}, // Unknown Message Type
    {NMEA_MESSAGE_TYPE::AAM, "AAM"},                 // Waypoint Arrival Alarm
    {NMEA_MESSAGE_TYPE::ALM, "ALM"},                 // Almanac data
    {NMEA_MESSAGE_TYPE::APA, "APA"},                 // Auto Pilot A sentence
    {NMEA_MESSAGE_TYPE::APB, "APB"},                 // Auto Pilot B sentence
    {NMEA_MESSAGE_TYPE::BOD, "BOD"}, // Bearing Origin to Destination
    {NMEA_MESSAGE_TYPE::BWC, "BWC"}, // Bearing using Great Circle route
    {NMEA_MESSAGE_TYPE::DTM, "DTM"}, // Datum being used.
    {NMEA_MESSAGE_TYPE::GBS, "GBS"}, // GNSS Satellite Fault Detection
    {NMEA_MESSAGE_TYPE::GGA, "GGA"}, // Fix information
    {NMEA_MESSAGE_TYPE::GLL, "GLL"}, // Lat/Lon data
    {NMEA_MESSAGE_TYPE::GRS, "GRS"}, // GPS Range Residuals
    {NMEA_MESSAGE_TYPE::GSA, "GSA"}, // Overall Satellite data
    {NMEA_MESSAGE_TYPE::GST, "GST"}, // GPS Pseudorange Noise Statistics
    {NMEA_MESSAGE_TYPE::GSV, "GSV"}, // Detailed Satellite data
    {NMEA_MESSAGE_TYPE::MSK, "MSK"}, // send control for a beacon receiver
    {NMEA_MESSAGE_TYPE::MSS, "MSS"}, // Beacon receiver status information.
    {NMEA_MESSAGE_TYPE::RMA, "RMA"}, // recommended Loran data
    {NMEA_MESSAGE_TYPE::RMB, "RMB"}, // recommended navigation data for gps
    {NMEA_MESSAGE_TYPE::RMC, "RMC"}, // recommended minimum data for gps
    {NMEA_MESSAGE_TYPE::RTE, "RTE"}, // route message
    {NMEA_MESSAGE_TYPE::THS, "THS"}, // true heading and status
    {NMEA_MESSAGE_TYPE::TRF, "TRF"}, // Transit Fix Data
    {NMEA_MESSAGE_TYPE::STN, "STN"}, // Multiple Data ID
    {NMEA_MESSAGE_TYPE::VBW, "VBW"}, // dual Ground / Water Spped
    {NMEA_MESSAGE_TYPE::VTG, "VTG"}, // Vector track an Speed over the Ground
    {NMEA_MESSAGE_TYPE::WCV,
     "WCV"}, // Waypoint closure velocity (Velocity Made Good)
    {NMEA_MESSAGE_TYPE::WPL, "WPL"}, // Waypoint Location information
    {NMEA_MESSAGE_TYPE::XTC, "XTC"}, // cross track error
    {NMEA_MESSAGE_TYPE::XTE, "XTE"}, // measured cross track error
    {NMEA_MESSAGE_TYPE::ZTG,
     "ZTG"}, // Zulu (UTC) time and time to go (to destination)
    {NMEA_MESSAGE_TYPE::ZDA, "ZDA"}, // Date and Time
};                                   // NMEAGPSMessageName

/* MessageParse - Interface for Message Parsers
 * TODO
 */
struct MessageParser {
  virtual ~MessageParser() = 0;
  virtual void Parse(NMEAMessage *, const std::vector<std::string> &) const;
};

/* NMEAParser - Factory for NMEA message objects
 *
 * TODO: Document this once we have initial work on messages done.
 */
class NMEAParser {
  std::vector<MessageParser *> Parsers{NMEA_MESSAGE_TYPE::NMEA_GPS_MESSAGE_NUM};

public:
  NMEAParser();
  ~NMEAParser();
  NMEAMessage *Parse(const std::string &String) const;
}; // NMEAParser
} // NMEA
#endif
