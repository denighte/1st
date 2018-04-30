//
// Created by dmitr on 4/27/2018.
//

#include <random>
#include <ctime>
#include "CounterManager.h"
CycleList<Student>::iterator getRandomStudent(CycleList<Student> &lst);

Student CounterManager::NextCount() {
    if(student_lst_.length() == 1) {  //search fow winner, if number of the participants > 1 then choose 1 loser
        game_state_ = true;
        return (*student_lst_.begin());
    }

    if(current_word_ == FIRST_COUNTER_START) {
        current_student_ = getRandomStudent(student_lst_);  //choose random student
        current_word_= str_.nextWord(); //make a count
        return *current_student_;
    }

    current_word_ = str_.nextWord(); //make a count


    if(current_word_ == EMPTY_LINE) {  //in case the count was over
        counter_state_ = true;
        student_lst_.erase(current_student_);  //delete loser
        CycleList<Student>::iterator current_student_ = getRandomStudent(student_lst_);  //choose random student
        str_.restart(); //restart counter
        return *current_student_;
    }

    counter_state_ = false;
    ++current_student_;  //find the next student
    return *current_student_;
}


CycleList<Student>::iterator getRandomStudent(CycleList<Student> &lst) {
    std::srand(std::time(0));
    int number = (lst.length() != 0) ? (std::rand() % lst.length()) : (0);
    CycleList<Student>::iterator it(lst.begin());
    for(int j = 0; j != number; ++j, ++it);
    return it;
}
