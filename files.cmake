
function(set_files)

set(INCLUDE_FILES
   include/JsonArray.hpp
   include/JsonDataReader.hpp
   include/JsonNode.hpp
   include/JsonObject.hpp
   include/JsonParser.hpp
   include/JsonRawValue.hpp
)

set(SRC_FILES
   src/JsonArray.cpp
   src/JsonObject.cpp
   src/JsonParser.cpp
   src/JsonTraversalAlgorithm.hpp
)

set(ALL_FILES ${INCLUDE_FILES} ${SRC_FILES})

target_sources(${JSON_PARSER_LIBRARY_NAME} PRIVATE ${ALL_FILES})
   
source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${ALL_FILES})

target_include_directories(${JSON_PARSER_LIBRARY_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

endfunction()