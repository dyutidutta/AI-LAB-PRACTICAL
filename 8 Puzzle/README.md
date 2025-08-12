<h1 align="center">Artificial Intelligence</h1>

## Practical :- 8-Puzzle Problem using BFS, DFS, Best-First Search, and Hill Climbing in C++


### ● Problem Statement

The **8-Puzzle Problem** is a classic problem in artificial intelligence and graph theory. It consists of a 3x3 grid with tiles numbered 1-8 and one empty space (represented as `0`). The goal is to move the tiles into the correct position by sliding them one at a time into the empty space, ultimately reaching a predefined goal state.

---

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

---

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

---

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

---

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

---

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
---

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

---

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

---

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
 

---
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
 

---

### ● Time and Space Complexities
  - b → branching factor (max possible moves from a state; for 8-puzzle, b ≤ 4)
  - d → depth of the goal state

| Algorithm            | Time Complexity                                       | Space Complexity |
|----------------------|-------------------------------------------------------|------------------|
| `BreadthFirstSearch` | O(b<sup>d</sup>)                                      | O(b·d)           |
| `DepthFirstSearch`   | O(b<sup>d</sup>)                                      | O(b<sup>d</sup>) | 
| `BestFirstSearch`    | O(b·log b × d) (average) to O(b<sup>d</sup>) (worst)  | O(b<sup>d</sup>) |
| `HillClimbing`       | O(b·d)       | O(d)             |

---

### ● Files

| Filename                 | Description                                  |
|--------------------------|----------------------------------------------|
| `BreadthFirstSearch.cpp` | BFS-based 8-puzzle solver                    |
| `DepthFirstSearch.cpp`   | DFS-based 8-puzzle solver                    |
| `BestFirstSearch.cpp`    | Best-First Search 8-puzzle solver            |
| `HillClimbingApproach.cpp` | Hill Climbing-based 8-puzzle solver        |
| `README.md`              | Explanation and documentation                |
