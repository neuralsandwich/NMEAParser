#ifndef NMEA_H
#define NMEA_H

#include <time.h>

// NMEA Talker IDs
enum NMEA_TALKER_ID {
  UNKNOWN_TALKER_ID,
  GPS,
  GLONASS,
  NMEA_TALKER_ID_NUM,
}; // NMEA_TALKER_ID
typedef enum NMEA_TALKER_ID NMEA_TALKER_ID;

// NMEA Messages Types
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
typedef enum NMEA_MESSAGE_TYPE NMEA_MESSAGE_TYPE;

// Data Types

/* NMEAHeader - Generic class for NMEA Protocol
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
typedef struct NMEAHeader {
  enum NMEA_TALKER_ID ID;
  enum NMEA_MESSAGE_TYPE Type;
  char *Data;
  int Valid;
} NMEAHeader;

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
typedef struct GPRMC {
  // UTC time stamp of data fix
  time_t TimeStamp;
  // Status A = active, V = void
  int Status;
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
} GPRMC;

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
typedef struct GPGGA {
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
  int Status;
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
} GPGGA;

/* GPGLL - Latitude and longitude, with time of position fix and status
 *
 * Message Structure:
 * $GPGLL,Latitude,N,Longitude,E,hhmmss.ss,Valid,Mode*cs<CR><LF>
 *
 * 01. Message ID, GLL protocol header
 * 02. Latitude, Degrees + minutes
 * 03. North/South hemisphere indicator
 * 04. Longitude, Degrees + minutes
 * 05. East/West indicator
 * 06. UTC Time, Current time
 * 07. V = Data invalid, A = Data valid
 * 07. [Optional] Positioning mode
 * 08. Checksum in hex
 * 09. <CR><LF>
 */
typedef struct GPGLL {
  // Latitude of position:
  // e.g. 4807.038,N = 48 deg 07.038' N
  // N = positive, S = negative
  float Latitude;
  // Longitude of position:
  // e.g. 01131.000,E = 11 deg 31.000' E
  // E = positive, W = negative
  float Longitude;
  // UTC time stamp of data fix
  time_t TimeStamp;
  // Validity of the data
  int Status;
  // combined GPS/SFDR position fix (ADR with external sensors)
  char PositioningMode;
} GPGLL;

/* GPVTG - Course over groud and Ground speed
 *
 * Message Structure:
 * $GPVTG,cogt,T,cogm,M,sog,N,kph,K,mode*cs<CR><LF>
 *
 * 01. Message ID, VTG protocol header
 * 02. Course over ground (true)
 * 03. Fixed field: true
 * 04. Course over ground (magenetic)
 * 05. Fixed field: magnetic
 * 06. Speed over ground
 * 07. Fixed field: knots
 * 08. Speed over ground km/h
 * 09. Fixed Field: kilometers per hour
 * 10. Mode Indicator
 * 11. Checksum
 * 12. <CR><LF>
 */
typedef struct GPVTG {
  // Course over ground (true)
  float cogt;
  // Fixed field: true
  char T;
  // Course over ground (magnetic)
  float cogm;
  // Fixed field: magnetic
  char M;
  // Speed over ground (knots)
  float sog;
  // Fixed field: knots
  char N;
  // Speed over ground (km/h)
  float kph;
  // Fixed field: kilometers per hour
  char K;
  // Mode Indicator
  char mode;
} GPVTG;

/* GPGSA - GNSS DOP and Active Satellites
 *
 * Message structure:
 * $GPGSA,Smode,FS{,sv},PDOP,HDOP,VDOP*cs<CR><LF>
 *
 * 01. Message ID, GSA protocol header
 * 02. Smode
 * 03. Fix status
 * 04. Satellite number - Repeated up to 12 times
 * 16. Position dilution of precision
 * 17. Horizontal dilution of precision
 * 18. Vertical dilution of precision
 * 19. Vertical dilution of precision
 * 20. Carriage Return and Line Feed
 */
typedef struct GPGSA {
  // Smode
  // M - Manual, forced to operate in 2D/3D mode
  // A - Allowed to automatically switch 2D/3D mode
  char Smode;
  // FS (Fix Status)
  // 1 - Fix not available
  // 2 - 2D Fix
  // 3 - 3D fix
  int FixStatus;
  // SV (Satilite)
  // 01-32 GPS satellites
  // 33-64 SBAS satellites (33 = SBAS PRN 120, 34 = SBAS PRN 121, etc)
  int *sv;
  // Position dilution of percision
  float pdop;
  // Horizontal dilution of percision
  float hdop;
  // Vertical dilution of percision
  float vdop;
} GPGSA;

/* GPGSV - GNSS Satellites in View
 *
 * Message structure:
 * $GPGSV,NoMsg,MsgNo,NoSv,{,sv,elv,az,cno}*cs<CR><LF>
 *
 * 01. Message ID, GSV protocol header
 * 02. Number of messages
 * 03. Number of this message
 * 04. Satellites in View
 * - Start of repeating block 1..4
 * 05. Satellite ID
 * 06. Elevation
 * 07. Azimuth
 * 08. Signal/Noise ratio
 * - End of repeating block
 * 15. Checksum
 * 16. <CR><LF>
 */
typedef struct GPGSV {
  // Number of messages - total number of GPGSV message being output
  int NoMSG;
  // Number of this message
  int MSGNo;
  // Satellites in view
  int NoSV;
  // Satellite ID
  int *sv;
  // Elevation - range 0..90
  int *elv;
  // Azimuth - range 0..359
  int *az;
  // Signal/Noise ratio - range 0..99, NULL when not tracked
  int *cno;

  // Helper value
  int DataFieldsInMessage;
} GPGSV;

typedef struct NMEAMessage {
  NMEAHeader *Header;
  union {
    // GPAAM *AAM,
    // GPALM *ALM,
    // GPAPA *APA,
    // GPAPB *APB,
    // GPBOD *BOD,
    // GPBWC *BWC,
    // GPDTM *DTM,
    GPGGA *GGA;
    GPGLL *GLL;
    // GPGRS *GRS,
    GPGSA *GSA;
    // GPGST *GST,
    GPGSV *GSV;
    // GPMSK *MSK,
    // GPMSS *MSS,
    // GPRMA *RMA,
    // GPRMB *RMB,
    GPRMC *RMC;
    // GPRTE *RTE,
    // GPTRF *TRF,
    // GPSTN *STN,
    // GPVBW *VBW,
    GPVTG *VTG;
    // GPWCV *WCV,
    // GPWPL *WPL,
    // GPXTC *XTC,
    // GPXTE *XTE,
    // GPZTG *ZTG,
    // GPZDA *ZDA,
  };
} NMEAMessage;

struct HNMEAParser;
typedef struct HNMEAParser HNMEAParser;

// HNMEAParser
HNMEAParser *HNMEAParser_Create();
void HNMEAParser_Destroy(HNMEAParser *Parser);
NMEAMessage *HNMEAParser_Parse(HNMEAParser *const Parser, const char *String);

// NMEAMessage
void NMEAMessage_Print(NMEAMessage *Message, char *Buffer, int Size);
void NMEAMessage_Destroy(NMEAMessage *Message);
#endif
