#include "NMEAParser.h"

extern "C" {
#include "NMEA.h"
}

void NMEAMessage_Print(NMEAMessage *Message, char *Buffer, int Size) {

  if ((Message == 0) || (Buffer == 0) || (Size == 0)) {
    return;
  }

  std::string Result("Talker ID: ");
  Result.append(NMEA::NMEATalkerIDName[Message->Header->ID]);
  Result.append("\nMessage Type: ");
  Result.append(NMEA::NMEAGPSMessageName[Message->Header->Type]);

  switch (Message->Header->Type) {
  case RMC: {
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
  } break;

  case GLL: {
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
  } break;

  case GGA: {
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
    Result.append(std::to_string(Message->GGA->MSL) + " (" +
                  Message->GGA->uMSL + ")");
    Result.append("\nGeoid Separation: ");
    Result.append(std::to_string(Message->GGA->GeoidSeparation) + " (" +
                  Message->GGA->uSep + ")");
    Result.append("\nDifferential Correction Age: ");
    Result.append(std::to_string(Message->GGA->DifferentialCorrectionAge));
    Result.append("\nDifferential Station ID: ");
    Result.append(std::to_string(Message->GGA->DifferentialStationID));
  } break;

  case VTG: {
    Result.append("\nCourse Over Ground (true): ");
    Result.append(std::to_string(Message->VTG->cogt));
    Result.append("\nCourse Over Ground (magentic): ");
    Result.append(std::to_string(Message->VTG->cogm));
    Result.append("\nSpeed Over Ground (knots): ");
    Result.append(std::to_string(Message->VTG->sog));
    Result.append("\nSpeed Over Ground (km/h): ");
    Result.append(std::to_string(Message->VTG->kph));
    Result.append("\nMode Indicator: ");
    Result.append(&Message->VTG->mode);
  } break;
  }

  Result.append("\nValid Checksum: ");
  if (Message->Header->Valid == 1) {
    Result.append("Valid");
  } else {
    Result.append("Invalid");
  }

  std::copy(Result.begin(), Result.end(), Buffer);
} // NMEAMessage_Print

void NMEAMessage_Destroy(NMEAMessage *Message) {
  if (nullptr == Message) {
    return;
  }

  delete Message;
} // NMEAMessage_Destory
