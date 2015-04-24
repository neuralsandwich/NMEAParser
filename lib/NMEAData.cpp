#include "NMEAParser.h"

namespace NMEA {
enum NMEA_TALKER_ID NMEAData::GetTalkerID() const { return ID_; } // GetTalkerID

enum NMEA_MESSAGE_TYPE NMEAData::GetMessageType() const {
  return Type_;
} // GetMessageType

bool NMEAData::IsValid() const { return Valid_; } // IsValid

std::string NMEAData::Print() const {
  std::string Result("Talker ID: ");
  Result.append(NMEATalkerIDName[ID_]);
  Result.append("\nMessage Type: ");
  Result.append(NMEAGPSMessageName[Type_]);

  if (Valid_) {
    Result.append("\nChecksum: Valid");
  } else {
    Result.append("\nChecksum: Invalid");
  }

  return Result;
} // Print
} // NMEA
