#ifndef JSONNODE_H
#define JSONNODE_H

#include <string>

namespace JSONParser {

  enum class JsonNodeType {
    RawValue,
    Array,
    Object
  };

  /// A node of a JSON data structure. JSON nodes can be raw values, arrays, or objects.
  class JsonNode {
  protected:
    explicit JsonNode(const JsonNodeType type)
      : type(type) {
    }

  public:
    JsonNodeType getType() const { return type; }

    virtual std::string toJsonString() const = 0;

  private:
    JsonNodeType type;
  };
}
#endif
