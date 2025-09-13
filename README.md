<h1 align="center">Artificial Intelligence</h1>

---

## Practical Aim:- 8-Puzzle Problem using BFS, DFS, Best-First Search, and Hill Climbing in C++

---

### ● Problem Statement

The **8-Puzzle Problem** is a classic problem in artificial intelligence and graph theory. It consists of a 3x3 grid with tiles numbered 1-8 and one empty space (represented as `0`). The goal is to move the tiles into the correct position by sliding them one at a time into the empty space, ultimately reaching a predefined goal state.

#

### ● Data Structures Used

| Component             | Data Structure / Type                   | Purpose                                                                  |
|-----------------------|-----------------------------------------|--------------------------------------------------------------------------|
| Puzzle State          | `vector<vector<int>>`                   | 3x3 matrix to represent the puzzle.                                      |
| Visited Set           | `unordered_set<string>`                 | Stores string representations of visited states.                         |
| Frontier (BFS)        | `queue<Matrix>`                         | Stores states to explore next in BFS.                                    |
| Frontier (DFS)        | `stack<Matrix>`                         | Stores states to explore next in DFS.                                    |
| Frontier (BestFS)     | `priority_queue<Node>`                  | Stores states prioritized by heuristic.                                  |
| State Generation      | `list<Matrix>`                          | Stores all valid next states.                                            |
| Node Structure  | `struct Node { Matrix state; int h; };` | Current state and heuristic (Manhattan Distance).                        |

#

### ● Algorithms: 

#### Common Helper Functions:

These two functions are used in **BFS**, **DFS**, **Best-First Search** and **Hill Climbing Approach**.

**1. State Generation (`genmove`)**  
Generates all possible valid moves from the current puzzle state.
```
FUNCTION genmove(state):
    nextStates ← empty list
    FIND coordinates (a, b) where state[a][b] = 0

    IF a > 0:
        s ← copy of state
        swap s[a][b] with s[a-1][b]
        append s to nextStates

    IF a < 2:
        s ← copy of state
        swap s[a][b] with s[a+1][b]
        append s to nextStates

    IF b > 0:
        s ← copy of state
        swap s[a][b] with s[a][b-1]
        append s to nextStates

    IF b < 2:
        s ← copy of state
        swap s[a][b] with s[a][b+1]
        append s to nextStates

    RETURN nextStates
```

**2. Matrix to String Conversion (`matrixToString`)**  
Converts a puzzle state into a single string for easy storage in visited sets.

```
FUNCTION matrixToString(mat):
    s ← empty string
    FOR each row in mat:
        FOR each value in row:
            append value to s as a string
    RETURN s
```    

#

#### Breadth-First Search (BFS)

##### **Idea**
Breadth-First Search explores states **level by level**, expanding all nodes at a given depth before moving to the next. Since all moves have equal cost in the 8-puzzle, BFS guarantees finding the **shortest solution path** if one exists.

##### **Input**
- `Matrix prob` → Initial puzzle configuration  
- `Matrix sol` → Goal puzzle configuration  

##### **Output**
- `"Success!"` if goal state is found  
- `"Failed!"` if no solution exists  

##### **Pseudocode**

```
FUNCTION bfs(prob, sol):
    q ← empty queue
    closed ← empty set

    ENQUEUE prob into q
    INSERT matrixToString(prob) into closed

    WHILE q is not empty:
        A ← DEQUEUE from q

        IF A equals sol:
            PRINT "Success!"
            RETURN

        states ← genmove(A)
        FOR each state in states:
            str ← matrixToString(state)
            IF str not in closed:
                INSERT str into closed
                ENQUEUE state into q

    PRINT "Failed!"
```

#

#### Depth-First Search (DFS)

##### **Idea**
Depth-First Search explores states by going **as deep as possible** along one path before backtracking. It uses less memory compared to BFS but does not guarantee the shortest solution and may get stuck exploring deep or infinite paths.

##### **Input**
- `Matrix prob` → Initial puzzle configuration  
- `Matrix sol` → Goal puzzle configuration  

##### **Output**
- `"Success!"` if goal state is found  
- `"Failed!"` if no solution exists  

##### **Pseudocode**
```
FUNCTION dfs(prob, sol):
    s ← empty stack
    closed ← empty set

    PUSH prob into s
    INSERT matrixToString(prob) into closed

    WHILE s is not empty:
        A ← POP from s

        IF A equals sol:
            PRINT "Success!"
            RETURN

        states ← genmove(A)
        FOR each state in states:
            str ← matrixToString(state)
            IF str not in closed:
                INSERT str into closed
                PUSH state into s

    PRINT "Failed!"
```

#

#### Best-First Search (Using Heuristics)

##### **Idea**
Best-First Search selects the next state to explore based on the **heuristic value** — an estimate of how close the current state is to the goal.  

##### **Heuristic Function**
The **Manhattan Distance** for a tile is the sum of the absolute differences between its current coordinates and its goal coordinates.  
The total heuristic is the sum over all tiles (ignoring `0`).

##### **Input**
- `Matrix prob` → Initial puzzle configuration  
- `Matrix goal` → Goal puzzle configuration  

##### **Output**
- `"Success!"` if goal state is found  
- `"Failed!"` if no solution exists 
##### **Pseudocode**
```
FUNCTION heuristic(state, goal):
    pos ← dictionary storing positions of each number in goal
    dist ← 0
    FOR i in 0..2:
        FOR j in 0..2:
            val ← state[i][j]
            IF val != 0:
                dist += |i - pos[val].row| + |j - pos[val].col|
    RETURN dist
```

```
FUNCTION bestFirstSearch(prob, goal):
    pq ← empty priority queue (min-heap by heuristic value)
    closed ← empty set

    CREATE Node with:
        state = prob
        h = heuristic(prob, goal)
    INSERT Node into pq (ordered by h)

    INSERT matrixToString(prob) into closed

    WHILE pq is not empty:
        cur ← REMOVE_TOP from pq

        IF cur.state == goal:
            PRINT "Success!"
            RETURN

        FOR each child in genmove(cur.state):
            str ← matrixToString(child)
            IF str not in closed:
                INSERT str into closed
                CREATE Node with:
                    state = child
                    h = heuristic(child, goal)
                INSERT Node into pq (ordered by h)

    PRINT "Failed!"
```
#

#### Hill Climbing Search

##### **Idea**
Hill Climbing is a **heuristic search algorithm** that continuously moves to the neighbor state with the **lowest heuristic value** (closest to the goal).  
Unlike BFS or Best-First, it only looks **one step ahead** and may get stuck in local minima or plateaus.

##### **Heuristic Function**
The **Manhattan Distance** for a tile is the sum of the absolute differences between its current coordinates and its goal coordinates.  
The total heuristic is the sum over all tiles (ignoring `0`).

##### **Input**
- `Matrix prob` → Initial puzzle configuration  
- `Matrix goal` → Goal puzzle configuration  

##### **Output**
- `"Success!"` if goal state is found  
- `"Stuck at local minimum or plateau!"` if no better neighbor is found (algorithm halts)

