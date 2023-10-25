#include "nmea_msg.hpp"
#include "msg_parser.hpp"
// TODO: move to tests
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <ctime>
// int calculateChecksum(const std::string& str) {
//     // TODO
// }

// TODO: move to tests

int main(int argc, char* argv[]) {
    // std::ifstream file("/home/q/repos/pegas-test/test/trash/nmea.log");
    // std::string str;

    // while (getline(file, str))
    // {
    //     StringIterator si(str, ',');
    //     char delimiter;
    //     std::string tag;
    //     si >> tag;

    //     if (tag == "$GPGGA") {
    //         GGAMsg msg;
    //         si >> msg;
    //     } else if (tag == "$GNVTG") {
    //         VTGMsg msg;
    //         si >> msg;
    //     }

    //     int checksum;
    //     si >> std::hex >> checksum;

    //     // TODO: check checksum
    // }

    std::cout << "hello world" << std::endl;

    return 0;
}