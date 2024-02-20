#ifndef AREA
#define AREA

#include <iostream>
#include <sstream>
#include <time.h>
#include "Player.h"

using namespace std;


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

class Area {
    public:
    virtual string getDescription() = 0;
    virtual void visit(Player& plr) = 0;
};

// TODO: Define at least 3 more types of derivded land types
// TODO: Add some unique effect to each new type

class Forest : public Area {
    public:
    int count = 0;
    string getDescription(){
        return "a densely wooded forest.";
    }
    
    void visit(Player& plr){
        count++;
        int randomNum = rand()*rand() % 100;
        
        if(randomNum < 75){
            cout <<"\nYou encounter a bear on your trek through the forest."<<endl;

            if (plr.getSanity() <= 2) {
                cout <<"1) You cannot be fooled. The bear is a god in disguise. Worship it by throwing stones. Entice it to bestow success upon you."<<endl;
                cout <<"2) The bear is but a distraction. You true devotion must be the pursuit of inner peace."<<endl;
                switch (optCheck(1,2)){
                case 1:
                    cout <<"The bear looks at you incredulously before lumbering over and casually mauling you. (-4 health)"<< endl;
                    plr.changeHealth(-4);
                    break;
                case 2:
                    cout << "You stare intently at a flower and yell \"INNER PEACE\" until your voice wears out. When nothing happens, you grab the flower and eat it. You look around. The bear seems to have left. Maybe it really was a god."<<endl;
                    break;
                }
            }
            else if (plr.getSanity() <= 5) {
                cout <<"1) Ask if the bear wants to be your friend."<<endl;
                cout <<"2) Ask the bear if it can tutor you in fourier series."<<endl;

                switch (optCheck(1,2)){
                case 1:
                    cout <<"The bear stares at you for a couple seconds then leaves, deciding that you are not worth the trouble. Feelsbad."<<endl;
                    break;
                case 2:
                    cout <<"The bear sniffs the air, then darts off in the opposite direction at breakneck velocities. Smart bear."<<endl;
                    break;
                }
            }
            else if (plr.getSanity() <= 10) {
                cout <<"1) Stand up tall, spread your arms, and scream curses at the bear."<<endl;
                cout <<"2) Pull out a gun and fire a warning shot. THIS IS MURICA."<<endl;

                switch (optCheck(1,2)){
                case 1:
                    cout <<"You channel your inner frustrations and yell at the bear. It backs away, possibly realizing that you have a lot more problems in your life."<<endl;
                    break;
                case 2:
                    cout <<"You inform the bear that it picked on the wrong murican. Then you reach for a gun before realizing that you don't own one. You are just a college student with a lot of debt. This is murica after all. To save face, you hold your finger out and yell \"BANG!\" The bear just looks insulted so you back away slowly."<<endl;
                    break;
                }
            }
            
        }
        else {
            plr.changeHealth(1);
            cout <<"You forage for berries in the woods and eat a few. Meal plans are expensive. (+1 health)"<<endl;
        }
    }
};

class Lake : public Area {
    public:
    string getDescription(){
        return "a clear sparkling lake.";
    }
    
