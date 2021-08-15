#ifndef JSONPARSER_FUNCTIONALTESTS_FIXTURES_H
#define JSONPARSER_FUNCTIONALTESTS_FIXTURES_H

#include "JsonParser_Common_Fixtures.hpp"
#include <filesystem>
#include <gtest/gtest.h>
#include <memory>
#include <string>

namespace FunctionalTests::JSONParser {

  using namespace Tests_Common::JSONParser;

  static const std::string jsonFilePath = "../../tests/test_files/jsonToDeserialize.json";
  static const std::string actualJsonFilePath = "../../tests/test_files/actualSerialization.json";
  static const std::string expectedJsonFilePath = "../../tests/test_files/expectedSerialization.json";

  // Creation methods.

  static std::unique_ptr<JsonObject> createJsonObject() {
    auto rootObject = std::make_unique<JsonObject>();

    addRawValueToObject(*rootObject, "name", "John Doe");
    addRawValueToObject(*rootObject, "age", "30");

    auto courseObject = std::make_unique<JsonObject>();

    addRawValueToObject(*courseObject, "teacher", "Jane Doe");
    addArrayToObject(*courseObject, "topics", {
                       "Introduction to Programming", "Algorithms and Data Structures", "Agile Development"
                     });

    auto universityObject = std::make_unique<JsonObject>();

    addRawValueToObject(*universityObject, "name", "Universitat Politecnica de Valencia");
    addArrayToObject(*universityObject, "campus", {"Valencia", "Gandia", "Alcoy"});

    addObjectToObject(*courseObject, "university", std::move(universityObject));
    addObjectToObject(*rootObject, "course", std::move(courseObject));

    return rootObject;
  }

  // Test fixture classes.

  class GivenJsonSerializer : public ::testing::Test {
  protected:
    void TearDown() override {
      std::filesystem::remove(actualJsonFilePath);
    }
  };
}

#endif
