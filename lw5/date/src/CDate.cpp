#include "CDate.h"

#include <algorithm>

namespace
{
constexpr unsigned MIN_YEAR = 1970;
constexpr unsigned MAX_YEAR = 9999;
constexpr unsigned MAX_TIMESTAMP = 2932896;
constexpr unsigned DAYS_IN_YEAR = 365;
constexpr unsigned DAYS_IN_LEAP_YEAR = 366;
constexpr unsigned DAYS_IN_FEBRUARY = 28;
constexpr unsigned DAYS_IN_LEAP_FEBRUARY = 29;

bool IsLeapYear(unsigned year)
{
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

unsigned GetDaysInMonth(Month month, unsigned year)
{
	switch (month)
	{
	case Month::FEBRUARY:
		return IsLeapYear(year) ? DAYS_IN_LEAP_FEBRUARY : DAYS_IN_FEBRUARY;
	case Month::APRIL:
	case Month::JUNE:
	case Month::SEPTEMBER:
	case Month::NOVEMBER:
		return 30;
	default:
		return 31;
	}
}

bool IsValidDate(unsigned day, Month month, unsigned year)
{
	return (MIN_YEAR <= year && year <= MAX_YEAR)
		&& (1 <= day && day <= GetDaysInMonth(month, year));
}

void TimestampToDate(unsigned timestamp, unsigned& day, Month& month, unsigned& year)
{
	unsigned remainedTime = timestamp;

	year = MIN_YEAR;
	while (true)
	{
		unsigned daysInYear = IsLeapYear(year) ? DAYS_IN_LEAP_YEAR : DAYS_IN_YEAR;
		if (remainedTime < daysInYear)
		{
			break;
		}
		remainedTime -= daysInYear;
		++year;
	}

	month = Month::JANUARY;
	while (true)
	{
		unsigned daysIsMonth = GetDaysInMonth(month, year);
		if (remainedTime < daysIsMonth)
		{
			break;
		}
		remainedTime -= daysIsMonth;
		month = static_cast<Month>(static_cast<unsigned>(month) + 1);
	}

	day = remainedTime + 1;
}

unsigned DateToTimestamp(unsigned day, Month month, unsigned year)
{
	if (!IsValidDate(day, month, year))
	{
		throw std::invalid_argument("Invalid date");
	}

	unsigned timestamp = 0;
	for (unsigned curr = MIN_YEAR; curr < year; ++curr)
	{
		timestamp += IsLeapYear(curr) ? DAYS_IN_LEAP_YEAR : DAYS_IN_YEAR;
	}

	for (unsigned curr = 1; curr < static_cast<unsigned>(month); ++curr)
	{
		timestamp += GetDaysInMonth(static_cast<Month>(curr), year);
	}

	return timestamp + day - 1;
}
} // namespace

CDate::CDate(unsigned day, Month month, unsigned year)
	: m_timestamp(DateToTimestamp(day, month, year))
{
}

CDate::CDate(unsigned timestamp)
	: m_timestamp(timestamp)
{
}

CDate::CDate()
	: m_timestamp(0)
{
}

unsigned CDate::GetDay() const
{
	unsigned day, year;
	Month month;
	TimestampToDate(m_timestamp, day, month, year);
	return day;
}

Month CDate::GetMonth() const
{
	unsigned day, year;
	Month month;
	TimestampToDate(m_timestamp, day, month, year);
	return month;
}

unsigned CDate::GetYear() const
{
	unsigned day, year;
	Month month;
	TimestampToDate(m_timestamp, day, month, year);
	return year;
}

WeekDay CDate::GetWeekDay() const
{
	return static_cast<WeekDay>((m_timestamp + 4) % 7);
}

CDate& CDate::operator++()
{
	if (m_timestamp >= MAX_TIMESTAMP)
	{
		throw std::out_of_range("Date is going to be out of range");
	}

	++m_timestamp;

	return *this;
}

CDate CDate::operator++(int)
{
	CDate temp = *this;
	++*this;
	return temp;
}

CDate& CDate::operator--()
{
	if (m_timestamp <= 0)
	{
		throw std::out_of_range("Date is going to be out of range");
	}

	--m_timestamp;
	return *this;
}

CDate CDate::operator--(int)
{
	CDate temp = *this;
	--*this;
	return temp;
}

CDate& CDate::operator+=(unsigned days)
{
	if (m_timestamp + days >= MAX_TIMESTAMP)
	{
		throw std::out_of_range("Date is going to be out of range");
	}

	m_timestamp += days;
	return *this;
}

CDate& CDate::operator-=(unsigned days)
{
	if (m_timestamp <= 0)
	{
		throw std::out_of_range("Date is going to be out of range");
	}

	m_timestamp -= days;
	return *this;
}

CDate CDate::operator+(unsigned days) const
{
	return CDate(m_timestamp + days);
}

CDate CDate::operator-(unsigned days) const
{
	return CDate(m_timestamp - days);
}