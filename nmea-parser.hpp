#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <ctime>

namespace nmea_parser {

#define COMMANDSTART 0x24
#define SENTENCESEPARATOR 0x2C
#define CHECKSUMSTART 0x2A

class NMEAData {
public:
  NMEAData() {};
  NMEAData(const std::string TalkerID, const std::string MessageType)
      : ID(TalkerID), Type(MessageType) {};
  NMEAData(const std::string TalkerID, const std::string MessageType,
           const std::string DataSentence)
      : ID(TalkerID), Type(MessageType), Data(DataSentence) {}
  std::string GetType() {
    return Type;
  };
  std::string GetTalkerID() {
    return ID;
  };
  std::string Print() {
    std::string Result;

    Result = "Talker ID: ";
    Result += ID + "\n";

    Result += "Message Type: ";
    Result += Type + "\n";

    return Result;
  };

  std::string ID;
  std::string Type;
  std::string Data;
};

class GPRMC : NMEAData {
public:
  GPRMC(const std::string TalkerID, const std::string MessageType,
        time_t TimeStamp, char Status, float Latitude, char LatitudeDirection,
        float Longitude, char LongitudeDirection, float Speed, float Angle,
        int Date, float MagneticVariation, char MagneticVariationDirection,
        std::string Checksum)
      : NMEAData(TalkerID, MessageType), TimeStamp(TimeStamp), Status(Status),
        Latitude(Latitude), LatitudeDirection(LatitudeDirection),
        Longitude(Longitude), LongitudeDirection(LongitudeDirection),
        Speed(Speed), Angle(Angle), Date(Date),
        MagneticVariation(MagneticVariation),
        MagneticVariationDirection(MagneticVariationDirection),
        Checksum(Checksum) {};

private:
  // Timestamp when fix was taken
  time_t TimeStamp;
  // Status A = active, V = void
  char Status;
  // Latitude of position:
  // e.g. 4807.038,N = 48 deg 07.038' N
  float Latitude;
  char LatitudeDirection;
  // Longitude of position:
  // e.g. 01131.000,E = 11 deg 31.000' E
  float Longitude;
  char LongitudeDirection;
  // Speed over the ground in knots
  float Speed;
  // Track angle in degrees True
  float Angle;
  // Date - date stamp
  // e.g. 230394 = 23rd of March 1994
  int Date;
  // Magnetic Variation
  // e.g. 003.1,W
  float MagneticVariation;
  char MagneticVariationDirection;
  // Checksum data
  // e.g. *6A
  std::string Checksum;
};

class NMEAParser {
public:
  NMEAParser() {}

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

  int GPRMCParseTimestamp(std::string *DataSentence) {
    time_t Result;
    struct tm *TimeInfo;

    const std::string StringHour = DataSentence->substr(0, 2);
    const std::string StringMinute = DataSentence->substr(2, 2);
    const std::string StringSecond = DataSentence->substr(4, 2);

    int Hour = std::stoi(StringHour, nullptr, 10);
    int Minute = std::stoi(StringMinute, nullptr, 10);
    int Second = std::stoi(StringSecond, nullptr, 10);

    time(&Result);
    // TODO: Do we want local time?
    TimeInfo = localtime(&Result);
    TimeInfo->tm_hour = Hour;
    TimeInfo->tm_min = Minute;
    TimeInfo->tm_sec = Second;
    Result = mktime(TimeInfo);

    char buffer[80];
    strftime(buffer, 80, "Time: %F %T", TimeInfo);
    std::cout << buffer << "\n";

    return Result;
  };

  NMEAData parse(const std::string *str) {
    NMEAData Result;

    // Strings starting without $ are invalid
    if (COMMANDSTART != str->at(0))
      return NMEAData("NONE", "INVALID");

    // TODO: Handle message from GLONASS
    if (('G' != str->at(1)) || ('P' != str->at(2)))
      return NMEAData("NONE", "INVALID");

    // TODO: Check if a command is longer or shorter than 3 characters
    if (str->at(6) != SENTENCESEPARATOR)
      return NMEAData("NONE", "INVALID");

    std::string TalkerID = str->substr(1, 2);
    std::string MessageType = str->substr(3, 3);

    if ("RMC" == MessageType) {
      std::string DataSentence = str->substr(7, str->length() - 4);
      const std::string Checksum =
          str->substr(str->length() - 2, (str->length() - 1));

      // Validate Checksum
      if (!ValidateChecksum(str, &Checksum))
        return NMEAData("NONE", "INVALID");

      GPRMCParseTimestamp(&DataSentence);
    }

    // Result = NMEAData(TalkerID, MessageType);

    return Result;
  }
};
};
