#include "CDate.h"

namespace
{
constexpr unsigned MIN_YEAR = 1970;
constexpr unsigned DAYS_IN_YEAR = 365;
constexpr unsigned DAYS_IN_LEAP_YEAR = 366;

bool IsLeapYear(unsigned year)
{
	return (year % 4 == 0 && year % 100 == 0) || year % 400 == 0;
}

unsigned GetDaysInMonth(Month month, unsigned year)
{
	switch (month)
	{
	case Month::FEBRUARY:
		return IsLeapYear(year) ? 29 : 28;
	case Month::APRIL:
	case Month::JUNE:
	case Month::SEPTEMBER:
	case Month::NOVEMBER:
		return 30;
	default:
		return 31;
	}
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
} // namespace

CDate::CDate(unsigned timestamp)
{
	m_timestamp = timestamp;
}

CDate::CDate()
{
	m_timestamp = 0;
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
	++m_timestamp;
	return *this;
}

CDate CDate::operator++(int)
{
	CDate temp = *this;
	++*this;
	return temp;
}

CDate& CDate::operator+=(unsigned days)
{
	m_timestamp += days;
	return *this;
}

CDate CDate::operator+(unsigned days) const
{
	return CDate(m_timestamp + days);
}