#pragma once
#include <algorithm>
#include <iterator>

template <typename T>
class CMyArray
{
public:
	CMyArray() = default;
	~CMyArray() noexcept;

	CMyArray(const CMyArray& other);
	CMyArray(CMyArray&& other) noexcept;
	CMyArray& operator=(const CMyArray& other);
	CMyArray& operator=(CMyArray&& other) noexcept;

	void PushBack(const T& item);
	[[nodiscard]] size_t Size() const noexcept;
	[[nodiscard]] size_t Capacity() const noexcept;
	void Resize(size_t newSize);
	void Clear();

	T& operator[](size_t index);
	const T& operator[](size_t index) const;

	using Iterator = T*;
	using ConstIterator = const T*;
	using ReverseIterator = std::reverse_iterator<Iterator>;
	using ConstReverseIterator = std::reverse_iterator<ConstIterator>;

	Iterator begin() noexcept { return m_data; }
	Iterator end() noexcept { return m_data + m_size; }
	ConstIterator begin() const noexcept { return const_cast<const T*>(m_data); }
	ConstIterator end() const noexcept { return const_cast<const T*>(m_data + m_size); }
	ReverseIterator rbegin() noexcept { return ReverseIterator(end()); }
	ReverseIterator rend() noexcept { return ReverseIterator(begin()); }
	ConstReverseIterator rbegin() const noexcept { return ConstReverseIterator(end()); }
	ConstReverseIterator rend() const noexcept { return ConstReverseIterator(begin()); }

	template <typename U>
	CMyArray& operator=(const CMyArray<U>& other);

private:
	void EnsureCapacity(size_t size);
	void Swap(CMyArray& other) noexcept;

	template <typename> friend class CMyArray;

	T* m_data = nullptr;
	size_t m_size = 0;
	size_t m_capacity = 0;
};

//-----------------Implementation-----------------

template <typename T>
CMyArray<T>::~CMyArray() noexcept
{
	try
	{
		Clear();
	}
	catch (...)
	{
	}
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
CMyArray<T>& CMyArray<T>::operator=(CMyArray&& other) noexcept
{
	if (this != &other)
	{
		CMyArray temp{ std::move(other) };
		Swap(temp);
	}

	return *this;
}

template <typename T>
template <typename U>
CMyArray<T>& CMyArray<T>::operator=(const CMyArray<U>& other)
{
	CMyArray temp;
	temp.Resize(other.Size());

	try
	{
		for (size_t i = 0; i < other.Size(); ++i)
		{
			temp.m_data[i] = static_cast<T>(other.m_data[i]);
		}
	}
	catch (...)
	{
		temp.Clear();
		throw;
	}

	Swap(temp);
	m_size = other.m_size;
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
void CMyArray<T>::Resize(size_t size)
{
	const size_t newSize = std::min(size, m_size);
	T* temp = new T[size];

	try
	{
		std::copy(m_data, m_data + newSize, temp);
	}
	catch (...)
	{
		delete[] temp;
		throw;
	}
	delete[] m_data;
	m_data = temp;
	m_size = newSize;
	m_capacity = size;
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
T& CMyArray<T>::operator[](size_t index)
{
	if (index >= m_size)
	{
		throw std::out_of_range("Index out of range");
	}

	return m_data[index];
}

template <typename T>
const T& CMyArray<T>::operator[](size_t index) const
{
	return const_cast<CMyArray*>(this)->operator[](index);
}

template <typename T>
void CMyArray<T>::EnsureCapacity(size_t size)
{
	if (size <= m_capacity)
	{
		return;
	}

	Resize(m_capacity ? m_capacity * 2 : 1);
}

template <typename T>
void CMyArray<T>::Swap(CMyArray& other) noexcept
{
	std::swap(m_size, other.m_size);
	std::swap(m_capacity, other.m_capacity);
	std::swap(m_data, other.m_data);
}
