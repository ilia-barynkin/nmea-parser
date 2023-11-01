find_library(MATH_LIB m)
add_library(nmea_parser filters.c nmea_parser.c distance.c)
target_include_directories(nmea_parser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(nmea_parser ${MATH_LIB})
