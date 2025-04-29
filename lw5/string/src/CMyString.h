#pragma once
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

	using Iterator = char*;
	using ConstIterator = const char*;
	using ReverseIterator = std::reverse_iterator<Iterator>;
	using ConstReverseIterator = std::reverse_iterator<ConstIterator>;

	Iterator begin() noexcept;
	Iterator end() noexcept;

	[[nodiscard]] ConstIterator begin() const noexcept;
	[[nodiscard]] ConstIterator end() const noexcept;

	[[nodiscard]] ConstIterator cbegin() const noexcept;
	[[nodiscard]] ConstIterator cend() const noexcept;

	ReverseIterator rbegin() noexcept;
	ReverseIterator rend() noexcept;

	[[nodiscard]] ConstReverseIterator rbegin() const noexcept;
	[[nodiscard]] ConstReverseIterator rend() const noexcept;

	[[nodiscard]] ConstReverseIterator crbegin() const noexcept;
	[[nodiscard]] ConstReverseIterator crend() const noexcept;


private:
	inline static char m_emptyString[] = { '\0' };

	char* m_chars;
	size_t m_size, m_capacity;
};