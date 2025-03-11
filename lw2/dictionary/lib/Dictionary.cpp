#include "Dictionary.h"

#include <algorithm>
#include <string>

std::string ToLower(const std::string& s)
{
	std::string result;
	result.reserve(s.size());

	std::ranges::transform(s, std::back_inserter(result), tolower);

	return result;
}

