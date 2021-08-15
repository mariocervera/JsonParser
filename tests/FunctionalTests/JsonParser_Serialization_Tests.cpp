#include "JsonParser_Common_Fixtures.hpp"
#include "JsonParser.hpp"
#include "JsonParser_Fixtures.hpp"
#include <fstream>

namespace FunctionalTests::JSONParser {

  // Helper functions.

  static std::string getFileAsString(const std::string& path) {
    const std::ifstream stream(path);
    std::stringstream buffer;
    buffer << stream.rdbuf();

    return buffer.str();
  }

  // Custom assertions.

  static void assertFilesAreEqual(const std::string& path1, const std::string& path2) {
    const auto fileContents1 = getFileAsString(path1);
    const auto fileContents2 = getFileAsString(path2);

    ASSERT_EQ(fileContents1, fileContents2);
  }

  // Tests.

  TEST_F(GivenJsonSerializer, WhenWeSerializeJsonObjectThenFileIsCreatedCorrectly) {

    const auto jsonObject = createJsonObject();

    createJsonFileFrom(*jsonObject, actualJsonFilePath);

    assertFilesAreEqual(expectedJsonFilePath, actualJsonFilePath);
  }
}
