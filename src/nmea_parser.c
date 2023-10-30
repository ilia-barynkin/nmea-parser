#include <memory.h>
#include <errno.h>
#include <string.h>

#include "nmea_msg.h"
#include "nmea_parser.h"
#include "config.h"

nmea_parser* init_nmea_parser(const char* data) {
    nmea_parser* parser = (nmea_parser*) malloc(sizeof(nmea_parser));
    
    if (!parser) {
        errno = ENOMEM;
        return NULL;
    }

    parser->filter = init_butterworth_filter(BUTTERWORTH_DEFULT_ORDER, BUTTERWORTH_DEFULT_CUTOFF_FREQUENCY, BUTTERWORTH_DEFULT_SAMPLING_FREQUENCY);
    parser->vtg_messages = vec_vtg_messages_init(MSG_BUFFER_LEN);
    parser->gga_messages = vec_gga_messages_init(MSG_BUFFER_LEN);
    parser->input = data;
    parser->crc = 0x00;

    return parser;
}

void parse_next(nmea_parser* parser) {
    parse_tag(parser);
    
    do {
        if(consume(parser) == ENDL_SYM || *parser->input ==  EOF_SYM)
            break;
    } while (true);
}

void parse_tag(nmea_parser* parser) {
    consume_many(parser, MSG_TAG_LEN);
    
    if (parser->crc == VTG_CHECKSUM) {
        consume(parser); // delimiter
        vtg_msg *msg = vec_gga_msg_push_empty(parser->vtg_messages);
        parse_vtg(parser, msg);
    } else if (parser->crc == WTG_CHECKSUM) {
        consume(parser); // delimiter
        vtg_msg *msg = vec_gga_msg_push_empty(parser->vtg_messages);
        parse_wtg(parser, msg);
    } else if (parser->crc == GGA_CHECKSUM) {
        consume(parser); // delimiter
        gga_msg *msg = vec_gga_msg_push_empty(parser->gga_messages);
        parse_gga(parser, msg);
    }
}

void parse_vtg(nmea_parser* parser, vtg_msg* msg) {
    msg->course_1 = parse_float(parser);
    msg->reference_1 = parse_char(parser);
    msg->course_2 = parse_float(parser);
    msg->reference_2 = parse_char(parser);
    msg->speed_1 = parse_float(parser);
    msg->speed_1_unit = parse_char(parser);
    msg->speed_2 = parse_float(parser);
    msg->speed_2_unit = consume(parser);
    msg->mode = consume(parser);

    char checksum = parser->crc;
    msg->is_ok = checksum == parse_hex(parser);
}

void parse_wtg(nmea_parser* parser, vtg_msg* msg) {
    parse_vtg(parser, msg);
    
    if (msg->is_ok) {
        msg->speed_1 = apply_butterworth_filter(parser->filter, msg->speed_1);
        msg->speed_2 = apply_butterworth_filter(parser->filter, msg->speed_2);
        msg->course_1 = apply_butterworth_filter(parser->filter, msg->course_1);
        msg->course_2 = apply_butterworth_filter(parser->filter, msg->course_2);
    }
}

void parse_gga(nmea_parser* parser, gga_msg* msg) {
    msg->time = parse_time(parser);
    msg->latitude = parse_double(parser);
    msg->ns_indicator = parse_char(parser);
    msg->longitude = parse_double(parser);
    msg->ew_indicator = parse_char(parser);
    msg->position_fix_indicator = parse_char(parser);
    msg->satellitesUsed = parse_char(parser);
    msg->hdop = parse_float(parser);
    msg->msl_altitude = parse_float(parser);
    msg->units_1 = parse_char(parser);
    msg->geoid_separation = parse_float(parser);
    msg->units_2 = parse_char(parser);
    msg->age_of_diff_corr = parse_int(parser);
    msg->diff_ref_station_id = parse_int(parser);

    int checksum = parser->crc;
    consume(parser); // asterisk
    msg->is_ok = checksum == parse_hex(parser);
}

double parse_time(nmea_parser* parser) {
    int time = parse_int(parser);
    int seconds = time % 100;
    int minutes = (time / 100) % 100;
    int hours = time / 10000;
    
    return seconds + 60.0 * (minutes + 60.0 * (hours)) + parse_fract(parser);
}

float parse_float(nmea_parser* parser) {
    float result = parse_int(parser);
    
    if (*(parser->input) = '.') {
        result += parse_fract(parser);
    }

    return result;
}

double parse_double(nmea_parser* parser) {
    double result = parse_int(parser);
    
    if (*(parser->input) = '.') {
        result += parse_fract(parser);
    }

    return result;
}

int parse_int(nmea_parser* parser) {
    char current_char = consume(parser);
    
    if (current_char == '-')
        return -1 * parse_int(parser);
    if (current_char < '0' || current_char > '9')
        return 0;
    
    return (int)(current_char - '0') + 10 * parse_int(parser);
}

float parse_fract(nmea_parser* parser) {
    char current_char = consume(parser);
    
    if (current_char < '0' || current_char > '9')
        return 0;
    
    return 0.1f *(float)(current_char - '0') + 0.1f * parse_fract(parser);
}

char parse_hex(nmea_parser* parser) {
    char current_char = consume(parser);
    
    if (current_char < 'A' && (current_char < '0' || current_char > '9') ||
        current_char > 'F') {
        return 0;
    }
    
    return (current_char - '0') + 0x10 * parse_hex(parser);
}

void nmea_parser_free(nmea_parser* parser) {
    free_butterworth_filter(parser->filter);
    vec_vtg_messages_free(parser->vtg_messages);
    vec_gga_messages_free(parser->gga_messages);
    free(parser);
}