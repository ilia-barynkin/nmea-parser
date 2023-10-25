add_library(nmea_parser nmea_parser.cpp butterworth_filter.cpp)

target_include_directories(nmea_parser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
