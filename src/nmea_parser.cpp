#include <istream>
#include <iomanip>
#include <ctime>

#include "nmea_parser.hpp"

// Overloaded input operator for VTG message
DelimitedStringIterator& operator>>(DelimitedStringIterator& input, VTGMsg& msg) {
    input >> msg.course1
          >> msg.reference1
          >> msg.course2
          >> msg.reference2
          >> msg.speed1
          >> msg.speed1Unit
          >> msg.speed2
          >> msg.speed2Unit
          >> msg.mode;

    return input;
}

// Overloaded input operator for time wrapper
std::istream& operator>>(std::istream& input, TimeWrapper& time) {
    // Parse time string to time_t
    tm t;
    char dot;
    int ms;

    input >> std::get_time(&t, "%H%M%S") >> dot >> ms;
    time.value = (t.tm_hour * 3600 + t.tm_min * 60 + t.tm_sec) * 1000 + ms;

    return input;
}

// Overloaded input operator for GGA message
DelimitedStringIterator& operator>>(DelimitedStringIterator& input, GGAMsg& msg) {
    input >> msg.time
          >> msg.latitude
          >> msg.nsIndicator
          >> msg.longitude
          >> msg.ewIndicator
          >> msg.positionFixIndicator
          >> msg.satellitesUsed
          >> msg.hdop
          >> msg.mslAltitude
          >> msg.units1
          >> msg.geoidSeparation
          >> msg.units2
          >> msg.ageOfDiffCorr
          >> msg.diffRefStationID;

    return input;
}

double NMEAParser::calculateTotalDistance() {
    double result = 0.0;
    std::string line;

    GGAMsg prevCoordMsg;
    VTGMsg speedMsg;

    while (getline(file, line)) {
        DelimitedStringIterator si(line, ',');
        std::string tag;
        si >> tag;
        GGAMsg coordMsg;

        if (tag == "$GPGGA") {
            si >> coordMsg;
        } else if (tag == "$GNVTG") {
            si >> speedMsg;

            result += speedMsg.speed1 > EPSILON ? calculateDistance(prevCoordMsg, coordMsg) : 0.0;
        }

        // TODO: check checksum

        std::swap(prevCoordMsg, coordMsg);
    }

    return result;
}