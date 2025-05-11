#pragma once
#include <string>

class CStringList
{
public:
	CStringList() noexcept;

	bool IsEmpty() const noexcept;
	size_t GetSize() const noexcept;

	void PushBack(const std::string& str) noexcept;

	struct Node;
	class Iterator;
	class ConstIterator;

	Iterator begin() const noexcept { return Iterator(m_head); }
	ConstIterator cbegin() const noexcept { return ConstIterator(m_head); }

	class Iterator
	{
	public:
		explicit Iterator(Node* node)
			: m_node(node)
		{
		}
		std::string operator*() const noexcept { return m_node->m_value; }
		const Iterator& operator++() noexcept
		{
			m_node = m_node->m_next;
			return *this;
		}

	private:
		Node* m_node;
	};

	class ConstIterator
	{
	public:
		explicit ConstIterator(const Node* node)
			: m_node(node)
		{
		}

	private:
		const Node* m_node;
	};

	struct Node
	{
		std::string m_value;
		Node* m_prev;
		Node* m_next;

		explicit Node(const std::string& value)
			: m_value(value)
			, m_prev(nullptr)
			, m_next(nullptr)
		{
		}
	};

private:
	Node* m_head;
	Node* m_tail;
	size_t m_size;
};