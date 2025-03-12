#include "lib/Dictionary.h"

#include <iostream>

struct Args
{
	std::string dictFilename;
};

void ParseArgs(Args& args, const char* argv[])
{
	args.dictFilename = argv[1];
}

void ProcessInput(Dictionary& dictionary, bool& modified)
{
	std::string input;
	while (true)
	{
		std::cout << ">";
		getline(std::cin, input);

		if (input == "...")
			break;

		const bool wordExists = TryPrintTranslation(std::cout, dictionary, input);
		if (!wordExists)
		{
			std::cout << "Неизвестное слово \"" << input << "\". Введите перевод или пустую строку для отказа.\n";
			std::cout << ">";
			std::string translation;
			getline(std::cin, translation);

			if (!translation.empty())
			{
				AddTranslation(dictionary, input, translation);
				std::cout << "Слово \"" << input << "\" сохранено в словаре как \"" << translation << "\".\n";
				modified = true;
			}
			else
			{
				std::cout << "Слово \"" << input << "\" проигнорировано.\n";
			}
		}
	}
}

void PromptSaveAndExit(const std::string& filename, const Dictionary& dict, const bool modified)
{
	if (modified)
	{
		std::cout << "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом.\n>";
		std::string choice;
		getline(std::cin, choice);
		if (choice == "Y" || choice == "y")
		{
			SaveDictionary(filename, dict);
			std::cout << "Изменения сохранены. До свидания.\n";
		}
	}
	else
	{
		std::cout << "До свидания.\n";
	}
}

int main(const int argc, const char* argv[])
{
	if (argc < 2)
	{
		std::cout << "Путь до словаря не указан\n";
		return 1;
	}

	try
	{
		Args args;
		ParseArgs(args, argv);
		Dictionary dictionary = LoadDictionary(args.dictFilename);

		bool modified = false;
		ProcessInput(dictionary, modified);
		PromptSaveAndExit(args.dictFilename, dictionary, modified);
		return 0;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}
}
