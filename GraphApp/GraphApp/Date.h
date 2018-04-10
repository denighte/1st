#pragma once
#include "stdafx.h"
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <iomanip>

using namespace std;

class Date {
	int _day;
	int _month;
	int _year;
	bool _era; //0 - our era, 1 - BC
	bool _vis;
	static int MonthCycle[2][12]; //= { {31,28,31,30,31,30,31,31,30,31,30,31},{31,29,31,30,31,30,31,31,30,31,30,31} };
public:
	Date();
	Date(int day, int month, int year, bool era = 0); //0 - our era, 1 - BC
	Date(const Date &a);
	Date &operator=(const Date &a);

	void setDay(int day) { _day = day; }
	int getDay() { return _day; }
	void setMonth(int m) { _month = m; }
	int getMonth() { return _month; }
	void setYear(int year) { _year = year; _era = (_year > 0) ? false : true; }
	int getYear() { return _year; }

	friend Date operator+(const Date& lhs, int days);
	friend Date operator-(const Date& lhs, int days);

	friend int operator-(const Date &lhs, const Date &rhs);

	friend bool operator==(const Date &lhs, const Date &rhs);
	friend bool operator!=(const Date &lhs, const Date &rhs);
	friend bool operator<(const Date &lhs, const Date &rhs);
	friend bool operator<=(const Date &lhs, const Date &rhs);
	friend bool operator>(const Date &lhs, const Date &rhs);
	friend bool operator>=(const Date &lhs, const Date &rhs);

	CString to_string() const;
	friend Date StringToDate(CString& str);

	friend Date DaysToDate(int days);//convert days to Date
	bool IsLeap(); //checks, if the year is Leap
	int days() const; //convert Date to days
	~Date() {}
};