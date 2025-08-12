#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <list>
using namespace std;

using Matrix = vector<vector<int>>;

struct Node {
    Matrix state;
    int h;
};

struct CompareNode {
    bool operator()( Node a, Node b) 
    {
        return a.h > b.h; // smaller h = higher priority
    }
};

list<Matrix> genmove( Matrix state) {
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

string matrixToString( Matrix mat) {
    string s;
    for (auto &row : mat)
        for (int val : row)
            s += char('0' + val);
    return s;
}

int heuristic( Matrix state, Matrix goal) {
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

void bestFirstSearch( Matrix prob, Matrix goal) {
    priority_queue<Node, vector<Node>, CompareNode> pq;
    unordered_set<string> closed;

    pq.push({prob, heuristic(prob, goal)});
    closed.insert(matrixToString(prob));

    while (!pq.empty()) {
        Node cur = pq.top();
        pq.pop();

        if (cur.state == goal) {
            cout << "Success!" << endl;
            return;
        }

        for (auto &child : genmove(cur.state)) {
            string childStr = matrixToString(child);
            if (closed.find(childStr) == closed.end()) {
                closed.insert(childStr);
                pq.push({child, heuristic(child, goal)});
            }
        }
    }

    cout << "Failed!" << endl;
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
    bestFirstSearch(prob, goal);
    return 0;
}
