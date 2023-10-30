# NMEA Parser with Butterworth Filtering

![Build Status](https://img.shields.io/badge/build-passing-brightgreen)

The NMEA Parser is a program that parses NMEA log files via ad-hoc finite-state machine. It implements low-pass Butterworth filter to remove noise from the data stream and geoid distance calculation.

## TODO

1. Add unit tests.
2. Add documentation.
3. Add tests for distance calculation via can-utils.
4. Add pygame GUI and display gps movements.
