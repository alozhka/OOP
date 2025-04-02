#include "../include/Variable.h"

Variable::Variable(double value)
{
	m_value = value;
}

Variable::Variable(Expression* expr)
{
	m_value = expr->GetResult();
}

double Variable::GetResult()
{
	return m_value;
}

void Variable::SetValue(double value)
{
	m_value = value;
}
