%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Le jeu d othello - *une* correction V. Renault 
%   -> representation.pl : module de représentation du jeu (affichage, manipulation de la grille, etc).
%
% Dependances :
%   -> othello.pl : module principal qui charge tous les modules necessaires au deroulement du jeu. 
%   -> regles.pl : module de modelisation des regles du jeu.
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% question 1 :
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Definition de la grille de depart de jeu
% il n y a pas besoin de guillemets pour chaque element de la liste
grilleDeDepart([[-,-,-,-,-,-,-,-],
[-,-,-,-,-,-,-,-],
[-,-,-,-,-,-,-,-],
[-,-,-,o,x,-,-,-],
[-,-,-,x,o,-,-,-],
[-,-,-,-,-,-,-,-],
[-,-,-,-,-,-,-,-],
[-,-,-,-,-,-,-,-]]).

% Garder la possibilite de faire des tests sur une grille plus petite 
grilleTest([[-,-,-],[x,o,-],[-,-,-]]).


% lister toutes les cases disponibles pour jouer
toutesLesCasesDepart([[a,1],[b,1],[c,1],[d,1],[e,1],[f,1],[g,1],[h,1],
		      [a,2],[b,2],[c,2],[d,2],[e,2],[f,2],[g,2],[h,2],
		      [a,3],[b,3],[c,3],[d,3],[e,3],[f,3],[g,3],[h,3],
		      [a,4],[b,4],[c,4],            [f,4],[g,4],[h,4],
		      [a,5],[b,5],[c,5],	        [f,5],[g,5],[h,5],
		      [a,6],[b,6],[c,6],[d,6],[e,6],[f,6],[g,6],[h,6],
		      [a,7],[b,7],[c,7],[d,7],[e,7],[f,7],[g,7],[h,7],
		      [a,8],[b,8],[c,8],[d,8],[e,8],[f,8],[g,8],[h,8]]).



% lister toutes les cases du jeu
toutesLesCases([[a,1],[b,1],[c,1],[d,1],[e,1],[f,1],[g,1],[h,1],
		[a,2],[b,2],[c,2],[d,2],[e,2],[f,2],[g,2],[h,2],
	    [a,3],[b,3],[c,3],[d,3],[e,3],[f,3],[g,3],[h,3],
	    [a,4],[b,4],[c,4],[d,4],[e,4],[f,4],[g,4],[h,4],
	    [a,5],[b,5],[c,5],[d,5],[e,5],[f,5],[g,5],[h,5],
	    [a,6],[b,6],[c,6],[d,6],[e,6],[f,6],[g,6],[h,6],
		[a,7],[b,7],[c,7],[d,7],[e,7],[f,7],[g,7],[h,7],
	    [a,8],[b,8],[c,8],[d,8],[e,8],[f,8],[g,8],[h,8]]).






%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% question 2	
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Predicat : succNum/2
% Usage : succNum(X,Y) est satisfait si Y est le successeur de X
succNum(1,2).
succNum(2,3).
succNum(3,4).
succNum(4,5).
succNum(5,6).
succNum(6,7).
succNum(7,8).
	

% Predicat : succAlpha/2
% Usage : succAlpha(X,Y) est satisfait si Y est le successeur de X 
%	 (ordre lexico-graphique)
succAlpha(a,b).
succAlpha(b,c).
succAlpha(c,d).
succAlpha(d,e).
succAlpha(e,f).
succAlpha(f,g).
succAlpha(g,h).




%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% question 3
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Predicat : afficheLigne/1
% Usage : affigheLigne(Ligne)est satisfait si Ligne est une ligne d une grille de
%         morpion et qu elle l affiche proprement a l ecran.
% version 1 - non recursive :
afficheLigneMoche([A,B,C,D,E,F,G,H]):-
	tab(1), write('| '),
	write(A), tab(1), write('| '),
	write(B), tab(1), write('| '),
	write(C), tab(1), write('| '),
	write(D), tab(1), write('| '),
	write(E), tab(1), write('| '),
	write(F), tab(1), write('| '),
	write(G), tab(1), write('| '),
	write(H), tab(1), write('| ').

% version 2 - recursive : 
afficheLigne([Tete]):-
	tab(1),write('| '),write(Tete),write(' |'),!.
afficheLigne([Tete|Suite]):-
	tab(1),write('| '),write(Tete),
	afficheLigne(Suite).
          

