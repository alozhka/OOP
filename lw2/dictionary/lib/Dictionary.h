#pragma once

#include <set>
#include <string>
#include <unordered_map>

using Dictionary = std::unordered_map<std::string, std::set<std::string>>;

Dictionary LoadDictionary(const std::string& filename);

void AddTranslation(Dictionary& dictionary, const std::string& word, const std::string& translation);

bool TryPrintTranslation(std::ostream& output, const Dictionary& dictionary, const std::string& word);

void SaveDictionary(const std::string& filename, const Dictionary& dictionary);
