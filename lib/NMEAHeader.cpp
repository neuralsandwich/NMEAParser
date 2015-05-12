extern "C" {
#include "NMEA.h"
}

#include "NMEAParser.h"

#include <string>
void NMEAHeader_Print(NMEAMessage *Message, char *Buffer, int Size) {
  std::cout << "Message: " << Message << "\n";
  std::cout << "Message ID: " << Message->Header->ID << "\n";
  std::cout << "Buffer: " << Buffer << "\n";
  std::cout << "Size: " << Size << "\n";
  std::string Result("Talker ID: ");
  Result.append(NMEA::NMEATalkerIDName[Message->Header->ID]);
  Result.append("\nMessage Type: ");
  Result.append(NMEA::NMEAGPSMessageName[Message->Header->Type]);

  if (Message->Header->Valid) {
    Result.append("\nChecksum: Valid");
  } else {
    Result.append("\nChecksum: Invalid");
  }

  std::copy(Result.begin(), Result.end(), Buffer);
} // NMEAData_Print
