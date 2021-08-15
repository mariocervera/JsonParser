cmake_minimum_required(VERSION 3.18)

project(JsonParser)

include(FetchContent)


# GoogleTest dependency

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.10.0
)

FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
  FetchContent_Populate(googletest)
  add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()


# nlohmann dependency

FetchContent_Declare(json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.7.3)

FetchContent_GetProperties(json)
if(NOT json_POPULATED)
  FetchContent_Populate(json)
  add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()


# Json Parser library

set(JSON_PARSER_LIBRARY_NAME JsonParser)

add_library(${JSON_PARSER_LIBRARY_NAME})

include(files.cmake)
set_files()

target_compile_features(${JSON_PARSER_LIBRARY_NAME} PRIVATE cxx_std_17)

target_link_libraries(${JSON_PARSER_LIBRARY_NAME} PRIVATE nlohmann_json::nlohmann_json)

add_subdirectory(tests)