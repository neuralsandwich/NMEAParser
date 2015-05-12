/* NMEAParser
 *
 * This library is based on information from different sources on the internet.
 *
 * In theory is should be able to parse NMEA 0183 Version 2.3, so it is out of
 * date.
 *
 * TODO: Convert messages to structs
 */
#ifndef NMEA_PARSER_HPP
#define NMEA_PARSER_HPP

extern "C" {
#include "NMEA.h"
}

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <ctime>

namespace NMEA {
// Printable strings for Talker IDs
const char *const NMEATalkerIDName[NMEA_TALKER_ID_NUM] = {
    "Unknown", "GPS", "GLONASS"}; // NMEATalkerIDName

// Printable strings for Message types
const char *const NMEAGPSMessageName[NMEA_GPS_MESSAGE_NUM] = {
    "Unknown", // Unknown Message Type
    "AAM",     // Waypoint Arrival Alarm
    "ALM",     // Almanac data
    "APA",     // Auto Pilot A sentence
    "APB",     // Auto Pilot B sentence
    "BOD",     // Bearing Origin to Destination
    "BWC",     // Bearing using Great Circle route
    "DTM",     // Datum being used.
    "GGA",     // Fix information
    "GLL",     // Lat/Lon data
    "GRS",     // GPS Range Residuals
    "GSA",     // Overall Satellite data
    "GST",     // GPS Pseudorange Noise Statistics
    "GSV",     // Detailed Satellite data
    "MSK",     // send control for a beacon receiver
    "MSS",     // Beacon receiver status information.
    "RMA",     // recommended Loran data
    "RMB",     // recommended navigation data for gps
    "RMC",     // recommended minimum data for gps
    "RTE",     // route message
    "TRF",     // Transit Fix Data
    "STN",     // Multiple Data ID
    "VBW",     // dual Ground / Water Spped
    "VTG",     // Vector track an Speed over the Ground
    "WCV",     // Waypoint closure velocity (Velocity Made Good)
    "WPL",     // Waypoint Location information
    "XTC",     // cross track error
    "XTE",     // measured cross track error
    "ZTG",     // Zulu (UTC) time and time to go (to destination)
    "ZDA",     // Date and Time
}; // NMEAGPSMessageName

/* NMEAParser - Factory for NMEA message objects
 *
 * TODO: Document this once we have initial work on messages done.
 */
class NMEAParser {
public:
  NMEAMessage *Parse(const std::string &String);

private:
  bool ValidateChecksum(const std::string *Message,
                        const std::string *Checksum);
  enum NMEA_TALKER_ID ParseTalkerID(const std::string *ID);
  enum NMEA_MESSAGE_TYPE ParseMessageType(const std::string *Message);
  time_t ParseTimeStamp(const std::string *TimeStamp,
                        const std::string *DataStamp);
  time_t ParseTimeStamp(const std::string *TimeStamp);
  bool ParseStatus(const std::string *Status);
  float ParseLatitude(const std::string *Latitude,
                      const std::string *Direction);
  float ParseLongitude(const std::string *Longitude,
                       const std::string *Direction);
  float ParseSpeed(const std::string *Speed);
  float ParseAngle(const std::string *Angle);
  float ParseMagneticVariation(const std::string *MagneticVariation,
                               const std::string *MagneticVariatioDirection);
  int ParseSatiliteFixes(const std::string *SatiliteFixes);
  float ParseHDOP(const std::string *HDOP);
  float ParseMSL(const std::string *MDL);
  float ParseGeoidSeparation(const std::string *GeoidSeparation);
  float ParseDifferentialCorrectionAge(const std::string *CorrectionAge);
  float ParseDifferentialStationID(const std::string *StationID);
  float ParseCOGT(const std::string *CourseOverGroundTrue);
  float ParseCOGM(const std::string *CourseOverGroundMagnetic);
  float ParseSOG(const std::string *SpeedOverGround);
  char ParseModeIndicator(const std::string *ModeIndicator);
}; // NMEAParser
} // NMEA
#endif
