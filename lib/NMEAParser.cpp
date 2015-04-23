#include "NMEAParser.h"

namespace NMEA {
NMEAData *NMEAParser::Parse(const std::string *Message) {
  NMEAData *Result = new NMEAData(NMEA_TALKER_ID::UNKNOWN_TALKER_ID,
                                  NMEA_MESSAGE_TYPE::UNKNOWN_MESSAGE, false);
  std::vector<std::string> Elements(1);

  if (*(Message->begin()) != '$')
    return Result;

  for (auto it = Message->begin() + 1; it != Message->end(); ++it) {
    if (*it == ',' || *it == '*') {
      Elements.push_back(std::string());
      continue;
    } else {
      Elements.back() += *it;
    }
  }

  NMEA_TALKER_ID TalkerID = ParseTalkerID(&Elements.at(0));
  NMEA_MESSAGE_TYPE MessageType = ParseMessageType(&Elements.at(0));
  if (!ValidateChecksum(Message, &Elements.back()))
    return new NMEAData(TalkerID, MessageType, false);

  switch (MessageType) {

  // TODO: Implement Message factory
  case NMEA_MESSAGE_TYPE::RMC: {
    time_t TimeStamp = ParseTimeStamp(&Elements.at(1), &Elements.at(9));
    bool Status = ParseStatus(&Elements.at(2));
    float Latitude = ParseLatitude(&Elements.at(3), &Elements.at(4));
    float Longitude = ParseLongitude(&Elements.at(5), &Elements.at(6));
    float Speed = ParseSpeed(&Elements.at(7));
    float Angle = ParseAngle(&Elements.at(8));
    float MagneticVariation =
        ParseMagneticVariation(&Elements.at(10), &Elements.at(11));
    Result = new GPRMC(TimeStamp, Status, Latitude, Longitude, Speed, Angle,
                       MagneticVariation, true);
  } break;

  case NMEA_MESSAGE_TYPE::GGA: {
    time_t TimeStamp = ParseTimeStamp(&Elements.at(1));
    float Latitude = ParseLatitude(&Elements.at(2), &Elements.at(3));
    float Longitude = ParseLongitude(&Elements.at(4), &Elements.at(5));
    bool Status = ParseStatus(&Elements.at(6));
    int SatilitesFixes = ParseSatiliteFixes(&Elements.at(7));
    float HDOP = ParseHDOP(&Elements.at(8));
    float MSL = ParseMSL(&Elements.at(9));
    char uMSL = 'M';
    float GeoidSeparation = ParseGeoidSeparation(&Elements.at(11));
    char uSep = 'M';
    std::cout << "1: " << Elements.at(13) << "''\n";
    float DifferentialCorrectionAge =
        ParseDifferentialCorrectionAge(&Elements.at(13));

    float DifferentialStationID = ParseDifferentialStationID(&Elements.at(14));
    Result = new GPGGA(TimeStamp, Latitude, Longitude, Status, SatilitesFixes,
                       HDOP, MSL, uMSL, GeoidSeparation, uSep,
                       DifferentialCorrectionAge, DifferentialStationID, true);
  } break;

  default: { Result = new NMEAData(TalkerID, MessageType, true); } break;
  }

  return Result;
} // Parse

bool NMEAParser::ValidateChecksum(const std::string *Message,
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
} // ValidChecksum

enum NMEA_TALKER_ID NMEAParser::ParseTalkerID(const std::string *ID) {
  if (ID->at(0) != 'G')
    return NMEA_TALKER_ID::UNKNOWN_TALKER_ID;

  if (ID->at(1) == 'P')
    return NMEA_TALKER_ID::GPS;

  if (ID->at(1) == 'L')
    return NMEA_TALKER_ID::GLONASS;

