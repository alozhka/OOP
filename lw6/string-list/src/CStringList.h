#pragma once
#include <string>

class CStringList
{
public:
	CStringList() noexcept;
	CStringList(const CStringList& list);
	CStringList(CStringList&& list) noexcept;
	~CStringList() noexcept;

	CStringList& operator=(const CStringList& list);
	CStringList& operator=(CStringList&& list) noexcept;

	bool IsEmpty() const noexcept;
	size_t GetSize() const noexcept;

	void PushBack(const std::string& str) noexcept;
	void PushFront(const std::string& str) noexcept;
	void Clear() noexcept;

	struct Node;
	class Iterator;
	class ConstIterator;
	class ReverseIterator;
	class ConstReverseIterator;

	Iterator Insert(Iterator it, const std::string& str);
	Iterator Erase(Iterator it);

	Iterator begin() const noexcept { return Iterator(m_head); }
	Iterator end() const noexcept { return Iterator(nullptr); }
	ConstIterator cbegin() const noexcept { return ConstIterator(m_head); }
	ConstIterator cend() const noexcept { return ConstIterator(nullptr); }

	ReverseIterator rbegin() const noexcept { return ReverseIterator(m_tail); }
	ReverseIterator rend() const noexcept { return ReverseIterator(nullptr); }
	ConstReverseIterator crbegin() const noexcept { return ConstReverseIterator(m_tail); }
	ConstReverseIterator crend() const noexcept { return ConstReverseIterator(nullptr); }

	class Iterator
	{
	public:
		explicit Iterator(Node* node);

		std::string operator*() const noexcept;
		Iterator& operator++() noexcept;
		bool operator==(const Iterator& other) const noexcept;
		bool operator!=(const Iterator& other) const noexcept;

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

		std::string operator*() const noexcept { return m_node->m_value; }
		const ConstIterator& operator++() noexcept
		{
			if (m_node == nullptr)
			{
				throw std::out_of_range("Iterator is out of range");
			}
			m_node = m_node->m_next;
			return *this;
		}
		ConstIterator& operator--()
		{
			if (m_node == nullptr)
			{
				throw std::out_of_range("Iterator is out of range");
			}
			m_node = m_node->m_prev;
			return *this;
		}
		bool operator==(const ConstIterator& other) const noexcept { return m_node == other.m_node; }
		bool operator!=(const ConstIterator& other) const noexcept { return m_node != other.m_node; }

	private:
		const Node* m_node;
	};

	class ReverseIterator
	{
	public:
		explicit ReverseIterator(Node* node)
			: m_node(node)
		{
		}

		std::string operator*() const noexcept { return m_node->m_value; }
		const ReverseIterator& operator++() noexcept
		{
			if (m_node == nullptr)
			{
				throw std::out_of_range("Iterator is out of range");
			}
			m_node = m_node->m_prev;
			return *this;
		}
		bool operator==(const ReverseIterator& other) const noexcept { return m_node == other.m_node; }
		bool operator!=(const ReverseIterator& other) const noexcept { return m_node != other.m_node; }

	private:
		friend class CStringList;
		Node* m_node;
	};

	class ConstReverseIterator
	{
	public:
		explicit ConstReverseIterator(Node* node)
			: m_node(node)
		{
		}

		std::string operator*() const noexcept { return m_node->m_value; }
		const ConstReverseIterator& operator++() noexcept
		{
			if (m_node == nullptr)
			{
				throw std::out_of_range("Iterator is out of range");
			}
			m_node = m_node->m_prev;
			return *this;
		}
		bool operator==(const ConstReverseIterator& other) const noexcept { return m_node == other.m_node; }
		bool operator!=(const ConstReverseIterator& other) const noexcept { return m_node != other.m_node; }

	private:
		friend class CStringList;
		Node* m_node;
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
	void Copy(const CStringList& list);
	void Move(CStringList&& list);

	Node* m_head;
	Node* m_tail;
	size_t m_size;
};