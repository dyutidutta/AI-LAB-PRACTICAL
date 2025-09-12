% Main solver %
nqueens(N, Solution) :-
    numlist(1, N, Rows),
    permutation(Rows, Solution),
    safe(Solution).

% Check if queen placement is safe (no diagonal attacks)
safe([]).
safe([Q|Qs]) :-
    safe(Qs),
    no_attack(Q, Qs, 1).

% Check if queen Q attacks any queen in list Qs
no_attack(_, [], _).
no_attack(Q, [Q1|Qs], Dist) :-
    Q =\= Q1 + Dist,        % No diagonal attack (\)
    Q =\= Q1 - Dist,        % No diagonal attack (/)
    Dist1 is Dist + 1,
    no_attack(Q, Qs, Dist1).

% Solution finder %
% Find first solution
solve_nqueens(N) :-
    nqueens(N, Solution),
    format('Solution for ~w queens: ~w~n', [N, Solution]),
    print_board(N, Solution).

% Find all solutions and count them
count_solutions(N, Count) :-
    findall(Sol, nqueens(N, Sol), Solutions),
    length(Solutions, Count),
    format('~w-Queens has ~w solutions~n', [N, Count]).

% Board visualization %
print_board(N, Solution) :-
    format('Board (~wx~w):~n', [N, N]),
    numlist(1, N, Rows),
    maplist(print_row(N, Solution), Rows).

print_row(N, Solution, Row) :-
    numlist(1, N, Cols),
    maplist(print_cell(Solution, Row), Cols),
    nl.

print_cell(Solution, Row, Col) :-
    nth1(Col, Solution, Row),
    write('Q ').
print_cell(Solution, Row, Col) :-
    nth1(Col, Solution, QueenRow),
    QueenRow =\= Row,
    write('. ').

% Test cases %
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