##### **Pseudocode**
```
FUNCTION heuristic(state, goal):
    pos ← dictionary storing positions of each number in goal
    dist ← 0
    FOR i in 0..2:
        FOR j in 0..2:
            val ← state[i][j]
            IF val != 0:
                dist += |i - pos[val].row| + |j - pos[val].col|
    RETURN dist
```

```
FUNCTION hillClimbing(prob, goal):
    cur ← (prob, heuristic(prob, goal))
    visited ← empty set
    INSERT matrixToString(prob) into visited

    WHILE True:
        IF cur.state == goal:
            PRINT "Success!"
            RETURN

        neighbors ← genmove(cur.state)
        best ← cur

        FOR each n in neighbors:
            IF n not in visited:
                h ← heuristic(n, goal)
                IF h < best.h:
                    best ← (n, h)

        IF best.h >= cur.h:
            PRINT "Stuck at local minimum or plateau!"
            RETURN

        cur ← best
        INSERT matrixToString(cur.state) into visited
```

#

### ● Sample Test Cases: 
#### Breadth First Search:
**Initial State:**
```
1 2 3
4 0 6
7 5 8
```

**Goal State:**
```
1 2 3
4 5 6
7 8 0
```
**Output:**
```
Success!
```

#### Depth First Search:
**Initial State:**
```
1 2 3
4 5 6
0 7 8
```

**Goal State:**
```
1 2 3
4 5 6
7 8 0
```
**Output:**
```
Success!
```

#### Best-First Search:
**Initial State:**
```
1 2 3
5 0 6
4 7 8
```

**Goal State:**
```
1 2 3
4 5 6
7 8 0
```
**Output:**
```
Success!
```

#### Hill Climbing Approach:
**Initial State:**
```
1 2 3
5 0 6
4 7 8
```

**Goal State:**
```
1 2 3
4 5 6
7 8 0
```

**Output:**
```
Success!
```

#

### ● Use Cases: 

- **Breadth-First Search (BFS)**  
  - Finding the **shortest solution path** when all moves have equal cost (e.g., solving small puzzles, unweighted pathfinding).  
  - Teaching **uninformed search algorithms** in AI courses due to its simplicity and completeness.  

- **Depth-First Search (DFS)**  
  - Exploring **deep solutions** where the path length isn’t important, and memory efficiency is needed.  
  - Traversing **large state spaces** when only one valid solution is required without checking all possibilities.  

- **Best-First Search (Greedy Search)**  
  - Solving problems where a **heuristic estimate** can guide the search toward the goal efficiently (e.g., Manhattan distance in puzzles).  
  - AI navigation and **robot path planning** where we want a quick, heuristic-driven solution rather than guaranteed optimality.  

- **Hill Climbing Approach**  
    - Works well when the **heuristic landscape is smooth** with fewer local minima.  
    - Demonstrates **local search techniques** in AI courses.  
 
#

### ● Limitations

- **BFS**:  
  - High **memory usage** in large search spaces.  
  - Can be slow if the solution is deep.  

- **DFS**:  
  - **May get stuck** exploring a long or infinite branch.  
  - Not guaranteed to find the shortest solution.  

- **Best-First Search**:  
  - Heuristic may **mislead** the search into suboptimal paths.  
  - Not guaranteed to find the shortest path unless using A*.  

- **Hill Climbing Approach**:
    - May get stuck in **local minima** (better than all neighbors but not the goal).  
    - May get stuck on **plateaus** (all neighbors equally good).  
 
#

### ● Time and Space Complexities
  - b → branching factor (max possible moves from a state; for 8-puzzle, b ≤ 4)
  - d → depth of the goal state

| Algorithm            | Time Complexity                                       | Space Complexity |
|----------------------|-------------------------------------------------------|------------------|
| `BreadthFirstSearch` | O(b<sup>d</sup>)                                      | O(b<sup>d</sup>)   |
| `DepthFirstSearch`   | O(b<sup>d</sup>)                                      | O(b·d) | 
| `BestFirstSearch`    | O(b·log b × d) (average) to O(b<sup>d</sup>) (worst)  | O(b<sup>d</sup>) |
| `HillClimbing`       | O(b·d)       | O(d)             |

#

### ● Files

| Filename                 | Description                                  |
|--------------------------|----------------------------------------------|
| `BreadthFirstSearch.cpp` | BFS-based 8-puzzle solver                    |
| `DepthFirstSearch.cpp`   | DFS-based 8-puzzle solver                    |
| `BestFirstSearch.cpp`    | Best-First Search 8-puzzle solver            |
| `HillClimbingApproach.cpp` | Hill Climbing-based 8-puzzle solver        |
| `README.md`              | Explanation and documentation                |

#
---

## Practical Aim:- Magic Square Generation in C++

---

### ● Problem Statement

A **Magic Square** is an *n × n* grid filled with distinct positive integers from `1` to `n²` such that the sum of the integers in each row, column, and both main diagonals is the same — called the **Magic Constant**.

Depending on the order `n` of the square:
- **Odd Order** (`n` odd)  
- **Doubly Even Order** (`n % 4 == 0`)  
- **Singly Even Order** (`n` even but not divisible by 4)  

This program automatically generates the correct magic square based on the value of `n` entered by the user.

#

### ● Data Structures Used

| Component              | Data Structure / Type       | Purpose |
|------------------------|-----------------------------|---------|
| Magic Square           | `vector<vector<int>>`       | Stores the magic square grid. |
| Temporary Sub-Square   | `vector<vector<int>>`       | Used for constructing singly even squares from odd sub-squares. |
| Row/Column Iteration   | `int` variables             | Loop indices for filling cells. |

#

### ● Algorithms: 
#### 1. **Odd Order Magic Square (Siamese Method)**

##### Idea:
Start at the middle of the top row and place numbers sequentially, moving up and right. If the next cell is filled or out of bounds, move down one cell.

##### Pseudocode:
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

#

#### 2. **Doubly Even Order Magic Square (n % 4 == 0)**

##### Idea:
Fill numbers from 1 to n² in order, but in certain diagonals (cells where `(i % 4 == j % 4)` or `(i % 4 + j % 4 == 3)`) replace the value with `n² + 1 - value`.

##### Pseudocode:
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

#

#### 3. **Singly Even Order Magic Square (n even but not divisible by 4)**

##### Idea:
- Divide the square into four *n/2 × n/2* sub-squares.
- Fill each sub-square using the odd-order method.
- Swap specific columns and cells between sub-squares according to a fixed pattern.

##### Pseudocode:
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

#

#### 4. **Printing the Magic Square**

```
FUNCTION printMagicSquare(s):
    n ← size of s
    FOR each row in s:
        PRINT row elements separated by tabs
    PRINT "Magic Constant = n × (n² + 1) / 2"
```

#

### ● Sample Test Cases

#### Odd Order Example (n = 3):
```
Enter size of Magic Square (n >= 3): 3
Magic Square of size 3:
8   1   6
3   5   7
4   9   2
Magic Constant = 15
```

#### Doubly Even Order Example (n = 4):
```
Enter size of Magic Square (n >= 3): 4
Magic Square of size 4:
1   15  14  4
12  6   7   9
8   10  11  5
13  3   2   16
Magic Constant = 34
```

