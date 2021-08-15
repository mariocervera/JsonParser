
set(SRC_LIBRARY_NAME JsonParser)

add_library(${SRC_LIBRARY_NAME})

target_sources(${SRC_LIBRARY_NAME} PRIVATE
   ../include/JsonNode.hpp
   ../include/JsonObject.hpp
   JsonObject.cpp
   JsonParser.cpp )

target_compile_features(${SRC_LIBRARY_NAME} PRIVATE cxx_std_17)

target_include_directories(${SRC_LIBRARY_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)