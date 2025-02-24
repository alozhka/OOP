#include <array>
#include <ostream>

using matrix = std::array<std::array<int, 3>, 3>;

void PrintMatrix(std::ostream& out, const matrix m)
{
	for (const std::array<int, 3>& row : m)
	{
		for (const int cell : row)
		{
			out << cell << "\t";
		}
		out << std::endl;
	}
}