%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% question 4
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Predicat : afficheGrille/1
% version 1 - non recursive (deconseillee)
% afficheGrilleMoche([[A1,B1,C1,D1,E1,F1,G1,H1],[A2,B2,C2,D2,E2,F2,G2,H2],
% [A3,B3,C3,D3,E3,F3,G3,H3]... jusqu a H8]) :- 
%	afficheLigne([A1,B1,C1,D1,E1,F1,G1,H1]), nl,
%	afficheLigne(....
%	afficheLigne([A8,B8,C8,D8,E8,F8,G8,H8])).

% Predicat : afficheGrille/1
% version 2 - recursive mais sans utiliser succNum (version Ok)
% on utilise l operateur d evaluation 'is'
% la condition d arret est lorsque la grille est vide
% afficheGrilleSimple(_,[]). 
% afficheGrilleSimple(N,[Tete|Reste]):-
%	write(N),tab(1),afficheLigne(Tete),nl,
%	N1 is N + 1,	
%	afficheGrilleSimple(N1,Reste).
% afficheGrille(GrilleEntiere):-
%	tab(3),write( '| a | b | c | d | e | f | g | h |' ),nl,
%	afficheGrilleSimple(1,GrilleEntiere).	 


% Predicat : afficheGrille/1
% version 3 - recursive avec les succNum et succApha (version Ok - plus complexe, mais plus 'logique')
% Se décompose en plusieurs étapes
% -> affichePremiereLigne :
%    afficher la premiere ligne en fonction de la longueur de la première ligne de la grille :
%    la condition terminale permet d afficher la valeur de la derniere colonne, quelque
%    soit le dernier element qui reste dans le tableau;
%    On parcourt la ligne mais le contenu de cette ligne ne nous interesse pas.
% -> afficheGrilleSimple : 
%    afficher la grille en gérant les numéros de ligne avec le succNum;
% -> afficheGrille :
%    appelle les deux predicats precedants;
%

affichePremiereLigne(Val,[_]):- tab(1),write('| '),write(Val),write(' |'), nl.
affichePremiereLigne(Val,[_|Suite]):-
	tab(1),write('| '),write(Val),succAlpha(Val,Val2),
	affichePremiereLigne(Val2,Suite).

afficheGrilleSimple(_,[X]) :- tab(1), afficheLigne(X).
afficheGrilleSimple(N,[Tete|Reste]):-
	tab(1),afficheLigne(Tete),nl,
	succNum(N,N1),write(N1),
	afficheGrilleSimple(N1,Reste).
	
afficheGrille([Tete|Suite]):-
	tab(2),affichePremiereLigne(a,Tete),
	write('1'),
	afficheGrilleSimple(1,[Tete|Suite]).	 


%%% Tests du predicat
% ?- afficheGrille([[-,-,-,-,-,-,-,-],[-,-,-,-,-,-,-,-],[-,-,-,-,-,-,-,-],[-,-,-,o,x,-,-,-],[-,-,-,x,o,-,-,-],[-,-,-,-,-,-,-,-],[-,-,-,-,-,-,-,-],[-,-,-,-,-,-,-,-]]).
% ?- grilleDeDepart(X), afficheGrille(X).
% ?- grilleTest(X), afficheGrille(X).
% ?- afficheGrille([[x],[x]]).
% ?- afficheGrille([[x]]).


%%% Permet d afficher la grille au demarrage du jeu
% Predicat : afficheGrilleDep/0
% Usage : afficheGrilleDep affiche la grille de depart du jeu d othello,
%         sous la forme d une grille

afficheGrilleDep:-
	grilleDeDepart(G),
	afficheGrille(G),!.





%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% question 5
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% ligneDansGrille : verifier qu une ligne existe dans une grille;
% caseDansLigne : verifier qu une case existe dans une ligne;
% La methode consiste a tronquer la liste jusqu a arriver a la position qui nous interesse;
% on decremente les index a chaque recursion, 
% la position qui nous interesse est en position 1 ou a.

ligneDansGrille(1,[Tete|_],Tete).
ligneDansGrille(NumLig,[_|Reste],Lig):-
	succNum(I,NumLig),
	ligneDansGrille(I,Reste,Lig).


caseDansLigne(a,[Tete|_],Tete).
caseDansLigne(Col,[_|Reste],Case):-
	succAlpha(I,Col),
	caseDansLigne(I,Reste,Case).


