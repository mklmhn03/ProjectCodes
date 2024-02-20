//Mukul Mohan

#include <iostream>
#include <vector>

using namespace std;

//Collatz Sequence
int col(long long term) {
    if (term<1) return 0;
    int count = 1;
    while (term != 1) {
        if (term%2 == 0) term /= 2;
        else term = 3*term+1;
        ++count;
    }
    return count;
}

//returns term with the highest length in range
int colrng(int max) {
    int ans = 0; int res = 0;
    for (int i = 1; i<=max; i++) {
        long long term = i;
        int count = 1;
        while (term > 1) {
            if (term%2 == 0) term /= 2;
            else term = 3*term+1;
            ++count;
        }
        if (count>ans) {
            ans = count;
            res = i;
        }
    }
    return res;
}

int main() {
    //Input term to get length
    cout<<"Please input the initial positive integer term of the Collatz Sequence."<<endl;
    int a = 13;
    cin >>a;
    cout <<"The term length is: "<<col(a)<<endl;

    //Extra Credit
    int ans = colrng(1000000);
    cout <<"\nThe initial term for the longest sequence 1<a<10^6: "<<ans<<endl;
    cout <<"The length of the longest sequence in that range: "<<col(ans)<<endl;
    
    return 0;
}