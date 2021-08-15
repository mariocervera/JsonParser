#ifndef JSONDATAREADER_H
#define JSONDATAREADER_H

#include "JsonObject.hpp"
#include "JsonArray.hpp"
#include <sstream>
#include <vector>

namespace JSONParser {

  template <typename T>
  T readAs(const JsonRawValue& rawValue) {
    std::stringstream stream;
    stream << rawValue.getValue();
    T value;
    stream >> value;
    return value;
  }

  template <>
  inline std::string readAs(const JsonRawValue& rawValue) {
    return rawValue.getValue();
  }

  template <typename T>
  T readNodeAsRawValue(const JsonNode& node) {
    const auto* rawValue = static_cast<const JsonRawValue*>(&node);
    return readAs<T>(*rawValue);
  }

  inline const std::vector<std::unique_ptr<JsonRawValue>>& readNodeAsArray(const JsonNode& node) {
    const auto* array = static_cast<const JsonArray*>(&node);
    return array->getArray();
  }

  inline const std::unordered_map<std::string, std::unique_ptr<JsonNode>>& readNodeAsObject(const JsonNode& node) {
    const auto* object = static_cast<const JsonObject*>(&node);
    return object->getObjectMap();
  }
}
#endif
