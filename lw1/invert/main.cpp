#include "libmatrix.cpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

const std::string HELP_IDENTIFIER = "-h";

struct Args
{
	matrix given_matrix;
};

matrix ReadMatrix(std::istream& in)
{
	matrix m;
	size_t row = 0;

	for (std::string line; getline(in, line); row++)
	{
		std::istringstream ss(line);
		size_t col = 0;

		if (row >= 3)
		{
			throw std::invalid_argument("Invalid matrix format");
		}

		for (double n; ss >> n; col++)
		{
			if (col >= 3)
			{
				throw std::invalid_argument("Invalid matrix format");
			}

			m[row][col] = n;
		}

		if (!ss.eof() && col != 3)
		{
			throw std::invalid_argument("Invalid matrix");
		}
		if (col < 2)
		{
			throw std::invalid_argument("Invalid matrix format");
		}
	}

	if (row < 2)
	{
		throw std::invalid_argument("Invalid matrix format");
	}
	return m;
}

void ParseArgs(Args& args, const int argc, char* argv[])
{
	if (argc == 1)
	{
		args.given_matrix = ReadMatrix(std::cin);
		return;
	}

	const std::string filename = argv[1];
	std::ifstream in(filename);
	if (!in.is_open())
	{
		throw std::invalid_argument("Cannot open input file: " + filename);
	}
	args.given_matrix = ReadMatrix(in);

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

	try
	{
		Args args{};
		ParseArgs(args, argc, argv);
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
