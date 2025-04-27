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
	// Инициализируем дату заданными днем, месяцем и годом.
	// Примечание: год >= 1970
	CDate(unsigned day, Month month, unsigned year);

	// Инициализируем дату количеством дней, прошедших после 1 января 1970 года
	// Например, 2 = 3 января 1970, 32 = 2 февраля 1970 года и т.д.
	explicit CDate(unsigned timestamp);

	// Конструктор по умолчанию. Создаёт дату, равную 1 января 1970.
	CDate();

	// Возвращает день месяца (от 1 до 31)
	[[nodiscard]] unsigned GetDay()const;

	// Возвращает месяц
	[[nodiscard]] Month GetMonth()const;

	// Возвращает год
	[[nodiscard]] unsigned GetYear()const;

	// Возвращает день недели
	[[nodiscard]] WeekDay GetWeekDay()const;

	CDate& operator++();
	CDate operator++(int);

	CDate& operator+=(unsigned days);

	CDate operator+(unsigned days) const;

private:
	unsigned m_timestamp;
};
