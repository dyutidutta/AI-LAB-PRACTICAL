#include <iostream>
#include <vector>
#include <unordered_set>
#include <list>
using namespace std;

using Matrix = vector<vector<int>>;

struct Node {
    Matrix state;
    int h;
};

list<Matrix> genmove(Matrix state) {
    list<Matrix> nextStates;
    int a,b;
    for (int i=0; i<3; ++i)
        for (int j=0; j<3; ++j)
            if (state[i][j] == 0) { a=i; b=j; }

    if (a > 0) { Matrix s = state; swap(s[a][b], s[a-1][b]); nextStates.push_back(s); }
    if (a < 2) { Matrix s = state; swap(s[a][b], s[a+1][b]); nextStates.push_back(s); }
    if (b > 0) { Matrix s = state; swap(s[a][b], s[a][b-1]); nextStates.push_back(s); }
    if (b < 2) { Matrix s = state; swap(s[a][b], s[a][b+1]); nextStates.push_back(s); }

    return nextStates;
}

string matrixToString(Matrix mat) {
    string s;
    for (auto &row : mat)
        for (int val : row)
            s += char('0' + val);
    return s;
}

int heuristic(Matrix state, Matrix goal) {
    int pos[9][2];
    for (int i=0; i<3; ++i)
        for (int j=0; j<3; ++j) {
            pos[goal[i][j]][0] = i;
            pos[goal[i][j]][1] = j;
        }

    int dist = 0;
    for (int i=0; i<3; ++i)
        for (int j=0; j<3; ++j) {
            int val = state[i][j];
            if (val != 0) {
                dist += abs(i - pos[val][0]) + abs(j - pos[val][1]);
            }
        }
    return dist;
}

void hillClimbing(Matrix prob, Matrix goal) {
    Node cur = {prob, heuristic(prob, goal)};
    unordered_set<string> visited;
    visited.insert(matrixToString(cur.state));

    while (true) {
        if (cur.state == goal) {
            cout << "Success!" << endl;
            return;
        }

        auto neighbors = genmove(cur.state);

        Node best = cur;
        for (auto &n : neighbors) {
            string nStr = matrixToString(n);
            if (visited.find(nStr) != visited.end()) continue; 

            int h = heuristic(n, goal);
            if (h < best.h) {
                best = {n, h};
            }
        }

        if (best.h >= cur.h) {
            cout << "Stuck at local minimum or plateau!" << endl;
            //Local minimum: All neighbors have a worse heuristic value (higher cost), but you haven’t reached the goal.
            //Plateau: All neighbors have the same heuristic value, so there’s no clear better move.
            return;
        }

        cur = best;
        visited.insert(matrixToString(cur.state));
    }
}

int main() {
    Matrix prob = {
        {1,2,3},
        {5,0,6},
        {4,7,8}
    };
    Matrix goal = {
        {1,2,3},
        {4,5,6},
        {7,8,0}
    };
    hillClimbing(prob, goal);
    return 0;
}
