#include "JsonDataReader.hpp"
#include "JsonParser_Fixtures.hpp"
#include <gtest/gtest.h>

namespace UnitTests::JSONParser {

  // Verification methods (Act + Assert).

  static void verifyJsonObjectSerializesCorrectly(const JsonObject& jsonObject, const std::string& expectedJson) {
    const auto actualJson = jsonObject.toJsonString();
    ASSERT_EQ(actualJson, expectedJson);
  }

  // Parameterized tests (Arrange + Act + Assert).

  static void test_serializeJson_shouldSerializeRawValues(const std::vector<RawItem>& items,
                                                          const std::string& expectedJson) {
    const auto jsonObject = createJsonObjectWithRawValues(items);
    verifyJsonObjectSerializesCorrectly(*jsonObject, expectedJson);
  }

  static void test_serializeJson_shouldSerializeArray(const std::string& key,
                                                      const std::vector<std::string>& array,
                                                      const std::string& expectedJson) {
    const auto jsonObject = createJsonObjectWithArray(key, array);
    verifyJsonObjectSerializesCorrectly(*jsonObject, expectedJson);
  }

  // Test methods.

  TEST(JsonSerialization, WhenWeSerializeEmptyJsonThenResultIsCorrect) {

    const JsonObject jsonObject;

    const std::string expectedJson = "{}";
    ASSERT_EQ(jsonObject.toJsonString(), expectedJson);
  }

  TEST(JsonSerialization, WhenWeSerializeJsonWithRawValueThenResultIsCorrect) {

    const std::vector<RawItem> items = {RawItem(testKey1, stringTestValue1)};
    const auto expectedJson = "{\"" + testKey1 + "\" : \"" + stringTestValue1 + "\"}";

    test_serializeJson_shouldSerializeRawValues(items, expectedJson);
  }

  TEST(JsonSerialization, WhenWeSerializeJsonWithSeveralRawValuesThenResultIsCorrect) {

    const std::vector<RawItem> items = {RawItem(testKey1, stringTestValue1), RawItem(testKey2, stringTestValue2)};
    const auto expectedJson = "{\"" + testKey1 + "\" : \"" + stringTestValue1 + "\",\n\"" +
      testKey2 + "\" : \"" + stringTestValue2 + "\"}";

    test_serializeJson_shouldSerializeRawValues(items, expectedJson);
  }

  TEST(JsonSerialization, WhenWeSerializeJsonWithEmptyArrayThenResultIsCorrect) {

    const std::vector<std::string> array = {};
    const auto expectedJson = "{\"" + testKey1 + "\" : []}";

    test_serializeJson_shouldSerializeArray(testKey1, array, expectedJson);
  }

  TEST(JsonSerialization, WhenWeSerializeJsonWithOneElementArrayThenResultIsCorrect) {

    const std::vector<std::string> array = {stringTestValue1};
    const auto expectedJson = "{\"" + testKey1 + "\" : [\"" + stringTestValue1 + "\"]}";

    test_serializeJson_shouldSerializeArray(testKey1, array, expectedJson);
  }

  TEST(JsonSerialization, WhenWeSerializeJsonWithArrayWithSeveralElementsThenResultIsCorrect) {

    const std::vector<std::string> array = {stringTestValue1, stringTestValue2};
    const auto expectedJson = "{\"" + testKey1 + "\" : [\"" + stringTestValue1 + "\", \"" + stringTestValue2 + "\"]}";

    test_serializeJson_shouldSerializeArray(testKey1, array, expectedJson);
  }

  TEST(JsonSerialization, WhenWeSerializeJsonWithNestedObjectThenResultIsCorrect) {

    const auto jsonObject = createJsonObjectWithNestedObject(testKey1, testKey2, stringTestValue1);
    const auto expectedJson = "{\"" + testKey1 + "\" : {\"" + testKey2 + "\" : \"" + stringTestValue1 + "\"}}";

    verifyJsonObjectSerializesCorrectly(*jsonObject, expectedJson);
  }
}
