#include <iostream>
#include "dllist.h"

using namespace std;

void test() {
    //int
    dllist<int> dll;
    
    dll.push(1);
    dll.push(2);
    dll.push(3);
    
    dllist<int> dllCopy = dll;
    
    dllCopy.push(4);
    dllCopy.remove(1);
    dllCopy.remove(0);
    dllCopy.insert(5, 1);
    
    dll.print();
    dllCopy.print();
    
    dll = dllCopy;
    dll.print();
    cout << dll.at(dll.size()-3) <<endl;

    //string
    dllist<string> dlls;
    
    dlls.push("bugs");
    dlls.push("were");
    dlls.push("pain");
    
    dllist<string> dllsc = dlls;
    
    dllsc.push("life");
    dllsc.remove(1);
    dllsc.remove(0);
    dllsc.insert("is", 1);
    
    dlls.print();
    dllsc.print();
    
    dlls = dllsc;
    dlls.print();
    cout << dlls.at(dlls.size()-3) <<endl;
}

int main(){
    test();
    
    return 0;
}