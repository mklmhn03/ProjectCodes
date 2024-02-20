// Tic-tac-toe board - user plays against computer; displays board after each move
#include <iostream>
#include <vector>

using namespace std;

const int nRows = 3;
const int nCols = 3;

// 2D display of board contents
void displayBoard(vector<vector<char>>& board) {
    for(int i = 0; i < nRows; i++) {
        for(int j = 0; j < nCols; j++) {
            cout << board[i][j] << ' ';
        }
        cout <<endl;
    }
}

// Returns false if a dash on board; true otherwise
bool boardFull(vector<vector<char>>& board) {
    for(int i = 0; i < nRows; i++) {
        for(int j = 0; j < nCols; j++) {
            if (board[i][j] == '-') return false;
        }
    }
    return true;
}

// Ask user for input row, col. Mark 'X' at that location
// Be sure to check for invalid input
void userPlay(vector<vector<char>>& board) {
    char xc,yc = 'a';
    int x,y = -1;
    while ((isdigit(xc)+isdigit(yc) < 2) || !(x >= 0 && x < nRows && y >= 0 && y < nCols)) {
        cout <<"Input row and column (integers starting from 0)\nInput Row: "; cin >> xc;
        cout <<"Input Column: "; cin >> yc;
        if ((isdigit(xc)+isdigit(yc) == 2)) {
            x = xc-'0';
            y = yc-48;
        }
    }
    board[x][y] = 'X';
}

// Simple minded strategy - scan the board for the first dash. Mark an 'O' at that location
void computerPlay(vector<vector<char>>& board) {
    for(int i = 0; i < nRows; i++) {
        for(int j = 0; j < nCols; j++) {
            if (board[i][j] == '-') {
                board[i][j] = 'O';
                return;
            }
        }
    }
}


// Game loop
int main() {
    vector<vector<char>> board{ {'-', '-', '-'}, {'-', '-', '-'}, {'-', '-', '-'}};
    displayBoard(board);
    while(!boardFull(board)) {
        userPlay(board);
        computerPlay(board);
        displayBoard(board);
    }
}