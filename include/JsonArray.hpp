#ifndef JSONARRAY_H
#define JSONARRAY_H

#include "JsonNode.hpp"
#include "JsonRawValue.hpp"
#include <memory>
#include <vector>

namespace JSONParser {

  /// An array in a JSON data structure. Arrays can contain raw values.
  class JsonArray : public JsonNode {
  public:
    explicit JsonArray()
      : JsonNode(JsonNodeType::Array) {
    }

    const std::vector<std::unique_ptr<JsonRawValue>>& getArray() const {
      return array;
    }

    void add(std::unique_ptr<JsonRawValue> node) {
      array.emplace_back(std::move(node));
    }

    std::string toJsonString() const override;

  private:
    std::string getArrayContentsAsString() const;

  private:
    std::vector<std::unique_ptr<JsonRawValue>> array;
  };
}
#endif
