#include <iostream>
#include <vector>

using namespace std;

int optCheck(int min, int max);

class Employee {
    private:
    string empname;
    string title;
    double hourwage;

    public:
    Employee () {
        this-> empname = "Generic Joe";
        this-> title = "Rat";
        this-> hourwage = 5;
    }
    Employee (string empname, string title, double hourwage) {
        this-> empname = empname;
        this-> title = title;
        if (hourwage >= 0) this-> hourwage = hourwage;
        else this-> hourwage = 0;
    }

    void setWages(double wages) {
        if (wages >= 0) hourwage = wages;
        else {
            cout <<"\nCapitalism does not work this way."<<endl;
            hourwage = 0;
        }
    }

    Employee operator+(Employee const & obj) {
        Employee superemp = Employee();
        superemp.empname = empname+" "+obj.empname;
        superemp.title = title+" "+obj.title;
        superemp.hourwage = hourwage+obj.hourwage;
        return superemp;
    }

    string getName() const{
        return empname;
    }
    string getTitle() const{
        return title;
    }
    double getWages() const{
        return hourwage;
    }
};

int main() {
    vector<Employee> employees;
    employees.push_back(Employee("Sampon Sassypants", "Chief Executive Janitor", 10000.99));
    employees.push_back(Employee("Jameson Jacksonsmith", "Superior Volunteer", 0));
    employees.push_back(Employee("Shannon Sunshoestarter", "Secratary Of State", 9));
    employees.push_back(Employee("Isabella Iglesias", "Assistant Secratary Of State", 9.15));
    employees.push_back(Employee("Sam Shue", "Untenured Professor", 44.99));
    employees.push_back(Employee("Minwage Marcus", "Slave", -5.82));

    cout <<"\nGreetings user, this is the employee database. Since we have no security, anyone is allowed to access/change it by entering in the enumerated value associated with the desired option! You're welcome!"<<endl;
    Employee super = employees.at(1) + employees.at(5);
    cout <<"Name: "<<super.getName()<<"   Title: "<<super.getTitle()<<"   Hourly Wage: $"<<super.getWages()<<endl;

    bool exit = false;
    do {
        cout <<"\nWhat do you want to do?"<<endl;
        cout <<"1) Print list of employees\n2) Calculate total wages\n3) Exit application"<<endl;
        switch (optCheck(1,3)) {
            case 1:
                for (Employee emp: employees)
                    cout <<"Name: "<<emp.getName()<<"   Title: "<<emp.getTitle()<<"   Hourly Wage: $"<<emp.getWages()<<endl;
                break;
            case 2: {
                double sumwage = 0;
                for (Employee emp: employees) sumwage += emp.getWages();
                cout <<"Total Wages: "<<sumwage;
            }
                break;
            case 3:
                exit = true;
        }
    } while(!exit);
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