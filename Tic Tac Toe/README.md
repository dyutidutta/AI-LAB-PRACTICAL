<h1 align="center">Artificial Intelligence</h1>

## Practical :- Tic-Tac-Toe with and without Magic Square Logic
---

### ● Problem Statement
Tic-Tac-Toe is a two-player game played on a 3×3 grid. The players alternate placing marks (X or O) in empty cells, and the first to align three marks horizontally, vertically, or diagonally wins. 
Here, we present:
- **Normal Approach** – Win is detected by matching the player's value across a row, column, or diagonal.
- **Magic Square Approach** – Win is detected if the sum of the magic square values for a player's moves equals 15.
Both versions allow a **human player (O)** to play against the **computer (X)**.

---

### ● Data Structures Used

| Component          | Data Structure        | Purpose |
|--------------------|-----------------------|---------|
| Board              | `vector<int>`         | Stores cell state (`2` = blank, `3` = X, `5` = O). |
| Magic Square map   | `int magicSquare[10]` | Maps positions 1–9 to magic square values. |
| Turn counter       | `int`                 | Tracks turn number. |

---

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
	
---

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

---
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

---

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

---

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

---

### ● Time and Space Complexities
Both versions have **O(1)** time and **O(1)** space complexity since the board size is fixed (3×3).

| Method        | Time Complexity | Space Complexity |
|---------------|----------------|------------------|
| Magic Square  | O(1)           | O(1)             |
| Normal        | O(1)           | O(1)             |

---
### ● Use Cases
- **Educational** : Demonstrates how to apply magic squares to a game logic problem.
- **Game AI Development:** Example of turn-based decision-making logic.
- **Problem Solving Practice:** Uses combinatorics and optimization.
- **Beginner Game Programming:** Introduces board representation, user input handling, and AI strategy.

---
### ● Files
| Filename              | Description |
|-----------------------|-------------|
| `tictactoe.cpp`       | Contains Normal Tic-Tac-Toe implementation. |
| `tictactoe_magic_square.cpp` | Contains Magic Square Tic-Tac-Toe implementation. |
| `README.md`           | Documentation and explanation. |
