#include "Expression.h"

#include <sstream>
#include <stack>

int CalculateExpression(const std::string& expression)
{
	std::stack<int> values;
	std::stack<char> ops;
	std::istringstream iss(expression);
	char ch;

	while (iss >> ch)
	{
		if (ch == '(')
		{
			values.push(ch);
			continue;
		}
		if (ch == '+' || ch == '*')
		{
			ops.push(ch);
		}
		else if (ch == ')')
		{
			char op = ops.top();
			ops.pop();
			int result = 0;

			if (op == '+')
			{
				result = 0;
				while (!values.empty() && values.top() != '(')
				{
					result += values.top();
					values.pop();
				}
			}
			else if (op == '*')
			{
				result = 1;
				while (!values.empty() && values.top() != '(')
				{
					result *= values.top();
					values.pop();
				}
			}

			if (!values.empty() && values.top() == '(')
			{
				values.pop();
			}

			values.push(result);
		}
		else
		{
			iss.unget();
			int num;
			iss >> num;
			values.push(num);
		}
	}

	if (values.size() != 1)
	{
		throw std::invalid_argument("Invalid expression");
	}

	return values.top();
}
