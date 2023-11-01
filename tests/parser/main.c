#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

#include "nmea_parser.h"

int main(int argc, char* argv[]) {
    const char* data =
    "$GPGGA,092547.20,5157.89111643,N,04806.03913471,E,1,34,0.5,100.3851,M,-1.6215,M,02,999*4F"
    "$GNVTG,28.858,T,17.799,M,0.05550,N,0.10279,K,D*3E";

    nmea_parser* parser = init_nmea_parser(data);
    void* msg = NULL;
    MSG_TYPE result_type;

    while (msg = parse_next(parser, &result_type)) {
        switch (result_type) {
            case VTG:
                printf("VTG: %f %s\n", ((vtg_msg*)msg)->course_1, ((vtg_msg*)msg)->reference_1);
                break;
            case GGA:
                printf("GGA: %f %s\n", ((gga_msg*)msg)->time, ((gga_msg*)msg)->latitude);
                break;
            case WTG:
                printf("WTG: %f %s\n", ((vtg_msg*)msg)->course_1, ((vtg_msg*)msg)->reference_1);
                break;
            case ERR:
                printf("ERR\n");
                break;
            default:
                assert(false);
            break;
        }
    }

    nmea_parser_free(parser);

    return 0;
}