add_executable(gen_vec main.c)

target_link_libraries(gen_vec PRIVATE nmea_parser)

target_include_directories(gen_vec PUBLIC ../../src)

