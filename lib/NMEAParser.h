/* NMEAParser
 *
 * This library is based on information from different sources on the internet.
 *
 * In theory is should be able to parse NMEA 0183 Version 2.3, so it is out of
 * date.
 *
 * TODO: Convert messages to structs
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
}; // NMEA_TALKER_ID

enum NMEA_MESSAGE_TYPE {
  UNKNOWN_MESSAGE,
  AAM, // Waypoint Arrival Alarm
  ALM, // Almanac data
  APA, // Auto Pilot A sentence
  APB, // Auto Pilot B sentence
  BOD, // Bearing Origin to Destination
  BWC, // Bearing using Great Circle route
  DTM, // Datum being used.
  GGA, // Fix information
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
}; // NMEA_MESSAGE_TYPE

// Printable strings for Talker IDs
char const *const NMEATalkerIDName[NMEA_TALKER_ID_NUM] = {
        [UNKNOWN_TALKER_ID] = "Unknown", [GPS] = "GPS", [GLONASS] = "GLONASS",
}; // NMEATalkerIDName

// Printable strings for Message types
char const *const NMEAGPSMessageName[NMEA_GPS_MESSAGE_NUM] = {
        [UNKNOWN_MESSAGE] = "Unknown", [RMC] = "RMC", [GGA] = "GGA",
}; // NMEAGPSMessageName

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

  virtual ~NMEAData(){};

  enum NMEA_TALKER_ID GetTalkerID() const;
  enum NMEA_MESSAGE_TYPE GetMessageType() const;

  bool IsValid() const;

  // TODO: Remove this once done debugging
  virtual std::string Print() const;

protected:
  NMEA_TALKER_ID ID_;
  NMEA_MESSAGE_TYPE Type_;
  std::string Data_;
  bool Valid_;
}; // NMEAData

/* GPRMC - GPS Recommended Minimum Data
 *
 * The Recommended Minimum sentence defined by NMEA for GPS/Transit system data.
 *
 * Message Structure:
 * $GPRMC, hhmmss, status, latitude, N, longitude, E, spd, cog, ddmmyy, mv, mvE,
 * mode *cs <CR><LF>
 *
 * 01. Message ID, RMC protocol header
 * 02. UTC Time, Time of fix. HHMMSS format
 * 03. Status, V = Navigation receiver warning, A = Data valid.
 * 04. Latitude, Degrees + minutes
 * 05. North/South hemisphere indicator
 * 06. Longitude, Degrees + minutes
 * 07. East/West indicator
 * 08. Speed over ground (knots)
 * 09. Course over ground (degrees)
 * 10. Date in DDMMYY format
 * 11. Magnetic variation in degrees
 * 12. Magnetic variation, east/west indicator
 * 13. Mode indicator
 * 14. CheckSum in Hex
 * 15. <CR><LF>
 */
class GPRMC : public NMEAData {
public:
  GPRMC(time_t TimeStamp, bool Status, float Latitude, float Longitude,
        float Speed, float Angle, float MagneticVariation, bool ValidChecksum)
      : NMEAData(NMEA_TALKER_ID::GPS, NMEA_MESSAGE_TYPE::RMC, ValidChecksum),
        TimeStamp(TimeStamp), Status(Status), Latitude(Latitude),
        Longitude(Longitude), Speed(Speed), Angle(Angle),
        MagneticVariation(MagneticVariation){};

  GPRMC(NMEAData const &Data) : NMEAData(Data){};
  ~GPRMC(){};

  std::string Print() const;

  // UTC time stamp of data fix
  time_t TimeStamp;
  // Status A = active, V = void
  bool Status;
  // Latitude of position:
  // e.g. 4807.038,N = 48 deg 07.038' N
  // N = positive, S = negative
  float Latitude;
  // Longitude of position:
  // e.g. 01131.000,E = 11 deg 31.000' E
  // E = positive, W = negative
  float Longitude;
  // Speed over the ground in knots
  float Speed;
  // Track angle in degrees True
  float Angle;
  // Magnetic Variation
  // e.g. 003.1,W
  // E = positive, W = negative
  float MagneticVariation;
}; // GPRMC