#### Singly Even Order Example (n = 6):
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

#

### ● Use Cases

- **Mathematics Education** – Teaching combinatorics, number theory, and matrix manipulation.
- **Puzzle Generation** – Used in games and logic challenges.
- **Pattern Recognition** – Understanding symmetrical arrangements in AI research.
- **Art & Design** – Creating patterns with balanced sums for aesthetic purposes.

#

### ● Limitations

- **n < 3** – Magic square is not possible.
- For large `n`, computation is still efficient (O(n²)) but printing becomes large.
- This implementation generates **one** valid magic square; others exist.

#

### ● Time and Space Complexities
- **Odd Method:** O(n²) time, O(n²) space.
- **Doubly Even Method:** O(n²) time, O(n²) space.
- **Singly Even Method:** O(n²) time, O(n²) space.

| Method        | Time Complexity | Space Complexity |
|---------------|----------------|------------------|
| Odd           | O(n²)          | O(n²)            |
| Doubly Even   | O(n²)          | O(n²)            |
| Singly Even   | O(n²)          | O(n²)            |

#

### ● Files

| Filename               | Description                                   |
|------------------------|-----------------------------------------------|
| `magic_square.cpp`     | Generate magic squares |
| `README.md`            | Documentation and explanation                 |


#

---

## Practical Aim:- Tic-Tac-Toe with and without Magic Square Logic

---

### ● Problem Statement
Tic-Tac-Toe is a two-player game played on a 3×3 grid. The players alternate placing marks (X or O) in empty cells, and the first to align three marks horizontally, vertically, or diagonally wins. 
Here, we present:
- **Normal Approach** – Win is detected by matching the player's value across a row, column, or diagonal.
- **Magic Square Approach** – Win is detected if the sum of the magic square values for a player's moves equals 15.
Both versions allow a **human player (O)** to play against the **computer (X)**.

#

### ● Data Structures Used

| Component          | Data Structure        | Purpose |
|--------------------|-----------------------|---------|
| Board              | `vector<int>`         | Stores cell state (`2` = blank, `3` = X, `5` = O). |
| Magic Square map   | `int magicSquare[10]` | Maps positions 1–9 to magic square values. |
| Turn counter       | `int`                 | Tracks turn number. |

#

### ● Utility Functions

| Function Name       | Purpose |
|---------------------|---------|
| `isBlank(int pos)`    | Checks if a given board position is within range and empty (2). |
| `AnyBlank()` | Finds and returns the first available empty position on the board.|
| `Make2()`   | Picks center if available, otherwise selects a side position (not used in this code). |
| `Go(int pos)`        | Places the current player’s mark at the given position (or any blank if invalid).|
| `displayBoard()`    | Prints the current game board with X, O, and . for empty cells. |
| `userMove()`       | Prompts the human player for a valid move and updates the board. |
| `checkWin()`       | Checks all winning combinations to determine if there’s a winner.|
	
#

### ● Algorithms

#### 1. Normal Version
- **Idea:** Represent X as `3` and O as `5`.
- Winning line product for two marks and one blank = `player^2 * 2`.
- If found, place mark in the blank cell.

##### Pseudocode:
```
function Posswin(player):
    target = player * player * 2
    for each line in win options:
        if product == target:
            return blank cell
    return 0
```

#
#### 2. Magic Square Version
- **Idea:** Assign each board position a number from the Lo Shu Magic Square.
- If a player has exactly two positions filled in a win line, check if adding the blank position makes the sum `15`.
- If yes, complete the win.

##### Pseudocode:
```
magicSquare = {0,8,1,6,3,5,7,4,9,2}
function Posswin(player):
    for each line in win options:
        count player marks
        find blank cell
        sum values
        if count == 2 and sum + blank_value == 15:
            return blank_position
    return 0
```
#

### ● Game Flow (Both Versions)
1. Computer (X) starts first.
2. Moves are chosen based on:
   - Try to win.
   - Block opponent's win.
   - Pick strategic position (center, corners, sides).
3. Human enters move number (1–9).
4. After each move, check win condition.
5. End game when:
   - Someone wins.
   - Board is full (draw).

#

### ● Sample Gameplay (Computer X Wins)

```
You are O, computer is X.
Board:
. . .
. . .
. . .

Computer plays...
Board:
X . .
. . .
. . .

Enter your move (1-9): 5
Board:
X . .
. O .
. . .

Computer plays...
Board:
X X .
. O .
. . .

Enter your move (1-9): 9
Board:
X X .
. O .
. . O

Computer plays...
Board:
X X X
. O .
. . O

Computer (X) wins!
```

#

### ● Time and Space Complexities
Both versions have **O(1)** time and **O(1)** space complexity since the board size is fixed (3×3).

| Method        | Time Complexity | Space Complexity |
|---------------|----------------|------------------|
| Magic Square  | O(1)           | O(1)             |
| Normal        | O(1)           | O(1)             |

#
### ● Use Cases
- **Educational** : Demonstrates how to apply magic squares to a game logic problem.
- **Game AI Development:** Example of turn-based decision-making logic.
- **Problem Solving Practice:** Uses combinatorics and optimization.
- **Beginner Game Programming:** Introduces board representation, user input handling, and AI strategy.

#
### ● Files
| Filename              | Description |
|-----------------------|-------------|
| `tictactoe.cpp`       | Contains Normal Tic-Tac-Toe implementation. |
| `tictactoe_magic_square.cpp` | Contains Magic Square Tic-Tac-Toe implementation. |
| `README.md`           | Documentation and explanation. |


#
---

## Practical Aim:- Water Jug Problem (C++ Implementation)

---

### ● Problem Statement
The **Water Jug Problem** is a classic puzzle where we have two jugs with fixed capacities and the goal is to measure exactly `Z` liters of water using the jugs. The only operations allowed are:
- Fill a jug completely
- Empty a jug completely
- Pour water from one jug into the other until one is either empty or full

The program takes **jug capacities X and Y** and **goal volume Z**, and outputs the sequence of steps to achieve the goal.

#

### ● Objective
- Solve the Water Jug Problem using the **mathematical GCD condition** for solvability.
- Simulate step-by-step actions to reach the goal state.
- Demonstrate basic **problem-solving with constraints** in C++.

#

### ● Data Structures Used

| Component         | Data Structure | Purpose |
|-------------------|---------------|---------|
| Jug capacities    | `int`         | Stores maximum capacity of X and Y. |
| Current volumes   | `int`         | Tracks current amount of water in each jug. |
| Helper functions  | Functions     | Perform jug operations like fill, empty, pour. |

#

### ● Algorithm

**Mathematical Basis:**  
A goal volume `Z` is achievable if:
1. `Z <= max(X, Y)`
2. `Z` is a multiple of `gcd(X, Y)`

**Steps (X as main jug, Y as auxiliary):**
1. Start with both jugs empty `(0, 0)`.
2. If `X` is empty → Fill jug X.
3. If `Y` is not full → Pour water from X to Y.
4. If `Y` is full → Empty jug Y.
5. Repeat until either jug contains exactly `Z` liters.

#

#### Utility Functions

