#include "lib/LibMatrix.h"
#include <fstream>
#include <iostream>
#include <sstream>

// поправить парсинг (пр. 10a)
const std::string HELP_IDENTIFIER = "-h";

struct Args
{
	std::string input_file;
};

Matrix ReadMatrix(std::istream& in)
{
	Matrix m;
	size_t row = 0;
	std::invalid_argument invalidMatrixFormat("Invalid matrix format");

	for (std::string line; getline(in, line); row++)
	{
		std::istringstream ss(line);
		size_t col = 0;
		if (row >= 3)
		{
			throw invalidMatrixFormat;
		}

		for (double n; ss >> n; col++)
		{
			if (col >= 3)
			{
				throw invalidMatrixFormat;
			}

			m[row][col] = n;
		}

		if (!ss.eof() && col != 3)
		{
			throw std::invalid_argument("Invalid matrix");
		}
		if (col < 2)
		{
			throw invalidMatrixFormat;
		}
	}

	if (row < 2)
	{
		throw invalidMatrixFormat;
	}
	return m;
}

Args ParseArgs(char* argv[])
{
	Args args{};
	args.input_file = argv[1];

	return args;
}

void ReadMatrixFromFile(Matrix& m, const std::string& filename)
{
	std::ifstream in(filename);
	if (!in.is_open())
	{
		throw std::invalid_argument("Cannot open input file: " + filename);
	}
	m = ReadMatrix(in);
	in.close();
}

void PrintHelp()
{
	std::cout << "Usage: invert <input_file>\n";
}

int main(const int argc, char* argv[])
{
	if (argc == 2 && argv[1] == HELP_IDENTIFIER)
	{
		PrintHelp();
		return 0;
	}

	Matrix matrix;
	if (argc == 1)
	{
		matrix = ReadMatrix(std::cin);
	}
	else
	{
		const Args args = ParseArgs(argv);
		ReadMatrixFromFile(matrix, args.input_file);
	}

	try
	{
		const Matrix invertedMatrix = InvertMatrix(matrix);
		PrintMatrix(std::cout, invertedMatrix);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}
	return 0;
}
