## Practical Aim: Tic-Tac-Toe Game using Lisp

---

### ● Problem Statement
The **Tic-Tac-Toe Game** is a classic example of **game playing and decision-making** in Artificial Intelligence.  
The objective is to simulate a human vs computer game where the computer uses logical strategies to win or block the player.

The program implements Tic-Tac-Toe using **Lisp** with a one-dimensional board array representation and **basic AI rules** for move selection.

#

### ● Objective
- Implement **Tic-Tac-Toe** logic using Lisp.  
- Use a **one-dimensional array** to represent the 3×3 board.  
- Apply **AI logic** to determine the computer’s move.  
- Check for win conditions and display the result interactively.  

#

### ● Knowledge Representation

| Concept | Representation in Lisp |
|----------|-------------------------|
| Empty Cell | Represented by value `2` |
| Computer’s Move | Represented by value `3` (`X`) |
| Player’s Move | Represented by value `5` (`O`) |
| Board | One-dimensional array of size 10 (indices 1–9 used) |

#

### ● Functions Overview

| Function | Purpose |
|-----------|----------|
| `(is-blank pos)` | Checks if a given position is blank. |
| `(any-blank)` | Finds any available blank position. |
| `(make2)` | Chooses center or non-corner positions strategically. |
| `(posswin player-val)` | Checks if the player can win on the next move. |
| `(make-move pos)` | Places a mark (`X` or `O`) on the board. |
| `(display-board)` | Prints the current board state. |
| `(user-move)` | Accepts move input from the user. |
| `(check-win)` | Determines if there is a winner. |
| `(main)` | Controls the full game loop. |

#

### ● Algorithm (Game Logic)

**Steps:**
1. Initialize the board with all positions blank (`2`).  
2. Assign `X` to the computer and `O` to the user.  
3. Alternate turns between computer and player.  
4. For each computer turn:
   - Check if it can **win** (`posswin 3`).
   - Else check if it needs to **block** (`posswin 5`).
   - Else choose center or next blank cell.  
5. For each user turn:
   - Input position and mark it as `O`.  
6. After each move, check for a winner using `check-win`.  
7. Stop the game when either player wins or all cells are filled.

#

### ● Sample Execution

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

### ● Use Cases

1. **Artificial Intelligence** – Demonstrates rule-based AI decision-making.  
2. **Game Development** – Simple model of turn-based logic games.  
3. **Problem Solving** – Tests recursion and decision trees in Lisp.  
4. **Learning Tool** – Helps understand Lisp loops, arrays, and conditions.  

#

### ● Time and Space Complexity

| Operation | Time Complexity | Space Complexity |
|------------|-----------------|------------------|
| Checking Winning Combinations | O(1) | O(1) |
| Player Move Validation | O(1) | O(1) |
| Full Game Execution | O(N) (N ≤ 9) | O(N) |

The program runs efficiently in **Constant Time** per move, with linear time for the full game sequence.

#

### ● Files Used

| Filename | Description |
|-----------|-------------|
| `tictactoe.lisp` | Lisp implementation of Tic-Tac-Toe game logic. |
| `README.md` | Documentation for the Tic-Tac-Toe implementation. |

#
---
