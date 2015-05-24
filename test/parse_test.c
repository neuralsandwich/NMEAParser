#include <check.h>
#include "NMEA.h"
#include <stdio.h>

START_TEST(parse_gga) {
  char *MessageString = "$GPGGA,092725.00,4717.11399,N,00833.91590,E,1,8,1.01,"
                        "499.6,M,48.0,M,,0*5B";

  HNMEAParser *Parser = HNMEAParser_Create();
  ck_assert_msg(Parser, "Parser null after creation");

  NMEAMessage *Message = HNMEAParser_Parse(Parser, MessageString);
  ck_assert_msg(Message, "Message null after creation");

  char Buffer[500] = {};
  NMEAMessage_Print(Message, Buffer, 500);
  ck_assert_msg(Buffer, "Buffer null after NMEAMessage_Print");
  
  HNMEAParser_Destroy(Parser);
  NMEAMessage_Destroy(Message);
}
END_TEST

START_TEST(parse_gll) {
  char *MessageString =
    "$GPGLL,4717.11364,N,00833.91565,E,092321.00,A,A*60";

  HNMEAParser *Parser = HNMEAParser_Create();
  ck_assert_msg(Parser, "Parser null after creation");

  NMEAMessage *Message = HNMEAParser_Parse(Parser, MessageString);
  ck_assert_msg(Message, "Message null after creation");

  char Buffer[500];
  NMEAMessage_Print(Message, Buffer, 500);
  ck_assert_msg(Buffer, "Buffer null after NMEAMessage_Print");

  HNMEAParser_Destroy(Parser);
  NMEAMessage_Destroy(Message);
}
END_TEST

START_TEST(parse_gsa) {
  char *MessageString =
      "$GPGSA,A,3,23,29,07,08,09,18,26,28,,,,,1.94,1.18,1.54*0D";

  HNMEAParser *Parser = HNMEAParser_Create();
  ck_assert_msg(Parser, "Parser null after creation");

  NMEAMessage *Message = HNMEAParser_Parse(Parser, MessageString);
  ck_assert_msg(Message, "Message null after creation");

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
