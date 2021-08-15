
#include "JsonObject.hpp"
#include <gtest/gtest.h>

namespace EWOS::Infrastructure::UnitTests::JSONParser {

  // Test methods.

  TEST(JsonSerialization, WhenWeSerializeEmptyJsonThenResultIsCorrect) {

    const Infrastructure::JSONParser::JsonObject jsonObject;

    const std::string expectedJson = "{}";
    ASSERT_EQ(jsonObject.toJsonString(), expectedJson);

    ASSERT_TRUE(true);
  }
  
}
