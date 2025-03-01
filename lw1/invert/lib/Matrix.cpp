#include "LibMatrix.h"
#include <iomanip>

using MinorMatrix = std::array<std::array<double, 2>, 2>;

double Determinant(const Matrix& m)
{
	return m[0][0] * (m[1][1] * m[2][2] - m[2][1] * m[1][2])
		- m[0][1] * (m[1][0] * m[2][2] - m[2][0] * m[1][2])
		+ m[0][2] * (m[1][0] * m[2][1] - m[2][0] * m[1][1]);
}

double Determinant(const MinorMatrix& m)
{
	return m[0][0] * m[1][1] - m[1][0] * m[0][1];
}

/**
 * Находит минор матрицы для указанной ячейки
 */
MinorMatrix FindMinorMatrix(const Matrix& m, const size_t row, const size_t col)
{
	MinorMatrix result;

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
Matrix CofactorMatrix(const Matrix& m)
{
	Matrix result;

	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			const MinorMatrix minor = FindMinorMatrix(m, i, j);
			const double determinant = Determinant(minor);

			result[i][j] = ((i + j) % 2 == 0 ? 1 : -1) * determinant;
		}
	}

	return result;
}

Matrix TransposeMatrix(const Matrix& m)
{
	Matrix result;

	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			result[j][i] = m[i][j];
		}
	}

	return result;
}

Matrix DivideMatrix(const Matrix& m, const double divider)
{
	Matrix result;

	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			result[i][j] = m[i][j] / divider;
		}
	}

	return result;
}

Matrix InvertMatrix(const Matrix& matrix)
{
	const double determinant = Determinant(matrix);
	if (determinant == 0)
	{
		throw std::invalid_argument("Not-invertible");
	}

	const Matrix cofactorMatrix = CofactorMatrix(matrix);
	const Matrix adjMatrix = TransposeMatrix(cofactorMatrix);

	return DivideMatrix(adjMatrix, determinant);
}

void PrintMatrix(std::ostream& out, const Matrix& m)
{
	const std::streamsize old_precision = out.precision();
	out << std::fixed << std::setprecision(3);

	for (const std::array<double, 3>& row : m)
	{
		out << row[0] << "\t" << row[1] << "\t" << row[2] << std::endl;
	}

	out.unsetf(std::ios::fixed);
	out.precision(old_precision);
}