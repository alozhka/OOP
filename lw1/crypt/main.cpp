#include <iostream>
#include <string>

struct Args
{
	bool isCrypt = false;
	std::string inFilename, outFilename;
	unsigned short key = 0;
};

void PrintHelp()
{
	std::cout << "Usage: crypt crypt <input file> <output file> <key>\n"
				 "crypt decrypt <input file> <output file> <key>\n";
}

bool IsNumericString(const std::string& s)
{
	for (const char c : s)
	{
		if (!std::isdigit(c) && c != '.' && c != '-')
		{
			return false;
		}
	}
	return true;
}

Args ParseArgs(const char* argv[])
{
	Args args;
	std::string operation = argv[1];

	if (operation == "crypt")
	{
		args.isCrypt = true;
	}
	else if (operation == "decrypt")
	{
		args.isCrypt = false;
	}
	else
	{
		throw std::invalid_argument("Unsupported operation");
	}

	if (!IsNumericString(argv[4]))
	{
		throw std::invalid_argument("Invalid key");
	}

	const int key = std::stoi(argv[4]);
	if (key < 0 || key > 255)
	{
		throw std::out_of_range("Key must be in range [0, 255]");
	}

	args.inFilename = argv[2];
	args.outFilename = argv[3];
	args.key = key;
	return args;
}

int main(const int argc, const char* argv[])
{
	if (argc < 5)
	{
		PrintHelp();
		return 1;
	}

	try
	{
		if (const Args args = ParseArgs(argv); args.isCrypt)
		{
		}
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	return 0;
}
