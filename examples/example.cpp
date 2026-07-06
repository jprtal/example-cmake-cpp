#include <foo/json_utils.h>
#include <iostream>

int main() {
  // Create sample JSON
  auto json1 = createSampleJson();
  std::cout << "Sample JSON:\n" << json1.dump(2) << "\n\n";

  // Access values
  std::string name = getValue(json1, "name");
  std::cout << "Name: " << name << "\n";

  // Count array elements
  size_t tagCount = countArrayElements(json1["tags"]);
  std::cout << "Number of tags: " << tagCount << "\n\n";

  // Merge JSON objects
  nlohmann::json json2;
  json2["name"] = "Updated";
  json2["newKey"] = "newValue";

  auto merged = mergeJson(json1, json2);
  std::cout << "Merged JSON:\n" << merged.dump(2) << "\n";

  return 0;
}
