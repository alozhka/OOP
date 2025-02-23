#include <format>
#include <stdexcept>

int CharToInt(char ch)
{
	if ('0' <= ch && ch <= '9')
	{
		return ch - '0';
	}
	if ('A' <= ch && ch <= 'Z')
	{
		return ch - 'A' + 10;
	}
	if ('a' <= ch && ch <= 'z')
	{
		return ch - 'a' + 10;
	}

	throw std::invalid_argument("The number must be in the segments [0, 10] and [A, Z]");
}

void ThrowIfReachesOverflow(const bool isNegative, const int result, const int radix, const int number)
{
	if (isNegative)
	{
		if (-result < (std::numeric_limits<int>::min() + number) / radix)
		{
			throw std::overflow_error("Reached low overflow");
		}
	}
	else
	{
		if (result > (std::numeric_limits<int>::max() - number) / radix)
		{
			throw std::overflow_error("Reached top overflow");
		}
	}
}

int StringToInt(const std::string& str, int radix)
{
	if (radix < 2 || radix > 36)
	{
		throw std::invalid_argument("The base of the number system should be in the range from 2 to 36");
	}
	bool isNegative = false;
	size_t i = 0;
	int result = 0;

	if (str[0] == '-')
	{
		isNegative = true;
		i = 1;
	}

	for (; i < str.size(); i++)
	{
		int decimalDigit = CharToInt(str[i]);
		if (decimalDigit >= radix)
		{
			throw std::runtime_error(std::format("The number must be with base {}, got {}", radix, decimalDigit));
		}
		ThrowIfReachesOverflow(isNegative, result, radix, decimalDigit);
		result = result * radix + decimalDigit;
	}

	return isNegative ? -result : result;
}

std::string IntToString(int n, int radix)
{
	if (radix < 2 || radix > 36)
	{
		throw std::invalid_argument("The base of the number system should be in the range from 2 to 36");
	}

	throw std::invalid_argument("Not implemented");
}
