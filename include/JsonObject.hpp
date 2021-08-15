#ifndef JSONOBJECT_H
#define JSONOBJECT_H

#include "JsonNode.hpp"
#include <memory>
#include <string>
#include <unordered_map>

namespace JSONParser {

  /// An object in a JSON data structure. A JSON object contains key-value pairs.
  class JsonObject : public JsonNode {
  public:
    JsonObject()
      : JsonNode(JsonNodeType::Object) {
    }

    explicit JsonObject(const std::string& jsonObject);

    bool isWellFormed() const { return !parseError; }

    size_t size() const { return objectMap.size(); }

    const JsonNode* operator[](const std::string& key) const;

    std::unordered_map<std::string, std::unique_ptr<JsonNode>>& getObjectMap() { return objectMap; }
    const std::unordered_map<std::string, std::unique_ptr<JsonNode>>& getObjectMap() const { return objectMap; }

    std::string toJsonString() const override;

    std::string toFormattedJsonString() const;

  private:
    std::string getObjectContentsAsString() const;

  private:
    std::unordered_map<std::string, std::unique_ptr<JsonNode>> objectMap;
    bool parseError = false;
  };
}
#endif
