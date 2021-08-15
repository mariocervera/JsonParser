#include "JsonParser.hpp"
#include <fstream>

namespace EWOS::Infrastructure::JSONParser {

  static JsonObject createMalformedJsonObject() {
    return JsonObject("{{}");
  }

  static std::string readContents(std::ifstream& file) {
    std::string contents;
    std::string line;
    while (std::getline(file, line))
      contents += line;
    return contents;
  }

  JsonObject parseJsonFile(const std::string& path) {

    std::ifstream file(path);

    if (!file.is_open())
      return createMalformedJsonObject();

    const auto json = readContents(file);
    return JsonObject(json);
  }

  void createJsonFileFrom(const JsonObject& jsonObject, const std::string& targetPath) {
    std::ofstream file(targetPath);
    file << jsonObject.toFormattedJsonString();
    file.close();
  }
}
