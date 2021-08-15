  
set(TEST_NAME JsonParserTests)

add_executable(${TEST_NAME})

target_sources(${TEST_NAME} PRIVATE JsonParser_Serialization_Tests.cpp)

target_link_libraries(${TEST_NAME} JsonParser gtest gtest_main)

target_compile_features(${TEST_NAME} PRIVATE cxx_std_17)