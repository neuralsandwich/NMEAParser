/**
 * @file  NMEAParser.cpp
 * @brief Implementation of NMEAParser.h
 */
#include "NMEAParser.h"

#include <algorithm>
#include <cmath>
#include <ctime>
#include <iostream>
#include <stdexcept>

namespace NMEA {

bool NMEAParser::ValidateChecksum(const std::string &Message,
                                  const std::string &Checksum) const {
  unsigned int CalculatedChecksum = 0;
  unsigned int Check = 0;

  // Don't check the message length just make sure it is something there
  if (Message.empty()) {
    return false;
  }

  if (Checksum.empty() || Checksum.length() != 2) {
    return false;
  }

  for (unsigned int i = 1; i < (Message.length() - 3); ++i) {
    CalculatedChecksum ^= static_cast<unsigned int>(Message[i]);
  }

  Check = static_cast<unsigned int>(std::stoi(Checksum, nullptr, 16));

  if (Check == CalculatedChecksum)
    return true;

  return false;
} // ValidChecksum

enum NMEA_TALKER_ID NMEAParser::ParseTalkerID(const std::string &ID) const {
  if (ID[0] != 'G') {
    return NMEA_TALKER_ID::UNKNOWN_TALKER_ID;
  }

  if (ID[1] == 'P') {
    return NMEA_TALKER_ID::GPS;
  } else if (ID[1] == 'L') {
    return NMEA_TALKER_ID::GLONASS;
  } else {
    return NMEA_TALKER_ID::UNKNOWN_TALKER_ID;
  }
} // ParseTalkerID

enum NMEA_MESSAGE_TYPE
NMEAParser::ParseMessageType(const std::string &Message) const {
  if (Message.length() < 5) {
    return NMEA_MESSAGE_TYPE::UNKNOWN_MESSAGE;
  }

  for (int i = 0; i < NMEA_GPS_MESSAGE_NUM; ++i) {
    if (Message.substr(2, 3) == NMEAGPSMessageNames[i].String) {
      return NMEAGPSMessageNames[i].Type;
    }
  }

  return NMEA_MESSAGE_TYPE::UNKNOWN_MESSAGE;
} // ParseMessageType

static float ParseFloat(const std::string &String) {
  float Result = 0;
  try {
    Result = std::stof(String);
  } catch (const std::invalid_argument &ia) {
    std::cerr << "NMEAParser: ParseFloat: Invalid argument: " << ia.what()
              << "\n";
    return NAN;
  } catch (...) {
    std::cerr << "NMEAParser: ParseFloat: Unexpected exception";
    return NAN;
  }

  return Result;
} // ParseFloat

static int ParseInteger(const std::string &String) {
  int Result = 0;
  try {
    Result = std::stoi(String);
  } catch (const std::invalid_argument &ia) {
    std::cerr << "NMEAParser: ParseInteger: Invalid arugement: " << ia.what()
              << "\n";
    return 0;
  } catch (...) {
    std::cerr << "NMEAParser: ParseInteger: Unexpected exception";
    return 0;
  }

  return Result;
} // ParseInteger

time_t NMEAParser::ParseTimeStamp(const std::string &TimeStamp,
                                  const std::string &DateStamp) const {
  time_t Result = 0;
  struct tm *TimeInfo;

  // TimeStamp is in format HHMMSS in int
  time(&Result);
  TimeInfo = gmtime(&Result);
  if ((TimeStamp.length() >= 6) && (TimeStamp.length() <= 9) &&
      (DateStamp.length() == 6)) {
    try {
      TimeInfo->tm_mday = std::stoi(DateStamp.substr(0, 2), nullptr, 10);
      TimeInfo->tm_mon = std::stoi(DateStamp.substr(2, 2), nullptr, 10) - 1;
      TimeInfo->tm_year = std::stoi(DateStamp.substr(4, 2), nullptr, 10) + 100;
      TimeInfo->tm_hour = std::stoi(TimeStamp.substr(0, 2), nullptr, 10);
      TimeInfo->tm_min = std::stoi(TimeStamp.substr(2, 2), nullptr, 10);
      TimeInfo->tm_sec = std::stoi(TimeStamp.substr(4, 2), nullptr, 10);
      Result = mktime(TimeInfo);
    } catch (std::invalid_argument &) {
      Result = -1;
    } catch (std::out_of_range &) {
      Result = -1;
    }
  } else {
    Result = -1;
  }

  // We should never have to deal with anything before epoch.
  if (Result < 0) {
    Result = -1;
  }

  return Result;
} // ParseTimeStamp(TimeStamp DateStamp)

/**
 * ParserTimeStamp
 * @brief Parses time stamp string and returns a time_t
 *
 * ParserTimeStamp takes
 */
time_t NMEAParser::ParseTimeStamp(const std::string &TimeStamp) const {
  time_t Result = 0;
  struct tm *TimeInfo;

  time(&Result);
  TimeInfo = gmtime(&Result);
  char buffer[80];
  std::strftime(buffer, 80, "%d%m%y", TimeInfo);
  const std::string DateStamp(buffer);
  Result = ParseTimeStamp(TimeStamp, DateStamp);

  return Result;
} // ParseTimeStamp(TimeStamp)

bool NMEAParser::ParseStatus(const std::string &Status) const {
  if (Status.empty()) {
    return false;
  }

  if ("A" == Status) {
    return true;
  } else {
    return false;
  }
} // ParseStatus

int NMEAParser::ParseFixStatus(const std::string &Status) const {
  if (Status.empty()) {
    return 0;
  }

  if ((Status == "0") || (Status == "1") || (Status == "2") ||
      (Status == "6")) {
    return ParseInteger(Status);
  } else {
    return 0;
  }
} // ParseFixStatus

float NMEAParser::ParseLatitude(const std::string &Latitude,
                                const std::string &Direction) const {
  float Result = 0;

  if (Latitude.length() < 1 || Direction.length() < 1) {
    return NAN;
  }

  if ("S" != Direction && "N" != Direction) {
    return NAN;
  }

  Result = NMEA::ParseFloat(Latitude);

  if ("S" == Direction) {
    Result = 0 - Result;
  }

  return Result;
} // ParseLatitude

float NMEAParser::ParseLongitude(const std::string &Longitude,
                                 const std::string &Direction) const {
  float Result = 0;

  if (Longitude.length() < 1 || Direction.length() < 1) {
    return NAN;
  }

  if ("E" != Direction && "W" != Direction) {
    return NAN;
  }

  Result = NMEA::ParseFloat(Longitude);

  if ("W" == Direction)
    Result = 0 - Result;

  return Result;
} // ParseLongitude

float NMEAParser::ParseSpeed(const std::string &Speed) const {
  float Result = 0;

  if (Speed.length() < 1) {
    return NAN;
  }

  Result = NMEA::ParseFloat(Speed);

  return Result;
} // ParseSpeed

float NMEAParser::ParseAngle(const std::string &Angle) const {
  float Result = 0;

  Result = NMEA::ParseFloat(Angle);

  return Result;
} // ParseAngle

float NMEAParser::ParseMagneticVariation(
    const std::string &MagneticVariation,
    const std::string &MagneticVariationDirection) const {
  float Result = 0;

  if (MagneticVariationDirection.empty()) {
    return NAN;
  }

  if (MagneticVariationDirection != "W" && MagneticVariationDirection != "E") {
    return NAN;
  }

  Result = NMEA::ParseFloat(MagneticVariation);

  if ("W" == MagneticVariationDirection)
    Result = 0 - Result;

  return Result;
} // ParseMagneticVariation

int NMEAParser::ParseSatiliteFixes(const std::string &Fixes) const {
  int Result = 0;

  Result = ParseInteger(Fixes);

  return Result;
} // ParseSatiltieFixes

float NMEAParser::ParseHDOP(const std::string &HDOP) const {
  float Result = 0;

  Result = NMEA::ParseFloat(HDOP);

  return Result;
} // ParseHDOP

float NMEAParser::ParseMSL(const std::string &MSL) const {
  float Result = 0;

  Result = NMEA::ParseFloat(MSL);

  return Result;
} // ParseMSL

float NMEAParser::ParseGeoidSeparation(
    const std::string &GeoidSeparation) const {
  float Result = 0;

  Result = NMEA::ParseFloat(GeoidSeparation);

  return Result;
} // ParseGeoidSeparation

float NMEAParser::ParseDifferentialCorrectionAge(
    const std::string &CorrectionAge) const {
  float Result = 0;

  Result = NMEA::ParseFloat(CorrectionAge);

  return Result;
} // ParseDifferentialCorrectionAge

int NMEAParser::ParseDifferentialStationID(const std::string &StationID) const {
  int Result = 0;

  Result = NMEA::ParseInteger(StationID);

  return Result;
} // ParseDifferentialStationID

float NMEAParser::ParseCOGT(const std::string &CourseOverGroundTrue) const {
  float Result = 0;

  Result = NMEA::ParseFloat(CourseOverGroundTrue);

  return Result;
} // ParseCOGT

float NMEAParser::ParseCOGM(const std::string &CourseOverGroundMagnetic) const {
  float Result = 0;

  Result = NMEA::ParseFloat(CourseOverGroundMagnetic);

  return Result;
} // ParserCOGM

float NMEAParser::ParseSOG(const std::string &SpeedOverGround) const {
  float Result = 0;

  Result = NMEA::ParseFloat(SpeedOverGround);

  return Result;
} // ParseSOG

char NMEAParser::ParseModeIndicator(const enum NMEA_MESSAGE_TYPE Type,
                                    const std::string &ModeIndicator) const {
  char Result = 'N';

  if (ModeIndicator.empty()) {
    return Result;
  }

  if ((Type == NMEA_MESSAGE_TYPE::RMC) || (Type == NMEA_MESSAGE_TYPE::GLL) ||
      (Type == NMEA_MESSAGE_TYPE::VTG)) {
    if ((ModeIndicator[0] == 'N') || (ModeIndicator[0] == 'E') ||
        (ModeIndicator[0] == 'A') || (ModeIndicator[0] == 'D')) {
      return ModeIndicator[0];
    }
  }

  return Result;
} // ParseModeIndicator

char NMEAParser::ParseSmode(const std::string &String) const {
  char Result = 'M';

  if (String.empty()) {
    return Result;
  }

  if ('M' == String[0] || 'A' == String[0]) {
    Result = String[0];
  }

  return Result;
} // ParseSmode

int NMEAParser::ParseNavMode(const std::string &String) const {
  int Result = 1;

  Result = ParseInteger(String);

  if ((Result > 0) && (Result < 4)) {
    return Result;
  }

  return 1;
} // ParseNavMode

int *NMEAParser::ParseSV(std::vector<std::string>::iterator Start,
                         std::vector<std::string>::iterator End) const {
  std::vector<int> *Result = new std::vector<int>();
  std::vector<int> &ResultRef = *Result;

  for_each(Start, End,
           [&Result](std::string &s) { Result->push_back(ParseInteger(s)); });

  return &ResultRef[0];
} // ParseSV

float NMEAParser::ParseVDOP(const std::string &VDOP) const {
  float Result = 0;

  Result = NMEA::ParseFloat(VDOP);

  return Result;
} // ParseVDOP

float NMEAParser::ParsePDOP(const std::string &PDOP) const {
  float Result = 0;

  Result = NMEA::ParseFloat(PDOP);

  return Result;
} // ParsePDOP

static GPGSV *ParseGPGSV(std::vector<std::string> &Elements) {
  GPGSV *Result = new GPGSV{};

  Result->NoMSG = ParseInteger(Elements[1]);
  Result->MSGNo = ParseInteger(Elements[2]);
  Result->NoSV = ParseInteger(Elements[3]);

  std::vector<int> *SVs = new std::vector<int>();
  std::vector<int> *Elvs = new std::vector<int>();
  std::vector<int> *Azs = new std::vector<int>();
  std::vector<int> *Cnos = new std::vector<int>();
  std::vector<int> &SVsRef = *SVs;
  std::vector<int> &ElvsRef = *Elvs;
  std::vector<int> &AzsRef = *Azs;
  std::vector<int> &CnosRef = *Cnos;

  // This took a while to get
  unsigned int Iterations = 0;
  if (Result->MSGNo <= (Result->NoSV / 4)) {
    Iterations = 4;
  } else {
    Iterations = Result->NoSV % 4;
  }

  Result->DataFieldsInMessage = static_cast<int>(Iterations);

  for (unsigned int i = 0; i < Iterations; i++) {
    SVs->push_back(ParseInteger(Elements[4 + (i * 4)]));
    Elvs->push_back(ParseInteger(Elements[5 + (i * 4)]));
    Azs->push_back(ParseInteger(Elements[6 + (i * 4)]));
    Cnos->push_back(ParseInteger(Elements[7 + (i * 4)]));
  }

  Result->sv = &SVsRef[0];
  Result->elv = &ElvsRef[0];
  Result->az = &AzsRef[0];
  Result->cno = &CnosRef[0];

  return Result;
} // Parse GPGSV

NMEAMessage *NMEAParser::Parse(const std::string &Message) const {
  NMEAMessage *Result = new NMEAMessage{0, {0}};
  Result->Header = new NMEAHeader{NMEA_TALKER_ID::UNKNOWN_TALKER_ID,
                                  NMEA_MESSAGE_TYPE::UNKNOWN_MESSAGE, 0};
  std::vector<std::string> Elements(1);

  if (*(Message.begin()) != '$')
    return Result;

  for (auto it = Message.begin() + 1; it != Message.end(); ++it) {
    if (*it == ',' || *it == '*') {
      Elements.push_back(std::string());
      continue;
    } else {
      Elements.back() += *it;
    }
  }

  if (!ValidateChecksum(Message, Elements.back())) {
    return Result;
  }

  Result->Header->Valid = 1;
  Result->Header->ID = ParseTalkerID(Elements[0]);
  Result->Header->Type = ParseMessageType(Elements[0]);

  switch (Result->Header->Type) {

  case NMEA_MESSAGE_TYPE::RMC: {
    Result->RMC = new GPRMC{ParseTimeStamp(Elements[1], Elements[9]),
                            ParseStatus(Elements[2]),
                            ParseLatitude(Elements[3], Elements[4]),
                            ParseLongitude(Elements[5], Elements[6]),
                            ParseSpeed(Elements[7]),
                            ParseAngle(Elements[8]),
                            ParseMagneticVariation(Elements[10], Elements[11])};
  } break;

  case NMEA_MESSAGE_TYPE::GGA: {
    Result->GGA = new GPGGA{ParseTimeStamp(Elements[1]),
                            ParseLatitude(Elements[2], Elements[3]),
                            ParseLongitude(Elements[4], Elements[5]),
                            ParseFixStatus(Elements[6]),
                            ParseSatiliteFixes(Elements[7]),
                            ParseHDOP(Elements[8]),
                            ParseMSL(Elements[9]),
                            'M',
                            ParseGeoidSeparation(Elements[11]),
                            'M',
                            ParseDifferentialCorrectionAge(Elements[13]),
                            ParseDifferentialStationID(Elements[14])};
  } break;

  case NMEA_MESSAGE_TYPE::GLL: {
    Result->GLL = new GPGLL{
        ParseLatitude(Elements[1], Elements[2]),
        ParseLongitude(Elements[3], Elements[4]), ParseTimeStamp(Elements[5]),
        ParseStatus(Elements[6].c_str()),
        Elements[7][0]};
  } break;

  case NMEA_MESSAGE_TYPE::VTG: {
    Result->VTG =
        new GPVTG{ParseCOGT(Elements[1]), 'T', ParseCOGM(Elements[3]),  'M',
                  ParseSOG(Elements[5]),  'N', ParseSpeed(Elements[7]), 'K',
                  Elements[9][0]};
  } break;

  case NMEA_MESSAGE_TYPE::GSA: {
    Result->GSA =
        new GPGSA{ParseSmode(Elements[1]),
                  ParseNavMode(Elements[2]),
                  ParseSV(Elements.begin() + 3, Elements.begin() + 14),
                  ParsePDOP(Elements[15]),
                  ParseHDOP(Elements[16]),
                  ParseVDOP(Elements[17])};
  } break;

  case NMEA_MESSAGE_TYPE::GSV: {
    Result->GSV = ParseGPGSV(Elements);
  } break;

  default: { Result->Header->Valid = 1; } break;
  }

  return Result;
} // Parse
} // NMEA

// C API Functions
HNMEAParser *HNMEAParser_Create() {
  try {
    return reinterpret_cast<HNMEAParser *>(new NMEA::NMEAParser());
  } catch (...) {
    std::abort();
  }
} // HNMEAParser_Create

void HNMEAParser_Destroy(HNMEAParser *Parser) {
  try {
    delete reinterpret_cast<NMEA::NMEAParser *>(Parser);
  } catch (...) {
    std::abort();
  }
} // HNMEAParser_Destory

NMEAMessage *HNMEAParser_Parse(HNMEAParser *Parser, char *String) {
  try {
    NMEAMessage *Result =
        reinterpret_cast<NMEA::NMEAParser *>(Parser)->Parse(String);
    return Result;
  } catch (std::exception &e) {
    std::cout << e.what();
    std::abort();
  }
}
