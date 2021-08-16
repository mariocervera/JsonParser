  
set(JSON_PARSER_TESTS JsonParserTests)

add_executable(${JSON_PARSER_TESTS})

include(files.cmake)
set_files()

target_link_libraries(${JSON_PARSER_TESTS} JsonParser gtest gtest_main)

target_compile_features(${JSON_PARSER_TESTS} PRIVATE cxx_std_17)