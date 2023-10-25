#include <string>
#include <iostream>
#include <fstream>
#include <cmath>

#include "nmea_parser.hpp"

//Написать программу, которая берет из файла nmea.log координаты и считает по ним пройденный путь.
//Если скорость равна нулю, изменение координат в пройденном пути не учитывать.

int main(int argc, char* argv[]) {
    //NMEAParser parser("nmea.log");
    NMEAParser parser("VTG_and_WTG.log");
    double dist = parser.calculateTotalDistance();
    std::cout << dist << std::endl;

    return 0;
}