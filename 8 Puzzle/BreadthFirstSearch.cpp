#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <list>
using namespace std;

using Matrix = vector<vector<int>>;

list<Matrix> genmove(Matrix state)
{
    list<Matrix> nextStates;
    int a, b;

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (state[i][j] == 0)
            {
                a = i;
                b = j;
            }

    if (a > 0) { Matrix s = state; swap(s[a][b], s[a-1][b]); nextStates.push_back(s); }
    if (a < 2) { Matrix s = state; swap(s[a][b], s[a+1][b]); nextStates.push_back(s); }
    if (b > 0) { Matrix s = state; swap(s[a][b], s[a][b-1]); nextStates.push_back(s); }
    if (b < 2) { Matrix s = state; swap(s[a][b], s[a][b+1]); nextStates.push_back(s); }

    return nextStates;
}

string matrixToString(Matrix mat)
{
    string s;
    for (auto row : mat)
        for (int val : row)
            s += to_string(val);
    return s;
}

void bfs(Matrix prob, Matrix sol)
{
    queue<Matrix> q;
    unordered_set<string> closed;

    q.push(prob);
    closed.insert(matrixToString(prob));

    while (!q.empty())
    {
        Matrix A = q.front();
        q.pop();

        if (A == sol)
        {
            cout << "Success!" << endl;
            return;
        }

        list<Matrix> states = genmove(A);
        for (auto state : states)
        {
            string str = matrixToString(state);
            if (closed.find(str) == closed.end())
            {
                closed.insert(str);
                q.push(state);
            }
        }
    }

    cout << "Failed!" << endl;
}

int main()
{
    Matrix prob = {
        {1, 2, 3},
        {4, 0, 6},
        {7, 5, 8}};

    Matrix sol = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 0}};

    bfs(prob, sol);

    return 0;
}