| Function Name | Purpose |
|---------------|---------|
| `fillX()` | Fill jug X completely. |
| `fillY()` | Fill jug Y completely. |
| `emptyX()` | Empty jug X. |
| `emptyY()` | Empty jug Y. |
| `pourXtoY()` | Pour water from X into Y until X is empty or Y is full. |
| `pourYtoX()` | Pour water from Y into X until Y is empty or X is full. |
| `reachedGoal(Z)` | Check if either jug contains exactly Z liters. |
| `gcd(a, b)` | Find greatest common divisor (for solvability check). |

#

#### Pseudocode:
```
BEGIN
    INPUT X  
    INPUT Y  
    INPUT Z  

    FUNCTION gcd(a, b):
        WHILE b ≠ 0:
            temp ← b
            b ← a MOD b
            a ← temp
        RETURN a

    IF Z > MAX(X, Y) OR (Z MOD gcd(X, Y) ≠ 0) THEN
        PRINT "Goal not achievable"
        EXIT

    curX ← 0   
    curY ← 0  

    PRINT "Initial state: (curX, curY)"

    WHILE curX ≠ Z AND curY ≠ Z DO
        IF curX == 0 THEN
            curX ← X
            PRINT "Fill X: (curX, curY)"

        ELSE IF curY < Y THEN
            pour ← MIN(curX, Y - curY)
            curX ← curX - pour
            curY ← curY + pour
            PRINT "Pour X->Y: (curX, curY)"

        ELSE IF curY == Y THEN
            curY ← 0
            PRINT "Empty Y: (curX, curY)"
        END IF
    END WHILE

    PRINT "Goal reached."
END

```

#

### ● Sample Test Case

**Input:**
```
Enter capacity of jug X: 4
Enter capacity of jug Y: 3
Enter goal volume Z: 2
```

**Output:**
```
Initial state: (0, 0)
Fill X: (4, 0)
Pour X->Y: (1, 3)
Empty Y: (1, 0)
Pour X->Y: (0, 1)
Fill X: (4, 1)
Pour X->Y: (2, 3)
Goal reached.
```

#

### ● Use Cases

1. **AI Problem Solving Demonstrations** – Classic example in AI lectures.
2. **Mathematical Puzzles** – Solving constraints-based problems.
3. **Competitive Programming Practice** – Teaches modular problem-solving.
4. **Teaching GCD and Number Theory Applications**.
5. **Game & Puzzle Simulation Projects**.

#

### ● Time and Space Complexity

| Operation | Time Complexity | Space Complexity |
|-----------|----------------|------------------|
| GCD Calculation | O(log min(X, Y)) | O(1) |
| **Overall** | O(1) for fixed-size jugs | O(1) |

#

### ● Files Used

| Filename          | Description |
|-------------------|-------------|
| `waterjug.cpp`    | C++ implementation of the Water Jug Problem. |
| `README.md`       | Documentation for the problem and solution. |


#
---
## Practical Aim:- A* Pathfinding Algorithm (C++ Implementation)

---

### ● Problem Statement
The **A\* Algorithm** is a widely used **pathfinding and graph traversal** technique in Artificial Intelligence.  
Given a square grid of size **N × N**, a **start node**, a **goal node**, and some **obstacle cells (water nodes)**, the task is to find the shortest possible path from the start to the goal.  
#

### ● Objective
- Implement A* algorithm for grid-based pathfinding.  
- Avoid obstacle nodes (water cells).  
- Display the **explored states** and the **final shortest path** on the grid.  

#

### ● Data Structures Used

| Component          | Data Structure         | Purpose |
|--------------------|------------------------|---------|
| Grid        | `vector<vector<string>>` | Store symbols for grid display (start, goal, obstacles, explored, path). |
| Node representation | `struct Node`          | Store `(i, j)` position, path cost `g`, heuristic `h`, and parent pointer. |
| Open list          | `priority_queue<Node*>` | Stores frontier nodes, sorted by lowest `f = g + h`. |
| Closed list        | `vector<Node*>`         | Stores already explored nodes. |
| Path               | `vector<pair<int,int>>` | Final sequence of coordinates from start to goal. |

#

### ● Algorithm

**Heuristic Used:**  
- **Manhattan distance** `h = |x - goal_x| + |y - goal_y|`  

**Steps:**  
1. Initialize start node `(si, sj)` with `g=0` and heuristic `h`.  
2. Push start node into priority queue (open list).  
3. While queue is not empty:  
   - Pop node with smallest `f = g + h`.  
   - If node = goal → reconstruct path.  
   - Else, expand all valid 8 neighbors (horizontal, vertical, diagonal).  
   - Skip water nodes and already closed nodes.  
   - Push valid neighbors into queue.  
4. If queue empties without reaching goal → **no path exists**.  

#
#### Utility Functions

| Function | Purpose |
|----------|---------|
| `wincheck(node, gi, gj)` | Checks if current node is the goal. |
| `genmove(state, gi, gj, N, water)` | Generates valid neighbors for a node, assigns costs. |
| `displayGrid(...)` | Prints grid showing obstacles, explored nodes, and final path. |
| `astar(start, gi, gj, N, water)` | Main implementation of A* algorithm. |

#
#### Pseudocode:
```
BEGIN

    DEFINE STRUCT Node:
        i, j          
        g             
        h             
        parent       

    FUNCTION CompareNode(a, b):
        RETURN (a.g + a.h) > (b.g + b.h)   

    FUNCTION wincheck(node, gi, gj):
        RETURN (node.i == gi AND node.j == gj)

    FUNCTION genmove(state, gi, gj, N, water):
        nextStates ← empty list
        directions ← 8 possible moves:
            di = [-1, 1, 0, 0, -1, -1, 1, 1]
            dj = [ 0, 0,-1, 1, -1, 1,-1, 1]
        cost = [1, 1, 1, 1, 1.5, 1.5, 1.5, 1.5]

        FOR k from 0 to 7:
            ni ← state.i + di[k]
            nj ← state.j + dj[k]

            IF (ni, nj) inside grid (0 ≤ ni, nj < N) THEN
                newNode ← new Node
                newNode.i ← ni
                newNode.j ← nj
                newNode.g ← state.g + cost[k]
                newNode.parent ← state

                IF (ni, nj) in water THEN
                    newNode.h ← INFINITY
                ELSE
                    newNode.h ← |ni - gi| + |nj - gj|   
                ENDIF

                ADD newNode to nextStates
        RETURN nextStates

    FUNCTION displayGrid(N, water, closed, path, start, gi, gj):
        CREATE N×N grid filled with "."
        FOR each water cell → mark "W"
        FOR each closed node visited → mark "+"
        FOR each path step → mark step number
        Mark start with "S", goal with "G"
        PRINT the grid row by row

    FUNCTION astar(start, gi, gj, N, water):
        OPEN ← priority queue (min-heap by f = g+h)
        CLOSED ← empty list
        PUSH start into OPEN

        WHILE OPEN not empty:
            curr ← node with lowest f in OPEN
            REMOVE curr from OPEN

            IF curr already in CLOSED → CONTINUE
            ADD curr to CLOSED

            IF wincheck(curr, gi, gj) THEN
                PRINT "Path found!"
                path ← reconstruct path by backtracking parent links
                REVERSE path
                CALL displayGrid(N, water, CLOSED, path, start, gi, gj)
                PRINT path coordinates
                RETURN
            ENDIF

            neighbors ← genmove(curr, gi, gj, N, water)
            FOR each neighbor in neighbors:
                IF neighbor.h == INFINITY → skip   // water
                IF neighbor not in CLOSED → PUSH into OPEN

        PRINT "No path found!"

    MAIN:
        INPUT N
        INPUT start position (si, sj)
        INPUT goal position (gi, gj)
        INPUT number of water cells W
        FOR each water cell → record coordinates in list "water"

        start_h ← |si - gi| + |sj - gj|
        startNode ← new Node {i=si, j=sj, g=0, h=start_h, parent=NULL}

        CALL astar(startNode, gi, gj, N, water)

END

```