/* GPGGA - GPS Fix Data
 *
 * Time and position, together with GPS fixing related data (number of
 * satellites in use, and the resulting HDOP, age of differential data
 * if in use, etc.
 *
 * Message Structure:
 * $GPGGA, hhmmss.ss, Latitude, N, Longitude, E, FS, NoSV, HDOP, msl, m, Altref,
 * m, DiffAge, DiffStation *cs <CR><LF>
 *
 * 01. Message ID, GGA protocol header
 * 02. UTC Time, Current time
 * 03. Latitude, Degrees + minutes
 * 04. North/South hemisphere indicator
 * 05. Longitude, Degrees + minutes
 * 06. East/West indicator
 * 07. Position Fix Status Indicator
 * 08. Satellites Used, Range 0 to 12
 * 09. HDOP, Horizontal Dilution of Precision
 * 10. MSL Altitude
 * 11. Units, Meters (fixed field)
 * 12. Geoid Separation
 * 13. Units, Meters (fixed field)
 * 14. Age of Differential Corrections, Blank (Null) fields when DGPS
 *     is not used
 * 15. Diff. Reference Station ID
 * 16. Checksum in hex
 * 17. Carriage Return and Line Feed
 */
class GPGGA : public NMEAData {
public:
  GPGGA(const time_t TimeStamp, const float Latitude, const float Longitude,
        const bool Status, const int SatiliteFixes, const float HDOP,
        const float MSL, const char uMSL, const float GeoidSeparation,
        const char uSep, const float DifferentialCorrectionAge,
        const float DifferentialStationID, const bool ValidChecksum)
      : NMEAData(NMEA_TALKER_ID::GPS, NMEA_MESSAGE_TYPE::GGA, ValidChecksum),
        TimeStamp(TimeStamp), Latitude(Latitude), Longitude(Longitude),
        Status(Status), SatiliteFixes(SatiliteFixes), HDOP(HDOP), MSL(MSL),
        uMSL(uMSL), GeoidSeparation(GeoidSeparation), uSep(uSep),
        DifferentialCorrectionAge(DifferentialCorrectionAge),
        DifferentialStationID(DifferentialStationID){};
  GPGGA(NMEAData const &Data) : NMEAData(Data){};
  ~GPGGA(){};

  std::string Print() const;

  // UTC time stamp of data fix
  time_t TimeStamp;
  // Latitude of position:
  // e.g. 4807.038,N = 48 deg 07.038' N
  // N = positive, S = negative
  float Latitude;
  // Longitude of position:
  // e.g. 01131.000,E = 11 deg 31.000' E
  // E = positive, W = negative
  float Longitude;
  // Speed over the ground in knots
  bool Status;
  // Satellites Used, Range 0 to 12
  int SatiliteFixes;
  // Horizontal Dilution of Precision
  float HDOP;
  // MSL Altitude
  float MSL;
  // MSL Units
  char uMSL;
  // Geoid Separation
  float GeoidSeparation;
  // Geoid Separation Units
  char uSep;
  // Age of Differential Corrections
  float DifferentialCorrectionAge;
  // Diff. Reference Station ID
  float DifferentialStationID;
};

/* NMEAParser - Factory for NMEA message objects
 *
 * TODO: Document this once we have initial work on messages done.
 */
class NMEAParser {
public:
  NMEAData *Parse(const std::string *str);

private:
  bool ValidateChecksum(const std::string *Message,
                        const std::string *Checksum);
  enum NMEA_TALKER_ID ParseTalkerID(const std::string *ID);
  enum NMEA_MESSAGE_TYPE ParseMessageType(const std::string *Message);
  time_t ParseTimeStamp(const std::string *TimeStamp,
                        const std::string *DataStamp);
  time_t ParseTimeStamp(const std::string *TimeStamp);
  bool ParseStatus(const std::string *Status);
  float ParseLatitude(const std::string *Latitude,
                      const std::string *Direction);
  float ParseLongitude(const std::string *Longitude,
                       const std::string *Direction);
  float ParseSpeed(const std::string *Speed);
  float ParseAngle(const std::string *Angle);
  float ParseMagneticVariation(const std::string *MagneticVariation,
                               const std::string *MagneticVariatioDirection);
  int ParseSatiliteFixes(const std::string *SatiliteFixes);
  float ParseHDOP(const std::string *HDOP);
  float ParseMSL(const std::string *MDL);
  float ParseGeoidSeparation(const std::string *GeoidSeparation);
  float ParseDifferentialCorrectionAge(const std::string *CorrectionAge);
  float ParseDifferentialStationID(const std::string *StationID);
}; // NMEAParser
} // NMEA
#endif
