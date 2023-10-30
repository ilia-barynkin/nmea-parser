#include <assert.h>

#include "../src/nmea_crc.h"
#include "../src/nmea_msg.h"

//Написать программу, которая берет из файла nmea.log координаты и считает по ним пройденный путь.
//Если скорость равна нулю, изменение координат в пройденном пути не учитывать.

int main(int argc, char* argv[]) {
    //NMEAParser parser("nmea.log");
    // NMEAParser parser("VTG_and_WTG.log");
    // double dist = parser.calculateTotalDistance();
    // std::cout << dist << std::endl;

    const char wtg_checksum = WTG_CHECKSUM;
    const char vtg_checksum = VTG_CHECKSUM;
    const char gga_checksum = GGA_CHECKSUM;

    assert(wtg_checksum != vtg_checksum);
    assert(vtg_checksum != gga_checksum);
    assert(gga_checksum != wtg_checksum);


    return 0;
}