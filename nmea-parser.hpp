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
    [UNKNOWN_MESSAGE] = "Unknown", [RMC] = "RMC",                              \
  }

enum NMEA_TALKER_ID {
  UNKNOWN_TALKER_ID,
  GPS,
  GLONASS,
  NMEA_TALKER_ID_NUM,
};

enum NMEA_MESSAGE_TYPE {
  UNKNOWN_MESSAGE,
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
  NMEAData(NMEA_TALKER_ID TalkerID, NMEA_MESSAGE_TYPE MessageType,
           bool ValidChecksum)
      : ID_(TalkerID), Type_(MessageType), Valid_(ValidChecksum){};
  NMEAData(NMEA_TALKER_ID TalkerID, NMEA_MESSAGE_TYPE MessageType,
           const std::string DataSentence)
      : ID_(TalkerID), Type_(MessageType), Data_(DataSentence), Valid_(true){};

  ~NMEAData(){};

  enum NMEA_TALKER_ID GetTalkerID() { return ID_; };
  enum NMEA_MESSAGE_TYPE GetType() { return Type_; };

  bool IsValid() { return Valid_; };

  const std::string Print() const {
    std::string Result("Talker ID: ");
    Result.append(NMEA_TALKER_ID_NAME[ID_]);
    Result.append("\nMessage Type: ");
    Result.append(NMEA_GPS_MESSAGE_NAME[Type_]);

    if (Valid_) {
      Result.append("\nChecksum: Valid");
    } else {
      Result.append("\nChecksum: Invalid");
    }

    return Result;
  };

private:
  NMEA_TALKER_ID ID_;
  NMEA_MESSAGE_TYPE Type_;
  std::string Data_;
  bool Valid_;
};

class NMEAParser {
public:
  NMEAParser() {}

  NMEAData const parse(const std::string *str) {
    NMEAData Result = NMEAData(NMEA_TALKER_ID::UNKNOWN_TALKER_ID,
                               NMEA_MESSAGE_TYPE::UNKNOWN_MESSAGE, false);
    std::vector<std::string> Elements(1);

    if (*(str->begin()) != '$')
      return Result;

    for (auto it = str->begin() + 1; it != str->end(); ++it) {
      if (*it == ',' || *it == '*') {
        Elements.push_back(std::string());
        continue;
      } else {
        Elements.back() += *it;
      }
    }

    NMEA_TALKER_ID TalkerID = ParseTalkerID(&Elements.at(0));
    NMEA_MESSAGE_TYPE MessageType = ParseMessageType(&Elements.at(0));
    if (!ValidChecksum(str, &Elements.back()))
      return NMEAData(TalkerID, MessageType, false);

    switch (MessageType) {

      // TODO: Implement Message factory
      
    default: { Result = NMEAData(TalkerID, MessageType, true); } break;
    }

    return Result;
  }

private:
  bool ValidChecksum(const std::string *Message, const std::string *Checksum) {
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

  NMEA_TALKER_ID ParseTalkerID(const std::string *ID) {
    if (ID->at(0) != 'G')
      return NMEA_TALKER_ID::UNKNOWN_TALKER_ID;

    if (ID->at(1) == 'P')
      return NMEA_TALKER_ID::GPS;

    if (ID->at(1) == 'L')
      return NMEA_TALKER_ID::GLONASS;

    // Shouldn't reach here unless something weird happened
    return NMEA_TALKER_ID::UNKNOWN_TALKER_ID;
  }

  NMEA_MESSAGE_TYPE ParseMessageType(const std::string *Message) {
    if (Message->at(2) != 'R')
      return NMEA_MESSAGE_TYPE::UNKNOWN_MESSAGE;

    if (Message->at(3) != 'M')
      return NMEA_MESSAGE_TYPE::UNKNOWN_MESSAGE;

    if (Message->at(4) != 'C')
      return NMEA_MESSAGE_TYPE::UNKNOWN_MESSAGE;

    return NMEA_MESSAGE_TYPE::RMC;
  }
};
};
#endif
