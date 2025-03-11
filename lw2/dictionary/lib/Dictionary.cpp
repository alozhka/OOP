#include "Dictionary.h"

#include <algorithm>
#include <fstream>
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
	std::string line;
	while (std::getline(stream, line))
	{
		const size_t delimiterIndex = line.find(':');
		if (delimiterIndex == std::string::npos)
		{
			break;
		}

		std::string key = line.substr(0, delimiterIndex);
		std::string value = line.substr(delimiterIndex + 1);

		if (key.empty())
		{
			throw std::invalid_argument("Empty dictionary word");
		}
		if (value.empty())
		{
			throw std::invalid_argument("Empty dictionary translation");
		}

		d.emplace(ToLower(key), ToLower(value));
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
