
set(SRC_LIBRARY_NAME JsonParser)

add_library(${SRC_LIBRARY_NAME})

target_sources(${SRC_LIBRARY_NAME} PRIVATE
   ../include/JsonArray.hpp
   ../include/JsonDataReader.hpp
   ../include/JsonNode.hpp
   ../include/JsonObject.hpp
   ../include/JsonParser.hpp
   ../include/JsonRawValue.hpp
   JsonArray.cpp
   JsonObject.cpp
   JsonParser.cpp
   JsonTraversalAlgorithm.hpp )

target_compile_features(${SRC_LIBRARY_NAME} PRIVATE cxx_std_17)

target_include_directories(${SRC_LIBRARY_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)

target_link_libraries(${SRC_LIBRARY_NAME} PRIVATE nlohmann_json::nlohmann_json)