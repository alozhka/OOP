#include "Dictionary.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

constexpr char DASH = '-';

std::string ToLower(const std::string& s)
{
	std::string result;
	result.reserve(s.size());

	std::ranges::transform(s, std::back_inserter(result), tolower);

	return result;
}

bool IsEnglishString(const std::string& s)
{
	return std::ranges::all_of(s.begin(), s.end(), [](unsigned char c) { return std::isalpha(c) || std::isspace(c) || c == DASH; });
}

bool IsRussianString(const std::string& s)
{
	if (s.empty())
	{
		return false;
	}
	std::string russian;

	for (const auto ch : s)
	{
		std::cout << ch;
		russian += ch;
	}

	return true;
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

	const auto translationsIterator = dictionary.find(lowerInput);
	if (translationsIterator == dictionary.end())
	{
		return false;
	}

	bool first = true;
	for (const std::string& translation : translationsIterator->second)
	{
		if (!first)
		{
			output << ", ";
		}
		output << translation;
		first = false;
	}
	output << std::endl;

	return true;
}

std::string ReceiveTranslation(const std::string& word)
{
	std::cout << "Неизвестное слово \"" << word << "\". Введите перевод или пустую строку для отказа.\n";
	std::cout << ">";

	std::string translation;
	getline(std::cin, translation);

	return translation;
}

void ProcessDictionaryInput(Dictionary& dictionary, bool& dictModified)
{
	std::string input;
	while (true)
	{
		std::cout << ">";
		getline(std::cin, input);

		if (input == "...")
			break;

		if (!IsEnglishString(input))
		{
			std::cout << "Слово должно быть только на английском\n";
			continue;
		}

		const bool wordExists = TryPrintTranslation(std::cout, dictionary, input);
		if (!wordExists)
		{
			std::string translation = ReceiveTranslation(input);

			if (!translation.empty())
			{
				if (!IsRussianString(input))
				{
					std::cout << "Перевод должен быть только на русском\n";
					continue;
				}

				AddTranslation(dictionary, input, translation);
				std::cout << "Слово \"" << input << "\" сохранено в словаре как \"" << translation << "\".\n";
				dictModified = true;
			}
			else
			{
				std::cout << "Слово \"" << input << "\" проигнорировано.\n";
			}
		}
	}
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