#

### ● Sample Test Case

**Input:**
```
Enter grid size N: 5
Enter start (si sj): 0 0
Enter goal (gi gj): 4 4
Enter number of water nodes: 3
Enter water node 1 (wi wj): 1 1
Enter water node 2 (wi wj): 2 2
Enter water node 3 (wi wj): 3 3
```

**Output:**
```
Path found!

Grid representation:
  S   .   .   .   . 
  1   W   .   .   . 
  .   2   W   .   . 
  .   .   3   W   . 
  .   .   .   4   G 

Path coordinates:
(0,0) -> (1,0) -> (2,1) -> (3,2) -> (4,3) -> (4,4) 
```

#

### ● Use Cases

1. **AI Pathfinding in Games** – NPC movement, maze solving.  
2. **Robotics Navigation** – Grid-based path planning.  
3. **Geographic Mapping** – GPS navigation systems.  
4. **Simulation & Visualization** – Demonstrating search algorithms in AI classes. 

#

### ● Time and Space Complexity

| Operation       | Time Complexity            | Space Complexity |
|-----------------|----------------------------|------------------|
| Node expansion  | O(log V + W)               | O(1)             |
| All expansions  | O(V log V + V·W)           | O(V)             |
| **Overall**     | **O(N² log N + N²·W)**     | **O(N²)**        |

Where:  
- `V = N²` (total grid cells)  
- `W` = number of water cells  


#

### ● Files Used

| Filename     | Description |
|--------------|-------------|
| `astar.cpp`  | C++ implementation of A* pathfinding. |
| `README.md`  | Documentation for the implementation. |

#

---
## Practical Aim:- Beam Search Algorithm (C++ Implementation)

---

### ● Problem Statement
The **Beam Search Algorithm** is a heuristic search strategy used in Artificial Intelligence.  
It works by **limiting the search breadth** at each level to the **best `k` nodes** (where `k` is the **beam width**).  

Given:  
- A square grid of size **N × N**,  
- A **start node** `(si, sj)`,  
- A **goal node** `(gi, gj)`,  
- A set of **obstacle cells (water nodes)**,  

The task is to find a path from the start to the goal using Beam Search with a specified **beam width**.

#

### ● Objective
- Implement **Beam Search** for grid-based pathfinding.  
- Restrict search to only the best `k` nodes at each level.  
- Avoid exploring obstacle nodes (water cells).  
- Display the **grid representation**, explored nodes, and the final path.

#

### ● Data Structures Used


| Component          | Data Structure         | Purpose |
|--------------------|------------------------|---------|
| Grid cells         | `vector<vector<string>>` | Stores symbols for grid display (start, goal, obstacles, explored, path). |
| Node representation | `struct Node`          | Stores `(i, j)` position, heuristic `h`, and parent pointer. |
| Open list          | `vector<Node*>`         | Stores current beam candidates (expanded per level). |
| Closed list        | `vector<Node*>`         | Stores already explored nodes. |
| Path               | `vector<pair<int,int>>` | Final sequence of coordinates from start to goal. |

#

### ● Algorithm

**Heuristic Used:**  
- **Manhattan distance** `h = |x - goal_x| + |y - goal_y|`  

**Steps:**  
1. Initialize the start node `(si, sj)` with heuristic `h`.  
2. Put the start node into the **open list**.  
3. Repeat until goal is found or open list is empty:  
   - Expand all nodes in the current open list.  
   - Generate valid neighbors (skip water/obstacles).  
   - Collect all neighbors into a candidate list.  
   - Sort candidates by heuristic `h`.  
   - Keep only the **best `beamWidth`** candidates.  
   - Replace open list with this pruned candidate set.  
4. If goal node is reached → reconstruct and display path.  
5. If open list becomes empty without reaching goal → **no path exists**.  

#
#### Utility Functions

| Function | Purpose |
|----------|---------|
| `wincheck(node, gi, gj)` | Checks if current node is the goal. |
| `genmove(state, gi, gj, N, water)` | Expands valid neighbors for a node and assigns heuristic `h`. |
| `displayGrid(...)` | Prints grid showing obstacles, explored nodes, and final path. |
| `beamSearch(start, gi, gj, N, water, beamWidth)` | Main implementation of Beam Search algorithm. |

#

#### Pseudocode:
```
BEGIN

    DEFINE STRUCT Node:
        i, j        
        h           
        parent      

    FUNCTION wincheck(node, gi, gj):
        RETURN (node.i == gi AND node.j == gj)

    FUNCTION genmove(state, gi, gj, N, water):
        nextStates ← empty list
        directions ← 8 possible moves:
            di = [-1, 1, 0, 0, -1, -1, 1, 1]
            dj = [ 0, 0,-1, 1, -1,  1,-1, 1]

        FOR each direction k:
            ni ← state.i + di[k]
            nj ← state.j + dj[k]

            IF (0 ≤ ni < N) AND (0 ≤ nj < N) THEN
                newNode ← new Node
                newNode.i ← ni
                newNode.j ← nj
                newNode.parent ← state

                IF (ni, nj) in water THEN
                    newNode.h ← INFINITY
                ELSE
                    newNode.h ← |ni - gi| + |nj - gj|
                ENDIF

                ADD newNode to nextStates
        RETURN nextStates

    FUNCTION displayGrid(N, water, closed, path, start, gi, gj):
        CREATE grid[N][N] filled with "."
        FOR each water cell → mark "W"
        FOR each closed node → mark "+"
        FOR each path step (except start & goal) → mark step number
        Mark start as "S" and goal as "G"
        PRINT grid

    FUNCTION beamSearch(start, gi, gj, N, water, beamWidth):
        openList ← { start }
        closed ← empty list

        WHILE openList not empty:
            neighbours ← empty list

            FOR each curr in openList:
                IF curr in closed → skip
                ADD curr to closed

                IF wincheck(curr, gi, gj) THEN
                    PRINT "Path found!"
                    path ← backtrack from curr to start using parent links
                    REVERSE path
                    CALL displayGrid(N, water, closed, path, start, gi, gj)
                    PRINT path coordinates
                    RETURN

                expanded ← genmove(curr, gi, gj, N, water)
                FOR each n in expanded:
                    IF n.h ≠ INFINITY THEN
                        ADD n to neighbours

            SORT neighbours by h (ascending)
            IF size(neighbours) > beamWidth THEN
                KEEP only first beamWidth nodes

            openList ← neighbours

        PRINT "No path found!"

    MAIN:
        INPUT N
        INPUT start (si, sj)
        INPUT goal (gi, gj)
        INPUT number of water cells W
        READ water cell positions into list "water"
        start_h ← |si - gi| + |sj - gj|
        startNode ← new Node {i=si, j=sj, h=start_h, parent=NULL}
        INPUT beamWidth
        CALL beamSearch(startNode, gi, gj, N, water, beamWidth)

END

```

