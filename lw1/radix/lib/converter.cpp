#include <format>
#include <stdexcept>

constexpr char CHAR_0 = '0';
constexpr char CHAR_9 = '9';
constexpr char CHAR_UPPER_A = 'A';
constexpr char CHAR_UPPER_Z = 'Z';
constexpr char CHAR_A = 'a';
constexpr char CHAR_Z = 'z';

int CharToInt(const char ch)
{
	if (CHAR_0 <= ch && ch <= CHAR_9)
	{
		return ch - CHAR_0;
	}
	if (CHAR_UPPER_A <= ch && ch <= CHAR_UPPER_Z)
	{
		return ch - CHAR_UPPER_A + 10;
	}
	if (CHAR_A <= ch && ch <= CHAR_Z)
	{
		return ch - CHAR_A + 10;
	}

	throw std::invalid_argument("The digit must be in the segments [0, 10] and [A, Z]");
}

char IntToChar(const int i)
{
	if (0 <= i && i <= 9)
	{
		return CHAR_0 + i;
	}

	if (10 <= i && i <= 35)
	{
		return CHAR_UPPER_A + i - 10;
	}

	throw std::invalid_argument("Integer has to be in range from 0 to 35");
}

void ThrowIfRadixOutOfRange(int radix)
{
	if (radix < 2 || radix > 36)
	{
		throw std::invalid_argument("The radix should be in the range from 2 to 36");
	}
}

void ThrowIfReachesOverflow(const bool isNegative, const int result, const int radix, const int number)
{
	if (isNegative)
	{
		if (-result < (std::numeric_limits<int>::min() + number) / radix)
		{
			throw std::overflow_error("Reached overflow");
		}
	}
	else
	{
		if (result > (std::numeric_limits<int>::max() - number) / radix)
		{
			throw std::overflow_error("Reached overflow");
		}
	}
}

int StringToInt(const std::string& str, const int radix)
{
	ThrowIfRadixOutOfRange(radix);
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
		const int decimalDigit = CharToInt(str[i]);
		if (decimalDigit >= radix)
		{
			throw std::runtime_error(std::format("The number must be with base {}, got {}", radix, IntToChar(decimalDigit)));
		}
		ThrowIfReachesOverflow(isNegative, result, radix, decimalDigit);
		result = result * radix + decimalDigit;
	}

	return isNegative ? -result : result;
}

std::string IntToString(int n, const int radix)
{
	ThrowIfRadixOutOfRange(radix);
	if (n == 0)
	{
		return "0";
	}

	std::string result;
	bool isNegative = false;

	if (n < 0)
	{
		isNegative = true;
	}

	while (n != 0)
	{
		int i = n % radix;
		if (isNegative)
		{
			i = -i;
		}
		result.push_back(IntToChar(i));
		n /= radix;
	}

	if (isNegative)
	{
		result.push_back('-');
	}

	std::reverse(result.begin(), result.end());
	return result;
}
