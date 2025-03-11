#pragma once
#include <map>
#include <string>

using Dictionary = std::multimap<std::string, std::string>;

Dictionary LoadDictionary(std::string filename);

void AddTranslation(const Dictionary& dictionary, std::string key);

void FindTranslation(const Dictionary& dictionary, std::string key);

void SaveDictionary(const Dictionary& dictionary, std::string filename);
