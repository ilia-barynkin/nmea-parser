#include <assert.h>

#include "nmea_parser.h"


int main(int argc, char* argv[]) {
    nmea_parser* parser = init_nmea_parser(argv[1]);

    return 0;
}