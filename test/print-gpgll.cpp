#include "../lib/NMEAParser.h"

#include <string>
#include <iostream>
#include <vector>

using namespace std;
using namespace NMEA;

int main() {
  vector<NMEAData *> Messages;
  const string NMEAString1 =
    "$GPGLL,4717.11364,N,00833.91565,E,092321.00,A,A*60";

  NMEAParser parser = NMEAParser();
  Messages.push_back(parser.Parse(&NMEAString1));

  if (Messages.back()->GetMessageType() == NMEA_MESSAGE_TYPE::GLL) {
    std::cout << "GLL Message: " << NMEAString1 << "\n";
    GPGLL *gpgll = static_cast<GPGLL *>(Messages.back());
    // Check that casting worked
    if (gpgll) {
      std::cout << gpgll->Print() << std::endl;
    }
  } else {
    std::cout << Messages.back()->Print() << std::endl;
  };

  return 0;
}
