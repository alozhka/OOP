#include <fstream>
#include <iostream>

constexpr ushort ARGS_AMOUNT = 5;
const std::string HELP_IDENTIFIER = "-h";

struct Input
{
	std::string inFile, outFile, searchString, replaceString;
};

void ParseInputFromCommandLine(const char* argv[], Input& input)
{
	input.inFile = argv[1];
	input.outFile = argv[2];
	input.searchString = argv[3];
	input.replaceString = argv[4];
}

bool TryParseInputFromStdIn(Input& input)
{
	if (!std::getline(std::cin, input.searchString))
	{
		return false;
	}
	if (!std::getline(std::cin, input.replaceString))
	{
		return false;
	}

	return !std::cin.eof();
}

std::string CopyStringWithReplacement(const std::string& line, const std::string& searchStr, const std::string& replaceStr)
{
	size_t pos = 0;
	std::string result;

	if (searchStr.empty())
	{
		return line;
	}

	while (pos < line.size())
	{
		const size_t foundPos = line.find(searchStr, pos);
		if (foundPos < line.size())
		{
			result.append(line, pos, foundPos - pos);
			result.append(replaceStr);
			pos = foundPos + searchStr.size();
		}
		else
		{
			result.append(line, pos);
			pos = std::string::npos;
		}
	}
	return result;
}

void CopyStreamWithReplacement(
	std::istream& input, std::ostream& output,
	const std::string& searchStr, const std::string& replaceStr)
{
	std::string line;
	while (getline(input, line))
	{
		std::string replacedLine = CopyStringWithReplacement(line, searchStr, replaceStr);
		output << replacedLine << std::endl;
	}
}

bool TryCopyFileWithReplacement(
	const std::string& inFilename, const std::string& outFilename,
	const std::string& searchStr, const std::string& replaceStr)
{
	std::ifstream inFile(inFilename);
	if (!inFile.is_open())
	{
		return false;
	}
	std::ofstream outFile(outFilename);
	if (!outFile.is_open())
	{
		return false;
	}

	CopyStreamWithReplacement(inFile, outFile, searchStr, replaceStr);

	inFile.close();
	outFile.close();
	return true;
}

void PrintHelp()
{
	std::cout << "Usage: replace <input_file> <output_file> <search_string> <replace_string>\n";
}

void ReplaceFromStdin()
{
	Input input;

	if (!TryParseInputFromStdIn(input))
	{
		std::cout << "ERROR\n";
		return;
	}
	CopyStreamWithReplacement(std::cin, std::cout, input.searchString, input.replaceString);
}

bool TryReplaceFromFile(const char* argv[])
{
	Input input;

	ParseInputFromCommandLine(argv, input);
	if (!TryCopyFileWithReplacement(input.inFile, input.outFile, input.searchString, input.replaceString))
	{
		std::cout << "ERROR\n";
		return false;
	}

	return true;
}

int main(const int argc, const char* argv[])
{
	setlocale(LC_ALL, "rus");

	if (argc == 1)
	{
		ReplaceFromStdin();
		return 0;
	}

	if (argv[1] == HELP_IDENTIFIER)
	{
		PrintHelp();
		return 0;
	}

	if (argc < ARGS_AMOUNT)
	{
		std::cout << "ERROR\n";
		return 1;
	}

	return !TryReplaceFromFile(argv);
}
