#ifndef JSONPARSER_COMMON_FIXTURES_H
#define JSONPARSER_COMMON_FIXTURES_H

#include "JsonArray.hpp"
#include "JsonObject.hpp"
#include "JsonRawValue.hpp"
#include <string>

namespace EWOS::Infrastructure::Tests::Common::JSONParser {

  using namespace Infrastructure::JSONParser;

  // Helper functions for fixture creation code (for both functional and unit tests).

  static std::unique_ptr<JsonArray> createJsonArrayfromStdVector(const std::vector<std::string>& array) {
    auto jsonArray = std::make_unique<JsonArray>();
    for (const auto& element : array) {
      auto rawValue = std::make_unique<JsonRawValue>(element);
      jsonArray->add(std::move(rawValue));
    }

    return jsonArray;
  }

  static void addRawValueToObject(JsonObject& jsonObject, const std::string& key, const std::string& value) {
    auto rawValue = std::make_unique<JsonRawValue>(value);
    jsonObject.getObjectMap()[key] = std::move(rawValue);
  }

  static void addArrayToObject(JsonObject& jsonObject, const std::string& key,
                               const std::vector<std::string>& array) {

    auto jsonArray = createJsonArrayfromStdVector(array);
    jsonObject.getObjectMap()[key] = std::move(jsonArray);
  }

  static void addObjectToObject(JsonObject& containerObject, const std::string& key,
                                std::unique_ptr<JsonObject> containedObject) {
    containerObject.getObjectMap()[key] = std::move(containedObject);
  }
}

#endif
