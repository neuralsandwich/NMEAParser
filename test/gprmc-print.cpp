#include "../lib/NMEAParser.h"

#include <string>
#include <iostream>
#include <vector>

using namespace std;
using namespace NMEA;

int main() {
  vector<NMEAData *> Messages;
  const string NMEAString1 =
      "$GPRMC,123519,A,4807.038,N,01131.000,E,022.4,084.4,230394,003.1,W*6A";

  NMEAParser parser = NMEAParser();
  Messages.push_back(parser.Parse(&NMEAString1));

  if (Messages.back()->GetMessageType() == NMEA_MESSAGE_TYPE::RMC) {
    std::cout << "RMC Message: " << NMEAString1 << "\n";
    GPRMC *gprmc = static_cast<GPRMC *>(Messages.back());
    // Check that casting worked
    if (gprmc) {
      std::cout << gprmc->Print() << std::endl;
    }
  } else {
    std::cout << Messages.back()->Print() << std::endl;
  };

  return 0;
}
