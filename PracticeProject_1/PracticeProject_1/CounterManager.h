//
// Created by dmitr on 4/27/2018.
//

#ifndef PRACTICE_TASK_1_CLASSES_COUNTERMANAGER_H
#define PRACTICE_TASK_1_CLASSES_COUNTERMANAGER_H


#include "Counter.h"
#include "CycleList.h"
#define  FIRST_COUNTER_START L"id1723451"

class SPicture {
private:
	int id_;
public:
	explicit SPicture(int a) : id_(a) {}
	int id() const { return id_; }
	void selectImage() {}
};

class Student {
private:
	std::wstring name_;
	int id_;
	SPicture img_;
public:
	Student() : name_(EMPTY_LINE), id_(0), img_(0) {}
	Student(const std::wstring &name, int id, const SPicture &img) : name_(name), id_(id), img_(img) {}
	const std::wstring & name() const { return name_; }
	int id() const { return id_; }
};

class CounterManager {
private:
	Counter str_;
	CycleList<Student> &student_lst_;

	std::wstring current_word_;
	CycleList<Student>::iterator current_student_;

	bool game_state_;
	bool counter_state_;
public:
	CounterManager(const Counter &str, CycleList<Student> &lst) : str_(str), student_lst_(lst), current_word_(FIRST_COUNTER_START),
		game_state_(false), counter_state_(false), current_student_(student_lst_.begin()) {};
	Student NextCount();
	const std::wstring &CurrentWord() const { return current_word_; }
	bool eoc() const { return counter_state_; }
	bool eog() const { return game_state_; }
};


#endif //PRACTICE_TASK_1_CLASSES_COUNTERMANAGER_H
