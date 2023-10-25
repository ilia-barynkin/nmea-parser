# NMEA Parser with Butterworth Filtering

![Build Status](https://img.shields.io/badge/build-passing-brightgreen)

The NMEA Parser is a program that parses NMEA log files via C++ stream objects. It implements low-pass Butterworth filter to remove noise from the data stream. The filter is only applied to WTG messages.

## TODO

0. Add CRC checking.
1. Add python front-end with matplotlib or pygame to plot the data.
2. Add tests.
3. Implement multithreading.