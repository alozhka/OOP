#include "lib/converter.cpp"
#include <iostream>

struct Args
{
	int sourceRadix = 0;
	int destinationRadix = 0;
	std::string str;
};

int DigitStringToInt(const std::string& s)
{
	if (!std::all_of(s.begin(), s.end(), isdigit))
	{
		throw std::invalid_argument("Base must be decimal number");
	}

	return std::atoi(s.c_str());
}

void ParseArgs(const int argc, char* argv[], Args& args)
{
	if (argc < 4)
	{
		throw std::invalid_argument("Less arguments provided."
									"Usage: radix.exe <source notation> <destination notation> <value>");
	}
	args.sourceRadix = DigitStringToInt(argv[1]);
	args.destinationRadix = DigitStringToInt(argv[2]);
	args.str = argv[3];
}

int main(const int argc, char* argv[])
{
	try
	{
		Args args;
		ParseArgs(argc, argv, args);
		const int number = StringToInt(args.str, args.sourceRadix);
		std::cout << IntToString(number, args.destinationRadix) << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}
	return 0;
}
