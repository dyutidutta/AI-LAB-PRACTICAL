% Utility predicates %
member_eq(X,[X|_]) :- !.
member_eq(X,[_|T]) :- member_eq(X,T).

% Action definitions %
% action(Name, Preconditions, DeleteEffects, AddEffects)

action(pickup(X), [clear(X), ontable(X), holding(none)], 
       [ontable(X), clear(X), holding(none)], [holding(X)]).

action(putdown(X), [holding(X)], [holding(X)], 
       [ontable(X), clear(X), holding(none)]).

action(unstack(X,Y), [on(X,Y), clear(X), holding(none)], 
       [on(X,Y), clear(X), holding(none)], [holding(X), clear(Y)]).

action(stack(X,Y), [holding(X), clear(Y)], [holding(X), clear(Y)], 
       [on(X,Y), clear(X), holding(none)]).

% Action application %
% Check if an action is applicable in a given state
applicable(Action, State) :-
    action(Action, Pre, _, _),
    forall(member(P, Pre), member_eq(P, State)).

% Apply an action to a state, producing a new state
apply(Action, State, NewState) :-
    action(Action, Pre, Del, Add),
    forall(member(P, Pre), member_eq(P, State)),
    foldl(select, Del, State, S1),
    append(Add, S1, NewState).

% Goal testing %
goal_satisfied([], _).
goal_satisfied([G|Gs], State) :-
    member_eq(G, State),
    goal_satisfied(Gs, State).

% Dynamic block generation %
% Define available blocks (can be extended)
block(a). block(b). block(c).

% Generate all possible action instances
action_schema_instance(pickup(X)) :- block(X).
action_schema_instance(putdown(X)) :- block(X).
action_schema_instance(unstack(X,Y)) :- block(X), block(Y), X \= Y.
action_schema_instance(stack(X,Y)) :- block(X), block(Y), X \= Y.

% Planning algorithm %
% Main planning predicate
plan(Init, Goal, Plan) :-
    search(Init, Goal, [], Plan).

% Depth-first search with basic optimizations
search(State, Goal, Actions, Plan) :-
    goal_satisfied(Goal, State),
    reverse(Actions, Plan).

search(State, Goal, Actions, Plan) :-
    length(Actions, Len), Len < 10,  % Configurable depth limit
    action_schema_instance(Action),
    applicable(Action, State),
    \+ redundant_move(Action, Actions),
    apply(Action, State, NewState),
    search(NewState, Goal, [Action|Actions], Plan).

% Basic redundancy prevention
redundant_move(pickup(X), [putdown(X)|_]).
redundant_move(putdown(X), [pickup(X)|_]).
redundant_move(stack(X,Y), [unstack(X,Y)|_]).
redundant_move(unstack(X,Y), [stack(X,Y)|_]).

% Test cases %
test_simple :-
    Init = [ontable(a), ontable(b), ontable(c), clear(a), clear(b), clear(c), holding(none)],
    Goal = [on(a,b)],
    writeln('Testing simple stacking...'),
    ( plan(Init, Goal, Plan) ->
        format('SUCCESS! Plan: ~w~n', [Plan])
    ;
        writeln('FAILED - no plan found')
    ).

test_tower :-
    Init = [ontable(a), ontable(b), ontable(c), clear(a), clear(b), clear(c), holding(none)],
    Goal = [on(a,b), on(b,c)],
    writeln('Testing tower building...'),
    ( plan(Init, Goal, Plan) ->
        format('SUCCESS! Plan: ~w~n', [Plan])
    ;
        writeln('FAILED - no plan found')
    ).

test_complex :-
    Init = [ontable(a), on(b,a), ontable(c), clear(b), clear(c), holding(none)],
    Goal = [on(c,b)],
    writeln('Testing complex rearrangement...'),
    ( plan(Init, Goal, Plan) ->
        format('SUCCESS! Plan: ~w~n', [Plan])
    ;
        writeln('FAILED - no plan found')
    ).

% Run all tests
run_tests :- test_simple, test_tower, test_complex.
