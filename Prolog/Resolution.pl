% --- FACTS ---
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

% --- RULES DERIVED FROM FACTS ---
mortal(X) :- human(X).              
wise(X) :- philosopher(X).          
teaches(X, Y) :- wise(X), student(Y, X).  

% --- ADDITIONAL KNOWN RELATIONSHIPS ---
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
