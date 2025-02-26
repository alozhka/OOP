#include "libmatrix.cpp"
#include <fstream>
#include <iostream>
#include <sstream>

const std::string HELP_IDENTIFIER = "-h";

struct Args
{
	matrix given_matrix;
};

bool IsNumber(const std::string& str)
{
	for (char const& c : str)
	{
		if (!isdigit(c) && c != '.' && c != '-')
		{
			return false;
		}
	}
	return true;
}

matrix ReadMatrix(std::istream& in)
{
	std::vector<std::vector<double>> m;
	std::string line;

	while (getline(in, line))
	{
		std::istringstream ss(line);
		std::string token;
		std::vector<double> row;

		while (ss >> token)
		{
			if (!IsNumber(token))
			{
				throw std::invalid_argument("Invalid matrix");
			}
			row.push_back(std::stod(token));
		}

		m.push_back(row);
	}

	if (m.size() != 3)
	{
		throw std::invalid_argument("Invalid matrix format");
	}
	for (const std::vector<double>& row : m)
	{
		if (row.size() != 3)
		{
			throw std::invalid_argument("Invalid matrix format");
		}
	}

	return matrix{ { { m[0][0], m[0][1], m[0][2] }, { m[1][0], m[1][1], m[1][2] }, { m[2][0], m[2][1], m[2][2] } } };
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
