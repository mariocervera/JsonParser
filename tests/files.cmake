
function(set_files)

set(COMMON_FILES
    Common/JsonParser_Common_Fixtures.hpp
)

set(UNIT_TESTS_FILES
    UnitTests/JsonParser_Fixtures.hpp
	UnitTests/JsonParser_Serialization_Tests.cpp
	UnitTests/JsonParser_Deserialization_Tests.cpp
)

set(FUNCTIONAL_TESTS_FILES
    FunctionalTests/JsonParser_Fixtures.hpp
	FunctionalTests/JsonParser_Serialization_Tests.cpp
	FunctionalTests/JsonParser_Deserialization_Tests.cpp
)

set(ALL_FILES ${COMMON_FILES} ${UNIT_TESTS_FILES} ${FUNCTIONAL_TESTS_FILES})

target_sources(${JSON_PARSER_TESTS} PRIVATE ${ALL_FILES})

source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${ALL_FILES})

target_include_directories(${JSON_PARSER_TESTS} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Common)

endfunction()