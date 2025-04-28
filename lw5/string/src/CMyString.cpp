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
	, m_capacity(std::exchange(other.m_capacity, 0))
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
	if (length + start > m_size)
	{
		throw std::out_of_range("Invalid substring start position");
	}


	return CMyString(m_chars + start, length);
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