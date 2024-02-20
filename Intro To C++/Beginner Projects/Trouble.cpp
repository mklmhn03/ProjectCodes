#include <iostream>
#include <cstdlib>
#include <vector>
#include <array>
#include <map>

using namespace std;

const int rows = 4;
const int cols = 11;
struct piece {bool start = false; char col; int pos = 0;};
vector<vector<piece>> rep;
string board[rows][cols];

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
        if (numCheck(s))
            opt = stoi(s);
    }
    return opt;
}

bool posCheck(int plr, int pce, int die) {
    for (int i = 0; i<4; i++) {
        if (rep[plr][pce].pos+die == rep[plr][i].pos && i!=pce && rep[plr][i].start)
            return false;
    }
    return true;
}

int rollDie() {
    srand(time(0));
    int min = 1; // the min number a die can roll is 1
    int max = 6; // this->dieSize; // the max value is the die size
    return rand() % (max - min + 1) + min;
}

// 2D board
void resetBoard() {
    for (int i = 0; i<rows; i++)
        for (int j = 0; j<cols; j++) board[i][j] = "__";
}
bool refreshBoard() {
    resetBoard();
    bool g = true;
        for (int i = 0; i<rep.size(); i++) {
            for (int j = 0, win = 0; j<4; j++) {
                if (rep[i][j].start) {
                    if (rep[i][j].pos<28)
                        board[(rep[i][j].pos/7+i)%4][rep[i][j].pos%7] = rep[i][j].col+to_string(j+1);
                    else board[i][rep[i][j].pos-21] = rep[i][j].col+to_string(j+1);
                }
                if (rep[i][j].pos >= 28) win++;
                if (win == 4) {
                    g = false;
                    cout<<"\nPlayer "<<rep[i][0].col<<" Wins :O"<<endl;
                    break;
                }
            }
        }
    cout << endl;
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            cout <<" ";
            if (c==7)cout <<"  ";
            cout <<board[r][c];
        }
        cout << endl;
    }
    cout << endl;
    return g;
}



int main() {
    bool game = true;
    resetBoard();

    cout <<"Welcome to Trouble!\nHow many players are there (Enter an integer from 2-4)?"<<endl;
    int players = optCheck(2,4);

    for (int i = 0; i < players; i++) {
        for (int j = 0; j<4; j++) {
            rep.push_back(vector<piece>(4));
        }
        bool test = false;
        int color;
        while (!test) {
            cout <<"Player "<<(i+1)<<", what free color would you like?\n1)Green\n2)Red\n3)Blue\n4)Yellow"<<endl;
            color = optCheck(1,4); test = true;
            for (int j = 0; j<i; j++) {
                switch (color) {
                    case 1: if (rep[j][0].col == 'G') test = false; break;
                    case 2: if (rep[j][0].col == 'R') test = false; break;
                    case 3: if (rep[j][0].col == 'B') test = false; break;
                    case 4: if (rep[j][0].col == 'Y') test = false;
                }
            }
        }
        for (int j = 0; j<4; j++) {
            switch (color) {
                case 1: rep[i][j].col = 'G'; break;
                case 2: rep[i][j].col = 'R'; break;
                case 3: rep[i][j].col = 'B'; break;
                case 4: rep[i][j].col = 'Y';
            }
        }
    }
    for (int i = 0; i < players; i++) {
        cout <<"Player "<<i+1<<": "<<rep[i][0].col<<endl;
    }

    for(int turn = 1; game; turn++) { //when game is finished, set game to false and loop will stop
        cout <<"\nTurn "<<turn<<endl;
        int die;
        for(int i = 0; i<players; i++) {
            int max = 0;
            cout <<"\nPlayer "<<rep[i][0].col<<", enter 0 to roll your die."<<endl;
            if (optCheck(0,0) == 0) die = rollDie();
            //die = optCheck(1,6);

            cout <<"You rolled a "<<die<<"."<<endl;
            for (int j = 0; j<4; j++) {
                if (rep[i][j].pos+die < 32 && ((die == 6 && posCheck(i,j,0) && rep[i][j].pos==0) || (rep[i][j].start && posCheck(i,j,die)))) {
                    max++;
                    if (max==1) cout <<"Which piece do you want to move?"<<endl;
                    cout <<max<<")"<<rep[i][j].col<<j+1<<endl;
                } //checks what options you have based on game rules
            }

            if (max<1) cout <<"You can't move :)"<<endl;
            else { //executes your choice
                int ans = optCheck(1,max);
                for (int j = 0,k = 0; j<4; j++){
                    if (rep[i][j].pos+die < 32 && ((die == 6 && posCheck(i,j,0) && rep[i][j].pos==0) || (rep[i][j].start && posCheck(i,j,die))))
                        k++;
                    if (k==ans) {
                        if (rep[i][j].start) {
                            rep[i][j].pos += die;
                            for (int k = 0; k<players; k++) {
                                for (int a = 0; a<4; a++) {
                                    if (i!=k && rep[k][a].start && rep[k][a].pos<28 && (rep[i][j].pos/7+i)%4 == (rep[k][a].pos/7+k)%4 && rep[i][j].pos%7 == rep[k][a].pos%7) {
                                        rep[k][a].start = false; rep[k][a].pos = 0;
                                        cout<<"You knocked "<<rep[k][a].col<<a+1<<" back to the start!"<<endl;
                                        break;
                                    }
                                }
                                if (k+1 == players) {
                                    cout <<"You moved "<<rep[i][j].col<<j+1<<"."<<endl;
                                    if (rep[i][j].pos>27) cout <<rep[i][j].col<<j+1<<" is finished!"<<endl;
                                    break;
                                }
                            }
                            break;
                        }
                        else {
                            rep[i][j].start = true;
                            cout <<"You moved "<<rep[i][j].col<<j+1<<" to the board."<<endl;
                            for (int l = 0; l<players; l++) {
                                for (int a = 0; a<4; a++) {
                                    if (i!=l && rep[l][a].start && rep[l][a].pos<28 && (rep[i][j].pos/7+i)%4 == (rep[l][a].pos/7+l)%4 && rep[i][j].pos%7 == rep[l][a].pos%7) {
                                        rep[l][a].start = false; rep[l][a].pos = 0;
                                        cout<<"You knocked "<<rep[l][a].col<<a+1<<" back to the start!"<<endl;
                                        break;
                                    }
                                }
                            }
                            break;
                        }
                    }
                }
            }
            //game & board
            if (!refreshBoard()) {
                cout<<"\nGAME OVER. Life is cruel."<<endl;
                game = false; break;
            }

            if (die == 6 && game) {
                cout <<"You get to roll again :|"<<endl;
                i--;
            }
        }
    }
    system("pause");
}