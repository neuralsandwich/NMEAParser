#include "../lib/NMEA.h"

#include <stdio.h>

int main() {
  NMEAMessage *Message;
  const char *NMEAString[] = {
      "$GPRMC,123519,A,4807.038,N,01131.000,E,022.4,084.4,230394,003.1,W*6A",
      "$GPGGA,092725.00,4717.11399,N,00833.91590,E,1,8,1.01,499.6,M,48.0,M,,0*"
      "5B",
      "$GPGLL,4717.11364,N,00833.91565,E,092321.00,A,A*60"};
  HNMEAParser *Parser = HNMEAParser_Create();

  for (int i = 0; i < 3; i++) {
    printf("Message: %d\n", i);
    Message = HNMEAParser_Parse(Parser, NMEAString[i]);

    if (Message == NULL)
      return 1;

    switch (Message->Header->Type) {
    case RMC: {
      printf("RMC Message: %s\n", NMEAString[i]);

      char Buffer[1000] = {};
      GPRMC_Print(Message, Buffer, 1000);
      printf("%s\n", Buffer);
    } break;

    case GGA: {
      printf("GGA Message: %s\n", NMEAString[i]);

      char Buffer[1000] = {};
      GPGGA_Print(Message, Buffer, 1000);
      printf("%s\n", Buffer);
    } break;

    case GLL: {
      printf("GLL Message: %s\n", NMEAString[i]);

      char Buffer[1000] = {};
      GPGLL_Print(Message, Buffer, 1000);
      printf("%s\n", Buffer);
    } break;

    default: {
      char Buffer[1000] = {};
      NMEAHeader_Print(Message, Buffer, 1000);
      printf("%s\n", Buffer);
    } break;
    }
    puts("");
  }

  return 0;
}
