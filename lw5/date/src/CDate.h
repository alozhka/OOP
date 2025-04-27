#pragma once

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
	SUNDAY,
	INVALID
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

private:
	unsigned m_timestamp;
};
