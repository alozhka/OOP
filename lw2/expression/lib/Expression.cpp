#include "Expression.h"

#include <sstream>
#include <stack>

constexpr char OPENED_BRACE = '(';
constexpr char CLOSED_BRACE = ')';
constexpr char PLUS = '+';
constexpr char MULTIPLY = '*';

int PerformOperation(const char operation, std::stack<int>& values)
{
	int result = 0;

	if (operation == PLUS)
	{
		result = 0;
		while (!values.empty() && values.top() != OPENED_BRACE)
		{
			result += values.top();
			values.pop();
		}
	}
	else if (operation == MULTIPLY)
	{
		result = 1;
		while (!values.empty() && values.top() != CLOSED_BRACE)
		{
			result *= values.top();
			values.pop();
		}
	}

	return result;
}

int PerformAddition(std::stack<std::string>& values) {
	int result = 0;
	while (!values.empty() && values.top() != "(") {
		result += std::stoi(values.top());
		values.pop();
	}
	return result;
}

int PerformMultiplication(std::stack<std::string>& values) {
	int result = 1;
	while (!values.empty() && values.top() != "(") {
		result *= std::stoi(values.top());
		values.pop();
	}
	return result;
}


int CalculateExpression(const std::string& expression)
{
	std::stack<std::string> values;
	std::stack<char> operations;
	std::istringstream iss(expression);
	char ch;

	while (iss >> ch)
	{
		if (ch == '(')
		{
			values.emplace("(");
		}
		else if (ch == '+' || ch == '*')
		{
			operations.push(ch);
		}
		else if (ch == ')')
		{
			char operation = operations.top();
			operations.pop();

			int result = 0;
			if (operation == '+')
			{
				result = PerformAddition(values);
			}
			else if (operation == '*')
			{
				result = PerformMultiplication(values);
			}

			if (!values.empty() && values.top() == "(")
			{
				values.pop();
			}

			values.push(std::to_string(result));
		}
		else
		{
			iss.unget();
			int num;
			iss >> num;
			values.push(std::to_string(num));
		}
	}

	if (values.size() != 1)
	{
		throw std::invalid_argument("Invalid expression");
	}

	return std::stoi(values.top());
}