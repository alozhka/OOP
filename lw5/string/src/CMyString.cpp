#include "CMyString.h"

namespace
{
char* AllocateChars(size_t length)
{
	return new char[length];
}

void ReleaseChars(char* pChars)
{
	delete[] pChars;
}
} // namespace

CMyString::CMyString()
	: m_chars(m_emptyString)
	, m_size(0)
	, m_capacity(1)
{
}

CMyString::CMyString(const char* pString)
	: CMyString(pString, std::strlen(pString))
{
}

CMyString::CMyString(const char* pString, size_t length)
{
	m_size = length;
	m_capacity = length + 1;

	if (length == 0)
	{
		m_chars = m_emptyString;
		return;
	}

	m_chars = AllocateChars(length);

	std::uninitialized_copy_n(pString, length, m_chars);
	m_chars[m_size] = '\0';
}

CMyString::CMyString(const CMyString& other)
	: CMyString(other.m_chars, other.m_size)
{
}

CMyString::CMyString(CMyString&& other) noexcept
	: m_chars(std::exchange(other.m_chars, m_emptyString))
	, m_size(std::exchange(other.m_size, 0))
	, m_capacity(std::exchange(other.m_capacity, 1))
{
}

CMyString::CMyString(const std::string& stlString)
	: CMyString(stlString.c_str(), stlString.size())
{
}

CMyString::~CMyString()
{
	if (m_chars != m_emptyString)
	{
		ReleaseChars(m_chars);
	}
}

size_t CMyString::GetLength() const
{
	return m_size;
}

const char* CMyString::GetStringData() const
{
	return m_chars;
}

CMyString CMyString::SubString(size_t start, size_t length) const
{
	if (length > m_size)
	{
		throw std::out_of_range("Invalid substring position");
	}

	return { m_chars + start, length };
}

size_t CMyString::GetCapacity() const
{
	return m_capacity;
}
void CMyString::Clear()
{
	if (m_chars != m_emptyString)
	{
		ReleaseChars(m_chars);
	}

	m_capacity = 1;
	m_size = 0;
	m_chars = m_emptyString;
}

bool CMyString::operator==(const CMyString& other) const noexcept
{
	if (m_chars == other.m_chars)
	{
		return true;
	}

	if (m_size != other.m_size)
	{
		return false;
	}

	return std::strcmp(m_chars, other.m_chars) == 0;
}

CMyString& CMyString::operator=(const CMyString& other)
{
	if (this != &other)
	{
		if (m_capacity >= other.m_size && m_chars != m_emptyString)
		{
			std::destroy_n(m_chars, m_size + 1);
			std::uninitialized_copy_n(other.m_chars, m_size + 1, m_chars);
			m_size = other.m_size;
		}
		else
		{
			CMyString copy{ other };
			std::swap(m_size, copy.m_size);
			std::swap(m_capacity, copy.m_capacity);
			std::swap(m_chars, copy.m_chars);
		}
	}
	return *this;
}

CMyString& CMyString::operator=(CMyString&& other) noexcept
{
	if (this != &other)
	{
		if (m_chars != m_emptyString)
		{
			ReleaseChars(m_chars);
		}

		m_size = std::exchange(other.m_size, 0);
		m_capacity = std::exchange(other.m_capacity, 1);
		m_chars = std::exchange(other.m_chars, m_emptyString);
	}
	return *this;
}

std::strong_ordering CMyString::operator<=>(const CMyString& other) const noexcept
{
	if (m_chars == other.m_chars)
	{
		return std::strong_ordering::equal;
	}

	return std::strcmp(m_chars, other.m_chars) <=> 0;
}

CMyString CMyString::operator+(const CMyString& other) const
{
	CMyString result;

	result.m_size = m_size + other.m_size;
	result.m_capacity = result.m_size + 1;

	result.m_chars = AllocateChars(result.m_capacity);
	std::memcpy(result.m_chars, m_chars, m_size);
	std::memcpy(result.m_chars + m_size, other.m_chars, other.m_size);
	result.m_chars[result.m_size] = '\0';

	return result;
}

CMyString CMyString::operator+(const std::string& other) const
{
	return *this + CMyString(other);
}

CMyString CMyString::operator+(const char* other) const
{
	return *this + CMyString(other);
}

CMyString& CMyString::operator+=(const CMyString& other)
{
	if (other.m_size + m_size >= m_capacity)
	{
		m_capacity = std::max(other.m_size + m_size + 1, m_capacity * 2);

		const auto chars = AllocateChars(m_capacity);
		std::memcpy(chars, m_chars, m_size);
		m_chars = chars;
	}

	std::memcpy(m_chars + m_size, other.m_chars, other.m_size + 1);
	m_size = m_size + other.m_size;

	return *this;
}

const char& CMyString::operator[](size_t index) const
{
	if (index >= m_size)
	{
		throw std::out_of_range("Index is out of range");
	}
	return m_chars[index];
}
char& CMyString::operator[](size_t index)
{
	if (index >= m_size)
	{
		throw std::out_of_range("Index out of range");
	}
	return m_chars[index];
}

CMyString::Iterator CMyString::begin() noexcept
{
	return m_chars;
}

CMyString::Iterator CMyString::end() noexcept
{
	return m_chars + m_size;
}

CMyString::ConstIterator CMyString::begin() const noexcept
{
	return m_chars;
}

CMyString::ConstIterator CMyString::end() const noexcept
{
	return m_chars + m_size;
}

CMyString::ConstIterator CMyString::cbegin() const noexcept
{
	return begin();
}

CMyString::ConstIterator CMyString::cend() const noexcept
{
	return end();
}

CMyString::ReverseIterator CMyString::rbegin() noexcept
{
	return ReverseIterator(end());
}

CMyString::ReverseIterator CMyString::rend() noexcept
{
	return ReverseIterator(begin());
}

CMyString::ConstReverseIterator CMyString::rbegin() const noexcept
{
	return ConstReverseIterator(end());
}

CMyString::ConstReverseIterator CMyString::rend() const noexcept
{
	return ConstReverseIterator(begin());
}

CMyString::ConstReverseIterator CMyString::crbegin() const noexcept
{
	return ConstReverseIterator(end());
}

CMyString::ConstReverseIterator CMyString::crend() const noexcept
{
	return ConstReverseIterator(begin());
}

std::ostream& operator<<(std::ostream& out, const CMyString& str)
{
	return out << str.m_chars;
}

std::istream& operator>>(std::istream& in, CMyString& str)
{
	std::string word;
	in >> word;
	str = CMyString(word);
	return in;
}