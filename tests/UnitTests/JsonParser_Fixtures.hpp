#ifndef JSONPARSER_UNITTESTS_FIXTURES_H
#define JSONPARSER_UNITTESTS_FIXTURES_H

#include "JsonParser_Common_Fixtures.hpp"

namespace EWOS::Infrastructure::UnitTests::JSONParser {

  using namespace Infrastructure::JSONParser;
  using namespace Tests::Common::JSONParser;

  static const std::string testKey1 = "Test Key 1";
  static const std::string testKey2 = "Test Key 2";
  static const std::string testKey3 = "Test Key 3";
  static const bool boolTestValue1 = false;
  static const bool boolTestValue2 = true;
  static const int intTestValue1 = 1;
  static const int intTestValue2 = 2;
  static const float floatTestValue1 = 1.5;
  static const float floatTestValue2 = 2.5;
  static const std::string stringTestValue1 = "Test Value 1";
  static const std::string stringTestValue2 = "Test Value 2";

  static const std::string jsonOneKey = R"({"DummyKey" : "DummyValue"})";

  const std::string jsonThreeKeys = "{"
    R"("DummyKey_1" : "DummyValue_1",)"
    R"("DummyKey_2" : "DummyValue_2",)"
    R"("DummyKey_3" : "DummyValue_3")"
    "}";

  struct RawItem {

    RawItem(std::string key, std::string value)
      : key(std::move(key)), value(std::move(value)) {
    }

    std::string key;
    std::string value;
  };

  template <typename T>
  static std::string createJsonWithRawData(const std::string& key, T value) {
    return "{\"" + key + "\" : \"" + std::to_string(value) + "\"}";
  }

  template <>
  static std::string createJsonWithRawData(const std::string& key, std::string value) {
    return "{\"" + key + "\" : \"" + value + "\"}";
  }

  static std::string createJsonWithRawData(const std::string& key) {
    return createJsonWithRawData<std::string>(key, stringTestValue1);
  }

  static std::string createJsonWithEmptyArray(const std::string& key) {
    return "{\"" + key + "\" : []}";
  }

  template <typename T>
  static std::string createJsonWithArray(const std::string& key, T value1, T value2) {
    return "{\"" + key + "\" : [" + std::to_string(value1) + ", " + std::to_string(value2) + "]}";
  }

  template <>
  static std::string createJsonWithArray(const std::string& key, std::string value1, std::string value2) {
    return "{\"" + key + "\" : [\"" + value1 + "\", \"" + value2 + "\"]}";
  }

  static std::string createJsonWithArray(const std::string& key) {
    return createJsonWithArray<std::string>(key, "1", "Dummy Value");
  }

  template <typename T>
  static std::string createJsonWithObject(const std::string& key1, const std::string& key2, T value) {
    return "{\"" + key1 + "\" : {\"" + key2 + "\" : \"" + std::to_string(value) + "\"}}";
  }

  template <>
  static std::string createJsonWithObject(const std::string& key1, const std::string& key2, std::string value) {
    return "{\"" + key1 + "\" : {\"" + key2 + "\" : \"" + value + "\"}}";
  }

  static std::string createJsonWithObject(const std::string& key) {
    return "{\"" + key + R"(" : {"Dummy Key" : "Dummy Value"}})";
  }

  static std::string createJsonWithNesting(const std::string& key1, const std::string& key2, const std::string& key3,
                                           int value) {
    return "{\"" + key1 + "\" : {\"" + key2 + "\" : {\"" + key3 + "\" : [\"" + std::to_string(value) + "\"]}}}";
  }

  static std::unique_ptr<JsonObject> createJsonObjectWithRawValues(const std::vector<RawItem>& items) {
    auto jsonObject = std::make_unique<JsonObject>();
    for (const auto& item : items)
      addRawValueToObject(*jsonObject, item.key, item.value);

    return jsonObject;
  }

  static std::unique_ptr<JsonObject> createJsonObjectWithArray(const std::string& key,
                                                               const std::vector<std::string>& array) {
    auto jsonObject = std::make_unique<JsonObject>();
    addArrayToObject(*jsonObject, key, array);

    return jsonObject;
  }

  static std::unique_ptr<JsonObject> createJsonObjectWithNestedObject(const std::string& key1,
                                                                      const std::string& key2,
                                                                      const std::string& value) {
    auto nestedObject = createJsonObjectWithRawValues({RawItem(key2, value)});
    auto jsonObject = std::make_unique<JsonObject>();
    addObjectToObject(*jsonObject, key1, std::move(nestedObject));

    return jsonObject;
  }
}

#endif
