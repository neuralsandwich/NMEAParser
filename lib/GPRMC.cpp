#include "NMEAParser.h"

#include <ctime>

void GPRMC_Print(NMEAMessage *Message, char *Buffer, int Size) {

  // TODO: Tidy this up
  std::string Result("Talker ID: ");
  Result.append(NMEA::NMEATalkerIDName[Message->Header->ID]);
  Result.append("\nMessage Type: ");
  Result.append(NMEA::NMEAGPSMessageName[Message->Header->Type]);
  Result.append("\nDate Time: ");
  Result.append(ctime(&Message->RMC->TimeStamp));
  Result.append("Status: ");
  if (Message->RMC->Status) {
    Result.append(std::to_string(Message->RMC->Status));
  } else {
    Result.append("Void");
  }
  Result.append("\nLatitude: ");
  Result.append(std::to_string(Message->RMC->Latitude));
  Result.append("\nLongitude: ");
  Result.append(std::to_string(Message->RMC->Longitude));
  Result.append("\nSpeed: ");
  Result.append(std::to_string(Message->RMC->Speed));
  Result.append("\nAngle: ");
  Result.append(std::to_string(Message->RMC->Angle));
  Result.append("\nMagnetic Variation: ");
  Result.append(std::to_string(Message->RMC->MagneticVariation));

  if (Message->Header->Valid) {
    Result.append("\nChecksum: Valid");
  }

  std::copy(Result.begin(), Result.end(), Buffer);
} // Print
