#include "NMEAParser.h"

#include <ctime>

namespace NMEA {
std::string GPGGA::Print() const {

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
  Result.append("\nSatilite Fixes: ");
  Result.append(std::to_string(SatiliteFixes));
  Result.append("\nHDOP: ");
  Result.append(std::to_string(HDOP));
  Result.append("\nMSL: ");
  Result.append(std::to_string(MSL) + " (" + uMSL + ")");
  Result.append("\nGeoid Separation: ");
  Result.append(std::to_string(GeoidSeparation) + " (" + uSep + ")");
  Result.append("\nDifferential Correction Age: ");
  Result.append(std::to_string(DifferentialCorrectionAge));
  Result.append("\nDifferential Station ID: ");
  Result.append(std::to_string(DifferentialStationID));
  Result.append("\nValid Checksum: ");

  if (Valid_) {
    Result.append("Valid");
  } else {
    Result.append("Invalid");
  }

  return Result;
};
} // NMEA
