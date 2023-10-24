#include "include/nmea_msg.hpp"
#include "include/msg_parser.hpp"
// TODO: move to tests
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <ctime>

StringIterator& operator>>(StringIterator& is, VTGMsg& msg) {
    try
    {
        is >> msg.course1   // 28.858
        >> msg.reference1   // T
        >> msg.course2      // 17.799
        >> msg.reference2   // M
        >> msg.speed1       // 0.05550
        >> msg.speed1Unit   // N
        >> msg.speed2       // 0.10279
        >> msg.speed2Unit   // K
        >> msg.mode;        // D
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return is;
}

// from time string (format: hhmmss.sss) to time_t
std::istream& operator>>(std::istream& ss, TimeWrapper& time) {
    tm t;
    char dot;
    int ms;

    ss >> std::get_time(&t, "%H%M%S") >> dot >> ms; // 092547.30
    time.value = (t.tm_hour * 3600 + t.tm_min * 60 + t.tm_sec) * 1000 + ms;
    
    return ss;
}

StringIterator& operator>>(StringIterator& is, GGAMsg& msg) {
    try
    {
        //$GPGGA,092547.20,5157.89111643,N,04806.03913471,E,1,34,0.5,100.3851,M,-1.6215,M,02,999*4F
        is >> msg.time                  // 092547.30
        >> msg.latitude                 // 5157.89111607
        >> msg.nsIndicator              // N
        >> msg.longitude                // 04806.03913459
        >> msg.ewIndicator              // E
        >> msg.positionFixIndicator     // 1
        >> msg.satellitesUsed           // 34
        >> msg.hdop                     // 0.5
        >> msg.mslAltitude              // 100.3837
        >> msg.units1                   // M
        >> msg.geoidSeparation          // -1.6215
        >> msg.units2                   // M
        >> msg.ageOfDiffCorr            // 02 ?
        >> msg.diffRefStationID;        // 999
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return is;
}

// int calculateChecksum(const std::string& str) {
//     // TODO
// }

// TODO: move to tests

// int main(int argc, char* argv[]) {
//     std::ifstream file("/home/q/repos/pegas-test/test/trash/nmea.log");
//     std::string str;

//     while (getline(file, str))
//     {
//         StringIterator si(str, ',');
//         char delimiter;
//         std::string tag;
//         si >> tag;

//         if (tag == "$GPGGA") {
//             GGAMsg msg;
//             si >> msg;
//         } else if (tag == "$GNVTG") {
//             VTGMsg msg;
//             si >> msg;
//         }

//         int checksum;
//         si >> std::hex >> checksum;

//         // TODO: check checksum
//     }

//     return 0;
// }