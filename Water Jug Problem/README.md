<h1 align="center">Artificial Intelligence</h1>

## Practical :- Water Jug Problem (C++ Implementation)

---

### ● Problem Statement
The **Water Jug Problem** is a classic puzzle where we have two jugs with fixed capacities and the goal is to measure exactly `Z` liters of water using the jugs. The only operations allowed are:
- Fill a jug completely
- Empty a jug completely
- Pour water from one jug into the other until one is either empty or full

The program takes **jug capacities X and Y** and **goal volume Z**, and outputs the sequence of steps to achieve the goal.

---

### ● Objective
- Solve the Water Jug Problem using the **mathematical GCD condition** for solvability.
- Simulate step-by-step actions to reach the goal state.
- Demonstrate basic **problem-solving with constraints** in C++.

---

### ● Data Structures Used

| Component         | Data Structure | Purpose |
|-------------------|---------------|---------|
| Jug capacities    | `int`         | Stores maximum capacity of X and Y. |
| Current volumes   | `int`         | Tracks current amount of water in each jug. |
| Helper functions  | Functions     | Perform jug operations like fill, empty, pour. |

---

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

---

#### Pseudocode:
```
function gcd(a, b):
    while b != 0:
        temp = b
        b = a % b
        a = temp
    return a

if Z > max(X, Y) or Z % gcd(X, Y) != 0:
    print "Not achievable"
else:
    while not reachedGoal(Z):
        if curX == 0:
            fillX()
        else if curY < Y:
            pourXtoY()
        else if curY == Y:
            emptyY()
```

---

### ● Utility Functions

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

---

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

---

### ● Use Cases

1. **AI Problem Solving Demonstrations** – Classic example in AI lectures.
2. **Mathematical Puzzles** – Solving constraints-based problems.
3. **Competitive Programming Practice** – Teaches modular problem-solving.
4. **Teaching GCD and Number Theory Applications**.
5. **Game & Puzzle Simulation Projects**.

---

### ● Time and Space Complexity

| Operation | Time Complexity | Space Complexity |
|-----------|----------------|------------------|
| GCD Calculation | O(log min(X, Y)) | O(1) |
| **Overall** | O(1) for fixed-size jugs | O(1) |

---

### ● Files Used

| Filename          | Description |
|-------------------|-------------|
| `waterjug.cpp`    | C++ implementation of the Water Jug Problem. |
| `README.md`       | Documentation for the problem and solution. |

---
