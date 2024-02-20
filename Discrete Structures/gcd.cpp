//Mukul Mohan

#include <iostream>
using namespace std;


int gcd(int a, int b) {
    a = abs(a);
    b = abs(b);
    if (b>a) {
        int r1 = b;
        b = a;
        a = r1;
    }
    while (b != 0) {
        int r1 = b;
        b = a%b;
        a = r1;
    }
    return a;
}

void backsub(int a, int b) {
    int g = gcd(a,b);
    int ac = a; int bc = b;
    int r, q, u1 = 1, u2 = 0, v1 = 0, v2 = 1;

    while (bc != 0) {
        q = ac/bc;
        r = ac%bc;
        ac = bc;
        bc = r;

        int temp = u2;
        u2 = u1 - q * u2;
        u1 = temp;

        temp = v2;
        v2 = v1-q*v2;
        v1 = temp;
    }
    cout <<"The linear combination of "<<a<<" and "<<b<<" is: "<<a<<"*"<<u1<<" + "<<b<<"*"<<v1<<" = "<<g<<endl;
}

int main() {
    //Input a and b to get the gcd
    cout<<"Please input a."<<endl;
    int a = -125;
    int b = 200;
    cin >>a;
    cout<<"Please input b."<<endl;
    cin >>b;
    cout <<"The gcd of "<<a<<" and "<<b<<" is: "<<gcd(a,b)<<endl;

    //Extra Credit
    backsub(a,b);
    
    return 0;
}