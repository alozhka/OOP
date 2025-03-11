#pragma once

#include <set>
#include <string>
#include <unordered_map>

using Dictionary = std::unordered_map<std::string, std::set<std::string>>;

Dictionary LoadDictionary(std::string filename);

void AddTranslation(const Dictionary& dictionary, std::string key);

void PrintTranslation(std::ostream& output, const Dictionary& dictionary, std::string key);

void SaveDictionary(const Dictionary& dictionary, std::string filename);
