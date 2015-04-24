#include "NMEAParser.h"

#include <ctime>

namespace NMEA {
std::string GPRMC::Print() const {

  // TODO: Tidy this up
  std::string Result("Talker ID: ");
  Result.append(NMEATalkerIDName[ID_]);
  Result.append("\nMessage Type: ");
  Result.append(NMEAGPSMessageName[Type_]);
  Result.append("\nDate Time: ");
  Result.append(ctime(&TimeStamp));
  Result.append("Status: ");
  if (Status) {
    Result.append(std::to_string(Status));
  } else {
    Result.append("Void");
  }
  Result.append("\nLatitude: ");
  Result.append(std::to_string(Latitude));
  Result.append("\nLongitude: ");
  Result.append(std::to_string(Longitude));
  Result.append("\nSpeed: ");
  Result.append(std::to_string(Speed));
  Result.append("\nAngle: ");
  Result.append(std::to_string(Angle));
  Result.append("\nMagnetic Variation: ");
  Result.append(std::to_string(MagneticVariation));

  if (Valid_) {
    Result.append("\nChecksum: Valid");
  }

  return Result;
} // Print
} // NMEA
