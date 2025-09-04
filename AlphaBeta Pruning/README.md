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

