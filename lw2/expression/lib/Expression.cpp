#include "Expression.h"

#include <sstream>
#include <stack>

constexpr char OPENED_BRACE = '(';
constexpr std::string OPENED_BRACE_STR = "(";
constexpr char CLOSED_BRACE = ')';
constexpr std::string CLOSED_BRACE_STR = ")";
constexpr char PLUS = '+';
constexpr char MULTIPLY = '*';

int PerformAddition(std::stack<std::string>& values)
{
	int result = 0;
	while (!values.empty() && values.top() != OPENED_BRACE_STR)
	{
		result += std::stoi(values.top());
		values.pop();
	}
	return result;
}

int PerformMultiplication(std::stack<std::string>& values)
{
	int result = 1;
	while (!values.empty() && values.top() != OPENED_BRACE_STR)
	{
		result *= std::stoi(values.top());
		values.pop();
	}
	return result;
}

void CalculateLastOperation(std::stack<char>& operations, std::stack<std::string>& values)
{
	const char operation = operations.top();
	operations.pop();

	int result = 0;
	if (operation == PLUS)
	{
		result = PerformAddition(values);
	}
	else if (operation == MULTIPLY)
	{
		result = PerformMultiplication(values);
	}

	if (!values.empty() && values.top() == OPENED_BRACE_STR)
	{
		values.pop();
	}

	values.push(std::to_string(result));
}

void ParseOperation(std::istringstream& iss, std::stack<char>& operations)
{
	char operation;
	if (!(iss >> operation))
	{
		throw std::invalid_argument("Invalid operation");
	}

	if (operation != PLUS && operation != MULTIPLY)
	{
		throw std::invalid_argument("Invalid operation");
	}

	operations.push(operation);
}

int CalculateExpression(const std::string& expression)
{
	std::stack<std::string> values;
	std::stack<char> operations;
	std::istringstream iss(expression);
	char ch;

	while (iss >> ch)
	{
		if (ch == OPENED_BRACE)
		{
			values.emplace(OPENED_BRACE_STR);
			ParseOperation(iss, operations);
		}
		else if (ch == CLOSED_BRACE)
		{
			CalculateLastOperation(operations, values);
		}
		else
		{
			iss.unget();
			int num;
			if (!(iss >> num))
			{
				throw std::invalid_argument("Invalid number");
			}
			values.push(std::to_string(num));
		}
	}

	if (values.size() != 1)
	{
		throw std::invalid_argument("Invalid expression");
	}

	return std::stoi(values.top());
}