#

### ● Sample Test Case

**Input:**
```
Enter grid size N: 5
Enter start (si sj): 0 0
Enter goal (gi gj): 4 4
Enter number of water nodes: 2
Enter water node 1 (wi wj): 1 1
Enter water node 2 (wi wj): 3 2
Enter beam width: 3
```

**Output:**
```
Path found!

Grid representation:
  S   1   .   .   . 
  +   W   2   +   . 
  +   +   .   3   . 
  .   +   W   +   4 
  .   .   +   .   G 

Path coordinates:
(0,0) -> (0,1) -> (1,2) -> (2,3) -> (3,4) -> (4,4)
```
#

### ● Use Cases

1. **Natural Language Processing (NLP)** – Used in machine translation, speech recognition, etc.  
2. **AI Pathfinding with Constraints** – When memory and computation must be limited.  
3. **Optimization Problems** – Situations where a near-optimal solution is acceptable.  
4. **Robotics & Game AI** – Navigation with limited computational budget. 

#

### ● Time and Space Complexity

| Operation       | Time Complexity            | Space Complexity |
|-----------------|----------------------------|------------------|
| Node expansion  | O(B log B)                 | O(B)             |
| All expansions  | O(d · B log B)             | O(d · B)         |
| **Overall**     | **O(d · B log B)**         | **O(d · B)**     |

Where:  
- `B` = beam width  
- `d` = depth of the solution path (≤ N² in worst case)  


#

### ● Files Used

| Filename         | Description |
|------------------|-------------|
| `beamsearch.cpp`       | C++ implementation of Beam Search pathfinding. |
| `README.md` | Documentation for the implementation. |


#
---

## Practical Aim: MiniMax Algorithm (C++ Implementation for Tic Tac Toe)

---

### ● Problem Statement
The **MiniMax Algorithm** is a decision-making algorithm used in **Artificial Intelligence** and **Game Theory**.  
It is widely used for two-player turn-based games (like Tic Tac Toe, Chess, Checkers).  

In Tic Tac Toe:  
- The AI (Maximizer → `X`) tries to maximize its chances of winning.  
- The User (Minimizer → `O`) tries to minimize AI’s chances of winning.  

The algorithm explores all possible game states and chooses the **optimal move** assuming the opponent also plays optimally.

#

### ● Objective
- Implement **MiniMax Algorithm** for Tic Tac Toe.  
- Allow **AI (X)** to play against a **human user (O)**.  
- Ensure AI always makes the **best possible move**.  
- Display the game board after each move and declare the result.  

#

### ● Data Structures Used


| Component          | Data Structure   | Purpose |
|--------------------|------------------|---------|
| Game board         | `vector<int>`    | Represents Tic Tac Toe board with values: `2 = empty`, `3 = X`, `5 = O`. |
| Win checking       | `2D array`       | Stores winning combinations of 3 cells. |
| MiniMax recursion  | `int minimax()`  | Evaluates game states recursively and returns best score. |
| User input         | `cin` (int)      | Takes move from player. |

#

### ● Algorithm

**Scoring Function:**  
- `+1` → AI (`X`) wins  
- `-1` → User (`O`) wins  
- `0` → Draw  

**Steps:**  
1. Represent board as an array of size `9`.  
2. At each step, check if game is over (win or draw).  
3. If not, recursively evaluate all possible moves:  
   - **Maximizer’s turn (AI):** choose move with **maximum score**.  
   - **Minimizer’s turn (User):** choose move with **minimum score**.  
4. AI selects the move with the **best minimax value**.  
5. Game continues until win/draw condition is met.   

#
#### Utility Functions

| Function | Purpose |
|----------|---------|
| `isBlank(pos)` | Checks if a given board position is empty. |
| `AnyBlank()` | Returns the first available empty position. |
| `displayBoard()` | Prints the current Tic Tac Toe board. |
| `checkWin()` | Checks if either player has won the game. |
| `movesLeft()` | Checks if there are any moves remaining. |
| `minimax(isMaxLevel)` | Recursively evaluates game states and returns best score. |
| `AI_Move()` | Determines the best move for the AI using minimax. |
| `User_Move()` | Takes user input for their move. |

#

#### Pseudocode:
```
FUNCTION minimax(isMaxLevel):
    winner ← checkWin()
    IF winner = X THEN RETURN +1
    IF winner = O THEN RETURN -1
    IF no moves left THEN RETURN 0

    IF isMaxLevel:
        best ← -10
        FOR each empty cell:
            place X in cell
            best ← max(best, minimax(false))
            undo move
        RETURN best
    ELSE:
        best ← +10
        FOR each empty cell:
            place O in cell
            best ← min(best, minimax(true))
            undo move
        RETURN best

FUNCTION AI_Move():
    bestVal ← -10
    bestMove ← -1
    FOR each empty cell:
        place X in cell
        moveVal ← minimax(false)
        undo move
        IF moveVal > bestVal:
            bestMove ← cell
            bestVal ← moveVal
    RETURN bestMove
```

#

### ● Sample Test Case

**Game Run Example:**
```
You are O, computer is X.

Board:
. . . 
. . . 
. . . 

Computer played 1

Board:
X . . 
. . . 
. . . 

Enter your move (1-9): 2

Board:
X O . 
. . . 
. . . 

Computer played 4

Board:
X O . 
X . . 
. . . 

Enter your move (1-9): 7

Board:
X O . 
X . . 
O . . 

Computer played 5

Board:
X O . 
X X . 
O . . 

Enter your move (1-9): 6

Board:
X O . 
X X O 
O . . 

Computer played 9

Board:
X O . 
X X O 
O . X

Computer (X) wins!
```

#

### ● Use Cases

1. **Two-player games** – Tic Tac Toe, Chess, Checkers.  
2. **AI Opponents** – Board games, computer-controlled strategy.  
3. **Decision Making** – Optimal strategies where players take alternate turns.  
4. **Teaching Tool** – Understanding Game Theory & adversarial search.

#

### ● Time and Space Complexity

| Operation       | Time Complexity | Space Complexity |
|-----------------|-----------------|------------------|
| Minimax search  | O(b^d)          | O(d)             |
| Board checking  | O(1)            | O(1)             |
| **Overall**     | **O(b^d)**      | **O(d)**         |

Where:  
- `b` = branching factor (≈ number of empty cells)  
- `d` = maximum depth (≤ 9 for Tic Tac Toe)   


#

### ● Files Used

| Filename      | Description |
|---------------|-------------|
| `minimax.cpp` | C++ implementation of MiniMax for Tic Tac Toe. |
| `README.md`   | Documentation for the implementation. |


