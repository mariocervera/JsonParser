#include "JsonDataReader.hpp"
#include "JsonParser_Fixtures.hpp"
#include <gtest/gtest.h>

namespace UnitTests::JSONParser {
	
	// Custom assertions.

	template <typename T>
	static void assertArrayContainsValueAt(const JsonNode& arrayNode, unsigned index, T value) {
		const auto& array = readNodeAsArray(arrayNode);
		ASSERT_EQ(readAs<T>(*array[index]), value);
	}

	// Parameterized tests.

	static void test_deserializeJson_shouldCreateObjectWithRightSize(const std::string& json, size_t size) {
		const JsonObject jsonObj(json);
		ASSERT_EQ(jsonObj.size(), size);
	}

	template <typename T>
	static void test_deserializeJson_shouldBePossibleToReadRawValue(const std::string& key, T value) {
		const auto json = createJsonWithRawData<T>(key, value);
		const JsonObject jsonObj(json);
		ASSERT_EQ(readNodeAsRawValue<T>(*jsonObj[key]), value);
	}

	template <typename T>
	static void test_deserializeJson_shouldBePossibleToReadArray(const std::string& key, T value1, T value2) {
		const auto json = createJsonWithArray<T>(key, value1, value2);

		const JsonObject jsonObj(json);

		assertArrayContainsValueAt<T>(*jsonObj[key], 0, value1);
		assertArrayContainsValueAt<T>(*jsonObj[key], 1, value2);
	}

	template <typename T>
	static void test_deserializeJson_shouldBePossibleToReadDataFromNestedObject(
		const std::string& key1, const std::string& key2, T value) {

		const auto json = createJsonWithObject<T>(key1, key2, value);
		const JsonObject jsonObj(json);

		const auto& obj = readNodeAsObject(*jsonObj[key1]);
		ASSERT_EQ(readNodeAsRawValue<T>(*obj.at(key2)), value);
	}

	// Test methods.

	TEST(JsonDeserialization, WhenWeDeserializeEmptyJsonThenWeGetMalformedObject) {
		const std::string emptyJson;

		const JsonObject jsonObj(emptyJson);

		ASSERT_FALSE(jsonObj.isWellFormed());
	}

	TEST(JsonDeserialization, WhenWeDeserializeIncorrectJsonThenWeGetMalformedObject) {
		const std::string incorrectJson = "{{}";

		const JsonObject jsonObj(incorrectJson);

		ASSERT_FALSE(jsonObj.isWellFormed());
	}

	TEST(JsonDeserialization, WhenWeDeserializeCorrectJsonThenWeGetWellFormedObject) {
		const std::string correctJson = "{}";

		const JsonObject jsonObj(correctJson);

		ASSERT_TRUE(jsonObj.isWellFormed());
	}

	TEST(JsonDeserialization, WhenWeDeserializeJsonWithRawDataThenSizeIsCorrect) {
		test_deserializeJson_shouldCreateObjectWithRightSize("", 0);
		test_deserializeJson_shouldCreateObjectWithRightSize("{}", 0);
		test_deserializeJson_shouldCreateObjectWithRightSize(jsonOneKey, 1);
		test_deserializeJson_shouldCreateObjectWithRightSize(jsonThreeKeys, 3);
	}

	TEST(JsonDeserialization, WhenWeTryToAccessNonExistentElementThenWeGetNullPointer) {
		const JsonObject jsonObj(jsonOneKey);

		const auto* jsonNode = jsonObj["Non Existent Key"];

		ASSERT_EQ(jsonNode, nullptr);
	}

	TEST(JsonDeserialization, WhenWeDeserializeJsonWithRawDataThenTypeIsCorrect) {
		const auto json = createJsonWithRawData(testKey1);

		const JsonObject jsonObj(json);

		ASSERT_EQ(jsonObj[testKey1]->getType(), JsonNodeType::RawValue);
	}

	TEST(JsonDeserialization, WhenWeDeserializeJsonWithRawDataThenWeCanReadTheData) {
		test_deserializeJson_shouldBePossibleToReadRawValue<bool>(testKey1, boolTestValue1);
		test_deserializeJson_shouldBePossibleToReadRawValue<int>(testKey1, intTestValue1);
		test_deserializeJson_shouldBePossibleToReadRawValue<float>(testKey1, floatTestValue1);
		test_deserializeJson_shouldBePossibleToReadRawValue<std::string>(testKey1, stringTestValue1);
	}

	TEST(JsonDeserialization, WhenWeDeserializeJsonWithArrayThenTypeIsCorrect) {
		const auto json = createJsonWithArray(testKey1);

		const JsonObject jsonObj(json);

		ASSERT_EQ(jsonObj[testKey1]->getType(), JsonNodeType::Array);
	}

	TEST(JsonDeserialization, WhenWeDeserializeJsonWithEmptyArrayThenWeGetArrayWithSizeZero) {
		const auto json = createJsonWithEmptyArray(testKey1);

		const JsonObject jsonObj(json);

		const auto& array = readNodeAsArray(*jsonObj[testKey1]);
		ASSERT_EQ(array.size(), 0);
	}

	TEST(JsonDeserialization, WhenWeDeserializeJsonWithArrayThenWeCanReadTheData) {
		test_deserializeJson_shouldBePossibleToReadArray<bool>(testKey1, boolTestValue1, boolTestValue2);
		test_deserializeJson_shouldBePossibleToReadArray<int>(testKey1, intTestValue1, intTestValue2);
		test_deserializeJson_shouldBePossibleToReadArray<float>(testKey1, floatTestValue1, floatTestValue2);
		test_deserializeJson_shouldBePossibleToReadArray<std::string>(testKey1, stringTestValue1, stringTestValue2);
	}

	TEST(JsonDeserialization, WhenWeDeserializeJsonWithNestedObjectThenTypeIsCorrect) {
		const auto json = createJsonWithObject(testKey1);

		const JsonObject jsonObj(json);

		ASSERT_EQ(jsonObj[testKey1]->getType(), JsonNodeType::Object);
	}

	TEST(JsonDeserialization, WhenWeDeserializeJsonWithNestedObjectWithRawDataThenWeCanReadTheData) {
		test_deserializeJson_shouldBePossibleToReadDataFromNestedObject<bool>(testKey1, testKey2, boolTestValue1);
		test_deserializeJson_shouldBePossibleToReadDataFromNestedObject<int>(testKey1, testKey2, intTestValue1);
		test_deserializeJson_shouldBePossibleToReadDataFromNestedObject<float>(testKey1, testKey2, floatTestValue1);
		test_deserializeJson_shouldBePossibleToReadDataFromNestedObject<std::string>(testKey1, testKey2, stringTestValue1);
	}

	TEST(JsonDeserialization, WhenWeDeserializeJsonWithNestingOfDifferentTypesThenWeCanReadTheData) {

		const std::string jsonWithNesting = createJsonWithNesting(testKey1, testKey2, testKey3, intTestValue1);

		const JsonObject jsonObj(jsonWithNesting);

		const JsonNode& node1 = *jsonObj[testKey1];
		const auto& map1 = readNodeAsObject(node1);
		const JsonNode& node2 = *map1.at(testKey2);
		const auto& map2 = readNodeAsObject(node2);
		const JsonNode& node3 = *map2.at(testKey3);
		const auto& array = readNodeAsArray(node3);

		ASSERT_EQ(readNodeAsRawValue<int>(*array[0]), intTestValue1);
	}
}
