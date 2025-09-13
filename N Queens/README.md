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