    void visit(Player& plr){
        cout <<"\nThe lake is beautiful with lush greenery and timid wildlife."<<endl;
        if (rand()%10 < 1 && plr.getSanity()<7) cout <<"A potato falls on your head."<<endl;

        if (plr.getSanity() <= 2) {
            cout <<"1) Go fish."<<endl;
            cout <<"2) Irrigate your potato garden."<<endl;

            switch (optCheck(1,2)){
            case 1:
                cout <<"You throw pieces of bread and laundry into to the water. When you see movement, you pounce, jumping in and knocking a fish out of water. You reflect, wondering if there was an easier way to do this. (+1 sanity)"<< endl;
                plr.changeSanity(1);
                break;
            case 2:
                cout <<"You came prepared, equipped with showels for digging, an unwilling friend for labor, and rope to prevent their escape."<<endl;
                break;
            }
        }
        else if (plr.getSanity() <= 5) {
            cout <<"1) Plant some potatoes."<<endl;
            cout <<"2) Yell at a passerby."<<endl;

            switch (optCheck(1,2)){
            case 1:
                cout <<"You plant some potatoes near the lake. It is very calming. (+1 sanity)"<<endl;
                plr.changeSanity(1);
                break;
            case 2:
                cout <<"\"AAArharHAHAHAgahh\" you yell at someone. They look at you before speedwalking away."<<endl;
                break;
            }
        }
        else if (plr.getSanity() <= 7) {
            cout <<"1) Stare intently at some grass."<<endl;
            cout <<"2) Make a beach."<<endl;

            switch (optCheck(1,2)){
            case 1:
                cout <<"You stare intently at some grass."<<endl;
                break;
            case 2:
                cout <<"You push a wheelbarrow of sand to the lake and dump it near the shore. Then you equip your sunglasses and relax. (+1 sanity)"<<endl;
                break;
            }
        }
        else if (plr.getSanity() <= 10) {
            cout <<"1) Take a deep breath and enjoy the lake."<<endl;
            cout <<"2) Take a nap on the hammock."<<endl;

            switch (optCheck(1,2)){
            case 1:
                cout <<"You accidentally breathe in a bug and start coughing. It was only one among a cloud of flies. You quickly leave the premises."<<endl;
                break;
            case 2:
                cout <<"You are quickly woken up by something trying to crawl into your ear. Apart from that, it was pretty relaxing though. (+1 sanity)"<<endl;
                plr.changeSanity(1);
                break;
            }
        }
    }  
};

class Gym : public Area {
    public:
    string getDescription(){
        return "a sprawling complex for exercise.";
    }
    
    void visit(Player& plr){
        cout <<"\nIt looks good. Very exercisy."<<endl;
        int randomNum = rand()*rand() % 100;
        if (randomNum < 20) {
            cout <<"A basketball hits you in the stomach, knocking the wind out of you. Another hits you in the back of the knee, making you stumble forward. A finisher hits you in the side of the head, knocking you down flat. You hear a \"Sorry, my bad!\" before passing out. (-1 health)"<<endl;
            plr.changeHealth(-1);
        }
        else if (randomNum <25) {
            cout <<"An unnaturally buff man 'bumps' into you. It hurts you significantly more than it hurts him. (-2 health)"<<endl;
            plr.changeHealth(-2);
        }

        cout <<"1) Play a sport.\n2) Work out."<<endl;
        switch (optCheck(1,2)){
            case 1:
                cout <<"You play a sport and feel healthy. (+1 health)"<< endl;
                plr.changeHealth(1);
                break;
            case 2:
                cout <<"You work out until your body feels like jello. (+1 health)"<<endl;
                plr.changeHealth(1);
                if (rand() % 2 < 1) {
                    cout <<"When your adrenaline drains, you collpase and realize that you can't really move. You decide that staying on the ground is the best option and miss class. (-0.2 GPA)"<<endl;
                    plr.changeGPA(-2);
                }
                break;
        }
    }  
};

class Library : public Area {
    public:
    string getDescription(){
        return "a library filled with books, tables, and comfortable chairs.";
    }
    
    void visit(Player& plr){
        cout <<"\nYou walk in and take a deep breath, noticing a slight aroma of jasmine and dust accented with mild desperation."<<endl;

        int randomNum = rand()*rand() % 100;
        if (randomNum < 25) {
            cout <<"A dictionary falls on you head. (-1 health)"<<endl;
            plr.changeHealth(-1);
        }
        if (randomNum < 50 && plr.getSanity()<5) {
            cout <<"As you recover, you could have sworn you heard galloping."<<endl;
        }
        
        cout <<"You bump into some friends who offer to study with you.\n1) Study with them.\n2) Study alone."<<endl;
        switch (optCheck(1,2)){
            case 1:
                randomNum = rand()*rand() % 4 - 2;
                cout <<"You have fun but your friends are equally clueless. (+1 sanity)("<<randomNum/10.0<<" GPA)"<< endl;
                plr.changeSanity(1);
                plr.changeGPA(randomNum);
                break;
            case 2:
                cout <<"You study for hours. You learn that fear and stress are bad motivators. (-1 sanity)(0.2 GPA)"<<endl;
                break;
        }
    }
};

