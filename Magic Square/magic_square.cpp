#include <iostream>
#include <vector>
using namespace std;

void oddMagicSquare(int n, vector<vector<int>> &m)
{
    int i = 0, j = n / 2;
    for (int num = 1; num <= n * n; num++)
    {
        m[i][j] = num;
        int ni = (i - 1 + n) % n, nj = (j + 1) % n;
        if (m[ni][nj])
            i = (i + 1) % n;
        else
            i = ni, j = nj;
    }
}

void doublyEvenMagicSquare(int n, vector<vector<int>> &s)
{
    int num = 1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            s[i][j] = ((i % 4 == j % 4) || ((i % 4 + j % 4) == 3))
                          ? n * n + 1 - num++
                          : num++;
}

void singlyEvenMagicSquare(int n, vector<vector<int>> &s)
{
    int h = n / 2, subSize = h * h;
    vector<vector<int>> sub(h, vector<int>(h));
    oddMagicSquare(h, sub);

    for (int r = 0; r < h; r++)
        for (int c = 0; c < h; c++)
        {
            int v = sub[r][c];
            s[r][c] = v;
            s[r + h][c + h] = v + subSize;
            s[r][c + h] = v + 2 * subSize;
            s[r + h][c] = v + 3 * subSize;
        }

    int k = (h - 1) / 2;
    for (int r = 0; r < h; r++)
        for (int c = 0; c < k; c++)
            swap(s[r][c], s[r + h][c]);
    for (int r = 0; r < h; r++)
        for (int c = n - k + 1; c < n; c++)
            swap(s[r][c], s[r + h][c]);
}

void printMagicSquare(const vector<vector<int>> &s)
{
    int n = s.size();
    for (auto &row : s)
    {
        for (int v : row)
            cout << v << "\t";
        cout << "\n";
    }
    cout << "\nMagic Constant = " << n * (n * n + 1) / 2 << "\n";
}

int main()
{
    int n;
    cout << "Enter size of Magic Square (n >= 3): ";
    cin >> n;
    if (n < 3)
        return cout << "Magic square not possible for n < 3.\n", 0;

    vector<vector<int>> square(n, vector<int>(n));
    if (n % 2)
        oddMagicSquare(n, square);
    else if (n % 4 == 0)
        doublyEvenMagicSquare(n, square);
    else
        singlyEvenMagicSquare(n, square);

    cout << "\nMagic Square of size " << n << ":\n";
    printMagicSquare(square);
    return 0;
}
