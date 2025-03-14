#pragma once

#include <set>
#include <string>
#include <unordered_map>

using Dictionary = std::unordered_map<std::string, std::set<std::string>>;

Dictionary LoadDictionary(const std::string& filename);

void ProcessDictionaryInput(Dictionary& dictionary, bool& dictModified);

void SaveDictionary(const std::string& filename, const Dictionary& dictionary);
