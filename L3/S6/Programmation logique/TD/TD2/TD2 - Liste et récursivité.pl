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

/* Exercice 10 - Scinder une liste */
split([],[],[]).
split([H|T],[H|TP],N) :- H>=0,!,split(T,TP,N).
split([H|T],P,[H|TN]) :- split(T,P,TN).