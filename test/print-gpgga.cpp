#include "../lib/NMEAParser.h"

#include <string>
#include <iostream>
#include <vector>

using namespace std;
using namespace NMEA;

int main() {
  vector<NMEAData *> Messages;
  const string NMEAString1 =
      "$GPGGA,092725.00,4717.11399,N,00833.91590,E,1,8,1.01,499.6,M,48.0,M,,0*5B";

  NMEAParser parser = NMEAParser();
  Messages.push_back(parser.Parse(&NMEAString1));

  if (Messages.back()->GetMessageType() == NMEA_MESSAGE_TYPE::GGA) {
    std::cout << "GGA Message: " << NMEAString1 << "\n";
    GPGGA *gpgga = static_cast<GPGGA *>(Messages.back());
    // Check that casting worked
    if (gpgga) {
      std::cout << gpgga->Print() << std::endl;
    }
  } else {
    std::cout << Messages.back()->Print() << std::endl;
  };

  return 0;
}
