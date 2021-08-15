#ifndef JSONTRAVERSALALGORITHM_H
#define JSONTRAVERSALALGORITHM_H

#include "JsonObject.hpp"
#include "JsonArray.hpp"
#include <nlohmann/json.hpp>

namespace EWOS::Infrastructure::JSONParser {

  inline void addJsonRawValueToMap(std::unordered_map<std::string, std::unique_ptr<JsonNode>>& objectMap,
                                   const std::string& key, nlohmann::json& jsonRawValue) {

    objectMap[key] = std::make_unique<JsonRawValue>(jsonRawValue);
  }

  inline void addJsonRawValueToArray(JsonArray& array, nlohmann::json& jsonRawValue) {
    std::string value = jsonRawValue.is_string() ? jsonRawValue : jsonRawValue.dump();
    auto node = std::make_unique<JsonRawValue>(value);
    array.add(std::move(node));
  }

  inline void addJsonArrayToMap(std::unordered_map<std::string, std::unique_ptr<JsonNode>>& objectMap,
                                const std::string& key, nlohmann::json& jsonArray) {

    auto array = std::make_unique<JsonArray>();
    for (auto& rawValue : jsonArray)
      addJsonRawValueToArray(*array, rawValue);
    objectMap[key] = std::move(array);
  }

  void addJsonObjectToMap(std::unordered_map<std::string, std::unique_ptr<JsonNode>>& objectMap,
                          nlohmann::json& jsonObject);

  inline void addJsonObjectToMap(std::unordered_map<std::string, std::unique_ptr<JsonNode>>& objectMap,
                                 const std::string& key, nlohmann::json& jsonObject) {

    auto obj = std::make_unique<JsonObject>();
    addJsonObjectToMap(obj->getObjectMap(), jsonObject);
    objectMap[key] = std::move(obj);
  }

  inline void addJsonObjectToMap(std::unordered_map<std::string, std::unique_ptr<JsonNode>>& objectMap,
                                 nlohmann::json& jsonObject) {

    for (auto& [key, value] : jsonObject.items()) {
      if (value.is_array())
        addJsonArrayToMap(objectMap, key, value);
      else if (value.is_object())
        addJsonObjectToMap(objectMap, key, value);
      else
        addJsonRawValueToMap(objectMap, key, value);
    }
  }
}
#endif
