//
// Created by dmitr on 4/23/2018.
//

#ifndef PRACTICE_TASK_1_CLASSES_COUNTER_H
#define PRACTICE_TASK_1_CLASSES_COUNTER_H

#include <string>
#include <vector>
#include <exception>
#include <iostream>
#define EMPTY_LINE L""




class Counter {
private:
	std::vector<std::wstring> src_;
	std::vector<std::wstring>::size_type current_word_;
	bool state_;
public:
	Counter() : src_(), current_word_(), state_(false) {}
	~Counter() = default;
	Counter(const std::wstring &str);
	Counter(const Counter &counter) : src_(counter.src_), current_word_(counter.current_word_), state_(false) {}
	Counter &operator=(const Counter &counter);
	Counter &operator=(const std::wstring &str);

	std::wstring nextWord();
	bool eoc() const { return state_; }
	std::vector<std::wstring>::size_type size() const { return src_.size(); };
	void restart();
};

class CounterList {
private:
	std::vector<Counter> _vec;
public:
	CounterList() = default;
	CounterList(const CounterList & list) : _vec(list._vec) {}
	CounterList & operator=(const CounterList & list);

	void loadFromFile(const std::string &path);
	const Counter & getRandomCounter() const;

	class WrongPathException : std::exception {};
	class GetRandomException : std::exception {};
	/*void out() {
	for(int i = 0; i < _vec.size(); i++)
	std::cout << _vec[i].getSource() << std::endl;
	}*/
};

/*
class Student {
private:
std::string name;
SPicture _photo;
};

class StudentList {
private:
std::forward_list<Student> _clst;
public:
//
void Add();
void Remove();
void Start();
void Next();
size_t size();

};

class SPicture {
private:
std::string _name;
};

class MusicFile {

};

class CounterManager {
private:
Counter _str;
StudentList _slst;
public:
Student Count();
};
*/
#endif //PRACTICE_TASK_1_CLASSES_COUNTER_H
