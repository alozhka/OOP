#pragma once
#include <string>

class CStringList
{
public:
	CStringList() noexcept;

	bool IsEmpty() const noexcept;
	size_t GetSize() const noexcept;

	void PushBack(const std::string& str) noexcept;
	void PushFront(const std::string& str) noexcept;
	void Clear() noexcept;

	struct Node;
	class Iterator;
	class ConstIterator;

	Iterator Insert(Iterator it, const std::string& str);

	Iterator begin() const noexcept { return Iterator(m_head); }
	static Iterator end() noexcept { return Iterator(nullptr); }
	ConstIterator cbegin() const noexcept { return ConstIterator(m_head); }
	static ConstIterator cend() noexcept { return ConstIterator(nullptr); }

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
		bool operator==(const Iterator& other) const noexcept { return m_node == other.m_node; }
		bool operator!=(const Iterator& other) const noexcept { return m_node != other.m_node; }

	private:
		friend class CStringList;
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