%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Le jeu d othello - *une* correction V. Renault 
%   -> regles.pl : module de modelisation des regles du jeu.
%
% Dependances :
%   -> othello.pl : module principal qui charge tous les modules necessaires au deroulement du jeu. 
%   -> representation.pl : module de représentation du jeu (affichage, manipulation de la grille, etc).
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% question 8 : gestion des directions
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% Plusieurs solutions possibles : nord / sud... 
% direction(nord,-1,0).
% direction(sud,1,0).
% direction(est,0,1).
% direction(ouest,0,-1).
% direction(nordEst,-1,1).
% direction(nordOuest,-1,-1).
% direction(sudEst,1,1).
% direction(sudOuest,1,-1).

%%%%% sinon indiquer la direction selon la position par rapport à la case en cours C :
%  1  2  3  
%  8  C  4
%  7  6  5
% ce qui donne en se servant de succnum et succ alpha :
% Predicat : caseSuivante/3
% Usage : caseSuivante(Direction,Case,CaseSuivante)

caseSuivante(1,[Colonne,Ligne],[ColonneSuiv,LigneSuiv]):-
	succAlpha(ColonneSuiv,Colonne),
	succNum(LigneSuiv,Ligne),!.

caseSuivante(2,[Colonne,Ligne],[Colonne,LigneSuiv]):-
	succNum(LigneSuiv,Ligne),!.

caseSuivante(3,[Colonne,Ligne],[ColonneSuiv,LigneSuiv]):-
	succAlpha(Colonne,ColonneSuiv),
	succNum(LigneSuiv,Ligne),!.

caseSuivante(4,[Colonne,Ligne],[ColonneSuiv,Ligne]):-
	succAlpha(Colonne,ColonneSuiv),!.

caseSuivante(5,[Colonne,Ligne],[ColonneSuiv,LigneSuiv]):-
	succAlpha(Colonne,ColonneSuiv),
	succNum(Ligne,LigneSuiv),!.

caseSuivante(6,[Colonne,Ligne],[Colonne,LigneSuiv]):-
	succNum(Ligne,LigneSuiv),!.

caseSuivante(7,[Colonne,Ligne],[ColonneSuiv,LigneSuiv]):-
	succAlpha(ColonneSuiv,Colonne),
	succNum(Ligne,LigneSuiv),!.

caseSuivante(8,[Colonne,Ligne],[ColonneSuiv,Ligne]):-
	succAlpha(ColonneSuiv,Colonne),!.


%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% question 11 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Predicat : leCoupEstValide/3
% Usage : leCoupEstValide(Camp,Grille,Coup) verifie qu il n y a rien dans 
%         la case et que le pion va entoure des pions adverses
% ce qui est equivalent a leCoupEstValide/4 en decomposant le coup en ligne/colonne
leCoupEstValide(Camp,Grille,[Colonne,Ligne]):-
	caseDeGrille(Colonne,Ligne,Grille,-),
	lePionEncadre(_Direction,Camp,Grille,[Colonne,Ligne]),!.


% Predicat : lePionEncadre/4
% Usage : lePionEncadre(Direction,Camp,Grille,Case) verifie qu il existe 
%	  un pion adverse dans une des directions autour du pion 
%     utilise la question 8 pour les direction

lePionEncadre(Direction,Camp,Grille,Case):-
    % on verifie la valeur de la direction
	member(Direction,[1,2,3,4,5,6,7,8]),
	% on parcourt la case suivante dans une direction donnee
	caseSuivante(Direction,Case,[ColonneSuiv,LigneSuiv]),
	% on cherche si il y a un adversaire dans cette position
	campAdverse(Camp,CampAdv),
	caseDeGrille(ColonneSuiv,LigneSuiv,Grille,CampAdv),
	% on regarde si il y a bien un pion a 'nous' dans la case suivante
	caseSuivante(Direction,[ColonneSuiv,LigneSuiv],Case3),
	trouvePion(Direction,Camp,Grille,Case3),!.


% Predicat : trouvePion/4
% Usage : trouvePion(Direction,Camp,Grille,Case) verifie que le pion adverse 
%            est bien entoure de l autre cote par un pion du Camp

trouvePion(_Direction,Camp,Grille,[Colonne,Ligne]):-
	caseDeGrille(Colonne,Ligne,Grille,Camp),!.
 
trouvePion(Direction,Camp,Grille,[Colonne,Ligne]):-
	campAdverse(Camp,CampAdv),
	caseDeGrille(Colonne,Ligne,Grille,CampAdv),
	caseSuivante(Direction,[Colonne,Ligne],CaseSuiv),
	trouvePion(Direction,Camp,Grille,CaseSuiv).



