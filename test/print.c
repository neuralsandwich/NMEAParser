#include "../lib/NMEA.h"

#include <stdio.h>

int main() {
  NMEAMessage *Message;
  const char *NMEAString[] = {
      "$GPDTM,W84,,0.0,N,0.0,E,0.0,W84*6F",
      "$GPDTM,W72,,0.00,S,0.01,W,-2.8,W84*4F",
      "$GPDTM,999,CH95,0.08,N,0.07,E,-47.7,W84*1C",
      "$GPGBS,235503.00,1.6,1.4,3.2,,,,*40",
      "$GPGBS,235458.00,1.4,1.3,3.1,03,,-21.4,3.8*5B",
      "$GPGRS,082632.00,1,0.54,0.83,1.00,1.02,-2.12,2.64,-0.71,-1.18,0.25,,,*"
      "70",
      "$GPGSA,A,3,23,29,07,08,09,18,26,28,,,,,1.94,1.18,1.54*0D",
      "$GPGST,082356.00,1.8,,,,1.7,1.3,2.2*7E",
      "$GPGSV,3,1,10,23,38,230,44,29,71,156,47,07,29,116,41,08,09,081,36*7F",
      "$GPGSV,3,2,10,10,07,189,,05,05,220,,09,34,274,42,18,25,309,44*72",
      "$GPGSV,3,3,10,26,82,187,47,28,43,056,46*77",
      "$GPRMC,123519,A,4807.038,N,01131.000,E,022.4,084.4,230394,003.1,W*6A",
      "$GPTHS,77.52,E*32",
      "$GPGGA,092725.00,4717.11399,N,00833.91590,E,1,8,1.01,499.6,M,48.0,M,,0*"
      "5B",
      "$GPGLL,4717.11364,N,00833.91565,E,092321.00,A,A*60",
      "$GPTXT,01,01,02,ANTARIS ATR0620 HW 00000040*67",
      "$GPVTG,77.52,T,,M,0.004,N,0.008,K,A*06",
      "$GPZDA,082710.00,16,09,2002,00,00*64"
  };
    
  HNMEAParser *Parser = HNMEAParser_Create();

  for (int i = 0; i < 18; i++) {
    printf("Message: %d\n", i);
    Message = HNMEAParser_Parse(Parser, NMEAString[i]);

    if (Message == NULL) {
      return 1;
    }

    printf("NMEA Message: %s\n", NMEAString[i]);

    char Buffer[500] = {};
    NMEAMessage_Print(Message, Buffer, 1000);
    printf("%s\n\n", Buffer);
    NMEAMessage_Destroy(Message);
  }

  HNMEAParser_Destroy(Parser);
  
  return 0;
}
