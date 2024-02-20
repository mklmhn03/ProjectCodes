#ifndef FOOD
#define FOOD

#include <iostream>
#include <vector>

using namespace std;

class Food {
    private:
    string name;
    double calories;
    double totfat;
    double totsugar;
    double protein;
    double sodium;

    public:
    Food () {
        this-> name = "";
        this-> calories = 0;
        this-> totfat = 0;
        this-> totsugar = 0;
        this-> protein = 0;
        this-> sodium = 0;
    }
    Food (string name, double calories, double totfat, double totsugar, double protein, double sodium) {
        this-> name = name;
        this-> calories = max(calories,0.0);
        this-> totfat = max(totfat,0.0);
        this-> totsugar = max(totsugar,0.0);
        this-> protein = max(protein,0.0);
        this-> sodium = max(sodium,0.0);
    }

    Food operator+(const Food & obj) {
        Food superfood = Food();
        if (name == "") superfood.name = obj.name;
        else superfood.name = name+" & "+obj.name;
        superfood.calories = calories+obj.calories;
        superfood.totfat = totfat+obj.totfat;
        superfood.totsugar = totsugar+obj.totsugar;
        superfood.protein = protein+obj.protein;
        superfood.sodium = sodium+obj.sodium;
        return superfood;
    }
    friend ostream &operator<<(ostream& os, const Food & s);
    
    string getName() const{
        return name;
    }
    double getCalories() const{
        return calories;
    }
    double getFat() const{
        return totfat;
    }
    double getSugar() const{
        return totsugar;
    }
    double getProtein() const{
        return protein;
    }
    double getSodium() const{
        return sodium;
    }
};

ostream& operator << (ostream &os, const Food &s) {
    return (os <<"Name: "<<s.name<<"\nCalories: "<<s.calories<<"\nTotal Fat: "<<s.totfat<<" g\nTotal Sugar: "<<s.totsugar<<" g\nProtein: "<<s.protein<<" g\nSodium: "<<s.sodium<<" mg"<<endl);
}

#endif //FOOD