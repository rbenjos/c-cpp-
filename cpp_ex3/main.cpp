#include <iostream>
#include "HashMap.hpp"
#include <string>

using namespace std;
int main1()
{
    HashMap<int,char> h;
    cout << "\n";

    // test insertion/deletion
    cout << h.insert(2,'a');
    cout << h.insert(2,'a');
    h.insert(34,'b');
    h.insert(18,'e');
    h.insert(32,'e');
    h.insert(15,'e');
    h.insert(3,'a');
    h.insert(13,'b');
    h.insert(213,'e');
    h.insert(345,'e');
    h.insert(143,'e');
    h.printMap();


//    cout<<h.erase(2);
//    cout<<h.erase(34);
//    cout<<h.erase(2);
//    cout<<h.erase(34);
//    h.printMap();
//    h.erase(18);
//    h.erase(32);
//    h.erase(15);
//    h.erase(3);
//    h.erase(13);
//    h.erase(213);
//    h.erase(345);
//    h.erase(143);
//    h.printMap();

//
//    // test [] and at
//    h.insert(2,'a');
//    h.at(2) = 'b';
//
//
//    h[18] = 'b';
//    h[18] = 'c';
//    h[34] = 'e';
//    h[234] = 'w';
//    h[534] = 'e';
//    h[43] = 'd';
//    h[12] = 'x';
//    h[1] = 'q';
//    h[54] = 'v';
//
//    cout <<h[18] << "\n";
//    cout <<h[34] << "\n";
//    cout <<h[234] << "\n";
//    cout <<h[534] << "\n";
//    cout <<h[43] << "\n";
//    cout <<h[12] << "\n";
//
//    cout << "\n";
//
//    cout <<h.at(18) << "\n";
//    cout <<h.at(34) << "\n";
//    cout <<h.at(234) << "\n";
//    cout <<h.at(534) << "\n";
//    cout <<h.at(43) << "\n";
//    cout <<h.at(12) << "\n";




//    h.printMap();

// test iterator

    cout<< "starting to iterate\n";
    HashMap<int,char>::iterator iter;
    iter = h.begin();
    while(iter != h.end() )
    {
        cout << (*iter).first <<","<< (*iter).second <<" \n";
        ++iter;
    }


}