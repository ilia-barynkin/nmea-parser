# NMEA Parser with Butterworth Filtering

![Build Status](https://img.shields.io/badge/build-passing-brightgreen)

The NMEA Parser is a program that parses NMEA log files via C++ stream objects. It implements low-pass Butterworth filter to remove noise from the data stream. The filter is only applied to WTG messages.

## TODO

0. Add CRC checking.
1. Re-implement all this as a real-time app for embedded systems.
2. Add unit tests.
3. Add documentation.
4. Add server-side app to simulate client-server architecture via CAN bus.
5. Add pygame GUI and display gps movements.
7. Port all this BS to some Cortex development board e.g. Raspberry Pi Pico.