class Dorm : public Area {
    public:
    string getDescription(){
        return "your \'place of residence.\'";
    }
    
    void visit(Player& plr) {
        cout <<"\nYou live here."<<endl;
        cout <<"1) Sleep.\n2) Browse internet.\n3) Do homework."<<endl;
        
        int randomNum = rand() % 10;
        switch (optCheck(1,3)){
            case 1:
                if (randomNum < 4) {
                    cout <<"You get a refreshing 3 hours of rest. (+1 health)"<<endl;
                    plr.changeHealth(1);
                }
                else {
                    cout <<"You wake up to an itch on your arm. When you go to scratch, you feel some thing crawling on it. You jump off your bed and shake your clothes to see bedbugs falling out. (-1 health)(-1 sanity)"<<endl;
                    plr.changeHealth(-1);
                    plr.changeSanity(-1);

                    if (plr.getSanity()<3) cout <<"\nAs you shake out the pests, you hear a peculiar humming noise. You look around and notice that your blanket is covered in what appears to be white hair. You rub you eyes and slap your self twice. Both the noise and hair are gone. Weird."<<endl;
                }
                break;
            case 2:
                if (randomNum < 2) {
                    cout <<"You watch something that makes you laugh. (+1 sanity)"<<endl;
                    plr.changeSanity(1);
                }
                else if (randomNum < 5) {
                    cout <<"You learn from someone who teaches better than some of your professors. (0.2 GPA)"<<endl;
                    plr.changeGPA(2);
                }
                else if (randomNum < 8) {
                    cout <<"You are reminded about the depressing state of the world. (-1 sanity)"<<endl;
                    plr.changeSanity(-1);
                }
                else {
                    cout <<"You waste time (-0.1 GPA)."<<endl;
                    plr.changeGPA(-1);
                }
                break;
            case 3:
                if (randomNum < 6) {
                    cout <<"You get your homework done. (0.3 GPA)"<<endl;
                    plr.changeGPA(3);
                    if (rand()%2 < 1) {
                        cout <<"The hours of homework make you feel drained and stressed. (-1 sanity)"<<endl;
                        plr.changeSanity(-1);
                    }
                }
                else {
                    cout <<"You procastinate because you are tired. Then your internet goes out. The only thing left to do is to huddle in a corner and whisper reassurances to yourself. (-0.1 GPA)(-1 sanity)"<<endl;
                    plr.changeGPA(-1);
                    plr.changeSanity(-1);
                }
                break;
        }
    }  
};

class Cafeteria : public Area {
    public:
    string getDescription(){
        return "a place well renowned for consistently average food.";
    }
    
    void visit(Player& plr){
        cout <<"\nYou are not impressed by the food options."<<endl;
        
        int randomNum = rand()*rand() % 5;
        if (plr.getSanity() >= 5) {
            cout <<"1) Eat bad tasting healthy food.\n2) Eat average tasting unhealthy food."<<endl;
            switch (optCheck(1,2)){
                case 1:
                    cout <<"You consume the food for the sake of sustenance.";
                    if (randomNum < 1) {
                        cout <<" (+1 health)";
                        plr.changeHealth(1);
                    }
                    cout << endl;
                    break;
                case 2:
                    cout <<"You consume the food.";
                    if (randomNum < 1) {
                        cout <<" (-1 health)";
                        plr.changeHealth(-1);
                    }
                    cout << endl;
                    break;
            }
        }
        else {
            cout <<"You pretend to be an employee, sneak in, and make some average tasting healthy food for yourself.";
                if (randomNum < 2) {
                    cout <<" (+1 health)";
                    plr.changeHealth(1);
                }
                cout << endl;
        }
    }
};

