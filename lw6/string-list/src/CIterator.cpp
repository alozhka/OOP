#include "CStringList.h"

CStringList::Iterator::Iterator(Node* node)
	: m_node(node)
{
}

std::string CStringList::Iterator::operator*() const noexcept
{
	return m_node->m_value;
}

CStringList::Iterator& CStringList::Iterator::operator++() noexcept
{
	if (m_node == nullptr)
	{
		throw std::out_of_range("Iterator is out of range");
	}
	m_node = m_node->m_next;
	return *this;
}
