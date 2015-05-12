#include "NMEAParser.h"

#include <ctime>

void GPGGA_Print(NMEAMessage *Message, char *Buffer, int Size) {

  std::string Result("Talker ID: ");
  Result.append(NMEA::NMEATalkerIDName[Message->Header->ID]);
  Result.append("\nMessage Type: ");
  Result.append(NMEA::NMEAGPSMessageName[Message->Header->Type]);
  Result.append("\nDate Time: ");
  Result.append(ctime(&Message->GGA->TimeStamp));
  Result.append("Status: ");
  if (Message->GGA->Status) {
    Result.append(std::to_string(Message->GGA->Status));
  } else {
    Result.append("Void");
  }
  Result.append("\nLatitude: ");
  Result.append(std::to_string(Message->GGA->Latitude));
  Result.append("\nLongitude: ");
  Result.append(std::to_string(Message->GGA->Longitude));
  Result.append("\nSatilite Fixes: ");
  Result.append(std::to_string(Message->GGA->SatiliteFixes));
  Result.append("\nHDOP: ");
  Result.append(std::to_string(Message->GGA->HDOP));
  Result.append("\nMSL: ");
  Result.append(std::to_string(Message->GGA->MSL) + " (" + Message->GGA->uMSL +
                ")");
  Result.append("\nGeoid Separation: ");
  Result.append(std::to_string(Message->GGA->GeoidSeparation) + " (" +
                Message->GGA->uSep + ")");
  Result.append("\nDifferential Correction Age: ");
  Result.append(std::to_string(Message->GGA->DifferentialCorrectionAge));
  Result.append("\nDifferential Station ID: ");
  Result.append(std::to_string(Message->GGA->DifferentialStationID));
  Result.append("\nValid Checksum: ");

  if (Message->Header->Valid) {
    Result.append("Valid");
  } else {
    Result.append("Invalid");
  }

  std::copy(Result.begin(), Result.end(), Buffer);
} // Print
