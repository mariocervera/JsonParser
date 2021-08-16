#include "JsonDataReader.hpp"
#include "JsonParser.hpp"
#include "JsonParser_Fixtures.hpp"
#include <gtest/gtest.h>

namespace FunctionalTests::JSONParser {

  using JsonMap = std::unordered_map<std::string, std::unique_ptr<JsonNode>>;

  // Custom assertions.

  template <typename T>
  static void assertAttributeIsCorrect(const JsonMap& jsonMap, const std::string& attribute, T attributeValue) {
    const auto& attribNode = *jsonMap.at(attribute);
    const auto& attribValue = readNodeAsRawValue<T>(attribNode);
    ASSERT_EQ(attribValue, attributeValue);
  }

  template <typename T>
  static void assertAttributeIsCorrect(const JsonObject& jsonObj, const std::string& attribute, T attributeValue) {
    assertAttributeIsCorrect(jsonObj.getObjectMap(), attribute, attributeValue);
  }

  static void assertArrayIsCorrect(const JsonMap& jsonMap, const std::string& attribute,
                                   const std::string& value1, const std::string& value2, const std::string& value3) {
    const auto& attribNode = *jsonMap.at(attribute);
    const auto& attribValue = readNodeAsArray(attribNode);
    ASSERT_EQ(readNodeAsRawValue<std::string>(*attribValue[0]), value1);
    ASSERT_EQ(readNodeAsRawValue<std::string>(*attribValue[1]), value2);
    ASSERT_EQ(readNodeAsRawValue<std::string>(*attribValue[2]), value3);
  }

  // Verification methods.

  static void verifyJsonObjectCanBeRead(const JsonObject& jsonObj) {

    assertAttributeIsCorrect<std::string>(jsonObj, "name", "John Doe");
    assertAttributeIsCorrect<int>(jsonObj, "age", 30);

    const auto& courseNode = *jsonObj["course"];
    const auto& course = readNodeAsObject(courseNode);

    assertAttributeIsCorrect<std::string>(course, "teacher", "Jane Doe");
    assertArrayIsCorrect(course, "topics", "Introduction to Programming", "Algorithms and Data Structures",
                         "Agile Development");

    const auto& universityNode = *course.at("university");
    const auto& university = readNodeAsObject(universityNode);

    assertAttributeIsCorrect<std::string>(university, "name", "Universitat Politecnica de Valencia");
    assertArrayIsCorrect(university, "campus", "Valencia", "Gandia", "Alcoy");
  }

  // Test methods.

  TEST(GivenJsonDeserializer, WhenWeDeserializeNonExistentJsonFileThenWeGetMalformedObject) {

    JsonObject jsonObj = parseJsonFile("NonExistentFile");

    ASSERT_FALSE(jsonObj.isWellFormed());
  }

  TEST(GivenJsonDeserializer, WhenWeDeserializeExistentJsonFileThenWeGetWellformedObject) {

    JsonObject jsonObj = parseJsonFile(jsonFilePath);

    ASSERT_TRUE(jsonObj.isWellFormed());
  }

  TEST(GivenJsonDeserializer, WhenWeDeserializeJsonFileThenWeCanReadTheData) {

    const auto jsonObj = parseJsonFile(jsonFilePath);

    verifyJsonObjectCanBeRead(jsonObj);
  }
}