class PoliceStation : public Area {
    public:
    string getDescription(){
        return "a station of law enforcement. Members often find themselves subject to controversey.";
    }
    
    void visit(Player& plr){
        cout <<"\nYou stare at the Police station, an important facet of the executive branch in the USA."<<endl;
        if (rand()%10 < 1 && plr.getSanity()<7) cout <<"A potato hits you in the shoulder. Where is this coming from?!"<<endl;

        if (plr.getSanity() >= 5) cout <<"You walk past, curious about what happens inside."<<endl;
        else {
            cout <<"You walk up to the front camera and start breakdancing. Your moves become increasingly aggressive. You continue this until a slightly confused member of staff comes outside and asks you to stop. Although, before you leave, she compliments your moves."<<endl;
        }
    }  
};

class Class : public Area {
    public:
    string getDescription(){
        return "a place of learning for the passionate, a place of sacrifice for the monetarily inclined, and a place of disphoria for the sleep deprived. Class.";
    }
    
    void visit(Player& plr){
        cout <<"\nYou see some students asleep, some complaining about their grades, and some staring off into space or their devices."<<endl;

        if (rand()%10 < 1) cout <<"You overhear a classmate talking about his prototype potato launcher."<<endl;
        if (rand()%10 < 1 && plr.getSanity()<5) cout <<"You see something fluffy and white pass by in the hallway before the door closed. Strange, you didn't think pets were allowed in the building."<<endl;

        int randomNum = rand()*rand()%8;
        if (randomNum < 2) {
            cout <<"The professor walks in and hands out a test with an obliviously wicked gleam in his eyes. \"This test should be easy. It's just like the homework.\""<<endl;
            cout <<"The student next to you snorted, but succesfully held back his laugh.\n1) Take the test.\n2) Don't take the test."<<endl;
            switch (optCheck(1,2)) {
            case 1:
                randomNum = rand()%5-3;
                cout <<"Your GPA changes by "<<randomNum/10.0<<"."<<endl;
                plr.changeGPA(randomNum);
                break;
            
            case 2:
                cout <<"You insist that you would like to abstain from this exam. You successfully fail the exam. (-0.5 GPA)"<<endl;
                plr.changeGPA(-5);
                break;
            }
        }
        else if (randomNum < 5) {
            cout <<"There is a quiz today. You haven't gotten back any of your previous quizzes so you are nervous."<<endl;
            cout <<"You have only 5 minutes to complete it likely won't be enough.\n1) High speed, low accuracy.\n2) Low speed, high accuracy.\n3) Don't take the quiz."<<endl;
            switch (optCheck(1,3)) {
            case 1:
                cout <<"You don't do particularly well, but not terrible. (-0.1 GPA)"<<endl;
                plr.changeGPA(-1);
                break;
            
            case 2:
                cout <<"You don't do particularly well, but not terrible. (-0.1 GPA)"<<endl;
                plr.changeGPA(-1);
                break;
            case 3:
                cout <<"You hand in your blank quiz wrapped around a potato. You give your professor a sly wink as you give it to him.\nUnfortunately, he doesn't seem impressed. You fail the quiz spectacularly. (-0.2 GPA)"<<endl;
                plr.changeGPA(-2);
                break;
            }
        }
        else {
            cout <<"1) Try to learn in class.\n2) Do homework to be efficient."<<endl;
            switch (optCheck(1,2)) {
            case 1:
                cout <<"You sit in class and attempt to follow along as best you can. (0.1 GPA)"<<endl;
                plr.changeGPA(1);
                break;
            case 2:
                randomNum = rand()%3;
                cout <<"You do homework for efficiency. ("<<randomNum/10.0<<" GPA)."<<endl;
                plr.changeGPA(randomNum);
                break;
            }
        }
        if (rand()%10 < 1 && plr.getGPA() <= 3.3) {
            cout <<"You are very drained from the past few classes and feel pressured by your grades. (-1 sanity)"<<endl;
            plr.changeSanity(-1);
        }
    }  
};

#endif //AREA