#include <assert.h>
#include <string.h>

#include "nmea_parser.h"


int main(int argc, char* argv[]) {
    const char* data =
    "$GPGGA,092547.20,5157.89111643,N,04806.03913471,E,1,34,0.5,100.3851,M,-1.6215,M,02,999*4F"
    "$GNVTG,28.858,T,17.799,M,0.05550,N,0.10279,K,D*3E";

    nmea_parser* parser = init_nmea_parser(data);

    parse_next(parser);
    parse_next(parser);

    return 0;
}