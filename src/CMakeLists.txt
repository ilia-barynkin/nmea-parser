add_library(nmea_parser nmea_parser.c filters.c distance.c)
target_include_directories(nmea_parser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
