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
const char *const NMEATalkerIDName[NMEA_TALKER_ID_NUM] =
    {[UNKNOWN_TALKER_ID] = "Unknown", [GPS] = "GPS",
     [GLONASS] = "GLONASS"}; // NMEATalkerIDName

// Printable strings for Message types
const char *const NMEAGPSMessageName[NMEA_GPS_MESSAGE_NUM] =
    {[UNKNOWN_MESSAGE] = "Unknown", [RMC] = "RMC", [GGA] = "GGA",
     [GLL] = "GLL"}; // NMEAGPSMessageName

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
}; // NMEAParser
} // NMEA
#endif
