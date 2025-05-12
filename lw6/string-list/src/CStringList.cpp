#include "CStringList.h"

namespace
{

}

CStringList::CStringList() noexcept
	: m_head(nullptr)
	, m_tail(nullptr)
	, m_size(0)
{
}

CStringList::CStringList(const CStringList& list)
	: m_head(nullptr)
	, m_tail(nullptr)
	, m_size(0)
{
	Copy(list);
}

CStringList::CStringList(CStringList&& list) noexcept
	: m_head(nullptr)
	, m_tail(nullptr)
	, m_size(0)
{
	Move(std::move(list));
}

CStringList& CStringList::operator=(const CStringList& list)
{
	if (this != &list)
	{
		Copy(list);
	}

	return *this;
}

CStringList& CStringList::operator=(CStringList&& list) noexcept
{
	if (this != &list)
	{
		Clear();
		Move(std::move(list));
	}

	return *this;
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

void CStringList::Clear() noexcept
{
	while (m_head)
	{
		Node* temp = m_head;
		m_head = m_head->m_next;
		delete temp;
	}

	m_head = nullptr;
	m_tail = nullptr;
	m_size = 0;
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

void CStringList::Copy(const CStringList& list)
{
	for (const std::string& value : list)
	{
		PushBack(value);
	}
}

void CStringList::Move(CStringList&& list)
{
	m_head = list.m_head;
	m_tail = list.m_tail;
	m_size = list.m_size;

	list.m_head = nullptr;
	list.m_tail = nullptr;
	list.m_size = 0;
}