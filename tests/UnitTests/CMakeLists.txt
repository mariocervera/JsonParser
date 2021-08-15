
set(UNIT_TESTS_SOURCES
   JsonParser_Fixtures.hpp
   JsonParser_Serialization_Tests.cpp
   JsonParser_Deserialization_Tests.cpp)

target_sources(${TEST_NAME} PRIVATE
	${UNIT_TESTS_SOURCES})

source_group(UnitTests FILES ${UNIT_TESTS_SOURCES})

target_include_directories(${TEST_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../Common)