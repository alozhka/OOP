#include "CStringList.h"

CStringList::CStringList() noexcept
	: m_head(nullptr)
	, m_tail(nullptr)
	, m_size(0)
{
}

bool CStringList::IsEmpty() const noexcept
{
	return m_size == 0;
}

size_t CStringList::GetSize() const noexcept
{
	return m_size;
}

void CStringList::PushBack(const std::string& str) noexcept
{
	auto newNode = new Node(str);
	newNode->m_prev = m_tail;

	if (m_tail)
	{
		m_tail->m_next = newNode;
	}
	else
	{
		m_head = newNode;
	}

	m_tail = newNode;
	++m_size;
}

void CStringList::PushFront(const std::string& str) noexcept
{
	auto newNode = new Node(str);
	newNode->m_next = m_head;

	if (m_head)
	{
		m_head->m_prev = newNode;
	}
	else
	{
		m_tail = newNode;
	}

	m_head = newNode;
	++m_size;
}

CStringList::Iterator CStringList::Insert(Iterator it, const std::string& str)
{
	if (!it.m_node)
	{
		PushBack(str);
		return Iterator(m_tail);
	}

	auto newNode = new Node(str);
	newNode->m_next = it.m_node;
	newNode->m_prev = it.m_node->m_prev;

	if (!it.m_node->m_prev)
	{
		m_head = newNode;
	}
	else
	{
		it.m_node->m_prev->m_next = newNode;
	}

	it.m_node->m_prev = newNode;

	++m_size;
	return Iterator(newNode);
}