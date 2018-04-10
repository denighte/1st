#include "stdafx.h"
#include "Date.h"
//#pragma warning(disable:4996)
int Date::MonthCycle[2][12] = { { 31,28,31,30,31,30,31,31,30,31,30,31 },{ 31,29,31,30,31,30,31,31,30,31,30,31 } };

Date::Date() : _era(0) {
	time_t t = time(NULL);
	struct tm tm;
	localtime_s(&tm, &t);
	_day = tm.tm_mday;
	_month = tm.tm_mon + 1;
	_year = tm.tm_year + 1900;
	_vis = IsLeap();
}

Date::Date(int day, int month, int year, bool era) : _day(day), _month(month), _year(year), _era(era)
{
	_vis = IsLeap();
}

Date::Date(const Date &a) : _day(a._day), _month(a._month), _year(a._year), _era(a._era), _vis(a._vis) {}


Date& Date::operator=(const Date &a)
{
	_day = a._day;
	_month = a._month;
	_year = a._year;
	_era = a._era;
	_vis = a._vis;
	return *this;
}

bool Date::IsLeap()
{
	return (((_year - _era) % 100 != 0 && (_year - _era) % 4 == 0) || ((_year - _era) % 400 == 0));
}


int Date::days() const
{
	if (_year == 0)
		return 0;

	int days = _day;

	for (int i = 0; i < _month - 1; i++)
	{
		days = days + MonthCycle[_vis][i];
	}

	if (_era)
	{
		int LeapDays = ((_year - 1) / 4 - (_year - 1) / 100 + (_year - 1) / 400) + 1 /*+ vis*/;
		days = days - LeapDays;
		days = days - (365 * _year);
	}
	else
	{
		days = days + ((_year - 1) / 4 - (_year - 1) / 100 + (_year - 1) / 400);
		days = days + 365 * (_year - 1);
	}
	return days;
}


bool operator<(const Date &lhs, const Date &rhs) {
	if (lhs._era > rhs._era)
		return true;
	else if (lhs._era < rhs._era)
		return false;

	if (lhs._year < rhs._year)
		return true;
	else if (lhs._year == rhs._year) {
		if (lhs._month < rhs._month) {
			return true;
		}
		else if (lhs._month == rhs._month) {
			if (lhs._day < rhs._day) {
				return true;
			}
			else {
				return false;
			}
		}
	}
	return false;
}

bool operator>(const Date &lhs, const Date &rhs) {
	return rhs < lhs;
}

bool operator==(const Date &lhs, const Date &rhs) {
	if(lhs._era == rhs._era)
		if (lhs._year == rhs._year)
			if (lhs._month == rhs._month)
				if (lhs._day == rhs._day)
					return true;
	return false;
}

bool operator>=(const Date &lhs, const Date &rhs) {
	return (lhs > rhs && lhs == rhs);
}

bool operator<=(const Date &lhs, const Date &rhs) {
	return (lhs < rhs && lhs == rhs);
}

bool operator!=(const Date &lhs, const Date &rhs) {
	return !(lhs == rhs);
}


Date DaysToDate(int days)
{
	Date temp;


	if (days <= 0)
		temp._era = 1;

	days = abs(days);
	for (temp._year = 1; days > 365; temp._year++)
	{
		days = days - 365 - temp.IsLeap();
	}
	temp._vis = temp.IsLeap();
	int i;

	if (temp._era)
	{
		for (i = 11; days >= Date::MonthCycle[temp._vis][i]; i--)
		{
			days = days - Date::MonthCycle[temp._vis][i];
		}
		days = Date::MonthCycle[temp._vis][i] - days;
	}

	else
	{
		for (i = 0; days > Date::MonthCycle[temp._vis][i]; i++)
		{
			days = days - Date::MonthCycle[temp._vis][i];
		}
	}

	temp._month = i + 1;
	temp._day = days;
	return temp;


}

int operator-(const Date &lhs, const Date &rhs) {
	return (lhs.days() - rhs.days());
}
Date operator+(const Date& lhs, int days) {
	return DaysToDate(lhs.days() + days);
}
Date operator-(const Date& lhs, int days) {
	return DaysToDate(lhs.days() - days);
}

Date StringToDate(CString& str) {
	int pos = 0;
	const CString SEPARATORS = _T("/ ");

	int day = wcstol(str.Tokenize(SEPARATORS, pos), 0, 10);
	int month = wcstol(str.Tokenize(SEPARATORS, pos), 0, 10);
	int year = wcstol(str.Tokenize(SEPARATORS, pos), 0, 10);
	bool era = (str.Tokenize(SEPARATORS, pos) == _T("BC"));
	return Date(day, month, year, era);
}

CString Date::to_string() const {
	CString str;
	str.Format(_T("%0.2i/%0.2i/%0.4i"), _day, _month, _year);
	if (_era)
		str += _T(" BC");
	return str;
}