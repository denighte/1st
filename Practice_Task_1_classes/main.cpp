#include <iostream>
#include <cstdlib>

#include "counter.h"
#include "CycleList.h"
#include "CounterManager.h"
#include <forward_list>
#include <regex>
/*int main() {
    setlocale (LC_ALL,"Rus");
    Counter cnt("Hush, mouse, cat on the roof");
    CounterList a;
    a.loadFromFile("D:\\Development\\Cfile.txt");
    // a.out();
    //std::cout << a.getRandomCounter().getSource();

    for(std::string s = cnt.nextWord(); s != ""; s = cnt.nextWord())
        std::cout << s << std::endl;
    system("pause");
    return 0;
}*/



int main() {
    CycleList<Student> a;
    Counter cnt(L"Hush, mouse, cat on the roof");
    a.push_front(Student(std::wstring(L"stud_1"), 0, SPicture(1)));
    a.push_front(Student(std::wstring(L"stud_2"), 1, SPicture(2)));
    a.push_front(Student(std::wstring(L"stud_3"), 2, SPicture(3)));
    a.push_front(Student(std::wstring(L"stud_4"), 3, SPicture(4)));

    CounterManager manager(cnt, a);

    //CounterManager manager;
    //manager.Init(cnt, a);


    while (!manager.eog()) {
        Student participant = manager.NextCount();
        std::wcout << participant.name() << std::endl;
    }



    return 0;
}

/*int main() {
    CycleList<int> b;
    b.push_front(5);
    b.push_front(6);
    b.push_front(7);
    b.push_front(8);
    b.erase(CycleList<int>::iterator(b.begin()));
    b.clear();

    int j = 0;
    for(CycleList<int>::iterator it = b.begin(); j != 3; ++it, ++j)
        std::cout << *it << std::endl;

    return 0;

}*/