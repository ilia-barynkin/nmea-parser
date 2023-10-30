#ifndef NMEA_MSG_H
#define NMEA_MSG_H

#include "time.h"
#include "stdbool.h"

typedef struct vtg_msg {
    float course_1;                  // Measured heading in degrees
    char reference_1;                // True reference
    float course_2;                  // Measured heading in degrees
    char reference_2;                // Magnetic reference
    float speed_1;                   // Measured horizontal speed in knots
    char speed_1_unit;               // Speed units in knots
    float speed_2;                   // Measured horizontal speed in km/hr
    char speed_2_unit;               // Speed units in km/hr
    char mode;                       // Mode: A=Autonomous, D=DGPS, E=DR
    bool is_ok;
} vtg_msg;

typedef struct gga_msg {
    double time;                     // Time
    double latitude;                 // Latitude
    char ns_indicator;               // N/S Indicator
    double longitude;                // Longitude
    char ew_indicator;               // E/W Indicator
    char position_fix_indicator;     // Position Fix Indicator
    char satellitesUsed;             // Satellites Used
    float hdop;                      // HDOP
    float msl_altitude;              // MSL Altitude
    char units_1;                    // Units
    float geoid_separation;          // Geoid Separation
    char units_2;                    // Units
    int age_of_diff_corr;            // Age of Diff. Corr.
    int diff_ref_station_id;         // Diff. Ref. Station ID
    bool is_ok;
} gga_msg;

#endif // NMEA_MSG_H