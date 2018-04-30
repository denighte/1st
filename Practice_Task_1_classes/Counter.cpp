//
// Created by dmitr on 4/23/2018.
//

#include "Counter.h"
#include <fstream>
#include <ctime>
#include <random>
#define WORD_SEPARATORS L"-,. "


Counter & Counter::operator=(const Counter &counter) {
    _src = counter._src;
    _start = counter._start;
    _end = counter._end;
    return *this;
}
Counter & Counter::operator=(const std::wstring &str) {
    _src = str;
    _start = 0;
    _end = 0;
    return *this;
}

void Counter::setCounter(const std::wstring &str) {
    _src = str;
    _start = 0;
    _end = 0;
}

std::wstring Counter::nextWord() {
    _start = _src.find_first_not_of(WORD_SEPARATORS, _end);
    _end = _src.find_first_of(WORD_SEPARATORS, _start);

    if (_end != std::string::npos) {
        std::wstring word = _src.substr(_start, _end - _start);
        return word;
    } else if (_src.length() > _start) {
        return _src.substr(_start);
    } else {
        return std::wstring(EMPTY_LINE);
    }
}

void Counter::restart() {
    _start = 0;
    _end = 0;
}

CounterList& CounterList::operator=(const CounterList &list) {
    _vec = list._vec;
    return *this;
}

void CounterList::loadFromFile(const std::string &path) {
    std::wifstream file(path);
    if(!file.is_open())
        throw WrongPathException();

    std::wstring buffer;
    while(std::getline(file, buffer)) {
        if(buffer != EMPTY_LINE)
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
    std::vector<Counter>::size_type number = abs(std::rand() % _vec.size() - 1);
    return _vec.at(number);
}