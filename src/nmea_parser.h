#ifndef NMEA_PARSER_H
#define NMEA_PARSER_H

#include "nmea_msg.h"
#include "filters.h"
#include "config.h"

typedef struct {
    butterworth_filter *filter;
    vec_vtg_msg* vtg_messages;
    vec_gga_msg* gga_messages;
    const char* input;
    char crc;
} nmea_parser;

inline char consume(nmea_parser* parser) {
    return *(parser->input++) ^ (parser->crc ^= *parser->input);
}

inline char consume_many(nmea_parser* parser, int count) {
    for (int i = 0; i < count; i++) {
        consume(parser);
    }
    
    return consume(parser);
}

nmea_parser* init_nmea_parser(const char* data);

void parse_next(nmea_parser* parser);

void nmea_parser_free(nmea_parser* parser);

double parse_time(nmea_parser* parser);

float parse_float(nmea_parser* parser);

double parse_double(nmea_parser* parser);

int parse_int(nmea_parser* parser);

float parse_fract(nmea_parser* parser);

char parse_hex(nmea_parser* parser);

void parse_gga(nmea_parser* parser, gga_msg* msg);

void parse_wtg(nmea_parser* parser, vtg_msg* msg);

void parse_vtg(nmea_parser* parser, vtg_msg* msg);

void parse_tag(nmea_parser* parser);

#endif // NMEA_PARSER_H