#
---

## Practical Aim: MiniMax Algorithm with Alpha-Beta Pruning (C++ Implementation for Tic Tac Toe)

---

### ● Problem Statement
The **MiniMax Algorithm with Alpha-Beta Pruning** is an optimized version of the MiniMax Algorithm used in Artificial Intelligence and Game Theory.
It reduces the number of nodes explored by pruning branches that will never affect the final decision.

In Tic Tac Toe:  
- The AI (Maximizer → `X`) tries to maximize its chances of winning.  
- The User (Minimizer → `O`) tries to minimize AI’s chances of winning.  

#

### ● Objective
- Implement **MiniMax Algorithm with Alpha-Beta Pruning** for Tic Tac Toe. 
- Allow **AI (X)** to play against a **human user (O)**.
- Ensure AI always makes the best possible move.
- Improve efficiency over plain minimax by **pruning unnecessary branches**.
- Display the game board after each move and declare the result.  

#

### ● Data Structures Used

| Component          | Data Structure   | Purpose |
|--------------------|------------------|---------|
| Game board         | `vector<int>`    | Represents Tic Tac Toe board with values: `2 = empty`, `3 = X`, `5 = O`. |
| Win checking       | `2D array`       | Stores winning combinations of 3 cells. |
| Alpha-Beta Pruning | `int minimax()`  | Uses α (best for maximizer) and β (best for minimizer) to prune branches. |
| User input         | `cin` (int)      | Takes move from player. |

#

### ● Algorithm

**Scoring Function:**  
- `+1` → AI (`X`) wins  
- `-1` → User (`O`) wins  
- `0` → Draw  

**Steps:**  
1. Represent board as an array of size `9`.  
2. At each step, check if game is over (win or draw).  
3. If not, recursively evaluate all possible moves with alpha-beta pruning:  
   - **Maximizer’s turn (AI):** choose move with **maximum score**, update `alpha`.  
   - **Minimizer’s turn (User):** choose move with **minimum score**, update `beta`.  
4. Prune branches where `beta ≤ alpha`.  
5. AI selects the move with the **best minimax value**.  
6. Game continues until win/draw condition is met.    

#
#### Utility Functions

| Function | Purpose |
|----------|---------|
| `isBlank(pos)` | Checks if a given board position is empty. |
| `AnyBlank()` | Returns the first available empty position. |
| `displayBoard()` | Prints the current Tic Tac Toe board. |
| `checkWin()` | Checks if either player has won the game. |
| `movesLeft()` | Checks if there are any moves remaining. |
| `minimax(isMaxLevel, alpha, beta)` | Recursively evaluates game states with pruning. |
| `AI_Move()` | Determines the best move for the AI using minimax with pruning. |
| `User_Move()` | Takes user input for their move. |

#

#### Pseudocode:
```
FUNCTION minimax(isMaxLevel, alpha, beta):
    winner ← checkWin()
    IF winner = X THEN RETURN +1
    IF winner = O THEN RETURN -1
    IF no moves left THEN RETURN 0

    IF isMaxLevel:
        best ← -∞
        FOR each empty cell:
            place X in cell
            best ← max(best, minimax(false, alpha, beta))
            undo move
            alpha ← max(alpha, best)
            IF beta ≤ alpha THEN BREAK
        RETURN best
    ELSE:
        best ← +∞
        FOR each empty cell:
            place O in cell
            best ← min(best, minimax(true, alpha, beta))
            undo move
            beta ← min(beta, best)
            IF beta ≤ alpha THEN BREAK
        RETURN best

FUNCTION AI_Move():
    bestVal ← -∞
    bestMove ← -1
    FOR each empty cell:
        place X in cell
        moveVal ← minimax(false, -∞, +∞)
        undo move
        IF moveVal > bestVal:
            bestMove ← cell
            bestVal ← moveVal
    RETURN bestMove
```

#

### ● Sample Test Case
**Game Run Example:**
```
You are O, computer is X.

Board:
. . . 
. . . 
. . . 

Computer played 1

Board:
X . . 
. . . 
. . . 

Enter your move (1-9): 2

Board:
X O . 
. . . 
. . . 

Computer played 4

Board:
X O . 
X . . 
. . . 

Enter your move (1-9): 7

Board:
X O . 
X . . 
O . . 

Computer played 5

Board:
X O . 
X X . 
O . . 

Enter your move (1-9): 6

Board:
X O . 
X X O 
O . . 

Computer played 9

Board:
X O . 
X X O 
O . X

Computer (X) wins!
```

#

### ● Use Cases

1. **Two-player games** – Tic Tac Toe, Chess, Checkers.  
2. **AI Opponents** – Board games, computer-controlled strategy.  
3. **Decision Making** – Optimal strategies where players take alternate turns.  
4. **Efficiency** – Faster than plain minimax due to pruning. 

#

### ● Time and Space Complexity

| Operation       | Time Complexity | Space Complexity |
|-----------------|-----------------|------------------|
| Minimax search  | O(b^(d/2)) (avg)       | O(d)             |
| Board checking  | O(1)            | O(1)             |
| **Overall**     | **O(b^(d/2))**      | **O(d)**         |
 
Where:  
- `b` = branching factor (≈ number of empty cells)  
- `d` = maximum depth (≤ 9 for Tic Tac Toe) 


#

### ● Files Used

| Filename             | Description |
|----------------------|-------------|
| `alphabeta_tictactoe.cpp`      | C++ implementation of MiniMax with Alpha-Beta Pruning for Tic Tac Toe. |
| `README.md`          | Documentation for the implementation. |


#
---

## Practical Aim: Blocks World Planning (Prolog Implementation)

---

### ● Problem Statement
The **Blocks World Problem** is a classic problem in **Artificial Intelligence (AI) planning**.  
It involves a set of blocks placed on a table, and the goal is to rearrange them into a desired configuration using a sequence of valid actions.  

Each action must respect constraints (e.g., you cannot pick up a block if something is on top of it).  
The challenge is to find a sequence of actions (a **plan**) that transforms the **initial state** into the **goal state**.

#

### ● Objective
- Implement a **Blocks World planner** in Prolog.  
- Define valid **actions** (`pickup`, `putdown`, `stack`, `unstack`).  
- Check action **applicability** based on current state.  
- Apply actions to generate new states.  
- Use a **depth-first search planner** with redundancy prevention.  
- Validate the planner using **test cases**.  

#

### ● Knowledge Representation

| Concept              | Representation in Prolog |
|----------------------|----------------------------|
| States               | List of facts (e.g., `[ontable(a), clear(a), holding(none)]`) |
| Blocks               | Declared using `block(a). block(b). block(c).` |
| Actions              | `action(Name, Preconditions, DeleteEffects, AddEffects)` |
| Goal                 | List of required conditions |
| Plan                 | Sequence of actions that achieve the goal |

#

### ● Action Definitions

The planner supports **four actions**:

1. **pickup(X)**  
   - Preconditions: block `X` is clear, on the table, and nothing is being held.  
   - Effects: robot holds `X`, removes it from the table.  

