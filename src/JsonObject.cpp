#include "JsonObject.hpp"
#include "JsonArray.hpp"
#include "JsonTraversalAlgorithm.hpp"
#include <nlohmann/json.hpp>

static std::string removeExtraCommaFrom(const std::string& s) {
  return s.substr(0, s.size() - 2);
}

namespace JSONParser {

  using namespace nlohmann;

  static json parse(const std::string& jsonObject) {
    const auto allowExceptions = false;
    const json::parser_callback_t callback = nullptr;
    return json::parse(jsonObject, callback, allowExceptions);
  }

  JsonObject::JsonObject(const std::string& jsonObject)
    : JsonNode(JsonNodeType::Object) {

    auto parsedJsonObject = parse(jsonObject);

    if (!parsedJsonObject.is_discarded())
      addJsonObjectToMap(objectMap, parsedJsonObject);
    else
      parseError = true;
  }

  const JsonNode* JsonObject::operator[](const std::string& key) const {
    if (objectMap.find(key) != objectMap.end())
      return objectMap.at(key).get();
    return nullptr;
  }

  std::string JsonObject::toJsonString() const {
    return "{" + getObjectContentsAsString() + "}";
  }

  std::string JsonObject::toFormattedJsonString() const {
    const unsigned spacesOfIndent = 3;
    return json::parse(toJsonString()).dump(spacesOfIndent);
  }

  std::string JsonObject::getObjectContentsAsString() const {
    if (objectMap.empty())
      return "";

    std::string result;
    for (const auto& pair : objectMap)
      result += ("\"" + pair.first + "\" : " + pair.second->toJsonString() + ",\n");

    return removeExtraCommaFrom(result);
  }
}
