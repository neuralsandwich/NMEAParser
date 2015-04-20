/* NMEAParser
 *
 * This library is based on information from different sources on the internet.
 *
 * In theory is should be able to parse NMEA 0183 Version 2.3, so it is out of
 * date.
 */
#ifndef NMEA_PARSER_HPP
#define NMEA_PARSER_HPP

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <ctime>

namespace NMEA {

// TODO: Turn these into static const int or remove them?
#define COMMANDSTART 0x24
#define SENTENCESEPARATOR 0x2C
#define CHECKSUMSTART 0x2A

enum NMEA_TALKER_ID {
  UNKNOWN_TALKER_ID,
  GPS,
  GLONASS,
  NMEA_TALKER_ID_NUM,
};

enum NMEA_MESSAGE_TYPE {
  UNKNOWN_MESSAGE,
  AAM, // Waypoint Arrival Alarm
  ALM, // Almanac data
  APA, // Auto Pilot A sentence
  APB, // Auto Pilot B sentence
  BOD, // Bearing Origin to Destination
  BWC, // Bearing using Great Circle route
  DTM, // Datum being used.
  GAA, // Fix information
  GLL, // Lat/Lon data
  GRS, // GPS Range Residuals
  GSA, // Overall Satellite data
  GST, // GPS Pseudorange Noise Statistics
  GSV, // Detailed Satellite data
  MSK, // send control for a beacon receiver
  MSS, // Beacon receiver status information.
  RMA, // recommended Loran data
  RMB, // recommended navigation data for gps
  RMC, // recommended minimum data for gps
  RTE, // route message
  TRF, // Transit Fix Data
  STN, // Multiple Data ID
  VBW, // dual Ground / Water Spped
  VTG, // Vector track an Speed over the Ground
  WCV, // Waypoint closure velocity (Velocity Made Good)
  WPL, // Waypoint Location information
  XTC, // cross track error
  XTE, // measured cross track error
  ZTG, // Zulu (UTC) time and time to go (to destination)
  ZDA, // Date and Time
  NMEA_GPS_MESSAGE_NUM,
};

char const *const NMEATalkerIDName[NMEA_TALKER_ID_NUM] = { 
  [UNKNOWN_TALKER_ID] = "Unknown", [GPS] = "GPS", [GLONASS] = "GLONASS", };

                                             
char const *const NMEAGPSMessageName[NMEA_GPS_MESSAGE_NUM] = { [UNKNOWN_MESSAGE] = "Unknown", [RMC] = "RMC",};

/* NMEAData - Generic class for NMEA Protocol
 *
 * NMEA Protocol Frame
 *
 *  _____________________________________________________
 * | $ | <Address> | {,<value>} | *<checksum> | <CR><LF> |
 *  -----------------------------------------------------
 *
 * * Starting character - Always starts with $
 * * Address field      - Only digits and uppercase letters, cannot be null.
 *                        This field is subdivided into 2 fields:
 *                         ______________
 *                        | <XX> | <XXX> | * Talker ID, always GP for GPS.
 *                         --------------    P for propiertary messages.
 *                                         * Sentence Formatter. Defines the
 *                                           message content.
 * * Data field(s)      - Delimited by a ','. Length can vary, even for a
 *                        certain field.
 * * Checksum field     - Starts with a '*' and consists of two characters
 *                        representing a hax number. The checksum is the
 *                        exclusive OR (XOR) of all characters between '$' and
 *                        '*'.
 * * End sequence       - Always <CR><LF>
 *
 * For further information on the NMEA Standard please refer to NMEA 0183
 * Standard For Interfacing Marine Electronic Devices, Version 2.30, March 1,
 * 1998. See http://www.nmea.org/ for ordering instructions.
 */
class NMEAData {
public:
  // Constructor for returning invalid message
  NMEAData(const NMEA_TALKER_ID TalkerID, const NMEA_MESSAGE_TYPE MessageType,
           const bool ValidChecksum)
      : ID_(TalkerID), Type_(MessageType), Valid_(ValidChecksum){};
  
  // Constructor for returning valid but unknown messages
  NMEAData(const NMEA_TALKER_ID TalkerID, const NMEA_MESSAGE_TYPE MessageType,
           const std::string DataSentence)
      : ID_(TalkerID), Type_(MessageType), Data_(DataSentence), Valid_(true){};

  ~NMEAData(){};

  enum NMEA_TALKER_ID GetTalkerID() const;
  enum NMEA_MESSAGE_TYPE GetMessageType() const;

  bool IsValid() const;

  // TODO: Remove this once done debugging
  const std::string Print() const;

private:
  NMEA_TALKER_ID ID_;
  NMEA_MESSAGE_TYPE Type_;
  std::string Data_;
  bool Valid_;
};

/* NMEAParser - Factory for NMEA message objects
 */
class NMEAParser {
public:
  NMEAData Parse(const std::string *str);

private:
  bool ValidateChecksum(const std::string *Message, const std::string *Checksum);
  enum NMEA_TALKER_ID ParseTalkerID(const std::string *ID);
  enum NMEA_MESSAGE_TYPE ParseMessageType(const std::string *Message);
};
}
#endif
