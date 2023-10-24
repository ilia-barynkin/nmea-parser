#ifndef MSG_PARSER_HPP
#define MSG_PARSER_HPP

#include <string>
#include <sstream>
#include <iostream>

class StringIterator {
public:
    StringIterator(const std::string& str, char delimiter)
        : ss(str), delimiter(delimiter) {}

    template <typename T>
    StringIterator& operator>>(T& value) {
        std::string token;
        
        if (std::getline(ss, token, delimiter)) {
            std::istringstream tokenStream(token);
            tokenStream >> value;
        }
        
        return *this;
    }

private:
    std::istringstream ss;
    char delimiter;
};

#endif // MSG_PARSER_HPP