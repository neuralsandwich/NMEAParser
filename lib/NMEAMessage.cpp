#include "NMEAParser.h"

extern "C" {
#include "NMEA.h"
}

void NMEAMessage_Destroy(NMEAMessage *Message) {
  if (nullptr == Message) {
    return;
  }

  // TODO: Delete messages correctly
  
  delete Message;
} // NMEAMessage_Destory
