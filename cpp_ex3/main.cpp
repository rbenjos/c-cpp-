#include <iostream>
#include "HashMap.hpp"

using namespace std;
int main()
{
    HashMap<int,char> h;
    cout << h.capacity() << "\n";
    cout << h.size() << "\n";
    cout << h.loadfactor()<< "\n";
    h.insert(2,'a');
    h.insert(34,'b');
    h.insert(18,'e');
    h.insert(32,'e');
    h.insert(15,'e');
    h.insert(3,'a');
    h.insert(13,'b');
    h.insert(213,'e');
    h.insert(345,'e');
    h.insert(143,'e');

    h.erase(2);
//    h.erase(34);
//    h.erase(18);
//    h.erase(32);


   
    h.printMap();

}