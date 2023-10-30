#ifndef DISTANCE_H
#define DISTANCE_H

#include <math.h>

#include "nmea_msg.h"

inline double deg_to_rad(double degrees) {
    return degrees * M_PI / 180.0;
}

#endif // DISTANCE_H