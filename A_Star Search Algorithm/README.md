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


 

