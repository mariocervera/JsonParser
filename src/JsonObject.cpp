#include "JsonObject.hpp"

static std::string removeExtraCommaFrom(const std::string& s) {
  return s.substr(0, s.size() - 2);
}

namespace EWOS::Infrastructure::JSONParser {

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
    return "";
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
