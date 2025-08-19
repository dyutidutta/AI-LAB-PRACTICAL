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

 

