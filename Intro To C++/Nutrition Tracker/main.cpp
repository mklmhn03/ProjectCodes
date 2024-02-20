#include <iostream>
#include <vector>
#include <Food.h>

using namespace std;

int optCheck(int min, int max);

int main() {
    Food avg = Food("Avg", 2000, 70, 30, 50, 2300);
    vector<Food> items;
    items.push_back(Food("Grubs", 600, 90, 5.7, 70, 100));
    items.push_back(Food("Apple", 95, 0, 9, 1, 2));
    items.push_back(Food("Rock", 0, 0, 0, 0, 511.23));
    items.push_back(Food("Pie", 200, 5, 15, 7, 156));
    items.push_back(Food("Water", 0, 0, 0, 0, 0.01));
    items.push_back(Food("Tacocat", 230, 20, 2, 30, 210));
    items.push_back(Food("Cereal", 100, 2, 13, 1, 20));
    items.push_back(Food("Bear", 400, 300, 3.5, 80, 118));
    items.push_back(Food("Bark", 75, 7, 7, 1, 300));
    items.push_back(Food("Cheese", 420, 38, 0.5, 7, 174));
    items.push_back(Food("Carpet", 1, 0, 0, 0, 20));
    items.push_back(Food("Quick-Dry Cement", 80, 16, 19, 6, 850));

//description
    cout <<"\nGreetings user, this is the Nutrition Tracker. We are here to help you track your nutrition and stay healthy!\nDISCLAIMER: This tracker is not reccomended by 99.9% of nutritionists because it is not accurate and it may be a detriment to your health. Use at your own risk.\n\nPlease continue by entering in the enumerated value associated with the desired option! :)"<<endl;
    
    Food total = Food();
    bool exit = false;
    do {
        cout <<"\nPick any food from our variety!"<<endl;
        for (int i = 1; i<items.size()+1; i++) {
            cout <<i<<") "<<items.at(i-1).getName()<<endl;
        }
        cout <<items.size()+1<<") I'm done selecting (exit)"<<endl;
        
        int choice = optCheck(1,items.size()+1)-1;
        if (choice == items.size()) exit = true;
        else {
            cout <<items.at(choice);
            total = total + items.at(choice);
            //items.erase(items.begin()+choice);
        }
    } while(!exit);

    cout <<"\nThank you for using our program. Here is your total!\n"<<total<<endl;
    cout <<"Here is the daily nutrition intake for the average adult certified by Dr. Shue:\n"<<avg<<endl;
    int j = 0;
    if (total.getCalories()>avg.getCalories()) cout <<++j<<") You have exceeded Dr. Shue's reccomended calorie intake."<<endl;
    if (total.getFat()>avg.getFat()) cout <<++j<<") You have exceeded Dr. Shue's reccomended fat intake."<<endl;
    if (total.getSugar()>avg.getSugar()) cout <<++j<<") You have exceeded Dr. Shue's reccomended sugar intake."<<endl;
    if (total.getProtein()>avg.getProtein()) cout <<++j<<") You have exceeded Dr. Shue's reccomended protein intake."<<endl;
    if (total.getSodium()>avg.getSodium()) cout <<++j<<") You have exceeded Dr. Shue's reccomended sodium intake."<<endl;
    if (j) cout <<"Sprint "<<j*17<<" miles to avoid spontaneous expiration."<<endl;

    cout <<"\nThat's all for now. Please use this tracker again! (it is not reccomended that you consume carpets)"<<endl;
}

bool numCheck(string s) { //checks if a string is comprised of integers
    for (int i = 0; i < s.length(); i++)
        if (!isdigit(s[i])) return false;
    return true;
}
int optCheck(int min, int max) { //checks if input is an integer between min and max
    string s;
    int opt;
    while (!numCheck(s) || !(opt >= min && opt <= max)) { //this code basically prevents invalid inputs
        cout <<"Select a valid option number."<<endl;
        cin >> s;
        if (numCheck(s)) opt = stoi(s);
    }
    return opt;
}