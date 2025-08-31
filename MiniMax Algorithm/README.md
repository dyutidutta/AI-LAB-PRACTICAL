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

Computer played 5

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

