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
  Result.append(NMEA::NMEAGPSMessageNames[Message->Header->Type].String);

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

  case GSA: {
    Result.append("\nS mode: ");
    Result.append(&Message->GSA->Smode);
    Result.append("\nFix Status: ");
    Result.append(std::to_string(Message->GSA->FixStatus));
    Result.append("\nSatellite Number [1-12]:");
    for (int i = 0; i < 12; ++i) {
      Result.append("\n");
      Result.append(std::to_string(Message->GSA->sv[i]));
    }
    Result.append("\nPosition dilution of percision: ");
    Result.append(std::to_string(Message->GSA->pdop));
    Result.append("\nHorizontal dilution of percision: ");
    Result.append(std::to_string(Message->GSA->hdop));
    Result.append("\nVertical dilution of percision: ");
    Result.append(std::to_string(Message->GSA->vdop));
  } break;

  case GSV: {
    Result.append("\nNumber of Messages: ");
    Result.append(std::to_string(Message->GSV->NoMSG));
    Result.append("\nMessage Number: ");
    Result.append(std::to_string(Message->GSV->MSGNo));
    Result.append("\nSatillites in View: ");
    Result.append(std::to_string(Message->GSV->NoSV));

    for (int i = 0; i < Message->GSV->DataFieldsInMessage; ++i) {
      Result.append("\nSatellite ID: ");
      Result.append(std::to_string(*Message->GSV->sv + i));
      Result.append("\nSatellite Elevation: ");
      Result.append(std::to_string(*Message->GSV->elv + i));
      Result.append("\nSatellite Azimuth: ");
      Result.append(std::to_string(*Message->GSV->az + i));
      Result.append("\nSatellite Signal/Noise Ratio: ");
      Result.append(std::to_string(*Message->GSV->cno + i));
    }

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