%%% Tests du predicat
% ?- ligneDansGrille(5,[[-,-,-,-,-,-,-,-],[-,-,-,-,-,-,-,-],[-,-,-,-,-,-,-,-],[-,-,-,o,x,-,-,-],[-,-,-,x,o,-,-,-],[-,-,-,-,-,-,-,-],[-,-,-,-,-,-,-,-],[-,-,-,-,-,-,-,-]],X).
% ?- ligneDansGrille(X,[[-,-,-,-,-,-,-,-],[-,-,-,-,-,-,-,-],[-,-,-,-,-,-,-,-],[-,-,-,o,x,-,-,-],[-,-,-,x,o,-,-,-],[-,-,-,-,-,-,-,-],[-,-,-,-,-,-,-,-],[-,-,-,-,-,-,-,-]],[-,-,-,-,-,-,-,-]).
% ?- grilleDeDepart(X),ligneDansGrille(5,X,[-,-,-,x,o,-,-,-]).
% ?- grilleTest(X),ligneDansGrille(1,X,Y).
% ?- grilleTest(X),ligneDansGrille(3,X,Y).
% ?- grilleTest(X),ligneDansGrille(6,X,Y).


%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% question 6
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Predicat caseDeGrille/4
% usage : caseDeGrille(NumColonne,NumLigne,Grille,Case) est satisfait si la
%         Case correspond bien a l intersection de la de la colonne NumColonne
%	  et de la ligne NumLigne dans le Grille

caseDeGrille(NumColonne,NumLigne,Grille,Case):-
	ligneDansGrille(NumLigne,Grille,Ligne),
	caseDansLigne(NumColonne,Ligne,Case),!.




%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% question 7
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% caseVide(Grille, NumLigne, NumColonne)
% --> vérifier qu une case est vide, cad qu elle contient '-'

caseVide(Grille, NumLigne, NumColonne):-donneValeurDeCase(Grille,NumLigne,NumColonne,-).


%%% Tests du predicat
% ?- caseVide([[-,-,-,-,-,-,-,-],[-,-,-,-,-,-,-,-],[-,-,-,-,-,-,-,-],[-,-,-,o,x,-,-,-],[-,-,-,x,o,-,-,-],[-,-,-,-,-,-,-,-],[-,-,-,-,-,-,-,-],[-,-,-,-,-,-,-,-]],a,4).
% ?- grilleTest(X),caseVide(X,a,2).
% ?- grilleTest(X),caseVide(X,c,3).
% ?- grilleTest(X),caseVide(X,h,6).


%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% question 14
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Predicat : scoreLigne/3
% Usage : scoreLigne(Ligne,Camp,Score) donne le nombre de pion Camp dans
%	  la ligne de grille Ligne

scoreLigne([],_Camp,0):-!.

scoreLigne([Camp|Suite],Camp,Score):-
	scoreLigne(Suite,Camp,Score1),
	Score is Score1 +1.

scoreLigne([Tete|Suite],Camp,Score):-
	Tete \== Camp,
	scoreLigne(Suite,Camp,Score).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Predicat : score/3
% Usage : score(Grille,Camp,Score) donne le nombre de pion Camp dans la
%         grille Grille

score([],_Camp,0):-!.

score([Ligne1|Suite],Camp,Score):-
	scoreLigne(Ligne1,Camp,Score1),
	score(Suite,Camp,Score2),
	Score is Score1 + Score2.


%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% question 15 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% coordonneesOuListe(NomCol, NumLigne, Liste).
coordonneesOuListe(NomCol, NumLigne, [NomCol, NumLigne]).



%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% question 16 - 
%%% ces predicats aident juste a construire progressivement le predicat de la question 17
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Predicat : listeCasesVides/2
% Usage : listeCasesVides(Grille,ListesCasesLibres) donne a partir
%         d une grille la liste des cases libres

listeCasesVides(Grille,ListeCasesLibres):-
	toutesLesCasesDepart(ListesCases),
	listeCasesLibres(Grille,ListesCases,ListeCasesLibres),!.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Predicat : listeCasesLibres/3
% Usage : listeCasesLibres(Grille,ListeCases,ListeCasesLibres)

listeCasesLibres(_Grille,[],[]):-!.

