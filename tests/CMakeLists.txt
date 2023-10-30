add_executable(tests main.c)

target_link_libraries(tests PRIVATE nmea_parser)

target_include_directories(tests PUBLIC ../src)
