#include <istream>
#include <iomanip>
#include <ctime>
#include <cmath>

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

double degToRad(double degrees) {
    return degrees * M_PI / 180.0;
}

double NMEAParser::calculateDistance(const GGAMsg& coord0, const GGAMsg& coord1) {
    double lat1 = degToRad(coord0.latitude);
    double lon1 = degToRad(coord0.longitude);
    double lat2 = degToRad(coord1.latitude);
    double lon2 = degToRad(coord1.longitude);

    double deltaLat = std::abs(lat2 - lat1);
    double deltaLon = std::abs(lon2 - lon1);

    double sinDeltaLatHalf = sin(deltaLat / 2.0);
    double sinDeltaLonHalf = sin(deltaLon / 2.0);
    double cosLat1 = cos(lat1);
    double cosLat2 = cos(lat2);

    double a = sinDeltaLatHalf * sinDeltaLatHalf;
    double b = sinDeltaLonHalf * sinDeltaLonHalf * cosLat1 * cosLat2;
    double c = 2.0 * atan2(sqrt(a + b), sqrt(1.0 - a - b));
    
    double ellipsoidAltitude = coord0.mslAltitude + coord0.geoidSeparation;
    double deltaLatEllipsoidAltitude = deltaLat * ellipsoidAltitude;
    double deltaLonEllipsoidAltitude = deltaLon * ellipsoidAltitude;
    double distance = sqrt(deltaLatEllipsoidAltitude * deltaLatEllipsoidAltitude + deltaLonEllipsoidAltitude * deltaLonEllipsoidAltitude) * c;

    return distance;
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

        if (tag == "$GPGGA") {
            GGAMsg coordMsg;
            si >> coordMsg;

            if (speedMsg.speed1 > EPSILON) {
                result += calculateDistance(prevCoordMsg, coordMsg);
                std::cout << result << std::endl;
            }

            prevCoordMsg = coordMsg;
        } else if (tag == "$GNVTG") {
            si >> speedMsg;
        }
    }

    return result;
}
