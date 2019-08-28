#include<iostream>
using namespace std;

int foo(int a, int b = 4, int c = 2)

{

    cout<< ++a * ++b * --c ;

    return 0;

} int main()

{

    foo(6, 0, 0);

    return 0;

}