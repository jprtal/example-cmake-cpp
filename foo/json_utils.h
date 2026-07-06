#ifndef FOO_JSON_UTILS_H
#define FOO_JSON_UTILS_H

#include <nlohmann/json.hpp>
#include <string>

/**
 * @file json_utils.h
 * @brief Utility functions for JSON manipulation
 */

/**
 * @brief Creates a sample JSON object with various data types
 * @return Sample JSON object
 */
nlohmann::json createSampleJson();

/**
 * @brief Merges two JSON objects
 * @param base The base JSON object
 * @param overlay The JSON object to merge into base
 * @return Merged JSON object
 */
nlohmann::json mergeJson(const nlohmann::json &base,
                         const nlohmann::json &overlay);

/**
 * @brief Extracts a value from JSON using a key
 * @param j The JSON object to search
 * @param key The key to look for
 * @param defaultValue Default value if key not found
 * @return The value at the key, or defaultValue if not found
 */
std::string getValue(const nlohmann::json &j, const std::string &key,
                     const std::string &defaultValue = "");

/**
 * @brief Counts the number of elements in a JSON array
 * @param j The JSON object (should be an array)
 * @return Number of elements, or 0 if not an array
 */
size_t countArrayElements(const nlohmann::json &j);

#endif // FOO_JSON_UTILS_H
