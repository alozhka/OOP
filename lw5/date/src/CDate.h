#pragma once
#include <istream>

enum class Month
{
	JANUARY = 1,
	FEBRUARY,
	MARCH,
	APRIL,
	MAY,
	JUNE,
	JULY,
	AUGUST,
	SEPTEMBER,
	OCTOBER,
	NOVEMBER,
	DECEMBER
};

enum class WeekDay
{
	MONDAY = 1,
	TUESDAY,
	WEDNESDAY,
	THURSDAY,
	FRIDAY,
	SATURDAY,
	SUNDAY
};

class CDate
{
public:
	CDate(unsigned day, Month month, unsigned year);
	explicit CDate(unsigned timestamp);
	CDate();

	[[nodiscard]] unsigned GetDay() const;
	[[nodiscard]] Month GetMonth() const;
	[[nodiscard]] unsigned GetYear() const;
	[[nodiscard]] WeekDay GetWeekDay() const;

	CDate& operator++();
	CDate operator++(int);
	CDate& operator--();
	CDate operator--(int);

	CDate& operator+=(unsigned days);
	CDate& operator-=(unsigned days);

	CDate operator+(unsigned days) const;
	CDate operator-(unsigned days) const;

	bool operator==(const CDate& other) const;
	bool operator!=(const CDate& other) const;
	bool operator<(const CDate& other) const;
	bool operator>(const CDate& other) const;
	bool operator<=(const CDate& other) const;
	bool operator>=(const CDate& other) const;

	friend std::istream& operator>>(std::istream& in, CDate& date);
	friend std::ostream& operator<<(std::ostream& out, CDate& date);

private:
	unsigned m_timestamp;
};
