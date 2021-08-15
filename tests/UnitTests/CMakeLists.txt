  
set(TEST_NAME JsonParserTests)

set(SOURCES
   JsonParser_Fixtures.hpp
   JsonParser_Serialization_Tests.cpp
   JsonParser_Deserialization_Tests.cpp)

add_executable(${TEST_NAME})

target_sources(${TEST_NAME} PRIVATE
    ../Common/JsonParser_Common_Fixtures.hpp
	${SOURCES})

source_group(UnitTests FILES ${SOURCES})

target_link_libraries(${TEST_NAME} JsonParser gtest gtest_main)

target_compile_features(${TEST_NAME} PRIVATE cxx_std_17)

target_include_directories(${TEST_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../Common)