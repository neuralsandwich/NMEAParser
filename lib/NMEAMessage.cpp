#include "NMEAParser.h"

extern "C" {
#include "NMEA.h"
}

void NMEAMessage_Destroy(NMEAMessage *Message) {
  if (nullptr == Message) {
    return;
  }

  switch(Message->Type) {
    case DTM: delete Message->DTM; break;
    case GBS: delete Message->GBS; break;
    case GGA: delete Message->GGA; break;
    case GLL: delete Message->GLL; break;
    case GRS: delete Message->GRS; break;
    case GSA: delete Message->GSA; break;
    case GST: delete Message->GST; break;
    case GSV: delete Message->GSV; break;
    case RMC: delete Message->RMC; break;
    case THS: delete Message->THS; break;
    case VTG: delete Message->VTG; break;
    case ZDA: delete Message->ZDA; break;
  }

  delete Message;
} // NMEAMessage_Destory
