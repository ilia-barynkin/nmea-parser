#ifndef NMEA_MSG_H
#define NMEA_MSG_H

#include <string>
#include <iostream>
#include <chrono>

struct TimeWrapper {
    time_t value;
    operator time_t() const {
        return value;
    }
};

struct VTGMsg {
    float course1;      // Measured heading in degrees
    bool reference1;    // True reference
    float course2;      // Measured heading in degrees
    char reference2;    // Magnetic reference
    float speed1;       // Measured horizontal speed in knots
    char speed1Unit;    // Speed units in knots
    float speed2;       // Measured horizontal speed in km/hr
    char speed2Unit;    // Speed units in km/hr
    char mode;          // Mode: A=Autonomous, D=DGPS, E=DR
};

struct GGAMsg {
    TimeWrapper time;           // UTC Time 
    double latitude;            // Latitude
    char nsIndicator;           // N/S Indicator
    double longitude;           // Longitude
    char ewIndicator;           // E/W Indicator
    char positionFixIndicator;  // Position Fix Indicator
    int satellitesUsed;         // Satellites Used
    float hdop;                 // HDOP
    float mslAltitude;          // MSL Altitude
    char units1;                // Units
    float geoidSeparation;      // Geoid Separation
    char units2;                // Units
    int ageOfDiffCorr;          // Age of Diff. Corr.
    int diffRefStationID;       // Diff. Ref. Station ID
};

#endif // NMEA_MSG_H