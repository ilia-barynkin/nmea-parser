add_executable(parser main.c)

target_link_libraries(parser PRIVATE nmea_parser)

target_include_directories(parser PUBLIC ../../src)

