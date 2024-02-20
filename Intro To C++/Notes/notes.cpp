#include <iostream>
#include <vector>
#include "slist.h"
using namespace std;


class myvector{
    public:
    myvector(){
        idx = 0;
        size = 3;
        int a[3];
        void push_back(int x) {
            if (++idx > size) {
                size +=3;
                int a[size];
            }
        }
    }
}
void foi(int& z) { //pass by reference
    z = 10;
}
void foi2(int* z) { //pointer to z
    *z = 10;
}

int main() {
    int x = 500;
    char c = 'A';

    int* p = &x; //saving address of x to pointer p (& gives )
    cout <<*p<<"\n"<<endl;

    //& returns the memory location of the thing after it.
    //pointer needs a type to know how many bytes to look at (char needs only one while int needs 4)
    //pointer is a data type that stores memory addresses
    //pointer can hold 64 bits of memory locations

    int a[3]; //just a collection of pointers
    a[2] = 6;
    int b = 2;
    int d = 5;
    cout <<a[2]<<endl;
    cout <<*(a+2)<<endl;
    cout <<(a+2)<<endl;
    cout <<*(a-8)<<endl; //accessing memory that is not part of array
    cout <<a[-8]<<endl; //accessing memory that is not part of array
}