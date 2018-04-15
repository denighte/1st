#pragma once
#include "Date.h"
class Time : public Date {
private:
	int _hour;
	int _min;
	int _sec;
public:
	Time();
	Time(int hour, int minute, int second);
	Time(int hour, int minute, int second, int day, int month, int year, bool era = false);
	Time(const Time& t);
	Time& operator=(const Time& t);

	int getHour() const { return _hour; }
	int getMin() const { return _min; }
	int getSec() const { return _sec; }

	friend bool operator<(const Time & lhs, const Time & rhs);
	friend bool operator>(const Time & lhs, const Time & rhs);
	friend bool operator==(const Time & lhs, const Time & rhs);
	friend bool operator!=(const Time & lhs, const Time & rhs);
	friend bool operator<=(const Time & lhs, const Time & rhs);
	friend bool operator>=(const Time & lhs, const Time & rhs);

};