listeCasesLibres(Grille,[[Colonne,Ligne]|SuiteCases],[[Colonne,Ligne]|SuiteCasesLibres]):-
	caseDeGrille(Colonne,Ligne,Grille,-),
	listeCasesLibres(Grille,SuiteCases,SuiteCasesLibres).

listeCasesLibres(Grille,[[Colonne,Ligne]|SuiteCases],SuiteCasesLibres):-
	not(caseDeGrille(Colonne,Ligne,Grille,-)),
	listeCasesLibres(Grille,SuiteCases,SuiteCasesLibres).




%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% question 17 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Predicat : listeCoupsValides/4
% Usage : listeCoupsValides(ListeCoups,Camp,Grille,ListeCoupsValides) pour un camp

listeCoupsValides([],_Camp,_Grille,[]):-!.

listeCoupsValides([[Colonne,Ligne]|Suite],Camp,Grille,[[Colonne,Ligne]|Suite2]):-
	leCoupEstValide(Camp,Grille,[Colonne,Ligne]),
	listeCoupsValides(Suite,Camp,Grille,Suite2).

listeCoupsValides([Case|Suite],Camp,Grille,Suite2):-
	not(leCoupEstValide(Camp,Grille,Case)),
	listeCoupsValides(Suite,Camp,Grille,Suite2).



%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% Predicats complementaires
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Predicat : testerCoup/3
% Usage : testerCoup(ListeCasesVides,Camp,Grille) verifie s il existe
%	  des coups possibles pour le camp Camp dans la Grille, a partir
%	  de la liste des cases vides

testerCoup([[Colonne,Ligne]|Suite],Camp,Grille):-
	leCoupEstValide(Camp,Grille,[Colonne,Ligne]);
	testerCoup(Suite,Camp,Grille).



%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% question 19
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Predicat : duneListeALautre/3
% Usage  : duneListeALautre(LC1,C,LC2) est satisfait si la liste LC1 est composee
%          de toutes le cases de la liste LC2 plus la case C

duneListeALautre([Tete|Suite],Tete,Suite):-!.

duneListeALautre([Tete|Suite],C,[Tete|Suite2]):-
	duneListeALautre(Suite,C,Suite2).


%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% question 20
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Predicat : campAdverse/2
% Usage : campAdverse(Camp,campAdverse) permet de trouver le camp advairse d un camp

campAdverse(x,o).
campAdverse(o,x).

% Predicat : campJoueur2/1
% Usage : campJoueur2(CampJ2) est satisfait si CampJ2 est le camp du joueur 2
% Le campJoueur1 est defini dynamiquement en debut de jeu et peut etre modifie en fonction
% du choix des joueurs.
% Permet d associer le nom d un joueur, avec son numero et sa couleur
campJoueur2(CampJ2):-
	campJoueur1(CampJ1),
	campAdverse(CampJ1,CampJ2),!.



%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% question 22
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Predicat : saisieUnCoup/2
% Usage : saisieUnCoup(NomCol,NumLig) permet de saisir un coup a jouer

saisieUnCoup(NomCol,NumLig):-
	nl, write('Entrez votre coup (sans oublier le point) :'), nl,
 	write('Colonne (a, b, c, d, e, f, g ou h) : '),
	saisieColonne(NomCol),
	write('Ligne (1, 2, 3, 4, 5, 6, 7 ou 8) : '),
	saisieLigne(NumLig).

% on peut affiner le predicat en testant les valeurs donnees par l utilisateur avec
% saisieColonne et saisieLigne.

% Predicat : saisieColonne/1
% Usage : saisieColonne(NomCol) permet d eviter les erreurs de saisie de la colonne
saisieColonne(NomCol):-
	read(NomCol),
	member(NomCol,[a,b,c,d,e,f,g,h]),!.

saisieColonne(NomCol):-
	write('Nom de colonne incorrect'),nl,
	write('Colonne (a, b, c, d, e, f, g ou h) : '),
	saisieColonne(NomCol).


% Predicat : saisieLigne/1
% Usage : saisieLigne(NumLig) permet d eviter les erreurs de saisie de la ligne

saisieLigne(NumLig):-
	read(NumLig),
	member(NumLig,[1,2,3,4,5,6,7,8]),!.

saisieLigne(NumLig):-
	nl,write('Coup invalide'),nl,
	saisieUnCoup(_NomCol,NumLig).






	



