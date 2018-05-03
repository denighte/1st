//
// Created by dmitr on 4/23/2018.
//
#include "stdafx.h"
#include "Counter.h"
#include <fstream>
#include <ctime>
#include <random>

#include <locale>
#include <codecvt>
#define WORD_SEPARATORS L"-,.!? "
void SplitToVector(std::vector<std::wstring> &v, const std::wstring &src, const std::wstring &dlm);


Counter & Counter::operator=(const Counter &counter) {
	src_ = counter.src_;
	current_word_ = counter.current_word_;
	state_ = counter.state_;
	return *this;
}
Counter & Counter::operator=(const std::wstring &str) {
	SplitToVector(src_, str, WORD_SEPARATORS);
	current_word_ = 0;
	state_ = false;
	return *this;
}

Counter::Counter(const std::wstring &str) : current_word_(0), state_(false) {
	SplitToVector(src_, str, WORD_SEPARATORS);
}

std::wstring Counter::nextWord() {
	if (current_word_ + 1 == src_.size())
		state_ = true;
	return src_.at(current_word_++);
}

void Counter::restart() {
	current_word_ = 0;
	state_ = false;
}

CounterList& CounterList::operator=(const CounterList &list) {
	_vec = list._vec;
	return *this;
}

void CounterList::loadFromFile(const std::wstring &path) {

	std::locale ru("rus_rus.1251");

	std::wofstream ofile(path);


	ofile.imbue(ru);


	ofile << L"Эники - беники ели вареники Эники - беники - клёц!Вышел весёлый матрос." << std::endl;
	ofile << L"Кони, кони, кони, кони, Мы сидели на балконе.Чай пили, чашки били, По - турецки говорили." << std::endl;
	ofile << L"Мишка косолапый по лесу идёт, Шишки собирает, песенку поёт.Шишка отлетела — прямо Мишке в лоб! Мишка рассердился и ногою — топ!" << std::endl;
	ofile.close();

	std::wifstream file(path);
	if (!file.is_open())
		throw WrongPathException();

	file.imbue(ru);

	std::wstring buffer;
	while (std::getline(file, buffer)) {
		if (buffer != EMPTY_LINE)
			_vec.push_back(Counter(buffer));
	}
	file.close();
}

const Counter & CounterList::getRandomCounter() const {
	if (_vec.size() == 0)
		throw GetRandomException();
	//std::random_device rd;  //Will be used to obtain a seed for the random number engine
	//std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	//std::uniform_int_distribution<> dis(0, _vec.size());
	std::srand(std::time(0));
	std::vector<Counter>::size_type number = static_cast<int>(std::abs(std::rand()) % _vec.size());
	return _vec.at(number);
}

void SplitToVector(std::vector<std::wstring> &v, const std::wstring &src, const std::wstring &dlm) {
	std::wstring::size_type p, start = 0, len = src.length();

	v.clear();
	start = src.find_first_not_of(dlm);
	p = src.find_first_of(dlm, start);
	while (p != std::wstring::npos) {
		v.push_back(src.substr(start, p - start));
		start = src.find_first_not_of(dlm, p);
		p = src.find_first_of(dlm, start);
	}
	if (len>start)//rest
		v.push_back(src.substr(start, len - start));
}
