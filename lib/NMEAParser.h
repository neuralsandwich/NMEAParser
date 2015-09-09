/* NMEAParser
 *
 * This library is based on information from different sources on the internet.
 *
 * In theory is should be able to parse NMEA 0183 Version 2.3, so it is out of
 * date.
 *
 */
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
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <ctime>
#include <cmath>

namespace NMEA {
// Printable strings for Talker IDs
const char *const NMEATalkerIDName[NMEA_TALKER_ID_NUM] = {
    "Unknown", "GPS", "GLONASS"}; // NMEATalkerIDName

typedef struct NMEAMessageTypeString {
  enum NMEA_MESSAGE_TYPE Type;
  const char *String;
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
  NMEAMessage *Parse(const std::string &String) const;

private:
#ifndef DEBUG
#else
  FRIEND_TEST(ValidateChecksum, Valid_Checksum);
  FRIEND_TEST(ValidateChecksum, Invalid_Checksum);
  FRIEND_TEST(ValidateChecksum, Invalid_Empty_Message);
  FRIEND_TEST(ValidateChecksum, Invalid_Empty_Checksum);
  FRIEND_TEST(ValidateChecksum, Invalid_Short_Range_Checksum);
  FRIEND_TEST(ValidateChecksum, Invalid_Long_Range_Checksum);
#endif
  bool ValidateChecksum(const std::string &Message,
                        const std::string &Checksum) const;
#ifndef DEBUG
#else
  FRIEND_TEST(ParseTalkerID, Valid_GPS_TalkerID);
  FRIEND_TEST(ParseTalkerID, Valid_GLONASS_TalkerID);
  FRIEND_TEST(ParseTalkerID, Invalid_First_Check_TalkerID);
  FRIEND_TEST(ParseTalkerID, Invalid_Second_Check_TalkerID);
  FRIEND_TEST(ParseTalkerID, Invalid_Empty_TalkerID);
#endif
  enum NMEA_TALKER_ID ParseTalkerID(const std::string &ID) const;
#ifndef DEBUG
#else
  FRIEND_TEST(ParseMessageType, Valid_Message_Type);
  FRIEND_TEST(ParseMessageType, Invalid_Message_Type);
  FRIEND_TEST(ParseMessageType, Invalid_Empty_Message_Type);
#endif
  enum NMEA_MESSAGE_TYPE ParseMessageType(const std::string &Message) const;
#ifndef DEBUG
#else
  FRIEND_TEST(ParseTimeStamp_String_String, Valid_TimeStamp_Valid_DateStamp);
  FRIEND_TEST(ParseTimeStamp_String_String, Invalid_TimeStamp_Valid_DateStamp);
  FRIEND_TEST(ParseTimeStamp_String_String, Valid_TimeStamp_Invalid_DateStamp);
  FRIEND_TEST(ParseTimeStamp_String_String,
              Invalid_TimeStamp_Invalid_DateStamp);
  FRIEND_TEST(ParseTimeStamp_String_String,
              Invalid_Long_Range_TimeStamp_Valid_DateStamp);
  FRIEND_TEST(ParseTimeStamp_String_String,
              Invalid_Short_Range_TimeStamp_Valid_DateStamp);
  FRIEND_TEST(ParseTimeStamp_String_String,
              Valid_TimeStamp_Invalid_Long_Range_DateStamp);
  FRIEND_TEST(ParseTimeStamp_String_String,
              Valid_TimeStamp_Invalid_Short_Range_DateStamp);
  FRIEND_TEST(ParseTimeStamp_String_String,
              Invalid_Short_Range_TimeStamp_Invalid_Short_Range_DateStamp);
  FRIEND_TEST(ParseTimeStamp_String_String,
              Invalid_Long_Range_TimeStamp_Invalid_Long_Range_DateStamp);
  FRIEND_TEST(ParseTimeStamp_String_String, Invalid_Before_Epoch);
#endif
  time_t ParseTimeStamp(const std::string &TimeStamp,
                        const std::string &DataStamp) const;
#ifndef DEBUG
#else
  FRIEND_TEST(FieldParseTests, Valid_ParseTimeStamp_String);
  FRIEND_TEST(FieldParseTests, Invalid_ParseTimeStamp_String);
  FRIEND_TEST(FieldParseTests, Invalid_Range_ParseTimeStamp_String);
  FRIEND_TEST(FieldParseTests, Invalid_Empty_String_ParseTimeStamp_String);
#endif
  time_t ParseTimeStamp(const std::string &TimeStamp) const;
#ifndef DEBUG
#else
  FRIEND_TEST(ParseStatus, Valid_Active_RMC_Status);
  FRIEND_TEST(ParseStatus, Valid_Void_RMC_Status);
  FRIEND_TEST(ParseStatus, Valid_Active_GLL_Status);
  FRIEND_TEST(ParseStatus, Valid_Void_GLL_Status);
  FRIEND_TEST(ParseStatus, Valid_Fix_GGA_Status);
  FRIEND_TEST(ParseStatus, Valid_No_Fix_GGA_Status);
  FRIEND_TEST(ParseStatus, Valid_Fix_GSA_Status);
  FRIEND_TEST(ParseStatus, Valid_No_Fix_GSA_Status);
  FRIEND_TEST(ParseStatus, Invalid_Empty_Status);
#endif
  bool ParseStatus(const enum NMEA_MESSAGE_TYPE Type,
                   const std::string &Status) const;
#ifndef DEBUG
#else
  FRIEND_TEST(ParseLatitude, Valid_Latitude_Valid_North);
  FRIEND_TEST(ParseLatitude, Valid_Latitude_Valid_South);
  FRIEND_TEST(ParseLatitude, Valid_Latitude_Invalid_Direction);
  FRIEND_TEST(ParseLatitude, Invalid_Latitude_Valid_Direction);
  FRIEND_TEST(ParseLatitude, Invalid_Latitude_Invalid_Direction);
  FRIEND_TEST(ParseLatitude, Empty_Latitude_Valid_Direction);
  FRIEND_TEST(ParseLatitude, Empty_Latitude_Invalid_Direction);
  FRIEND_TEST(ParseLatitude, Empty_Latitude_Empty_Direction);
#endif
  float ParseLatitude(const std::string &Latitude,
                      const std::string &Direction) const;
#ifndef DEBUG
#else
  FRIEND_TEST(ParseLongitude, Valid_Longitude_Valid_East);
  FRIEND_TEST(ParseLongitude, Valid_Longitude_Valid_West);
  FRIEND_TEST(ParseLongitude, Valid_Longitude_Invalid_Direction);
  FRIEND_TEST(ParseLongitude, Invalid_Longitude_Valid_Direction);
  FRIEND_TEST(ParseLongitude, Invalid_Longitude_Invalid_Direction);
  FRIEND_TEST(ParseLongitude, Empty_Longitude_Valid_Direction);
  FRIEND_TEST(ParseLongitude, Empty_Longitude_Invalid_Direction);
  FRIEND_TEST(ParseLongitude, Empty_Longitude_Empty_Direction);
#endif
  float ParseLongitude(const std::string &Longitude,
                       const std::string &Direction) const;
#ifndef DEBUG
#else
  FRIEND_TEST(ParseSpeed, Valid_Speed);
  FRIEND_TEST(ParseSpeed, Invalid_Speed);
  FRIEND_TEST(ParseSpeed, Empty_Speed);
#endif
  float ParseSpeed(const std::string &Speed) const;
  float ParseAngle(const std::string &Angle) const;
  float
  ParseMagneticVariation(const std::string &MagneticVariation,
                         const std::string &MagneticVariatioDirection) const;
  int ParseSatiliteFixes(const std::string &SatiliteFixes) const;
  float ParseHDOP(const std::string &HDOP) const;
  float ParseMSL(const std::string &MDL) const;
  float ParseGeoidSeparation(const std::string &GeoidSeparation) const;
  float ParseDifferentialCorrectionAge(const std::string &CorrectionAge) const;
  float ParseDifferentialStationID(const std::string &StationID) const;
  float ParseCOGT(const std::string &CourseOverGroundTrue) const;
  float ParseCOGM(const std::string &CourseOverGroundMagnetic) const;
  float ParseSOG(const std::string &SpeedOverGround) const;
  char ParseModeIndicator(const std::string &ModeIndicator) const;
  char ParseSmode(const std::string &String) const;
  int ParseFixStatus(const std::string &String) const;
  int *ParseSV(std::vector<std::string>::iterator Start,
               std::vector<std::string>::iterator End) const;
  float ParsePDOP(const std::string &String) const;
  float ParseVDOP(const std::string &String) const;
}; // NMEAParser
} // NMEA
#endif
