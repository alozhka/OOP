#include <array>
#include <iomanip>
#include <ostream>

using matrix = std::array<std::array<double, 3>, 3>;
using minor_matrix = std::array<std::array<double, 2>, 2>;

double Determinant(const matrix& m)
{
	return m[0][0] * (m[1][1] * m[2][2] - m[2][1] * m[1][2])
		- m[0][1] * (m[1][0] * m[2][2] - m[2][0] * m[1][2])
		+ m[0][2] * (m[1][0] * m[2][1] - m[2][0] * m[1][1]);
}

double Determinant(const minor_matrix& m)
{
	return m[0][0] * m[1][1] - m[1][0] * m[0][1];
}

minor_matrix MinorMatrix(const matrix& m, const size_t row, const size_t col)
{
	minor_matrix result;

	for (size_t r = 0, i = 0; i < 3; i++)
	{
		if (i == row)
		{
			continue;
		}

		for (size_t c = 0, j = 0; j < 3; j++)
		{
			if (j == col)
			{
				continue;
			}

			result[r][c] = m[i][j];
			c++;
		}
		r++;
	}

	return result;
}

/**
 * Вычисляет матрицу алгебраических дополнений
 */
matrix CofactorMatrix(const matrix& m)
{
	matrix result;

	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			const minor_matrix minor = MinorMatrix(m, i, j);
			const double determinant = Determinant(minor);

			result[i][j] = ((i + j) % 2 == 0 ? 1 : -1) * determinant;
		}
	}

	return result;
}

matrix TransposeMatrix(const matrix& m)
{
	matrix result;

	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			result[j][i] = m[i][j];
		}
	}

	return result;
}

matrix DivideMatrix(const matrix& m, const double divider)
{
	matrix result;

	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			result[i][j] = m[i][j] / divider;
		}
	}

	return result;
}

matrix InvertMatrix(const matrix& matrix)
{
	const double determinant = Determinant(matrix);
	if (determinant == 0)
	{
		throw std::invalid_argument("Not-invertible");
	}

	const ::matrix cofactorMatrix = CofactorMatrix(matrix);
	const ::matrix adjMatrix = TransposeMatrix(cofactorMatrix);

	return DivideMatrix(adjMatrix, determinant);
}

void PrintMatrix(std::ostream& out, const matrix& m)
{
	out << std::fixed << std::setprecision(3);
	for (const std::array<double, 3>& row : m)
	{
		for (const double cell : row)
		{
			out << cell << "\t";
		}
		out << std::endl;
	}
}