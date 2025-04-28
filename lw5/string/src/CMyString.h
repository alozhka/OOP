#pragma once
#include <string>

class CMyString
{
public:
	CMyString();
	explicit CMyString(const char* pString);
	CMyString(const char* pString, size_t length);
	CMyString(const CMyString& other);
	CMyString(CMyString&& other) noexcept;
	explicit CMyString(const std::string& stlString);
	~CMyString();

	[[nodiscard]] size_t GetLength() const;
	[[nodiscard]] const char* GetStringData() const;
	CMyString SubString(size_t start, size_t length = SIZE_MAX) const;
	[[nodiscard]] size_t GetCapacity() const;

	void Clear();

private:
	inline static char m_emptyString[] = { '\0' };

	char* m_chars;
	size_t m_size, m_capacity;
};