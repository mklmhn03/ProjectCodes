// Write a Fraction class that represents fractional numbers
// The class has a default constructor, and a two argument constructor
// Getters for numerator and denominator
// Add method that adds an input fraction

#include <iostream>

using namespace std;

class Fraction {
private:
    int _num;
    int _denom;
public:
    Fraction();
    Fraction(int num, int denom);
    int getNum();
    int getDenom();
    void add(Fraction f);
};

Fraction::Fraction() {
    _num = 0;
    _denom = 1;
}

Fraction::Fraction(int num, int denom) {
    _num = num;
    _denom = denom;
}

int Fraction::getNum() {
    return _num;
}

int Fraction::getDenom() {
    return _denom;
}

void Fraction::add(Fraction f) {
    if (f.getDenom() == _denom) {
        _num += f.getNum();
    }
    else {
        _num = _num*f.getDenom() + f.getNum()*_denom;
        _denom *= f.getDenom();
    }
}

// Test
int main() {
    Fraction f1; // Sets numerator to 0 and denominator to 1
    Fraction f2(1, 2);
    Fraction f3(1, 4);
    f2.add(f3);
    cout << f2.getNum() << "/" << f2.getDenom() << endl; // Should print 6/8
}