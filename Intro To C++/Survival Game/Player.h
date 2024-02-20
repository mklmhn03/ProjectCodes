#ifndef PLAYER
#define PLAYER

#include <iostream>
#include <sstream>
#include <time.h>

using namespace std;

class Player {
    private:
    int health, sanity, gpa, score;
    const int MAX_HEALTH = 10;
    int MAX_SANITY = 10;
    const int MAX_GPA = 40;

    public:
    int x, y;
    Player(int x, int y){
        health = MAX_HEALTH;
        sanity = MAX_SANITY;
        gpa = MAX_GPA;
        
        this->x = x;
        this->y = y;
        this->score = 0;
    }
    
    int getScore() const {
        return score;
    }
    
    void takeTurn(){
        int randomNum = rand() % 100;
        this->gpa--;
        int tempgp = 0;
        if (this->health <= MAX_HEALTH/4) {
            cout <<"You are trying really hard to prevent imminent death, too hard to focus on your grades. Weak. (-0.2 GPA)"<<endl;
            tempgp -= 2;
        }
        else if (this->health <= MAX_HEALTH/2) {
            cout <<"You get sick on a regular basis and it affects your grades. (-0.1 GPA)"<<endl;
            tempgp -= 1;
        }
        else if (this->health <= MAX_HEALTH*3/4 && randomNum > 49) {
            cout <<"You generally feel like crap, making it harder to focus. (-0.1 GPA)"<<endl;
            tempgp -= 1;
        }

        randomNum = rand()*rand() % 100;
        if (this->sanity <= 2 && MAX_SANITY > 2) {
            cout <<"Something in your soul breaks pemanently. You know you can never go back to how you were. (-1 max sanity)"<<endl;
            MAX_SANITY--;
        }
        else if (this->sanity <= 5 && MAX_SANITY > 5) {
            cout <<"Something in your soul breaks pemanently. You know you can never go back to how you were. (-1 max sanity)"<<endl;
            MAX_SANITY--;
        }
        else if (this->sanity <= 7 && MAX_SANITY > 7 && randomNum < 50) {
            cout <<"Something in your soul breaks pemanently. You know you can never go back to how you were. (-1 max sanity)"<<endl;
            MAX_SANITY--;
        }

        randomNum = rand()*rand() % 100;
        if (this->sanity <= 2) {
            cout <<"A wall looks a bit dirty so you bash your head against it for a couple minutes. (-2 health)"<<endl;
            this->health -= 2;
        }
        else if (this->sanity <= 5) {
            cout <<"You decide that utensils are more appetizing than food. (-1 health)"<<endl;
            this->health--;
        }
        else if (this->sanity <= 7 && randomNum < 75) {
            cout <<"You explain your despair to a wasp. Its friends sting you in return. (-1 health)"<<endl;
            this->health--;
        }
        
        randomNum = rand() % 100;
        if (this->gpa < 20) {
            cout <<"Society tells you that you will amount to nothing in life. Consider dropping out. (-2 sanity)"<<endl;
            this->sanity -= 2;
        }
        else if (this->gpa < 27) {
            cout <<"Looking at your low grades gives you a panic attack. (-1 sanity)"<<endl;
            this->sanity--;
        }
        else if (this->gpa < 34 && randomNum < 75) {
            cout <<"Your lost opportunities in life bring you distress. (-1 sanity)"<<endl;
            this->sanity--;
        }
        
        this->gpa += tempgp;
        this->score++;

        if (sanity<-1) {
            cout <<"\nYou are walking along the street. Suddenly, you see a shock of white fuzz. Curious, you turn your attention towards it. You are surprised to see a llama glaring at you. It trots to you. As it gets closer you notice that it is carrying a brown sack and in its mouth is a potato? Most notably, its eyes are red, as if it had been infected with pink-eye.\n\nIn one fluid whiplike motion, it launches the potato straight at your head. You duck just in time. But the llama reaches into its sack and pulls out another, flinging it at you with ridiculous speed.\n\nYou do your best to dodge but the llama is unrelenting in its persuit and projectiles. It jumps close to you and lets out a shriek. Trying to avoid it, you jump back onto the street and get hit by a car. (-7 health)"<<endl;
            sanity = MAX_SANITY;
        }

        if (health<0) health = 0;
        if (gpa<0) gpa = 0;
    }

    bool isAlive() const {
        return this->health > 0;
    }
    bool hasGrades() const {
        return this->gpa > 1;
    }
    bool isSane() const {
        return this->sanity >-2;
    }
    
    void changeHealth(int val){
        this->health += val;
        if(this->health > MAX_HEALTH) this->health = MAX_HEALTH;
        if(this->health < 0) this->health = 0;
    }

    void changeGPA(int val){
        this->gpa += val;
        if(this->gpa > MAX_GPA) this->gpa = MAX_GPA;
        if(this->gpa < 0) this->gpa = 0;
    }
    
    void changeSanity(int val){
        this->sanity += val;
        if(this->sanity > MAX_SANITY) this->sanity = MAX_SANITY;
        if(this->sanity < -3) this->sanity = -3;
    }

    int getHealth() {return health;}
    double getGPA() {return gpa/10.0;}
    int getSanity() {return sanity;}
    
    string getStats() const {
        stringstream ss;
        ss  << "============\n"
            << "Health: " << this->health << "\n" 
            << "Sanity: " << this->sanity << "\n" 
            << "GPA: " << this->gpa/10.0 << "\n"
            << "Location: ("<<x<<","<<y<<")\n"
            << "============\n";
        return ss.str();
    }
};

#endif //PLAYER