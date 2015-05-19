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
  "Unknown", "GPS", "GLONASS"
}; // NMEATalkerIDName

typedef struct NMEAMessageTypeString {
  enum NMEA_MESSAGE_TYPE Type;
  std::string String;
} NMEAGPSMessageName;

// Printable strings for Message types
const NMEAGPSMessageName NMEAGPSMessageNames[NMEA_GPS_MESSAGE_NUM] = {
  { NMEA_MESSAGE_TYPE::UNKNOWN_MESSAGE, "Unknown" }, // Unknown Message Type
  { NMEA_MESSAGE_TYPE::AAM, "AAM" },                 // Waypoint Arrival Alarm
  { NMEA_MESSAGE_TYPE::ALM, "ALM" },                 // Almanac data
  { NMEA_MESSAGE_TYPE::APA, "APA" },                 // Auto Pilot A sentence
  { NMEA_MESSAGE_TYPE::APB, "APB" },                 // Auto Pilot B sentence
  { NMEA_MESSAGE_TYPE::BOD, "BOD" }, // Bearing Origin to Destination
  { NMEA_MESSAGE_TYPE::BWC, "BWC" }, // Bearing using Great Circle route
  { NMEA_MESSAGE_TYPE::DTM, "DTM" }, // Datum being used.
  { NMEA_MESSAGE_TYPE::GGA, "GGA" }, // Fix information
  { NMEA_MESSAGE_TYPE::GLL, "GLL" }, // Lat/Lon data
  { NMEA_MESSAGE_TYPE::GRS, "GRS" }, // GPS Range Residuals
  { NMEA_MESSAGE_TYPE::GSA, "GSA" }, // Overall Satellite data
  { NMEA_MESSAGE_TYPE::GST, "GST" }, // GPS Pseudorange Noise Statistics
  { NMEA_MESSAGE_TYPE::GSV, "GSV" }, // Detailed Satellite data
  { NMEA_MESSAGE_TYPE::MSK, "MSK" }, // send control for a beacon receiver
  { NMEA_MESSAGE_TYPE::MSS, "MSS" }, // Beacon receiver status information.
  { NMEA_MESSAGE_TYPE::RMA, "RMA" }, // recommended Loran data
  { NMEA_MESSAGE_TYPE::RMB, "RMB" }, // recommended navigation data for gps
  { NMEA_MESSAGE_TYPE::RMC, "RMC" }, // recommended minimum data for gps
  { NMEA_MESSAGE_TYPE::RTE, "RTE" }, // route message
  { NMEA_MESSAGE_TYPE::TRF, "TRF" }, // Transit Fix Data
  { NMEA_MESSAGE_TYPE::STN, "STN" }, // Multiple Data ID
  { NMEA_MESSAGE_TYPE::VBW, "VBW" }, // dual Ground / Water Spped
  { NMEA_MESSAGE_TYPE::VTG, "VTG" }, // Vector track an Speed over the Ground
  { NMEA_MESSAGE_TYPE::WCV,
    "WCV" }, // Waypoint closure velocity (Velocity Made Good)
  { NMEA_MESSAGE_TYPE::WPL, "WPL" }, // Waypoint Location information
  { NMEA_MESSAGE_TYPE::XTC, "XTC" }, // cross track error
  { NMEA_MESSAGE_TYPE::XTE, "XTE" }, // measured cross track error
  { NMEA_MESSAGE_TYPE::ZTG,
    "ZTG" }, // Zulu (UTC) time and time to go (to destination)
  { NMEA_MESSAGE_TYPE::ZDA, "ZDA" }, // Date and Time
};                                   // NMEAGPSMessageName

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
  char ParseSmode(const std::string *String);
  int ParseFixStatus(const std::string *String);
  int *ParseSV(std::vector<std::string>::iterator Start,
               std::vector<std::string>::iterator End);
  float ParsePDOP(const std::string *String);
  float ParseVDOP(const std::string *String);
}; // NMEAParser
} // NMEA
#endif
