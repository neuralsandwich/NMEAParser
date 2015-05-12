#include "NMEAParser.h"

#include <ctime>

void GPGLL_Print(NMEAMessage *Message, char *Buffer, int Size) {
  std::string Result("Talker ID: ");
  Result.append(NMEA::NMEATalkerIDName[Message->Header->ID]);
  Result.append("\nMessage Type: ");
  Result.append(NMEA::NMEAGPSMessageName[Message->Header->Type]);
  Result.append("\nLatitude: ");
  Result.append(std::to_string(Message->GLL->Latitude));
  Result.append("\nLongitude: ");
  Result.append(std::to_string(Message->GLL->Longitude));
  Result.append("\nData Stamp: ");
  Result.append(ctime(&Message->GLL->TimeStamp));
  Result.append("Status: ");
  if (Message->GLL->Status) {
    Result.append(std::to_string(Message->GLL->Status));
  } else {
    Result.append("Void");
  }
  Result.append("\nPositioning Mode: ");
  Result.append(&Message->GLL->PositioningMode);

  if (Message->Header->Valid) {
    Result.append("\nChecksum: Valid");
  }

  std::copy(Result.begin(), Result.end(), Buffer);
}
