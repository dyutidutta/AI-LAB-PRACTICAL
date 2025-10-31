## Practical Aim: Water Jug Problem using Lisp

---

### ● Problem Statement
The **Water Jug Problem** is a classic **state-space search problem** in Artificial Intelligence.  
The goal is to measure exactly `Z` liters of water using two jugs with capacities `X` and `Y`, applying a sequence of valid operations (fill, empty, pour).

This program provides a **Lisp implementation** that simulates the process step by step until the desired goal amount is reached.

#

### ● Objective
- Implement the **Water Jug Problem** using Lisp.  
- Use mathematical logic and **Euclidean GCD** to verify solvability.  
- Simulate all **valid jug operations** until the goal state is achieved.  
- Display the **state transitions** after each operation.  

#

### ● Knowledge Representation

| Concept | Representation in Lisp |
|----------|-------------------------|
| Jug capacities | Variables `x` and `y` |
| Target amount | `z` |
| Current state | `(curx, cury)` |
| Goal state check | `(reached-goal z curx cury)` |
| GCD check for solvability | `(solve-gcd x y)` |

#

### ● Functions Overview

| Function | Purpose |
|-----------|----------|
| `(solve-gcd a b)` | Computes the greatest common divisor of `a` and `b`. |
| `(reached-goal z curx cury)` | Checks if the goal amount `z` is reached. |
| `(fill-x x curx)` | Fills jug X to capacity. |
| `(fill-y y cury)` | Fills jug Y to capacity. |
| `(empty-x)` | Empties jug X completely. |
| `(empty-y)` | Empties jug Y completely. |
| `(pour-x-to-y x y curx cury)` | Transfers water from X to Y until one is empty or full. |
| `(water-jug x y z)` | Main function to simulate jug operations and reach the goal. |

#

### ● Algorithm (Step-by-Step Execution)

**Steps:**
1. Input jug capacities `x`, `y` and goal amount `z`.  
2. Check solvability using **GCD condition**:  
   - If `z` is greater than both jugs or not divisible by `gcd(x, y)`, print “Goal not achievable.”  
3. Start with `(0, 0)` — both jugs empty.  
4. Repeat the following actions until the goal is reached:
   - If jug X is empty → **Fill X**.  
   - Else if jug X has water and jug Y is not full → **Pour from X to Y**.  
   - Else if jug Y is full → **Empty Y**.  
5. Stop when either jug has exactly `z` liters of water.  
6. Print the sequence of operations and final state.  

#

### ● Sample Execution

```
? (water-jug 4 3 2)
Initial state: (0, 0)
Fill X: (4, 0)
Pour X->Y: (1, 3)
Empty Y: (1, 0)
Pour X->Y: (0, 1)
Fill X: (4, 1)
Pour X->Y: (2, 3)
Goal reached! Final state: (2, 3)
```

#

### ● Use Cases

1. **Artificial Intelligence** – Demonstrates state-space search strategy.  
2. **Problem Solving** – Uses mathematical logic for solvability and path generation.  
3. **Algorithm Design** – Models procedural steps to achieve a target goal.  
4. **Teaching Tool** – Illustrates transitions between states in a simple problem space.  

#

### ● Time and Space Complexity

| Operation | Time Complexity | Space Complexity |
|------------|-----------------|------------------|
| GCD Calculation | O(log(min(x, y))) | O(1) |
| Each Jug Operation | O(1) | O(1) |
| Total | O(k) (where k = steps to reach goal) | O(1) |

Since each jug operation is constant-time, the overall time grows with the number of transitions required.

#

### ● Files Used

| Filename | Description |
|-----------|-------------|
| `waterjug.lisp` | Lisp implementation of the Water Jug Problem. |
| `README.md` | Documentation for the Water Jug implementation. |

#
---
