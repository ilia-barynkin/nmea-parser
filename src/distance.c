#include "distance.h"

double calculateDistance(gga_msg *coord0, gga_msg *coord1) {
    double lat1 = deg_to_rad(coord0->latitude);
    double lon1 = deg_to_rad(coord0->longitude);
    double lat2 = deg_to_rad(coord1->latitude);
    double lon2 = deg_to_rad(coord1->longitude);

    double deltaLat = abs(lat2 - lat1);
    double deltaLon = abs(lon2 - lon1);

    double sin_delta_lat_half = sin(deltaLat / 2.0);
    double sin_delta_lon_half = sin(deltaLon / 2.0);
    double cos_lat1 = cos(lat1);
    double cos_lat2 = cos(lat2);

    double a = sin_delta_lat_half * sin_delta_lat_half;
    double b = sin_delta_lon_half * sin_delta_lon_half * cos_lat1 * cos_lat2;
    double c = 2.0 * atan2(sqrt(a + b), sqrt(1.0 - a - b));
    
    double ellipsoidAltitude = coord0->msl_altitude + coord0->geoid_separation;
    double deltaLatEllipsoidAltitude = deltaLat * ellipsoidAltitude;
    double deltaLonEllipsoidAltitude = deltaLon * ellipsoidAltitude;
    double distance = sqrt(deltaLatEllipsoidAltitude * deltaLatEllipsoidAltitude + deltaLonEllipsoidAltitude * deltaLonEllipsoidAltitude) * c;

    return distance;
}