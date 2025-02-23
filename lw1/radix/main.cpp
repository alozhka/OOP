#include <iostream>
#include "lib/converter.cpp"

struct Args
{
	int sourceRadix = 0;
	int destinationRadix = 0;
	std::string str;
};

void ParseArgs(Args& args)
{
	std::cin >> args.sourceRadix;
	std::cin >> args.destinationRadix;
	std::cin >> args.str;
}

int main()
{
	try
	{
		Args args;
		ParseArgs(args);
		int number = StringToInt(args.str, args.sourceRadix);
		std::cout << IntToString(number, args.destinationRadix) << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}
