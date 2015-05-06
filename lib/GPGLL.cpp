#include "NMEAParser.h"

#include <ctime>

namespace NMEA {
  std::string GPGLL::Print() const {
    std::string Result("Talker ID: ");
    Result.append(NMEATalkerIDName[ID_]);
    Result.append("\nMessage Type: ");
    Result.append(NMEAGPSMessageName[Type_]);
    Result.append("\nLatitude: ");
    Result.append(std::to_string(Latitude));
    Result.append("\nLongitude: ");
    Result.append(std::to_string(Longitude));
    Result.append("\nData Stamp: ");
    Result.append(ctime(&TimeStamp));
    Result.append("Status: ");
    if (Status) {
      Result.append(std::to_string(Status));
    } else {
      Result.append("Void");
    }
    Result.append("\nPositioning Mode: ");
    Result.append(&PositioningMode);

    if (Valid_){
      Result.append("\nChecksum: Valid");
    }
    
    return Result;
  }
};
