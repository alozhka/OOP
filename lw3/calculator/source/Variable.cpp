#include "../include/Variable.h"

 Variable::Variable(double value)
{
	m_value = value;
}

double Variable::GetResult()
{
	return m_value;
}
