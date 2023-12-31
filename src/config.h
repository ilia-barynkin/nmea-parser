#ifndef CONFIG_H
#define CONFIG_H

#include "nmea_msg.h"

#define MSG_TAG_LEN 6

#define VTG_TAG "$GPVTG"
#define WTG_TAG "$GPWTG"
#define GGA_TAG "$GPGGA"

// inline char crc_xor(const char* input, size_t size) {
//     char result = 0;
//     for (size_t i = 0; i < size; i++) {
//         result ^= input[i];
//     }
//     return result;
// }

#define VTG_CHECKSUM 0x76
#define WTG_CHECKSUM 0x77
#define GGA_CHECKSUM 0x72

// control symbols

#define LINE_START_SYM '$'
#define ENDL_SYM '\n'
#define DELIMITER_SYM ','
#define CRC_SYM '*'
#define EOF_SYM '\0'

// Butterworth filter parameters

#define BUTTERWORTH_DEFULT_ORDER 4
#define BUTTERWORTH_DEFULT_CUTOFF_FREQUENCY 5
#define BUTTERWORTH_DEFULT_SAMPLING_FREQUENCY 10

#define MSG_BUFFER_LEN 0x10

#define EPSILON 0.00001

#endif // CONFIG_H