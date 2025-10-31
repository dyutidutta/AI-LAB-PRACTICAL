## Practical Aim: Knowledge Representation and Resolution in Prolog

---

### ● Problem Statement
The **Resolution Problem** demonstrates **knowledge representation and logical inference** in Prolog.  
The goal is to encode human knowledge (facts and relationships) and derive conclusions using **logical rules** and **queries**.  

This example represents philosophers, their wisdom, and teaching relationships using Prolog predicates such as `human`, `philosopher`, `wise`, and `teaches`.

#

### ● Objective
- Represent knowledge using **facts and rules**.  
- Infer new knowledge using **Prolog’s resolution mechanism**.  
- Demonstrate logical relationships among humans, philosophers, students, and teachers.  
- Execute queries to verify derived relationships (e.g., who teaches whom, who is mortal, etc.).

#

### ● Knowledge Representation

| Concept            | Representation in Prolog |
|--------------------|---------------------------|
| Humans             | `human(X)` |
| Mortality          | `mortal(X) :- human(X)` |
| Philosophers       | `philosopher(X)` |
| Wisdom             | `wise(X) :- philosopher(X)` |
| Students & Teachers | `student(Y, X)` and `teaches(X, Y)` |
| Existence Check    | `exists(X)` |

#

### ● Facts (Base Knowledge)

```prolog
fact(1, "All humans are mortal").
fact(2, "Socrates is a human").
fact(3, "Plato is a human").
fact(4, "Aristotle is a human").
fact(5, "If someone is a philosopher, then they are wise").
fact(6, "Socrates is a philosopher").
fact(7, "Plato is a philosopher").
fact(8, "Aristotle was a student of Plato").
fact(9, "Plato was a student of Socrates").
fact(10, "If someone is wise, then they teach others").
```

#

### ● Rules Derived from Facts

```prolog
mortal(X) :- human(X).                 % From fact 1
wise(X) :- philosopher(X).             % From fact 5
teaches(X, Y) :- wise(X), student(Y, X).   % From fact 10
```

#

### ● Additional Known Relationships

```prolog
human(socrates).
human(plato).
human(aristotle).

philosopher(socrates).
philosopher(plato).

student(aristotle, plato).
student(plato, socrates).

exists(socrates).
exists(plato).
exists(aristotle).
```

#

### ● Algorithm (Logical Inference)

**Steps:**
1. Represent all facts about humans, philosophers, and students.  
2. Encode logical rules linking attributes like mortality and wisdom.  
3. Use Prolog’s **resolution** to infer new knowledge:
   - If `human(X)` → infer `mortal(X)`.
   - If `philosopher(X)` → infer `wise(X)`.
   - If `wise(X)` and `student(Y, X)` → infer `teaches(X, Y)`.
4. Query the knowledge base to test logical conclusions.

#

### ● Sample Queries and Expected Results

| Query | Expected Result | Explanation |
|-------|------------------|-------------|
| `?- mortal(socrates).` | `true.` | Because Socrates is human. |
| `?- mortal(plato).` | `true.` | Because Plato is human. |
| `?- mortal(aristotle).` | `true.` | Because Aristotle is human. |
| `?- wise(socrates).` | `true.` | Because Socrates is a philosopher. |
| `?- teaches(plato, aristotle).` | `true.` | Because Plato is wise and Aristotle is his student. |
| `?- teaches(socrates, aristotle).` | `false.` | Because Socrates is wise but Aristotle is not his student. |

#

### ● Use Cases

1. **Artificial Intelligence** – Demonstrates logical inference through resolution.  
2. **Knowledge Representation** – Encodes facts and relationships.  
3. **Philosophical Reasoning** – Represents classical logic about philosophers and wisdom.  
4. **Education Modeling** – Models teacher-student relationships based on logic.

#

### ● Time and Space Complexity

| Operation | Time Complexity | Space Complexity |
|------------|-----------------|------------------|
| Fact Retrieval | O(1) | O(1) |
| Rule Resolution | O(N) | O(N) |
| Combined Inference | O(N × M) | O(N + M) |

Here, `N` is the number of facts and `M` is the number of rules.  
Inference cost grows linearly with rule chaining depth.

#

### ● Files Used

| Filename | Description |
|-----------|-------------|
| `resolution.pl` | Prolog implementation of the philosopher knowledge base. |
| `README.md` | Documentation for the implementation. |

#
---
