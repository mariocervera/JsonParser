#ifndef JSONRAWVALUE_H
#define JSONRAWVALUE_H

#include "JsonNode.hpp"
#include <memory>
#include <string>

namespace EWOS::Infrastructure::JSONParser {

  /// A raw value in a JSON data structure. Raw values are, for example, integers or strings.
  class JsonRawValue : public JsonNode {
  public:
    explicit JsonRawValue(std::string value)
      : JsonNode(JsonNodeType::RawValue), value(std::move(value)) {
    }

    const std::string& getValue() const { return value; }

    std::string toJsonString() const override { return "\"" + getValue() + "\""; }

  private:
    std::string value;
  };
}
#endif
