#pragma once
#include <iterator>
#include <utility>

template <typename T>
class CMyArray
{
public:
	CMyArray() = default;
	~CMyArray() noexcept;

	CMyArray(const CMyArray& other);
	CMyArray(CMyArray&& other) noexcept;
	CMyArray& operator=(const CMyArray& other);
	// CMyArray& operator=(CMyArray&& other) noexcept;

	void PushBack(const T& item);
	[[nodiscard]] size_t Size() const noexcept;
	[[nodiscard]] size_t Capacity() const noexcept;
	// void Resize();
	void Clear();

	// T& operator[](size_t index);
	// const T& operator[](size_t index) const;

	using Iterator = T*;
	using ReverseIterator = std::reverse_iterator<Iterator>;

	Iterator begin() const noexcept { return m_data; }
	Iterator end() const noexcept { return m_data + m_size; }
	ReverseIterator rbegin() const noexcept { return ReverseIterator(end()); }
	ReverseIterator rend() const noexcept { return ReverseIterator(begin()); }

private:
	void EnsureCapacity(size_t size);
	void IncreaseCapacity(size_t size);
	void Swap(CMyArray& other) noexcept;

	T* m_data = nullptr;
	size_t m_size = 0;
	size_t m_capacity = 0;
};

//-----------------Implementation-----------------

template <typename T>
CMyArray<T>::~CMyArray() noexcept
{
	Clear();
}

template <typename T>
CMyArray<T>::CMyArray(const CMyArray& other)
	: m_size(other.m_size)
	, m_capacity(other.m_capacity)
{
	T* temp = new T[other.m_size];
	try
	{
		std::copy(other.m_data, other.m_data + other.m_size, temp);
	}
	catch (...)
	{
		delete[] temp;
		throw;
	}

	delete[] m_data;
	m_data = temp;
}

template <typename T>
CMyArray<T>::CMyArray(CMyArray&& other) noexcept
{
	Swap(other);
}

template <typename T>
CMyArray<T>& CMyArray<T>::operator=(const CMyArray& other)
{
	if (this != &other)
	{
		CMyArray temp{ other };
		Swap(temp);
	}

	return *this;
}

template <typename T>
void CMyArray<T>::PushBack(const T& item)
{
	EnsureCapacity(m_size + 1);
	m_data[m_size++] = item;
}

template <typename T>
size_t CMyArray<T>::Size() const noexcept
{
	return m_size;
}

template <typename T>
size_t CMyArray<T>::Capacity() const noexcept
{
	return m_capacity;
}

template <typename T>
void CMyArray<T>::Clear()
{
	delete[] m_data;
	m_data = nullptr;
	m_size = 0;
	m_capacity = 0;
}

template <typename T>
void CMyArray<T>::EnsureCapacity(size_t size)
{
	if (size <= m_capacity)
	{
		return;
	}

	IncreaseCapacity(size);
}

template <typename T>
void CMyArray<T>::IncreaseCapacity(size_t size)
{
	const size_t newCapacity = std::max(size, m_capacity ? m_capacity * 2 : 1);
	T* newData = new T[newCapacity];

	for (size_t i = 0; i < m_size; ++i)
	{
		newData[i] = std::move(m_data[i]);
	}

	delete[] m_data;
	m_data = newData;
	m_capacity = newCapacity;
}

template <typename T>
void CMyArray<T>::Swap(CMyArray& other) noexcept
{
	std::swap(m_size, other.m_size);
	std::swap(m_capacity, other.m_capacity);
	std::swap(m_data, other.m_data);
}