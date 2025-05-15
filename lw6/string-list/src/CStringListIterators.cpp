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

bool CStringList::Iterator::operator==(const Iterator& other) const noexcept
{
	return m_node == other.m_node;
}

bool CStringList::Iterator::operator!=(const Iterator& other) const noexcept
{
	return m_node != other.m_node;
}

CStringList::ReverseIterator::ReverseIterator(Node* node)
	: m_node(node)
{
}

std::string CStringList::ReverseIterator::operator*() const noexcept
{
	return m_node->m_value;
}

const CStringList::ReverseIterator& CStringList::ReverseIterator::operator++() noexcept
{
	if (m_node == nullptr)
	{
		throw std::out_of_range("Iterator is out of range");
	}
	m_node = m_node->m_prev;
	return *this;
}

bool CStringList::ReverseIterator::operator==(const ReverseIterator& other) const noexcept
{
	return m_node == other.m_node;
}

bool CStringList::ReverseIterator::operator!=(const ReverseIterator& other) const noexcept
{
	return m_node != other.m_node;
}

CStringList::ConstIterator::ConstIterator(const Node* node)
	: m_node(node)
{
}

std::string CStringList::ConstIterator::operator*() const noexcept
{
	return m_node->m_value;
}

const CStringList::ConstIterator& CStringList::ConstIterator::operator++() noexcept
{
	if (m_node == nullptr)
	{
		throw std::out_of_range("Iterator is out of range");
	}
	m_node = m_node->m_next;
	return *this;
}

bool CStringList::ConstIterator::operator==(const ConstIterator& other) const noexcept
{
	return m_node == other.m_node;
}

bool CStringList::ConstIterator::operator!=(const ConstIterator& other) const noexcept
{
	return m_node != other.m_node;
}
