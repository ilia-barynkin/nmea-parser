#ifndef NMEA_PARSER_HPP
#define NMEA_PARSER_HPP

#include <sstream>
#include <fstream>
#include <string>

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

    double calculateDistance(const GGAMsg& coord0, const GGAMsg& coord1);
};

#endif // NMEA_PARSER_HPP