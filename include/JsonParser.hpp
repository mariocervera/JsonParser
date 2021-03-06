#ifndef JSONPARSER_H
#define JSONPARSER_H

#include "JsonObject.hpp"
#include <string>

namespace JSONParser {

  JsonObject parseJsonFile(const std::string& path);

  void createJsonFileFrom(const JsonObject& object, const std::string& targetPath);
}
#endif
