
set(COMMON_SOURCES
   JsonParser_Common_Fixtures.hpp)

target_sources(${TEST_NAME} PRIVATE
	${COMMON_SOURCES})

source_group(Common FILES ${COMMON_SOURCES})