#include "NMEAParser.h"

namespace NMEA {
NMEAData NMEAParser::Parse(const std::string *Message) {
  NMEAData Result = NMEAData(NMEA_TALKER_ID::UNKNOWN_TALKER_ID,
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
    return NMEAData(TalkerID, MessageType, false);

  switch (MessageType) {

  // TODO: Implement Message factory

  default: { Result = NMEAData(TalkerID, MessageType, true); } break;
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
    if (Message->at(2) != 'R')
      return NMEA_MESSAGE_TYPE::UNKNOWN_MESSAGE;

    if (Message->at(3) != 'M')
      return NMEA_MESSAGE_TYPE::UNKNOWN_MESSAGE;

    if (Message->at(4) != 'C')
      return NMEA_MESSAGE_TYPE::UNKNOWN_MESSAGE;

    return NMEA_MESSAGE_TYPE::RMC;
} // ParseMessageType
};
