#include "json_utils.h"
#include "foo/version.h"

nlohmann::json createSampleJson() {
  nlohmann::json j;
  j["name"] = "Example";
  j["version"] = FOO_REV_STRING;
  j["active"] = true;
  j["tags"] = nlohmann::json::array({"cpp", "json", "example"});
  j["config"] = {{"timeout", 30}, {"retries", 3}};
  return j;
}

nlohmann::json mergeJson(const nlohmann::json &base,
                         const nlohmann::json &overlay) {
  nlohmann::json result = base;
  for (auto it = overlay.begin(); it != overlay.end(); ++it) {
    result[it.key()] = it.value();
  }

  return result;
}

std::string getValue(const nlohmann::json &j, const std::string &key,
                     const std::string &defaultValue) {
  if (j.contains(key) && j[key].is_string()) {
    return j[key].get<std::string>();
  }

  return defaultValue;
}

size_t countArrayElements(const nlohmann::json &j) {
  if (j.is_array()) {
    return j.size();
  }

  return 0;
}
