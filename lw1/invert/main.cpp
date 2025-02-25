#include "libmatrix.cpp"
#include <fstream>
#include <iostream>

const std::string HELP_IDENTIFIER = "-h";

struct Args
{
	matrix given_matrix;
};

matrix ReadFromFile(const std::string& filename)
{
	std::ifstream in(filename);
	if (!in.is_open())
	{
		throw std::invalid_argument("Cannot open input file: " + filename);
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
	Args args{};

	if (argc == 1)
	{
		try
		{
			args.given_matrix = ReadMatrixFromStdIn();
		}
		catch (const std::exception&)
		{
			std::cout << "ERROR\n";
			return 0;
		}
	}
	else
	{
		if (argv[1] == HELP_IDENTIFIER)
		{
			PrintHelp();
			return 0;
		}
		args.given_matrix = ReadFromFile(argv[1]);
	}

	try
	{
		const matrix invertedMatrix = InvertMatrix(args.given_matrix);
		PrintMatrix(std::cout, invertedMatrix);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}
	return 0;
}
