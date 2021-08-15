  
set(TEST_NAME JsonParserTests)

add_executable(${TEST_NAME})

set(COMMON_FILES
    Common/JsonParser_Common_Fixtures.hpp
)

set(UNIT_TESTS_FILES
    UnitTests/JsonParser_Fixtures.hpp
	UnitTests/JsonParser_Serialization_Tests.cpp
	UnitTests/JsonParser_Deserialization_Tests.cpp
)

set(ALL_FILES ${COMMON_FILES} ${UNIT_TESTS_FILES})

target_sources(${TEST_NAME} PRIVATE ${ALL_FILES})

source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${ALL_FILES})

target_include_directories(${TEST_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Common)

target_link_libraries(${TEST_NAME} JsonParser gtest gtest_main)

target_compile_features(${TEST_NAME} PRIVATE cxx_std_17)