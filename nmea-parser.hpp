#ifndef NMEA_PARSER_HPP
#define NMEA_PARSER_HPP

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <ctime>

namespace NMEA {

#define COMMANDSTART 0x24
#define SENTENCESEPARATOR 0x2C
#define CHECKSUMSTART 0x2A

#define NMEA_TALKER_ID_NAME /**/                                               \
  (char const *const[NMEA_TALKER_ID_NUM]) {                                    \
    [UNKNOWN_TALKER_ID] = "Unknown", [GPS] = "GPS", [GLONASS] = "GLONASS",     \
  }

#define NMEA_GPS_MESSAGE_NAME /**/                                             \
  (char const *const[NMEA_GPS_MESSAGE_NUM]) {                                  \
    [UNKNOWN_GPS_MESSAGE] = "Unknown",                                         \
  }

enum NMEA_TALKER_ID {
  UNKNOWN_TALKER_ID,
  GPS,
  GLONASS,
  NMEA_TALKER_ID_NUM,
};

enum NMEA_GPS_MESSAGE {
  UNKNOWN_GPS_MESSAGE,
  AAM, // Waypoint Arrival Alarm
  ALM, // Almanac data
  APA, // Auto Pilot A sentence
  APB, // Auto Pilot B sentence
  BOD, // Bearing Origin to Destination
  BWC, // Bearing using Great Circle route
  DTM, // Datum being used.
  GAA, // Fix information
  GLL, // Lat/Lon data
  GRS, // GPS Range Residuals
  GSA, // Overall Satellite data
  GST, // GPS Pseudorange Noise Statistics
  GSV, // Detailed Satellite data
  MSK, // send control for a beacon receiver
  MSS, // Beacon receiver status information.
  RMA, // recommended Loran data
  RMB, // recommended navigation data for gps
  RMC, // recommended minimum data for gps
  RTE, // route message
  TRF, // Transit Fix Data
  STN, // Multiple Data ID
  VBW, // dual Ground / Water Spped
  VTG, // Vector track an Speed over the Ground
  WCV, // Waypoint closure velocity (Velocity Made Good)
  WPL, // Waypoint Location information
  XTC, // cross track error
  XTE, // measured cross track error
  ZTG, // Zulu (UTC) time and time to go (to destination)
  ZDA, // Date and Time
  NMEA_GPS_MESSAGE_NUM,
};

class NMEAData {
public:
  NMEAData(NMEA_TALKER_ID TalkerID, NMEA_GPS_MESSAGE MessageType)
      : ID_(TalkerID), Type_(MessageType){};
  NMEAData(NMEA_TALKER_ID TalkerID, NMEA_GPS_MESSAGE MessageType,
           const std::string DataSentence)
      : ID_(TalkerID), Type_(MessageType), Data_(DataSentence){};
  enum NMEA_TALKER_ID GetTalkerID() { return ID_; };
  enum NMEA_GPS_MESSAGE GetType() { return Type_; };

  const std::string Print() const {
    std::string Result("Talker ID: ");
    Result.append(NMEA_TALKER_ID_NAME[ID_]);
    Result.append("\nMessage Type: ");
    Result.append(NMEA_GPS_MESSAGE_NAME[Type_]);

    return Result;
  };

private:
  const NMEA_TALKER_ID ID_;
  const NMEA_GPS_MESSAGE Type_;
  const std::string Data_;
};

class NMEAParser {
public:
  NMEAParser() {}

  NMEAData const parse(const std::string *str) {
    NMEAData Result = NMEAData(UNKNOWN_TALKER_ID, UNKNOWN_GPS_MESSAGE);

    // Strings starting without $ are invalid
    if (COMMANDSTART != str->at(0))
      return Result;

    // TODO: Handle message from GLONASS
    if (('G' != str->at(1)) || ('P' != str->at(2)))
      return Result;

    // TODO: Check if a command is longer or shorter than 3 characters
    if (str->at(6) != SENTENCESEPARATOR)
      return Result;

    std::string TalkerID = str->substr(1, 2);
    std::string MessageType = str->substr(3, 3);

    std::string DataSentence = str->substr(7, str->length() - 4);
    const std::string Checksum =
        str->substr(str->length() - 2, (str->length() - 1));

    // Validate Checksum
    if (!ValidateChecksum(str, &Checksum))
      return Result;

    if ("GP" == TalkerID)
      return NMEAData(NMEA_TALKER_ID::GPS, UNKNOWN_GPS_MESSAGE);

    if ("RMC" == MessageType) {
      // GPRMCParseTimestamp(&DataSentence);
    }

    // Result = NMEAData(TalkerID, MessageType);

    return Result;
  }

private:
  bool ValidateChecksum(const std::string *Message,
                        const std::string *Checksum) {
    unsigned int CalculatedChecksum = 0;
    unsigned int Check = 0;

    for (unsigned int i = 1; i < (Message->length() - 3); ++i) {
      CalculatedChecksum ^= Message->at(i);
    }

    Check = std::stoi(*Checksum, nullptr, 16);

    if (Check == CalculatedChecksum)
      return true;

    return false;
  }
};
};
#endif
