## Practical Aim: Blocks World Planning (Prolog Implementation)

---

### ● Problem Statement
The **Blocks World Problem** is a classic problem in **Artificial Intelligence (AI) planning**.  
It involves a set of blocks placed on a table, and the goal is to rearrange them into a desired configuration using a sequence of valid actions.  

Each action must respect constraints (e.g., you cannot pick up a block if something is on top of it).  
The challenge is to find a sequence of actions (a **plan**) that transforms the **initial state** into the **goal state**.

#

### ● Objective
- Implement a **Blocks World planner** in Prolog.  
- Define valid **actions** (`pickup`, `putdown`, `stack`, `unstack`).  
- Check action **applicability** based on current state.  
- Apply actions to generate new states.  
- Use a **depth-first search planner** with redundancy prevention.  
- Validate the planner using **test cases**.  

#

### ● Knowledge Representation

| Concept              | Representation in Prolog |
|----------------------|----------------------------|
| States               | List of facts (e.g., `[ontable(a), clear(a), holding(none)]`) |
| Blocks               | Declared using `block(a). block(b). block(c).` |
| Actions              | `action(Name, Preconditions, DeleteEffects, AddEffects)` |
| Goal                 | List of required conditions |
| Plan                 | Sequence of actions that achieve the goal |

#

### ● Action Definitions

The planner supports **four actions**:

1. **pickup(X)**  
   - Preconditions: block `X` is clear, on the table, and nothing is being held.  
   - Effects: robot holds `X`, removes it from the table.  

2. **putdown(X)**  
   - Preconditions: robot is holding `X`.  
   - Effects: place `X` on table, robot is free.  

3. **unstack(X, Y)**  
   - Preconditions: `X` is on `Y`, `X` is clear, and robot is free.  
   - Effects: robot holds `X`, `Y` becomes clear.  

4. **stack(X, Y)**  
   - Preconditions: robot holds `X` and `Y` is clear.  
   - Effects: place `X` on top of `Y`, robot is free.  

#

### ● Algorithm

**Planning Approach:**  
- Uses **depth-first search** (DFS) with a **depth limit** to avoid infinite recursion.  
- Generates possible actions using block schemas.  
- Checks applicability of actions using preconditions.  
- Applies action effects (delete + add lists) to update state.  
- Stops when **goal state** is satisfied.  
- Avoids redundant back-and-forth moves (like `pickup` immediately after `putdown`).  

**Steps:**  
1. Start with `plan(Init, Goal, Plan)`.  
2. If goal is satisfied → return `Plan`.  
3. Otherwise, choose an applicable action:  
   - Ensure it’s not a redundant move.  
   - Apply it to generate a new state.  
4. Continue recursively until goal is reached or depth limit exceeded.  

#

### ● Utility Predicates

| Predicate | Purpose |
|-----------|---------|
| `member_eq(X, List)` | Membership check for states. |
| `applicable(Action, State)` | Verifies if action’s preconditions are met. |
| `apply(Action, State, NewState)` | Applies action effects (delete & add lists). |
| `goal_satisfied(Goal, State)` | Checks if goal conditions are met. |
| `redundant_move/2` | Prevents undoing the last move. |

#

### ● Sample Test Cases

1. **Simple stacking**  
```prolog
?- test_simple.
Testing simple stacking...
SUCCESS! Plan: [pickup(a),stack(a,b)]
```

2. **Tower building**  
```prolog
?- test_tower.
Testing tower building...
SUCCESS! Plan: [pickup(b),stack(b,c),pickup(a),stack(a,b)]
```

3. **Complex rearrangement**  
```prolog
?- test_complex.
Testing complex rearrangement...
SUCCESS! Plan: [pickup(c),stack(c,b)]
```

#

### ● Use Cases

1. **AI Planning Research** – Fundamental problem for automated planning.  
2. **Robotics** – Block-stacking scenarios for robotic arms.  
3. **Game/Simulation Development** – Creating simple puzzle games where players rearrange blocks to reach a goal state.
4. **Search Algorithms** – Demonstrating DFS with action schemas.  

#

### ● Time and Space Complexity

| Operation       | Time Complexity | Space Complexity |
|-----------------|-----------------|------------------|
| State checking  | O(n)            | O(1)             |
| Action check    | O(k)            | O(1)             |
| DFS planning    | O(b^d)          | O(d)             |

Where:  
- `n` = number of facts in state  
- `k` = number of actions  
- `b` = branching factor (# applicable actions)  
- `d` = search depth  

#

### ● Files Used

| Filename         | Description |
|------------------|-------------|
| `blocks_world.pl` | Prolog implementation of the Blocks World planner. |
| `README.md`      | Documentation for the implementation. |

#
---
