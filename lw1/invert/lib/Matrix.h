#pragma once

#include <array>
#include <ostream>

using Matrix = std::array<std::array<double, 3>, 3>;

Matrix InvertMatrix(const Matrix& matrix);
void PrintMatrix(std::ostream& out, const Matrix& m);
