#include <iostream>
#include <algorithm>
using namespace std;

int X, Y;     
int curX = 0, curY = 0;  

void fillX() {curX = X;}
void fillY() {curY = Y;}
void emptyX() {curX = 0;}
void emptyY() {curY = 0;}

void pourXtoY() {
    int pour = min(curX, Y - curY);
    curX -= pour;
    curY += pour;
}

void pourYtoX() {
    int pour = min(curY, X - curX);
    curY -= pour;
    curX += pour;
}

bool reachedGoal(int Z) {
    return (curX == Z || curY == Z);
}

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    cout << "Enter capacity of jug X: ";
    cin >> X;
    cout << "Enter capacity of jug Y: ";
    cin >> Y;
    cout << "Enter goal volume Z: ";
    int Z;
    cin >> Z;

    if (Z > max(X, Y) || Z % gcd(X, Y) != 0) {
        cout << "Goal not achievable with given jug sizes.\n";
        return 0;
    }

    curX = 0; curY = 0;

    cout << "Initial state: (" << curX << ", " << curY << ")\n";

    while (!reachedGoal(Z)) {
        if (curX == 0) {
            fillX();
            cout << "Fill X: (" << curX << ", " << curY << ")\n";
        } 
        else if (curY < Y) {
            pourXtoY();
            cout << "Pour X->Y: (" << curX << ", " << curY << ")\n";
        } 
        else if (curY == Y) {
            emptyY();
            cout << "Empty Y: (" << curX << ", " << curY << ")\n";
        }
    }

    cout << "Goal reached.\n";
    return 0;
}
