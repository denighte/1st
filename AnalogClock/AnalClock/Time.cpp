#include "stdafx.h"
#include "Time.h"
Time::Time() {
	time_t t = time(NULL);
	struct tm tm;
	localtime_s(&tm, &t);
	_hour = tm.tm_hour;
	_min = tm.tm_min;
	_sec = tm.tm_sec;
}

Time::Time(int hour, int minute, int second) : _hour(hour), _min(minute), _sec(second) {}
Time::Time(int hour, int minute, int second, int day, int month, int year, bool era) : Date(day, month, year, era), _hour(hour), _min(minute), _sec(second) {}
Time::Time(const Time& t) : Date(t), _hour(t._hour), _min(t._min), _sec(t._sec) {}

Time& Time::operator=(const Time& t) {
	Date::operator=(t);
	_hour = t._hour;
	_min = t._min;
	_sec = t._sec;
	return *this;
}

bool operator<(const Time& lhs, const Time& rhs) {
	if (static_cast<const Date&>(lhs) < static_cast<const Date&>(rhs))
		return true;
	else if (static_cast<const Date&>(lhs) == static_cast<const Date&>(rhs)) {
		if (lhs._hour < rhs._hour)
			return true;
		else if (lhs._hour == rhs._hour) {
			if (lhs._min < rhs._min)
				return true;
			else if (lhs._min == rhs._min) {
				if (lhs._sec < rhs._sec)
					return true;
				else
					return false;
			}
		}
	}
	return false;
}

bool operator==(const Time& lhs, const Time& rhs) {
	if (static_cast<const Date&>(lhs) == static_cast<const Date&>(rhs))
		if (lhs._hour == rhs._hour)
			if (lhs._min == rhs._min)
				if (lhs._sec == rhs._sec)
					return true;
	return false;
}

bool operator>(const Time & lhs, const Time & rhs) {
	return rhs < lhs;
}
bool operator!=(const Time & lhs, const Time & rhs) {
	return !(lhs == rhs);
}
bool operator<=(const Time & lhs, const Time & rhs) {
	return (lhs < rhs || lhs == rhs);
}
bool operator>=(const Time & lhs, const Time & rhs) {
	return (lhs > rhs || lhs == rhs);
}
