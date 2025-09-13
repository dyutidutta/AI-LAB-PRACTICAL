% Main solver %
solve_queens(N, Solution) :-
    solve_queens(N, N, [], Solution).

solve_queens(_, 0, Solution, Solution).
solve_queens(BoardSize, QueensLeft, PartialSolution, Solution) :-
    QueensLeft > 0,
    between(1, BoardSize, Col),              
    safe_position(Col, PartialSolution, 1),   
    QueensLeft1 is QueensLeft - 1,
    solve_queens(BoardSize, QueensLeft1, [Col|PartialSolution], Solution).

% Safety check %
safe_position(_, [], _).
safe_position(Col, [H|T], Row) :-
    Col =\= H,             % no same column
    Col =\= H + Row,       % no major diagonal
    Col =\= H - Row,       % no minor diagonal
    Row1 is Row + 1,
    safe_position(Col, T, Row1).

% Display %
solve_nqueens(N) :-
    solve_queens(N, Solution),
    reverse(Solution, DisplaySolution),
    format('Solution for ~w queens: ~w~n', [N, DisplaySolution]),
    print_board(N, DisplaySolution).

print_board(N, Solution) :-
    format('Board (~wx~w):~n', [N, N]),
    print_rows(1, N, Solution).

print_rows(Row, N, Solution) :-
    Row =< N,
    print_single_row(1, N, Row, Solution),
    nl,
    Row1 is Row + 1,
    print_rows(Row1, N, Solution).
print_rows(Row, N, _) :- Row > N.

print_single_row(Col, N, Row, Solution) :-
    Col =< N,
    nth1(Row, Solution, QueenCol),
    (Col =:= QueenCol -> write('Q ') ; write('. ')),
    Col1 is Col + 1,
    print_single_row(Col1, N, Row, Solution).
print_single_row(Col, N, _, _) :- Col > N.

% Counting solutions %
count_solutions(N, Count) :-
    aggregate_all(count, solve_queens(N, _), Count),
    format('~w-Queens has ~w solutions~n', [N, Count]).

% Tests %
test_4queens :-
    writeln('=== 4-Queens Test ==='),
    solve_nqueens(4).

test_8queens :-
    writeln('=== 8-Queens Test ==='),
    solve_nqueens(8).

test_counts :-
    writeln('=== Solution Counts ==='),
    count_solutions(4, _),
    count_solutions(5, _),
    count_solutions(6, _),
    count_solutions(8, _).
    
