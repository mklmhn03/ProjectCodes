#include <iostream>
#include <sstream>
#include <time.h>
#include <cctype>
#include "Player.h"
#include "Area.h"

using namespace std;

const int MAP_SIZE = 10;
Area* map[MAP_SIZE][MAP_SIZE];

void populateMap(){
    for(int i = 0; i < MAP_SIZE; i++){
        for(int j = 0; j < MAP_SIZE; j++){
            // TODO: Modify this code to add your new land types
            int randomNum = rand() % 100;
            if (randomNum < 25) map[i][j] = new Forest;
            else if (randomNum >= 25 && randomNum < 35) map[i][j] = new Lake;
            else if (randomNum >= 35 && randomNum < 40) map[i][j] = new Gym;
            else if (randomNum >= 40 && randomNum < 50) map[i][j] = new Library;
            else if (randomNum >= 50 && randomNum < 60) map[i][j] = new Cafeteria;
            else if (randomNum >= 60 && randomNum < 70) map[i][j] = new Dorm;
            else if (randomNum >= 70 && randomNum < 75) map[i][j] = new PoliceStation;
            else if (randomNum >= 75 && randomNum < 100) map[i][j] = new Class;
            else {
                cout << "Invalid land type selected" << endl;
            }
        }
    }
}

int main(){
    srand(time(0));
    
    populateMap();
    
    Player player(MAP_SIZE/2, MAP_SIZE/2);
    
    cout << "You wake up excited to be a prospective engineer!\n"<<endl;
    
    // TODO: Handle boundary conditions (e.g., if index out of bounds north, you index the south-most location)
    
    while(true){
        cout << "N) To the north you see " << map[player.x][(player.y + MAP_SIZE-1)%MAP_SIZE]->getDescription() << endl;
        cout << "E) To the east you see " << map[(player.x + 1)%MAP_SIZE][player.y]->getDescription() << endl;
        cout << "S) To the south you see " << map[player.x][(player.y + 1)%MAP_SIZE]->getDescription() << endl;
        cout << "W) To the west you see " << map[(player.x + MAP_SIZE-1)%MAP_SIZE][player.y]->getDescription() << endl;
        

        char userInput;
        cout << "\nWhich way will you go? Enter N, E, S, or W:"<<endl;
        cin >> userInput;
        while (toupper(userInput) != 'N' && toupper(userInput) != 'E' && toupper(userInput) != 'S' && toupper(userInput) != 'W') {
            cout << "Select a valid option (Enter N, E, S, or W): ";
            cin >> userInput;
        }
        
        switch(toupper(userInput)){
            case 'N':
                player.y = (player.y + MAP_SIZE-1)%MAP_SIZE;
                break;
            case 'E':
                player.x = (player.x + 1)%MAP_SIZE;
                break;
            case 'S':
                player.y = (player.y + 1)%MAP_SIZE;
                break;
            case 'W':
                player.x = (player.x + MAP_SIZE-1)%MAP_SIZE;
                break;
            default:
                break;
        }
        
        map[player.x][player.y]->visit(player);
        
        if (!player.isAlive() || !player.hasGrades() || player.getScore() > 25) break;
        player.takeTurn();
        cout << player.getStats() << endl;
    }
    
    if (!player.hasGrades()) cout <<"You were kicked out of college. You are in debt, degreeless, destined to desolate inadequacy."<<endl;
    if (!player.isAlive()) cout <<"You died. You will be missed... probably."<< endl;
    if (player.getScore() > 25) cout <<"You bested college and graduated as an engineer by making some sacrifices."<< endl;
    
    cout <<"Your score is: "<<player.getScore()<<endl;
    
    return 0;
}