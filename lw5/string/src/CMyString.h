#pragma once
#include <string>
#include <istream>
#include <ostream>

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
	[[nodiscard]] CMyString SubString(size_t start, size_t length = SIZE_MAX) const;
	[[nodiscard]] size_t GetCapacity() const;

	void Clear();

	bool operator==(const CMyString& other) const noexcept;
	CMyString& operator=(const CMyString& other);
	CMyString& operator=(CMyString&& other) noexcept;
	std::strong_ordering operator<=>(const CMyString& other) const noexcept;

	CMyString operator+(const CMyString& other) const;
	CMyString operator+(const std::string& other) const;
	CMyString operator+(const char* other) const;

	CMyString& operator+=(const CMyString& other);

	const char& operator[](size_t index) const;
	char& operator[](size_t index);

	friend std::ostream& operator<<(std::ostream& out, const CMyString& str);
	friend std::istream& operator>>(std::istream& in, CMyString& str);

private:
	inline static char m_emptyString[] = { '\0' };

	char* m_chars;
	size_t m_size, m_capacity;
};