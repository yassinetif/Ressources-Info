/* Exercice 1 - Dernier élément liste */
exo1(X,[X]). % X est le seul élement de la liste
exo1(X,[X|[]]). % X est le dernier élément de la liste
% Les deux sont équivalents

exo1(X,[_|T]):- my_last(X,T). % On parcourt la liste

/* Exercice 2 - Avant dernier élement liste */
exo2(X,[X|[_]]). % On a X puis un autre élement qui est le dernier
exo2(X,[X,_]). % On a une liste de deux élements, avec X le premier des deux

exo2(X,[_|T]):- my_last(X,T).

/* Exercice 3 - Kème élément lsite */
exo3(X,[X|_],1). % Si X est la tête de liste et que c'est la case qu'on recherche

exo3(X,[_|T],K):- A is K-1, exo3(X,T,A).

/* Exercice 4 - Longueur d'une liste */
/* Version non terminale */
exo4_1([],0). % Une liste vide est de longueur 0
exo4_1([_|T],O) :- exo4_1(T,N), O is N+1.

/* Version terminale */
exo4_2(L,R) :- exo4_2(L,0,R).
exo4_2([],X,X).
exo4_2([_|T],K,R) :- L is K+1, exo4_2(T,L,R).

/* Exercice 5 - Inverser une liste */
exo5([], R, R).

exo5([X|Y],L,R) :- exo5(Y,[X|L],R).

/* Exercice 6 - Palindrome */
exo6(L) :- exo5(L, [], L).

/* Exercice 7 - Aplatir une liste */
exo7([],[]).
exo7([H|T], L) :- is_list(H), !, exo7(H,Rh), exo7(T,Rt), append(Rh,Rt,L).
exo7([H,T], [H,Rt]) :- exo7(T,Rt).

% exo7([a,[b,[c,d],e]], X).

/* Exercice 8 - Éléminer les élements consécutifs et identiques */
exo8([],[]).
%exo8([E|[E|T]],L) :- exo8([E|T], L), !.
exo8([E,E|T],L) :- exo8([E|T], L), !.
exo8([E|T], [E|L]) :- exo8(T,L).

% exo8([a,a,a,a,b,c,c,a,a,d,e,e,e,e],X).

/* Exercice 9 - Empaqueter les éléments consécutifs d'une liste dans des sous-listes */
exo9([], []).
exo9([H|T], [SL|P]) :-
	!,
	creer_sous_liste(H, T, SL, SP),
	exo9(SP, P).

creer_sous_liste(H, [], [H], []).
creer_sous_liste(H, [I|T], [H], [I|T]) :- H \= I.
creer_sous_liste(H, [H|T], [H|SH], SP) :- creer_sous_liste(H, T, SH, SP).

% exo9([a,a,a,a,b,c,c,a,a,d,e,e,e,e],X).
% X = [[a,a,a,a],[b],[c,c],[a,a],[d],[e,e,e]]

/* Exercice 10 - Scinder une liste */
exo10([], []).
exo10([H|T], [[Longueur, H]|P]) :-
	!,
	creer_sous_liste(H, T, SL, SP),
	length(SL, Longueur),
	exo10(SP, P).

% exo9([a,a,a,a,b,c,c,a,a,d,e,e,e,e],X).
% X = [[4, a], [1, b], [2, c], [2, a], [1, d], [4, e]] 

/* Is_list */
is_list([]).
is_list([_|_]).

/* Append */
append([],L,L).
append([H|T],L2,[H|L]) :- append(T,L2,L).

/* Find all */
test(t1,t2).
test(t2,t3).

test2(X,Y):- test(X,Y).
test2(X,Y):- test(X,Z), test(Z,Y).

/* Even number of elements */
even([_,_|[]]).
even([[_|_]|T]) :- even(T).

/* Duplicate */
dupli([],[]).
dupli([H|T],[H,H|R]) :- dupli(T, R).

/* Sub list */
subset([L],[L]).
subset([], L).
subset([H|T],[H|L]) :- subset(T,L).
subset([H|T],[_|L]) :- subset([H|T], L).

is_member(X,[X|_).