#include "libmatrix.cpp"
#include <fstream>
#include <iostream>

struct Args
{
	matrix given_matrix;
};

matrix ReadFromFile(const std::string& filename)
{
	std::ifstream in(filename);
	if (!in.is_open())
	{
		throw std::invalid_argument("Cannot open input file");
	}
	matrix m;

	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			// TODO: проверка на неправильный формат матрицы
			in >> m[i][j];
		}
	}

	return m;
}

matrix ReadMatrixFromStdIn()
{
	throw std::invalid_argument("Not implemented");
}

void ParseArgs(Args& args, const int argc, char* argv[])
{
	if (argc == 0)
	{
		args.given_matrix = ReadMatrixFromStdIn();
		return;
	}

	args.given_matrix = ReadFromFile(argv[1]);
}

void PrintHelp()
{
	std::cout << "Usage: invert <input_file>\n";
}

int main(const int argc, char* argv[])
{
	if (argc == 2)
	{
		PrintHelp();
		return 0;
	}

	try
	{
		Args args;
		ParseArgs(args, argc, argv);
		std::cout << "Parsed" << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}
	return 0;
}
