#include <iostream>
#include <cstdlib>

#include "counter.h"
#include "flist.h"
#include <forward_list>
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
    CycleList<int> a;
    //a.push_front(5);
    //a.erase(a.begin());
    for (CycleList<int>::iterator i(a.begin()); i != a.last(); i++) {
        std::cout << *i << std::endl;
    }

    /*std::forward_list<int> b;
    b.push_front(5);
    b.push_front(6);
    b.push_front(7);
    for(std::forward_list<int>::iterator it = b.begin(); it != b.last(); it++) {
        std::cout << *it << std::endl;
    }*/
    return 0;
}