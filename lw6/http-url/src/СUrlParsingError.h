#pragma once
#include <stdexcept>

class СUrlParsingError final : public std::invalid_argument
{
public:
	explicit СUrlParsingError(const std::string& message)
		: std::invalid_argument(message)
	{
	}
};
