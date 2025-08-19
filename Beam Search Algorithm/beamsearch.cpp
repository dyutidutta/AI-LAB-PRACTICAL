#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <cmath>
#include <algorithm>
using namespace std;

struct Node {
    int i, j;    
    double h;    
    Node* parent;
};

struct CompareNode {
    bool operator()(Node* a, Node* b) {
        return a->h > b->h;   
    }
};

bool wincheck(Node* a, int gi, int gj) {
    return (a->i == gi && a->j == gj);
}

list<Node*> genmove(Node* state, int gi, int gj, int N, vector<pair<int,int>>& water) {
    list<Node*> nextStates;
    int a = state->i;
    int b = state->j;

    int di[8] = {-1,1,0,0,-1,-1,1,1};
    int dj[8] = {0,0,-1,1,-1,1,-1,1};

    for (int k=0; k<8; k++) {
        int ni = a + di[k], nj = b + dj[k];
        if (ni>=0 && ni<N && nj>=0 && nj<N) { 
            Node* s = new Node;
            s->parent = state;
            s->i = ni; s->j = nj;

            
            bool isWater = false;
            for (auto &w : water) {
                if (w.first == ni && w.second == nj) {
                    isWater = true;
                    break;
                }
            }

            if (isWater) {
                s->h = INFINITY;
            } else {
                s->h = abs(ni - gi) + abs(nj - gj); 
            }
            nextStates.push_back(s);
        }
    }
    return nextStates;
}

void displayGrid(int N, vector<pair<int,int>>& water, vector<Node*>& closed,
                 vector<pair<int,int>>& path, Node* start, int gi, int gj) {
    vector<vector<string>> grid(N, vector<string>(N, "."));  

    
    for (auto &w : water) grid[w.first][w.second] = "W";

    
    for (auto c : closed) {
        if (grid[c->i][c->j] == ".")
            grid[c->i][c->j] = "+";
    }

    
    for (size_t step = 0; step < path.size(); step++) {
        int x = path[step].first;
        int y = path[step].second;

        
        if (!(x == start->i && y == start->j) && !(x == gi && y == gj)) {
            grid[x][y] = to_string(step);  
        }
    }

    
    grid[start->i][start->j] = "S";
    grid[gi][gj] = "G";

    
    cout << "\nGrid representation:\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout.width(3);   
            cout << grid[i][j] << " ";
        }
        cout << "\n";
    }
}


void beamSearch(Node* start, int gi, int gj, int N, vector<pair<int,int>>& water, int beamWidth) {
    vector<Node*> openList;
    openList.push_back(start);
    vector<Node*> closed;

    while (!openList.empty()) {
        vector<Node*> neighbours;  

        for (auto curr : openList) {
            bool inClosed = false;
            for (auto c : closed) {
                if (c->i == curr->i && c->j == curr->j) {
                    inClosed = true;
                    break;
                }
            }
            if (inClosed) continue;
            closed.push_back(curr);

            if (wincheck(curr, gi, gj)) {
                cout << "Path found!\n";
                vector<pair<int,int>> path;
                Node* p = curr;
                while (p) {
                    path.push_back({p->i,p->j});
                    p = p->parent;
                }
                reverse(path.begin(), path.end());

                displayGrid(N, water, closed, path, start, gi, gj);

                cout << "\nPath coordinates:\n";
                for (size_t i = 0; i < path.size(); i++) {
                    cout << "(" << path[i].first << "," << path[i].second << ")";
                    if (i < path.size() - 1)
                        cout << " -> ";
                }
                cout << endl;
                return;
            }

            list<Node*> expanded = genmove(curr, gi, gj, N, water);
            for (Node* n : expanded) {
                if (n->h != INFINITY) {
                    neighbours.push_back(n);
                }
            }
        }

        sort(neighbours.begin(), neighbours.end(), [](Node* a, Node* b) {
            return a->h < b->h;
        });
        if ((int)neighbours.size() > beamWidth) {
            neighbours.resize(beamWidth);
        }

        openList = neighbours; 
    }
    cout << "No path found!\n";
}

int main() {
    int N;
    cout << "Enter grid size N: ";
    cin >> N;

    int si, sj, gi, gj;
    cout << "Enter start (si sj): ";
    cin >> si >> sj;
    cout << "Enter goal (gi gj): ";
    cin >> gi >> gj;

    int W;
    cout << "Enter number of water nodes: ";
    cin >> W;
    vector<pair<int,int>> water(W);
    for (int k=0; k<W; k++) {
        cout << "Enter water node " << k+1 << " (wi wj): ";
        cin >> water[k].first >> water[k].second;
    }

    double start_h = abs(si - gi) + abs(sj - gj);
    Node* start = new Node{si, sj, start_h, NULL};

    int beamWidth;
    cout << "Enter beam width: ";
    cin >> beamWidth;

    beamSearch(start, gi, gj, N, water, beamWidth);
    return 0;
}