2. **putdown(X)**  
   - Preconditions: robot is holding `X`.  
   - Effects: place `X` on table, robot is free.  

3. **unstack(X, Y)**  
   - Preconditions: `X` is on `Y`, `X` is clear, and robot is free.  
   - Effects: robot holds `X`, `Y` becomes clear.  

4. **stack(X, Y)**  
   - Preconditions: robot holds `X` and `Y` is clear.  
   - Effects: place `X` on top of `Y`, robot is free.  

#

### ● Algorithm

**Planning Approach:**  
- Uses **depth-first search** (DFS) with a **depth limit** to avoid infinite recursion.  
- Generates possible actions using block schemas.  
- Checks applicability of actions using preconditions.  
- Applies action effects (delete + add lists) to update state.  
- Stops when **goal state** is satisfied.  
- Avoids redundant back-and-forth moves (like `pickup` immediately after `putdown`).  

**Steps:**  
1. Start with `plan(Init, Goal, Plan)`.  
2. If goal is satisfied → return `Plan`.  
3. Otherwise, choose an applicable action:  
   - Ensure it’s not a redundant move.  
   - Apply it to generate a new state.  
4. Continue recursively until goal is reached or depth limit exceeded.  

#

### ● Utility Predicates

| Predicate | Purpose |
|-----------|---------|
| `member_eq(X, List)` | Membership check for states. |
| `applicable(Action, State)` | Verifies if action’s preconditions are met. |
| `apply(Action, State, NewState)` | Applies action effects (delete & add lists). |
| `goal_satisfied(Goal, State)` | Checks if goal conditions are met. |
| `redundant_move/2` | Prevents undoing the last move. |

#

### ● Sample Test Cases

1. **Simple stacking**  
```prolog
?- test_simple.
Testing simple stacking...
SUCCESS! Plan: [pickup(a),stack(a,b)]
```

2. **Tower building**  
```prolog
?- test_tower.
Testing tower building...
SUCCESS! Plan: [pickup(b),stack(b,c),pickup(a),stack(a,b)]
```

3. **Complex rearrangement**  
```prolog
?- test_complex.
Testing complex rearrangement...
SUCCESS! Plan: [pickup(c),stack(c,b)]
```

#

### ● Use Cases

1. **AI Planning Research** – Fundamental problem for automated planning.  
2. **Robotics** – Block-stacking scenarios for robotic arms.  
3. **Game/Simulation Development** – Creating simple puzzle games where players rearrange blocks to reach a goal state.
4. **Search Algorithms** – Demonstrating DFS with action schemas.  

#

### ● Time and Space Complexity

| Operation       | Time Complexity | Space Complexity |
|-----------------|-----------------|------------------|
| State checking  | O(n)            | O(1)             |
| Action check    | O(k)            | O(1)             |
| DFS planning    | O(b^d)          | O(d)             |

Where:  
- `n` = number of facts in state  
- `k` = number of actions  
- `b` = branching factor (# applicable actions)  
- `d` = search depth  

#

### ● Files Used

| Filename         | Description |
|------------------|-------------|
| `blocks_world.pl` | Prolog implementation of the Blocks World planner. |
| `README.md`      | Documentation for the implementation. |

#
---

## Practical Aim: N-Queens Problem (Prolog Implementation)

---

### ● Problem Statement
The **N-Queens Problem** is a classic **constraint satisfaction problem (CSP)** in Artificial Intelligence.  
The task is to place `N` queens on an `N × N` chessboard such that:  

1. No two queens are in the same row.  
2. No two queens are in the same column.  
3. No two queens are in the same diagonal.  

The challenge is to generate valid configurations for different values of `N`, count all possible solutions, and visualize them.

#

### ● Objective
-   Implement the **N-Queens Problem** in Prolog using **pure backtracking**.
-   Generate valid queen placements with **safe position checks**.
-   Verify solutions with **no diagonal attacks**.
-   Display solutions with a **chessboard-like visualization**.
-   Provide functionality to **find one solution** or **count all solutions**. 

#

### ● Knowledge Representation

| Concept              | Representation in Prolog |
|----------------------|----------------------------|
| Chessboard           | Represented implicitly by `N`. |
| Queens placement     | List `Solution` where index = column, value = row. |
| Safe placement       | Checked using `safe_position/3`. |
| Visualization        | Printed grid with `Q` for queen and `.` for empty cell. |

#

### ● Algorithm

**Steps:**  
1. Start with an empty partial solution.
2. Place queens row by row. 
3. For each row, try placing a queen in every column `1..N`.  
4. Use `safe_position/3` to check column and diagonal safety. If safe, continue with recursive backtracking.
5. If all queens placed → valid solution.
6. Print and count solutions.  
7. Use `aggregate_all(count, …)` to count all solutions.
8. Print solutions with `print_board/2`

**Diagonal Safety Check:**  
For a queen at `(Row, Col)` and another at `(Row+k, Col±k)`, they must not attack each other.

#

### ● Utility Predicates

| Predicate | Purpose |
|-----------|---------|
| `solve_queens(N, Solution)` | Backtracking solver that finds one solution. |
| `safe_position(Col, Partial, Row)` | Checks if a queen can be placed safely. |
| `solve_nqueens(N)` | Finds and prints one solution. |
| `count_solutions(N, Count)` | Finds total number of solutions. |
| `print_board(N, Solution)` | Prints board with queens. |

#

### ● Sample Test Cases

1. **4-Queens**  
```prolog
?- test_4queens.
=== 4-Queens Test ===
Solution for 4 queens: [2,4,1,3]
Board (4x4):
. Q . . 
. . . Q 
Q . . . 
. . Q . 
```

2. **8-Queens**  
```prolog
?- test_8queens.
=== 8-Queens Test ===
Solution for 8 queens: [1,5,8,6,3,7,2,4]
Board (8x8):
Q . . . . . . . 
. . . . Q . . . 
. . . . . . . Q 
. . . . . Q . . 
. . Q . . . . . 
. . . . . . Q . 
. Q . . . . . . 
. . . Q . . . . 
```

3. **Counting Solutions**  
```prolog
?- test_counts.
=== Solution Counts ===
4-Queens has 2 solutions
5-Queens has 10 solutions
6-Queens has 4 solutions
8-Queens has 92 solutions
```

#

### ● Use Cases

1. **Artificial Intelligence** – Constraint Satisfaction Problems (CSP).  
2. **Chess Programming** – Understanding attacking positions.  
3. **Search Algorithms** – Explains recursive backtracking and pruning.  
4. **Mathematics** – Exploring combinatorial solution spaces.  

#

### ● Time and Space Complexity

| Operation          | Time Complexity | Space Complexity |
|--------------------|-----------------|------------------|
| Permutation Gen.   | O(N!)           | O(N)             |
| Safety Check       | O(N) per placement           | O(1)             |
| Overall (N-Queens) | O(N! × N)       | O(N)             |

The algorithm is exponential in nature since the **solution space grows factorially** with `N`.  

#

### ● Files Used

| Filename        | Description |
|-----------------|-------------|
| `nqueens.pl`    | Prolog implementation of the N-Queens problem. |
| `README.md`     | Documentation for the implementation. |

#
---


