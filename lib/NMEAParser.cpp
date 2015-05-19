#include "NMEAParser.h"

namespace NMEA {
NMEAMessage *NMEAParser::Parse(const std::string &Message) {
  NMEAMessage *Result = new NMEAMessage{0};
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

  if (!ValidateChecksum(&Message, &Elements.back())) {
    return Result;
  }

  Result->Header->Valid = 1;
  Result->Header->ID = ParseTalkerID(&Elements.at(0));
  Result->Header->Type = ParseMessageType(&Elements.at(0));

  switch (Result->Header->Type) {

  case NMEA_MESSAGE_TYPE::RMC: {
    Result->RMC =
        new GPRMC{ParseTimeStamp(&Elements.at(1), &Elements.at(9)),
                  ParseStatus(&Elements.at(2)),
                  ParseLatitude(&Elements.at(3), &Elements.at(4)),
                  ParseLongitude(&Elements.at(5), &Elements.at(6)),
                  ParseSpeed(&Elements.at(7)), ParseAngle(&Elements.at(8)),
                  ParseMagneticVariation(&Elements.at(10), &Elements.at(11))};
  } break;

  case NMEA_MESSAGE_TYPE::GGA: {
    Result->GGA = new GPGGA{
        ParseTimeStamp(&Elements.at(1)),
        ParseLatitude(&Elements.at(2), &Elements.at(3)),
        ParseLongitude(&Elements.at(4), &Elements.at(5)),
        ParseStatus(&Elements.at(6)), ParseSatiliteFixes(&Elements.at(7)),
        ParseHDOP(&Elements.at(8)), ParseMSL(&Elements.at(9)), 'M',
        ParseGeoidSeparation(&Elements.at(11)), 'M',
        ParseDifferentialCorrectionAge(&Elements.at(13)),
        ParseDifferentialStationID(&Elements.at(14))};
  } break;

  case NMEA_MESSAGE_TYPE::GLL: {
    Result->GLL = new GPGLL{ParseLatitude(&Elements.at(1), &Elements.at(2)),
                            ParseLongitude(&Elements.at(3), &Elements.at(4)),
                            ParseTimeStamp(&Elements.at(5)),
                            ParseStatus(&Elements.at(6)), Elements.at(7).at(0)};
  } break;

  case NMEA_MESSAGE_TYPE::VTG: {
    Result->VTG =
        new GPVTG{ParseCOGT(&Elements.at(1)), 'T', ParseCOGM(&Elements.at(3)),
                  'M', ParseSOG(&Elements.at(5)), 'N',
                  ParseSpeed(&Elements.at(7)), 'K', Elements.at(9).at(0)};
  } break;

  case NMEA_MESSAGE_TYPE::GSA: {
    Result->GSA =
        new GPGSA{ParseSmode(&Elements.at(1)), ParseFixStatus(&Elements.at(2)),
                  ParseSV(Elements.begin() + 3, Elements.begin() + 14),
                  ParsePDOP(&Elements.at(15)), ParseHDOP(&Elements.at(16)),
                  ParseVDOP(&Elements.at(17))};
  } break;

  default: { Result->Header->Valid = 1; } break;
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

  for (int i = 0; i < NMEA_GPS_MESSAGE_NUM; ++i) {
    if (Message->substr(2,3) == NMEAGPSMessageNames[i].String) {
      return NMEAGPSMessageNames[i].Type;
    }
  }

  return NMEA_MESSAGE_TYPE::UNKNOWN_MESSAGE;
} // ParseMessageType

float ParseFloat(const std::string *String) {
  float Result = 0;
  try {
    Result = std::stof(*String);
  } catch (const std::invalid_argument &ia) {
    std::cerr << "NMEAParser: ParseFloat: Invalid arugement: " << ia.what()
              << "\n";
  } catch (...) {
    std::cerr << "NMEAParser: ParseFloat: Unexpected exception";
  }

  return Result;
} // ParseFloat

float ParseInteger(const std::string &String) {
  float Result = 0;
  try {
    Result = std::stoi(String);
  } catch (const std::invalid_argument &ia) {
    return 0;
  } catch (...) {
    std::cerr << "NMEAParser: ParseInteger: Unexpected exception";
    return 0;
  }

  return Result;
} // ParseInteger

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

  Result = NMEA::ParseFloat(Latitude);

  if ("S" == *Direction)
    Result = 0 - Result;

  return Result;
} // ParseLatitude

float NMEAParser::ParseLongitude(const std::string *Longitude,
                                 const std::string *Direction) {
  float Result = 0;

  Result = NMEA::ParseFloat(Longitude);

  if ("W" == *Direction)
    Result = 0 - Result;

  return Result;
} // ParseLongitude

float NMEAParser::ParseSpeed(const std::string *Speed) {
  float Result = 0;

  Result = NMEA::ParseFloat(Speed);

  return Result;
} // ParseSpeed

float NMEAParser::ParseAngle(const std::string *Angle) {
  float Result = 0;

  Result = NMEA::ParseFloat(Angle);

  return Result;
} // ParseAngle

float NMEAParser::ParseMagneticVariation(
    const std::string *MagneticVariation,
    const std::string *MagneticVariatioDirection) {
  float Result = 0;

  Result = NMEA::ParseFloat(MagneticVariation);

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

  Result = NMEA::ParseFloat(HDOP);

  return Result;
} // ParseHDOP

float NMEAParser::ParseMSL(const std::string *MSL) {
  float Result = 0;

  Result = NMEA::ParseFloat(MSL);

  return Result;
} // ParseHDOP

float NMEAParser::ParseGeoidSeparation(const std::string *GeoidSeparation) {
  float Result = 0;

  Result = NMEA::ParseFloat(GeoidSeparation);

  return Result;
} // ParseGeoidSeparation

float NMEAParser::ParseDifferentialCorrectionAge(
    const std::string *CorrectionAge) {
  float Result = 0;

  if (CorrectionAge->empty())
    return Result;

  Result = NMEA::ParseFloat(CorrectionAge);

  return Result;
} // ParseDifferentialCorrectionAge

float NMEAParser::ParseDifferentialStationID(const std::string *StationID) {
  float Result = 0;

  Result = NMEA::ParseFloat(StationID);

  return Result;
} // ParseDifferentialStationID

float NMEAParser::ParseCOGT(const std::string *CourseOverGroundTrue) {
  float Result = 0;

  Result = NMEA::ParseFloat(CourseOverGroundTrue);

  return Result;
} // ParseCOGT

float NMEAParser::ParseCOGM(const std::string *CourseOverGroundMagnetic) {
  float Result = 0;

  if (CourseOverGroundMagnetic->empty())
    return Result;

  Result = NMEA::ParseFloat(CourseOverGroundMagnetic);

  return Result;
} // ParserCOGM

float NMEAParser::ParseSOG(const std::string *SpeedOverGround) {
  float Result = 0;

  Result = NMEA::ParseFloat(SpeedOverGround);

  return Result;
} // ParseSOG

char NMEAParser::ParseModeIndicator(const std::string *ModeIndicator) {
  char Result = 'N';

  if ((*ModeIndicator->c_str() == 'N') || (*ModeIndicator->c_str() == 'E') ||
      (*ModeIndicator->c_str() == 'D') || (*ModeIndicator->c_str() == 'A')) {
    Result = *ModeIndicator->c_str();
  }

  return Result;
} // ParseModeIndicator

char NMEAParser::ParseSmode(const std::string *String) {
  char Result = '1';

  if ('M' == String->at(0) || 'A' == String->at(0)) {
    Result = String->at(0);
  }

  return Result;
} // ParseSmode

int NMEAParser::ParseFixStatus(const std::string *String) {
  int Result = 1;

  Result = ParseInteger(*String);

  if ((Result > 0) && (Result < 4)) {
    return Result;
  }

  return 1;
} // ParseFixStatus

int *NMEAParser::ParseSV(std::vector<std::string>::iterator Start,
                         std::vector<std::string>::iterator End) {
  std::vector<int> *Result = new std::vector<int>();

  for_each(Start, End,
           [&Result](std::string &s) { Result->push_back(ParseInteger(s)); });

  return &Result->at(0);
} // ParseSV

float NMEAParser::ParseVDOP(const std::string *VDOP) {
  float Result = 0;

  Result = NMEA::ParseFloat(VDOP);

  return Result;
} // ParseVDOP

float NMEAParser::ParsePDOP(const std::string *PDOP) {
  float Result = 0;

  Result = NMEA::ParseFloat(PDOP);

  return Result;
} // ParsePDOP

} // NMEA

// C API Functions
HNMEAParser *HNMEAParser_Create() {
  try {
    return reinterpret_cast<HNMEAParser *>(new NMEA::NMEAParser());
  } catch (...) {
    std::abort();
    return nullptr;
  }
} // HNMEAParser_Create

void HNMEAParser_Destroy(HNMEAParser *Parser) {
  try {
    delete reinterpret_cast<NMEA::NMEAParser *>(Parser);
  } catch (...) {
    std::abort();
  }
} // HNMEAParser_Destory

NMEAMessage *HNMEAParser_Parse(HNMEAParser *const Parser, const char *String) {
  try {
    NMEAMessage *Result =
        reinterpret_cast<NMEA::NMEAParser *>(Parser)->Parse(String);
    return Result;
  } catch (std::exception &e) {
    std::cout << e.what();
    std::abort();
    return nullptr;
  }
}
