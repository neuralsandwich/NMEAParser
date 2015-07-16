#include <check.h>
#include "NMEA.h"
#include <stdio.h>

START_TEST(parse_gga) {
  char *MessageString = "$GPGGA,092725.00,4717.11399,N,00833.91590,E,1,8,1.01,"
                        "499.6,M,48.0,M,,0*5B";

  HNMEAParser *Parser = HNMEAParser_Create();
  fail_unless(Parser, "Parser null after creation");

  NMEAMessage *Message = HNMEAParser_Parse(Parser, MessageString);
  fail_unless(Message, "Message null after creation");
  fail_unless((Message->Header->Type == GGA), "Not GGA Message");

  GPGGA *Body = Message->GGA;
  fail_unless((Body->TimeStamp == 1437035245), "Time stamp is incorrect");
  fail_unless((Body->Latitude == 4717.113770f), "Latitude is incorrect");
  fail_unless((Body->Longitude == 833.915894f), "Longitude is incorrect");
  fail_unless((Body->SatelliteFixes == 8), "Satellite fixes is incorrect");
  fail_unless((Body->HDOP == 1.01f),
              "Horizontal Dilution of Precision is incorrect");
  fail_unless((Body->MSL == 499.6f), "MSL Altitude is incorrect");
  fail_unless((Body->uMSL == 'M'), "MSL Units is incorrect");
  fail_unless((Body->GeoidSeparation == 48.0f),
              "Geoid separation is incorrect");
  fail_unless((Body->uSep == 'M'), "Geoid Separation Units");
  fail_unless((Body->DifferentialCorrectionAge == 0.0f),
              "Differential Correction Age is incorrect");
  fail_unless((Body->DifferentialStationID == 0.0f),
              "Differential Station ID is incorrect");

  // NOTE: This fails, it shouldn't it ParseStatus is wrong
  fail_unless((Body->Status == 1), "Status is incorrect");

  char Buffer[500] = {};
  NMEAMessage_Print(Message, Buffer, 500);
  fail_unless(Buffer, "Buffer null after NMEAMessage_Print");
  printf("%s\n", Buffer);

  HNMEAParser_Destroy(Parser);
  NMEAMessage_Destroy(Message);
}
END_TEST

START_TEST(parse_gll) {
  char *MessageString = "$GPGLL,4717.11364,N,00833.91565,E,092321.00,A,A*60";

  HNMEAParser *Parser = HNMEAParser_Create();
  fail_unless(Parser, "Parser null after creation");

  NMEAMessage *Message = HNMEAParser_Parse(Parser, MessageString);
  fail_unless(Message, "Message null after creation");
  fail_unless(Message->Header->Type == GLL, "Not GLL Message");

  GPGLL *Body = Message->GLL;
  fail_unless((Body->Latitude == 4717.11364f), "Latitude is incorrect");
  fail_unless((Body->Longitude == 833.91565f), "Longitude is incorrect");
  fail_unless((Body->TimeStamp == 1437035001), "Time stamp is incorrect");
  fail_unless((Body->Status == 1), "Status is incorrect");
  fail_unless((Body->PositioningMode == 'A'), "Positioning Mode is incorrect");

  char Buffer[500];
  NMEAMessage_Print(Message, Buffer, 500);
  fail_unless(Buffer, "Buffer null after NMEAMessage_Print");

  HNMEAParser_Destroy(Parser);
  NMEAMessage_Destroy(Message);
}
END_TEST

START_TEST(parse_gsa) {
  char *MessageString =
      "$GPGSA,A,3,23,29,07,08,09,18,26,28,,,,,1.94,1.18,1.54*0D";

  HNMEAParser *Parser = HNMEAParser_Create();
  fail_unless(Parser, "Parser null after creation");

  NMEAMessage *Message = HNMEAParser_Parse(Parser, MessageString);
  fail_unless(Message, "Message null after creation");
  fail_unless(Message->Header->Type == GSA, "Not GSA Message");

  GPGSA *Body = Message->GSA;
  fail_unless((Body->Smode == 'A'), "S mode is incorrect");
  fail_unless((Body->FixStatus == 3), "Satellites fix status is incorrect");
  fail_unless((Body->sv), "Satellites vector is not valid");
  fail_unless((Body->pdop == 1.94f),
              "Position dilution of percision is incorrect");
  fail_unless((Body->hdop == 1.18f),
              "Horizontal dilution of percision is incorrect");
  fail_unless((Body->vdop == 1.54f), "Vertical diluation of percision");

  char Buffer[500];
  NMEAMessage_Print(Message, Buffer, 500);
  ck_assert_msg(Buffer, "Buffer null after NMEAMessage_Print");

  HNMEAParser_Destroy(Parser);
  NMEAMessage_Destroy(Message);
}
END_TEST

Suite *parse_suite() {
  Suite *suite = suite_create("ParseTest");
  TCase *tcase = tcase_create("Valid Messages");
  tcase_add_test(tcase, parse_gga);
  tcase_add_test(tcase, parse_gsa);
  tcase_add_test(tcase, parse_gll);
  suite_add_tcase(suite, tcase);

  return suite;
}

int main(int argc, char *argv[]) {
  int number_failed = 0;

  Suite *suite = parse_suite();
  SRunner *runner = srunner_create(suite);
  srunner_run_all(runner, CK_NORMAL);
  number_failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return number_failed;
}
