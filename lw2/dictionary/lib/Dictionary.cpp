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
		}
	}

	return d;
}

Dictionary LoadDictionary(const std::string& filename)
{
	std::ifstream stream(filename);
	if (!stream.is_open())
	{
		throw std::invalid_argument("Не удалось открыть входной файл");
	}
	Dictionary d = LoadDictionary(stream);
	stream.close();
	return d;
}

void AddTranslation(Dictionary& dictionary, const std::string& word, const std::string& translation)
{
	dictionary[ToLower(word)].insert(translation);
}

bool TryPrintTranslation(std::ostream& output, const Dictionary& dictionary, const std::string& word)
{
	const std::string lowerInput = ToLower(word);

	if (!dictionary.contains(lowerInput))
	{
		return false;
	}

	bool first = true;
	for (const auto& translation : dictionary.at(lowerInput))
	{
		if (!first)
			output << ", ";
		output << translation;
		first = false;
	}
	output << std::endl;

	return true;
}

void SaveDictionary(std::ostream& out, const Dictionary& dictionary)
{
	for (const auto& [key, translations] : dictionary)
	{
		out << key << ":";
		bool first = true;
		for (const auto& word : translations)
		{
			if (!first)
				out << ",";
			out << word;
			first = false;
		}
		out << std::endl;
	}
}

void SaveDictionary(const std::string& filename, const Dictionary& dictionary)
{
	std::ofstream file(filename);
	for (const auto& [key, translations] : dictionary)
	{
		file << key << ":";
		bool first = true;
		for (const auto& word : translations)
		{
			if (!first)
				file << ",";
			file << word;
			first = false;
		}
		file << "\n";
	}
}