%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% question 12
%%%  --> placer le pion ou on veut jouer 
%%%  --> retourner les autres pions
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Predicat : placePionDansLigne/4
% Usage : placePionDansLigne(NomCol,Val,LigneDep,LigneArr) est satisfait si LigneArr
%         peut etre obtenue a partir de LigneDep en jouant le coup valide qui consiste
%         a mettre la valeur Val en NomCol, NumLig.
%	  On suppose donc que le coup que l on desire jouer est valide.

placePionDansLigne(a,Val,[_|SuiteLigneDep],[Val|SuiteLigneDep]):-!.

placePionDansLigne(NomCol,Val,[Tete|SuiteLigneDep],[Tete|SuiteLigneArr]):-
	succAlpha(Predecesseur,NomCol),
	placePionDansLigne(Predecesseur,Val,SuiteLigneDep,SuiteLigneArr).


% Predicat : placePionDansGrille/5
% Usage : placePionDansGrille(NomCol,NumLig,Val,GrilleDep,GrilleArr) est satisfait
%         si GrilleArr est obtenue a partir de GrilleDep dans laquelle on a joue
%         Val en NomCol, NumLig, et cela etant d autre part un coup valide.

placePionDansGrille(NomCol,1,Val,[Ligne1|SuiteGrille],[Ligne2|SuiteGrille]):-
	placePionDansLigne(NomCol,Val,Ligne1,Ligne2),!.

placePionDansGrille(NomCol,NumLig,Val,[Ligne1|SuiteGrilleDep],[Ligne1|SuiteGrilleArr]):-
	succNum(Predecesseur,NumLig),
	placePionDansGrille(NomCol,Predecesseur,Val,SuiteGrilleDep,SuiteGrilleArr).



% Predicat : mangePion/5
% Usage : mangePion(Direction,Camp,Grille,GrilleArr,Case) retourne les pions entoures

mangePion(Direction,_Camp,Grille,Grille,Case):-
	not(caseSuivante(Direction,Case,_CaseSuiv)),!.

mangePion(Direction,Camp,Grille,Grille,Case):-
	caseSuivante(Direction,Case,CaseSuiv),
	not(trouvePion(Direction,Camp,Grille,CaseSuiv)),!.

mangePion(Direction,Camp,Grille,Grille,Case):-
	caseSuivante(Direction,Case,[Colonne,Ligne]),
	caseDeGrille(Colonne,Ligne,Grille,Camp),!.

mangePion(Direction,Camp,Grille,GrilleArr,Case):-
	caseSuivante(Direction,Case,[Colonne,Ligne]),
	trouvePion(Direction,Camp,Grille,[Colonne,Ligne]),
	campAdverse(Camp,CampAdv),
	caseDeGrille(Colonne,Ligne,Grille,CampAdv),
	placePionDansGrille(Colonne,Ligne,Camp,Grille,GrilleProv),
	mangePion(Direction,Camp,GrilleProv,GrilleArr,[Colonne,Ligne]).


%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% question 13
%%%  --> placer le pion ou on veut jouer 
%%%  --> retourner les autres pions
%%%%%%%%%%%%%%%%%%%%%%%%%%%%


% Predicat : joueLeCoupDansGrille/4
% Usage : joueLeCoupDansGrille(Camp,Coups,Grille,GrilleArr) place le pion 
%         Camp dans la Grille, retourne les pions entoures puis rend 
%         la Grille d arrivee GrilleArr

joueLeCoupDansGrille(Camp,[Colonne,Ligne],Grille,GrilleArr):-
        leCoupEstValide(Camp,Grille,[Colonne,Ligne]),
	placePionDansGrille(Colonne,Ligne,Camp,Grille,_Grille0),
	mangePion(1,Camp,_Grille0,_Grille1,[Colonne,Ligne]),
	mangePion(2,Camp,_Grille1,_Grille2,[Colonne,Ligne]),
	mangePion(3,Camp,_Grille2,_Grille3,[Colonne,Ligne]),
	mangePion(4,Camp,_Grille3,_Grille4,[Colonne,Ligne]),
	mangePion(5,Camp,_Grille4,_Grille5,[Colonne,Ligne]),
	mangePion(6,Camp,_Grille5,_Grille6,[Colonne,Ligne]),
	mangePion(7,Camp,_Grille6,_Grille7,[Colonne,Ligne]),
	mangePion(8,Camp,_Grille7,GrilleArr,[Colonne,Ligne]),!.






