#include <iostream>
#include <vector>
using namespace std;

vector<int> board(10, 2); // indices 1-9 2 = blank, 3 = X, 5 = O
int turn;

int magicSquare[10] = {0, 8, 1, 6,
                          3, 5, 7,
                          4, 9, 2};

bool isBlank(int pos) {
    return pos >= 1 && pos <= 9 && board[pos] == 2;
}

int AnyBlank() {
    for (int i = 1; i <= 9; ++i) if (isBlank(i)) return i;
    return 0;
}

int Make2() {
    int noncorners[] = {2, 4, 6, 8};
    if (isBlank(5)) return 5;
    for (int n : noncorners) if (isBlank(n)) return n;
    return 0;
}

int Posswin(int playerVal) {
    int winoption[8][3] = {
        {1,2,3}, {4,5,6}, {7,8,9},
        {1,4,7}, {2,5,8}, {3,6,9},
        {1,5,9}, {3,5,7}
    };
    for (int i = 0; i < 8; ++i) {
        int sum = 0, blankPos = 0, count = 0;
        for (int j = 0; j < 3; j++) {
            int pos = winoption[i][j];
            if (board[pos] == playerVal) {
                sum += magicSquare[pos];
                count++;
            } else if (board[pos] == 2) {
                blankPos = pos;
            }
        }
        if (count == 2 && blankPos != 0 && sum + magicSquare[blankPos] == 15) {
            return blankPos;
        }
    }
    return 0;
}

void Go(int pos) {
    if (!isBlank(pos)) pos = AnyBlank();
    if (pos == 0) return;
    int playerVal = (turn % 2 == 1) ? 3 : 5; 
    board[pos] = playerVal;
}

void displayBoard() {
    cout << "\nBoard:\n";
    for (int i = 1; i <= 9; ++i) {
        char ch = (board[i] == 3) ? 'X' : (board[i] == 5 ? 'O' : '.');
        cout << ch << ' ';
        if (i % 3 == 0) cout << '\n';
    }
    cout << '\n';
}

void userMove() {
    int pos;
    while (true) {
        cout << "Enter your move (1-9): ";
        cin >> pos;
        if (isBlank(pos)) {
            board[pos] = 5; 
            break;
        } else {
            cout << "Invalid move, try again.\n";
        }
    }
}

int checkWin() {
    int winoption[8][3] = {
        {1,2,3}, {4,5,6}, {7,8,9},
        {1,4,7}, {2,5,8}, {3,6,9},
        {1,5,9}, {3,5,7}
    };
    for (auto &line : winoption) {
        int sumX = 0, sumO = 0;
        for (int i = 0; i < 3; i++) {
            int pos = line[i];
            if (board[pos] == 3) sumX += magicSquare[pos];
            else if (board[pos] == 5) sumO += magicSquare[pos];
        }
        if (sumX == 15) return 3;
        if (sumO == 15) return 5;
    }
    return 0; 
}

int main() {
    cout << "You are O, computer is X.\n";
    displayBoard();

    for (turn = 1; turn <= 9; ++turn) {
        int move = 0;

        if (turn % 2 == 1) { 
            if (turn == 1) Go(1);
            else if (turn == 3) { if (isBlank(9)) Go(9); else Go(3); }
            else if (turn == 5) { move = Posswin(3); if (move) Go(move); else { move = Posswin(5); if (move) Go(move); else if (isBlank(7)) Go(7); else Go(3);} }
            else if (turn == 7) { move = Posswin(3); if (move) Go(move); else { move = Posswin(5); if (move) Go(move); else Go(AnyBlank()); } }
            else if (turn == 9) { move = Posswin(3); if (move) Go(move); else { move = Posswin(5); if (move) Go(move); else Go(AnyBlank()); } }
        } 
        else { 
            userMove();
        }

        displayBoard();

        int winner = checkWin();
        if (winner == 3) {
            cout << "Computer (X) wins!\n";
            break;
        } else if (winner == 5) {
            cout << "You (O) win!\n";
            break;
        }
    }

    return 0;
}