  // Shouldn't reach here unless something weird happened
  return NMEA_TALKER_ID::UNKNOWN_TALKER_ID;
} // ParseTalkerID

enum NMEA_MESSAGE_TYPE
NMEAParser::ParseMessageType(const std::string *Message) {
  if (Message->at(2) != 'R' && Message->at(2) != 'G')
    return NMEA_MESSAGE_TYPE::UNKNOWN_MESSAGE;

  if (Message->at(3) != 'M' && Message->at(3) != 'G')
    return NMEA_MESSAGE_TYPE::UNKNOWN_MESSAGE;

  if (Message->at(4) == 'C')
    return NMEA_MESSAGE_TYPE::RMC;

  if (Message->at(4) == 'A')
    return NMEA_MESSAGE_TYPE::GGA;
} // ParseMessageType

time_t NMEAParser::ParseTimeStamp(const std::string *TimeStamp,
                                  const std::string *DateStamp) {
  time_t Result;
  struct tm *TimeInfo;

  // TimeStamp is in format HHMMSS in int

  time(&Result);
  // TODO: Do we want local time? No we don't
  TimeInfo = localtime(&Result);
  TimeInfo->tm_mday = std::stoi(DateStamp->substr(0, 2), nullptr, 10);
  TimeInfo->tm_mon = std::stoi(DateStamp->substr(2, 2), nullptr, 10);
  TimeInfo->tm_year = std::stoi(DateStamp->substr(4, 2), nullptr, 10);
  TimeInfo->tm_hour = std::stoi(TimeStamp->substr(0, 2), nullptr, 10);
  TimeInfo->tm_min = std::stoi(TimeStamp->substr(2, 2), nullptr, 10);
  TimeInfo->tm_sec = std::stoi(TimeStamp->substr(4, 2), nullptr, 10);
  Result = mktime(TimeInfo);

  return Result;
} // ParseTimeStamp(TimeStamp DateStamp)

time_t NMEAParser::ParseTimeStamp(const std::string *TimeStamp) {
  time_t Result;
  struct tm *TimeInfo;

  // TimeStamp is in format HHMMSS in int

  time(&Result);
  // TODO: Do we want local time? No we don't
  TimeInfo = localtime(&Result);
  TimeInfo->tm_hour = std::stoi(TimeStamp->substr(0, 2), nullptr, 10);
  TimeInfo->tm_min = std::stoi(TimeStamp->substr(2, 2), nullptr, 10);
  TimeInfo->tm_sec = std::stoi(TimeStamp->substr(4, 2), nullptr, 10);
  Result = mktime(TimeInfo);

  return Result;
} // ParseTimeStamp(TimeStamp)

bool NMEAParser::ParseStatus(const std::string *Status) {
  bool Result = false;

  if ("A" == *Status)
    Result = true;

  return Result;
} // ParseStatus

float NMEAParser::ParseLatitude(const std::string *Latitude,
                                const std::string *Direction) {
  float Result = 0;

  Result = std::stof(*Latitude);

  if ("S" == *Direction)
    Result = 0 - Result;

  return Result;
} // ParseLatitude

float NMEAParser::ParseLongitude(const std::string *Longitude,
                                 const std::string *Direction) {
  float Result = 0;

  Result = std::stof(*Longitude);

  if ("W" == *Direction)
    Result = 0 - Result;

  return Result;
} // ParseLongitude

float NMEAParser::ParseSpeed(const std::string *Speed) {
  float Result = 0;

  Result = std::stof(*Speed);

  return Result;
} // ParseSpeed

float NMEAParser::ParseAngle(const std::string *Angle) {
  float Result = 0;

  Result = std::stof(*Angle);

  return Result;
} // ParseAngle

float NMEAParser::ParseMagneticVariation(
    const std::string *MagneticVariation,
    const std::string *MagneticVariatioDirection) {
  float Result = 0;

  Result = std::stof(*MagneticVariation);

  if ("W" == *MagneticVariatioDirection)
    Result = 0 - Result;

  return Result;
} // ParseMagneticVariation

int NMEAParser::ParseSatiliteFixes(const std::string *Fixes) {
  int Result = 0;

  Result = std::stoi(*Fixes);

  return Result;
} // ParseSatiltieFixes

float NMEAParser::ParseHDOP(const std::string *HDOP) {
  float Result = 0;

  Result = std::stof(*HDOP);

  return Result;
} // ParseHDOP

float NMEAParser::ParseMSL(const std::string *MSL) {
  float Result = 0;

  Result = std::stof(*MSL);

  return Result;
} // ParseHDOP

float NMEAParser::ParseGeoidSeparation(const std::string *GeoidSeparation) {
  float Result;

  Result = std::stof(*GeoidSeparation);

  return Result;
} // ParseGeoidSeparation

float
NMEAParser::ParseDifferentialCorrectionAge(const std::string *CorrectionAge) {
  float Result;

  if (CorrectionAge->empty())
    return Result;

  Result = std::stof(*CorrectionAge);

  return Result;
} // ParseDifferentialCorrectionAge

float NMEAParser::ParseDifferentialStationID(const std::string *StationID) {
  float Result;

  Result = std::stof(*StationID);

  return Result;
} // ParseDifferentialStationID
} // NMEA
