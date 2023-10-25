#ifndef NMEA_MSG_H
#define NMEA_MSG_H

#include <string>
#include <iostream>
#include <chrono>

typedef struct TimeWrapper {
    time_t value;
    operator time_t() const {
        return value;
    }
} TimeWrapper;

// VTG - Course Over Ground and Ground Speed

// Name             Example     Unit        Description
//
// Message ID       $GPVTG                  VTG protocol header
// Course           309.62      degrees     Measured heading
// Reference        T                       True
// Course                       degrees     Measured heading
// Reference        M                       Magnetic
// Speed            0.13        knots       Measured horizontal speed
// Units            N                       Knots
// Speed            0.2         km/hr       Measured horizontal speed
// Units            K                       Kilometers per hour
// Mode             A                       A=Autonomous, D=DGPS, E=DR
// Checksum         *23
// <CR> <LF> End of message termination

// Example: $GNVTG,28.858,T,17.799,M,0.05550,N,0.10279,K,D*3E

typedef struct VTGMsg {
    float course1;
    bool reference1;
    float course2;
    char reference2;
    float speed1;
    char speed1Unit;
    float speed2;
    char speed2Unit;
    char mode;
} VTGMsg;

// GGA - Global Positioning System Fixed Data
//
// Name                     Example     Unit        Description
// Message ID               $GPGGA                  GGA protocol header
// UTC Time                 002153.000              hhmmss.sss
// Latitude                 3342.6618               ddmm.mmmm
// N/S Indicator            N                       N=north or S=south
// Longitude                11751.3858              dddmm.mmmm
// E/W Indicator            W                       E=east or W=west
// Position Fix Indicator   1                       See Table 1-4
// Satellites Used          10                      Range 0 to 12
// HDOP                     1.2                     Horizontal Dilution of Precision
// MSL Altitude             27.0        meters
// Units                    M           meters
// Geoid Separation         -34.2       meters      Geoid-to-ellipsoid separation.
//                                                  Ellipsoid altitude = MSL Altitude + Geoid Separation.
// Units                    M           meters
// Age of Diff. Corr.                   sec         Null fields when DGPS is not used
// Diff. Ref. Station ID    0000
// Checksum *5E

// Example: $GPGGA,092547.30,5157.89111607,N,04806.03913459,E,1,34,0.5,100.3837,M,-1.6215,M,02,999*44

// M
// 02
// 999*44

// TODO: convert positionFixIndicator type to enum

typedef struct GGAMsg {
    TimeWrapper time;           // 092547.30
    double latitude;            // 5157.89111607
    char nsIndicator;           // N
    double longitude;           // 04806.03913459
    char ewIndicator;           // E
    char positionFixIndicator;  // 1
    int satellitesUsed;         // 34
    float hdop;                 // 0.5
    float mslAltitude;          // 100.3837
    char units1;                // M
    float geoidSeparation;      // -1.6215
    char units2;                // M
    int ageOfDiffCorr;          // 02 ?
    int diffRefStationID;       // 999
} GGAMsg;

#endif // NMEA_MSG_H