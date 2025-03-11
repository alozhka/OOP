#include "Dictionary.h"

#include <algorithm>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>

std::string ToLower(const std::string& s)
{
	std::string result;
	result.reserve(s.size());

	std::ranges::transform(s, std::back_inserter(result), tolower);

	return result;
}

Dictionary LoadDictionary(std::istream& stream)
{
	Dictionary d;
	std::string line, key, value;
	while (std::getline(stream, line))
	{
		std::istringstream iss(line);

		if (std::getline(iss, key, ':'))
		{
			std::set<std::string> translations;
			while (std::getline(iss, value, ','))
			{
				translations.insert(value);
			}

			d[key] = translations;
			for (const std::string& translation : translations)
			{
				d[translation].insert(key);
			}
		}
	}

	return d;
}

Dictionary LoadDictionary(const std::string& filename)
{
	std::ifstream stream(filename);
	if (!stream.is_open())
	{
		throw std::invalid_argument("Input file not found");
	}
	Dictionary d = LoadDictionary(stream);
	stream.close();
	return d;
}

void AddTranslation(const Dictionary& dictionary, std::string key)
{
	throw std::runtime_error("Not Implemented");
}

void PrintTranslation(std::ostream& output, const Dictionary& dictionary, std::string key)
{
	auto translations = dictionary.equal_range(key);
}
