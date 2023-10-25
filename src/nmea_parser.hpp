#ifndef NMEA_PARSER_HPP
#define NMEA_PARSER_HPP

#include <sstream>
#include <fstream>
#include <string>
#include <cmath>

#include "nmea_msg.hpp"

class DelimitedStringIterator {
public:
    DelimitedStringIterator(const std::string& str, char delimiter)
        : stream(str), delimiterChar(delimiter) {}

    template <typename T>
    DelimitedStringIterator& operator>>(T& value) {
        std::string token;
        
        if (std::getline(stream, token, delimiterChar)) {
            std::istringstream tokenStream(token);
            tokenStream >> value;
        }
        
        return *this;
    }

private:
    std::istringstream stream;
    char delimiterChar;
};

#define EPSILON 0.00001

class NMEAParser {

public:
    NMEAParser(const std::string& filename) : file(filename) {}

    double calculateTotalDistance();

private:
    std::ifstream file;

inline double calculateDistance(GGAMsg coord0, GGAMsg coord1) {
    double geoidSeparation = coord0.geoidSeparation;
    double lat1 = coord0.latitude * M_PI / 180.0;
    double lon1 = coord0.longitude * M_PI / 180.0;
    double lat2 = coord1.latitude * M_PI / 180.0;
    double lon2 = coord1.longitude * M_PI / 180.0;

    double deltaLat = lat2 - lat1;
    double deltaLon = lon2 - lon1;

    double a = sin(deltaLat / 2) * sin(deltaLat / 2) + cos(lat1) * cos(lat2) * sin(deltaLon / 2) * sin(deltaLon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    double distance = geoidSeparation * c;

    return distance;
}
};

#endif // NMEA_PARSER_HPP