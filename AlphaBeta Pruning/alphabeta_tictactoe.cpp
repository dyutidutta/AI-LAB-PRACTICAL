#include <iostream>
#include <vector>
#include <limits>
using namespace std;

vector<int> board(10, 2);
// 2 = blank, 3 = X (AI), 5 = O (User)
int turn;

bool isBlank(int pos)
{
    return pos >= 1 && pos <= 9 && board[pos] == 2;
}

int AnyBlank()
{
    for (int i = 1; i <= 9; ++i)
        if (isBlank(i))
            return i;
    return 0;
}

void displayBoard()
{
    cout << "\nBoard:\n";
    for (int i = 1; i <= 9; ++i)
    {
        char ch = (board[i] == 3) ? 'X' : (board[i] == 5 ? 'O' : '.');
        cout << ch << ' ';
        if (i % 3 == 0)
            cout << '\n';
    }
    cout << '\n';
}

int checkWin()
{
    int winoption[8][3] = {
        {1, 2, 3}, {4, 5, 6}, {7, 8, 9},
        {1, 4, 7}, {2, 5, 8}, {3, 6, 9},
        {1, 5, 9}, {3, 5, 7}};
    for (auto &trio : winoption)
    {
        int prod = board[trio[0]] * board[trio[1]] * board[trio[2]];
        if (prod == 27)  return 3; // X wins
        if (prod == 125) return 5; // O wins
    }
    return 0;
}

bool movesLeft()
{
    for (int i = 1; i <= 9; i++)
        if (board[i] == 2)
            return true;
    return false;
}

int minimax(bool isMaxLevel, int alpha, int beta)
{
    int winner = checkWin();
    if (winner == 3) return 1;   // AI wins
    if (winner == 5) return -1;  // User wins
    if (!movesLeft()) return 0;  // Draw

    if (isMaxLevel)
    {
        int best = -10;
        for (int i = 1; i <= 9; i++)
        {
            if (board[i] == 2)
            {
                board[i] = 3; 
                best = max(best, minimax(false, alpha, beta));
                board[i] = 2; 
                alpha = max(alpha, best);
                if (alpha >= beta) break; 
            }
        }
        return best;
    }
    else
    {
        int best = 10;
        for (int i = 1; i <= 9; i++)
        {
            if (board[i] == 2)
            {
                board[i] = 5; 
                best = min(best, minimax(true, alpha, beta));
                board[i] = 2; 
                beta = min(beta, best);
                if (beta <= alpha) break; // pruning
            }
        }
        return best;
    }
}

int AI_Move()
{
    int bestVal = -10;
    int bestMove = -1;
    for (int i = 1; i <= 9; i++)
    {
        if (board[i] == 2)
        {
            board[i] = 3; 
            int moveVal = minimax(false, -10, 10);
            board[i] = 2; 
            if (moveVal > bestVal)
            {
                bestMove = i;
                bestVal = moveVal;
            }
        }
    }
    return bestMove;
}

void User_Move()
{
    int pos;
    while (true)
    {
        cout << "Enter your move (1-9): ";
        cin >> pos;
        if (isBlank(pos))
        {
            board[pos] = 5;
            break;
        }
        else
        {
            cout << "Invalid move, try again.\n";
        }
    }
}

int main()
{
    cout << "You are O, computer is X.\n";
    displayBoard();
    for (turn = 1; turn <= 9; turn++)
    {
        if (turn % 2 == 1)
        {
            int aiMove = AI_Move();
            board[aiMove] = 3;
            cout << "Computer played " << aiMove << "\n";
        }
        else
        {
            User_Move();
        }
        displayBoard();
        int winner = checkWin();
        if (winner == 3)
        {
            cout << "Computer (X) wins!\n";
            break;
        }
        if (winner == 5)
        {
            cout << "You (O) win!\n";
            break;
        }
    }
    if (!checkWin() && !movesLeft())
    {
        cout << "It's a draw!\n";
    }
    return 0;
}
