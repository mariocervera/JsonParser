#include "JsonArray.hpp"

static std::string removeExtraCommaFrom(const std::string& s) {
  return s.substr(0, s.size() - 2);
}

namespace JSONParser {

  std::string JsonArray::toJsonString() const {
    return "[" + getArrayContentsAsString() + "]";
  }

  std::string JsonArray::getArrayContentsAsString() const {
    if (array.empty())
      return "";

    std::string result;
    for (const auto& element : array)
      result += element->toJsonString() + ", ";

    return removeExtraCommaFrom(result);
  }
}
