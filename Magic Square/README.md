<h1 align="center">Artificial Intelligence</h1>

## Practical :- Magic Square Generation (Odd, Doubly Even, Singly Even) in C++

### ● Problem Statement

A **Magic Square** is an *n × n* grid filled with distinct positive integers from `1` to `n²` such that the sum of the integers in each row, column, and both main diagonals is the same — called the **Magic Constant**.

Depending on the order `n` of the square:
- **Odd Order** (`n` odd)  
- **Doubly Even Order** (`n % 4 == 0`)  
- **Singly Even Order** (`n` even but not divisible by 4)  

This program automatically generates the correct magic square based on the value of `n` entered by the user.

---

### ● Data Structures Used

| Component              | Data Structure / Type       | Purpose |
|------------------------|-----------------------------|---------|
| Magic Square           | `vector<vector<int>>`       | Stores the magic square grid. |
| Temporary Sub-Square   | `vector<vector<int>>`       | Used for constructing singly even squares from odd sub-squares. |
| Row/Column Iteration   | `int` variables             | Loop indices for filling cells. |

---

## ● Algorithms: 
### 1. **Odd Order Magic Square (Siamese Method)**

#### Idea:
Start at the middle of the top row and place numbers sequentially, moving up and right. If the next cell is filled or out of bounds, move down one cell.

#### Pseudocode:
```
FUNCTION oddMagicSquare(n, m):
    i ← 0
    j ← n / 2
    FOR num = 1 to n²:
        m[i][j] ← num
        ni ← (i - 1 + n) mod n
        nj ← (j + 1) mod n
        IF m[ni][nj] is already filled:
            i ← (i + 1) mod n
        ELSE:
            i ← ni
            j ← nj
```

---

### 2. **Doubly Even Order Magic Square (n % 4 == 0)**

#### Idea:
Fill numbers from 1 to n² in order, but in certain diagonals (cells where `(i % 4 == j % 4)` or `(i % 4 + j % 4 == 3)`) replace the value with `n² + 1 - value`.

#### Pseudocode:
```
FUNCTION doublyEvenMagicSquare(n, s):
    num ← 1
    FOR i = 0 to n-1:
        FOR j = 0 to n-1:
            IF (i % 4 == j % 4) OR ((i % 4 + j % 4) == 3):
                s[i][j] ← n² + 1 - num
            ELSE:
                s[i][j] ← num
            num++
```

---

### 3. **Singly Even Order Magic Square (n even but not divisible by 4)**

#### Idea:
- Divide the square into four *n/2 × n/2* sub-squares.
- Fill each sub-square using the odd-order method.
- Swap specific columns and cells between sub-squares according to a fixed pattern.

#### Pseudocode:
```
FUNCTION singlyEvenMagicSquare(n, s):
    h ← n / 2
    subSize ← h²
    sub ← h × h magic square (odd method)

    FOR r = 0 to h-1:
        FOR c = 0 to h-1:
            v ← sub[r][c]
            s[r][c] ← v
            s[r + h][c + h] ← v + subSize
            s[r][c + h] ← v + 2*subSize
            s[r + h][c] ← v + 3*subSize

    k ← (h - 1) / 2
    FOR r = 0 to h-1:
        FOR c = 0 to k-1:
            SWAP s[r][c] ↔ s[r + h][c]

    FOR r = 0 to h-1:
        FOR c = n - k + 1 to n-1:
            SWAP s[r][c] ↔ s[r + h][c]
```

---

### 4. **Printing the Magic Square**

```
FUNCTION printMagicSquare(s):
    n ← size of s
    FOR each row in s:
        PRINT row elements separated by tabs
    PRINT "Magic Constant = n × (n² + 1) / 2"
```

---

## ● Sample Test Cases

### Odd Order Example (n = 3):
```
Enter size of Magic Square (n >= 3): 3
Magic Square of size 3:
8   1   6
3   5   7
4   9   2
Magic Constant = 15
```

### Doubly Even Order Example (n = 4):
```
Enter size of Magic Square (n >= 3): 4
Magic Square of size 4:
1   15  14  4
12  6   7   9
8   10  11  5
13  3   2   16
Magic Constant = 34
```

### Singly Even Order Example (n = 6):
```
Enter size of Magic Square (n >= 3): 6
Magic Square of size 6:
35  1   6   26  19  24
3   32  7   21  23  25
31  9   2   22  27  20
8   28  33  17  10  15
30  5   34  12  14  16
4   36  29  13  18  11
Magic Constant = 111
```

---

### ● Use Cases

- **Mathematics Education** – Teaching combinatorics, number theory, and matrix manipulation.
- **Puzzle Generation** – Used in games and logic challenges.
- **Pattern Recognition** – Understanding symmetrical arrangements in AI research.
- **Art & Design** – Creating patterns with balanced sums for aesthetic purposes.

---

### ● Limitations

- **n < 3** – Magic square is not possible.
- For large `n`, computation is still efficient (O(n²)) but printing becomes large.
- This implementation generates **one** valid magic square; others exist.

---

### ● Time and Space Complexities
- **Odd Method:** O(n²) time, O(n²) space.
- **Doubly Even Method:** O(n²) time, O(n²) space.
- **Singly Even Method:** O(n²) time, O(n²) space.

| Method        | Time Complexity | Space Complexity |
|---------------|----------------|------------------|
| Odd           | O(n²)          | O(n²)            |
| Doubly Even   | O(n²)          | O(n²)            |
| Singly Even   | O(n²)          | O(n²)            |

---

### ● Files

| Filename               | Description                                   |
|------------------------|-----------------------------------------------|
| `magic_square.cpp`     | Generate magic squares |
| `README.md`            | Documentation and explanation                 |
