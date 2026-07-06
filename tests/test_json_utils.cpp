#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <foo/json_utils.h>

TEST_CASE("createSampleJson creates valid JSON", "[json]") {
  auto j = createSampleJson();

  REQUIRE(j.contains("name"));
  REQUIRE(j["name"] == "Example");
  REQUIRE(j["version"] == 1.0);
  REQUIRE(j["active"] == true);
  REQUIRE(j["tags"].is_array());
  REQUIRE(j["tags"].size() == 3);
}

TEST_CASE("mergeJson combines two JSON objects", "[json]") {
  nlohmann::json base = {{"a", 1}, {"b", 2}};
  nlohmann::json overlay = {{"b", 3}, {"c", 4}};

  auto result = mergeJson(base, overlay);

  REQUIRE(result["a"] == 1);
  REQUIRE(result["b"] == 3);
  REQUIRE(result["c"] == 4);
}

TEST_CASE("getValue retrieves string values", "[json]") {
  nlohmann::json j = {{"key1", "value1"}, {"key2", 123}};

  SECTION("existing string key") { REQUIRE(getValue(j, "key1") == "value1"); }

  SECTION("non-existent key returns default") {
    REQUIRE(getValue(j, "missing", "default") == "default");
  }

  SECTION("non-string value returns default") {
    REQUIRE(getValue(j, "key2", "default") == "default");
  }
}

TEST_CASE("countArrayElements counts array size", "[json]") {
  SECTION("valid array") {
    nlohmann::json arr = nlohmann::json::array({1, 2, 3, 4, 5});
    REQUIRE(countArrayElements(arr) == 5);
  }

  SECTION("empty array") {
    nlohmann::json arr = nlohmann::json::array();
    REQUIRE(countArrayElements(arr) == 0);
  }

  SECTION("non-array returns 0") {
    nlohmann::json obj = {{"key", "value"}};
    REQUIRE(countArrayElements(obj) == 0);
  }
}
