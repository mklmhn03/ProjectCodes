#include <iostream>
#include <vector>
#include <cmath>

using namespace std;


const int stops = 5; //# of locations you want to travel to (cannot be <1 or greater than optns)
const double rad = 3958.8; //Earth's radius in miles
const double speed = 500.0; //Plane's speed in mph
//can also use define instead of const


double haversine(double lat1, double long1, double lat2, double long2, double radius);

double getFlightTime(double lat1, double long1, double lat2, double long2);

bool numCheck(string s);
int optCheck(int min, int max);


int main() {
    // vector of struct locations
    struct loc {string place; double lat; double lon;};
    vector<loc> opts;

    opts.push_back({"Bowling Green, KY, USA",36.976524,-86.456017});
    opts.push_back({"Fargo, ND, USA",46.877186,-96.789803});
    opts.push_back({"Miami Beach, FL, USA",25.793449,-80.139198});
    opts.push_back({"Idaho City, ID, USA",43.828850,-115.837860});
    opts.push_back({"Sioux City, IA, USA",42.495132,-96.400070});
    opts.push_back({"Valparaiso, IN, USA",41.483845,-87.063965});
    opts.push_back({"Delray Beach, FL, USA",26.459763,-80.105545});
    opts.push_back({"Atlantic City, NJ, USA",39.370121,-74.438942});
    opts.push_back({"Crossett, AR, USA",33.132671,-91.971634});
    opts.push_back({"Merced, CA, USA",37.325954,-120.499992});
    opts.push_back({"Fairfield, IA, USA",41.006950,-91.973419});
    opts.push_back({"New Castle, DE, USA",39.668564,-75.586189});

    loc locs[stops];
    for (int d = 0; d<stops; d++) {
        string st = "destination";
        if (d==0) st = "departure location";
        cout <<"\nGreetings unidentified flying user. Please select a "<<st<<" by entering in the enumerated value associated with the desired location."<<endl;
        for (int i = 0; i < opts.size(); i++)
            cout <<i+1<<")\t"<<opts.at(i).place<<"\t\tLat: "<<opts.at(i).lat<<" Long: "<<opts.at(i).lon<<endl;

        int choice = optCheck(1,opts.size())-1;
        locs[d] = opts[choice];
        opts.erase(opts.begin()+choice);
    }

    cout <<"\nUnidentified flying user, your chosen locations are:"<<endl;
    double dist = 0;
    double time = 0;
    for (int i = 0; i<stops; i++) {
        if (i > 0) {
            dist += haversine(locs[i-1].lat,locs[i-1].lon,locs[i].lat,locs[i].lon,rad);
            time += getFlightTime(locs[i-1].lat,locs[i-1].lon,locs[i].lat,locs[i].lon);
        }
        cout <<locs[i].place<<", "<<locs[i].lat<<", "<<locs[i].lon<<endl;
    }

    cout <<"\nThe total distance between your ordered locations is:\t\t"<<dist<<" miles"<<endl;
    cout <<"The flight time to visit your locations in order at "<<speed<<"mph is:\t"<<time<<" hours"<<endl;
    cout <<"\nUnidentified flying user, we hope you to know that you are a valued customer and we appreciate you using our service instead of Google Maps.\nYou owe: $"<<pow(stops,10)<<".99 (Like everything else, this is not covered by health insurance)"<<endl;
}


double haversine(double lat1, double long1, double lat2, double long2, double radius) {
    float inside = pow(sin((lat2-lat1)/2),2)+cos(lat1)*cos(lat2)*pow(sin((long2-long1)/2),2);
    return 2*radius*asin(sqrt(inside));
}

double getFlightTime(double lat1, double long1, double lat2, double long2) {
    return haversine(lat1,long1,lat2,long2,rad)/speed;
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