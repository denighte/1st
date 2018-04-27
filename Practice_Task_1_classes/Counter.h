//
// Created by dmitr on 4/23/2018.
//

#ifndef PRACTICE_TASK_1_CLASSES_COUNTER_H
#define PRACTICE_TASK_1_CLASSES_COUNTER_H

#include <string>
#include <vector>
#include <exception>
#include <iostream>

#define DEBUG



class Counter {
private:
    std::string _src;
    std::string::size_type _start;
    std::string::size_type _end;
public:
    Counter() : _src() {}
    ~Counter() = default;
    Counter(const std::string &str) : _src(str), _start(0), _end(0) {}
    Counter(const Counter &counter) : _src(counter._src), _start(counter._start), _end(counter._end) {}
    Counter &operator=(const Counter &counter);
    Counter &operator=(const std::string &str);

    void setCounter(const std::string &str);
    const std::string & getSource() const { return _src; };

    std::string nextWord();
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
    void out() {
        for(int i = 0; i < _vec.size(); i++)
            std::cout << _vec[i].getSource() << std::endl;
    }
};

/*
class Student {
private:
    std::string name;
    Picture _photo;
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

class Picture {
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
