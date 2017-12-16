%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Le jeu d othello - *une* correction V. Renault 
%
% othello.pl : module principal qui charge tous les modules necessaires au deroulement du jeu. 
%   -> predicat principal lanceJeu : demarre la partie;
%   -> permet de choisir le mode, la couleur (x ou o), alternance entre les joueurs, etc.
%
% Dependances :
%   -> representation.pl : module de représentation du jeu (affichage, manipulation de la grille, etc).
%   -> regles.pl : module de modelisation des regles du jeu.
%
%
% Pour lancer le jeu : 
%  ?- consult(othello).
%  ?- lanceJeu.
%
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Permet de separer les predicats en differents fichiers selon leur role.
% Appelle le predicat consult/1 directement dans le fichier pour charger les
%   faits et les regles ecrits dans les autres fichiers.
loadModules:-
   consult(representation),
   consult(regles).


%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% question 24
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Predicat : lanceJeu/0
% Usage : lanceJeu lance le jeu d othello

lanceJeu:-
    loadModules,
	menuPrincipal,!.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Predicat : menuPrincipal/0
% Usage : menuPrincipal est le menu principal du jeu

menuPrincipal:-
	nl,tab(8),write('Menu Principal'),
	nl,tab(8),write('--------------'),
	nl,tab(6),write('1 - Humain vs Humain'),
	% on pourra rajouter ici la possibilite de jouer contre l ordinateur
	nl,tab(6),write('0 - Quitter'),nl,
	saisieChoix(Choix),
	lanceChoix(Choix),!.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%
saisieChoix(Choix):-
	nl,write('Choisissez une option (sans oublier le point) : '),
	read(Choix).
	
	
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Predicat :saisieNomJoueur1/0
% Usage : saisieNomJoueur1 enregistre le nom du joueur 1 et le rajoute a la base de fait

saisieNomJoueur1:-
	nl,write('Entrez le nom du Joueur 1 (sans oublier le point) : '),
	read(J1),
	% Supprime le nom du joueur 1 s il y en avait deja un dans la base de fait :
	%  - retract(P) : recherche une clause dans la base de connaissances qui s unifie avec P
	%        et l efface
	%  - retractall(P) : enleve toutes les clauses qui s unifient a P.
	retractall(nomJoueur1(_X)),
	% Rajoute le nouveau nom du joueur dans la base de fait :
	%  - assert(P) : permet d ajouter P a la base de faits, peut etre ecrit n importe ou
	%  - asserta(P) : ajoute en debut de base
	%  - assertz(P) : ajoute en fin de base
	asserta(nomJoueur1(J1)),!.


%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Predicat : saisieNomJoueur2
% Usage : saisieNomJoueur2 enregistre le nom du joueur 2
saisieNomJoueur2:-
	nl,write('Entrez le nom du Joueur 2 (sans oublier le point) : '),
	read(J2),
	retractall(nomJoueur2(_X)),
	asserta(nomJoueur2(J2)),!.
	
%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Predicat : lanceChoix/1
% Usage : lanceChoix(Choix) lance le choix correspondant au menu principal

%%% choix de sortir du programme
lanceChoix(0):-
	nl,tab(10),write('A tres bientot...'),nl,!.

%%% choix de lancer le jeu humain contre humain
lanceChoix(1):-
    % recupere le nom des joueurs et l ajoute dans la BF
	saisieNomJoueur1,
	saisieNomJoueur2,nl,
	% affiche la grille de depart
	afficheGrilleDep,
	grilleDeDepart(Grille),nl,
	% initialise tous les coups disponibles au depart
	toutesLesCasesDepart(ListeCoups),
	nomJoueur1(J1),
	nl,write('Voulez-vous commencer '),write(J1),write(' ? o. pour OUI ou n. pour NON : '),
	read(Commence),
	% lance le moteur humain contre humain
	lanceMoteurHH(Grille,ListeCoups, Commence),!.


%%% Rajouter ici les autres choix (humain/CPU) / (CPU/CPU)


%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% Etape 1 : Jeu Humain contre Humain
%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Predicat : lanceMoteurHH/3
% Usage : lanceMoteurHH(Grille,ListeCoups,Commence) lance le moteur de jeu 
%   Commence : contient la reponse oui (o) ou non (n) a la question : est-ce que
%   le joueur1 commence
%
% 

/* Lance le moteur de jeu du joueur 1 */

lanceMoteurHH(Grille,ListeCoups,o):-
    % le joueur1 commence, on lui associe les pions 'x' 
    % et on ajoute l information a la base de fait
	retractall(campJoueur1(_X)),
	asserta(campJoueur1(x)),
	campJoueur1(CampJ1),campJoueur2(CampJ2),
	% calcul du score actuel
	score(Grille,CampJ1,ScoreJ1),
	score(Grille,CampJ2,ScoreJ2),
	% on recupere le nom de chaque joueur pour afficher son score
	nomJoueur1(J1),nomJoueur2(J2),
	nl,write(J1),write(' a '),write(ScoreJ1),write(' point(s)'),nl,
	write(J2),write(' a '),write(ScoreJ2),write(' point(s)'),nl,
	% lance le moteur de jeu pour 'x'
	moteurH1H2(Grille,ListeCoups,CampJ1),!.


/* Lance le moteur du joueur 2 */

lanceMoteurHH(Grille,ListeCoups,n):-
	% le joueur2 commence, on lui associe les pions 'x' 
	% et on associe les 'o' au joueur 1
	retractall(campJoueur1(_X)),
	asserta(campJoueur1(o)),
	campJoueur1(CampJ1),campJoueur2(CampJ2),
	score(Grille,CampJ1,ScoreJ1),
	score(Grille,CampJ2,ScoreJ2),
	nomJoueur1(J1),nomJoueur2(J2),
	nl,write(J1),write(' a '),write(ScoreJ1),write(' point(s)'),nl,
	write(J2),write(' a '),write(ScoreJ2),write(' point(s)'),nl,
	moteurH2H1(Grille,ListeCoups,CampJ2),!.



%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% Moteur du joueur 1
%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Predicat: moteurH1H2/3
% Usage : moteurH1H2(Grille,ListeCoups,CampJ1) est le moteur de jeu du joueur 1
%

% cas : partie finie
moteurH1H2(Grille,[],CampJ1):-
	campJoueur1(CampJ1),
	moteurHHFin(Grille),!.

% cas : il n y a plus de coups disponibles pour aucun des joueurs - partie finie
moteurH1H2(Grille,ListeCoups,CampJ1):-
	ListeCoups \== [],
	campJoueur1(CampJ1),
	campJoueur2(CampJ2),
	not(testerCoup(ListeCoups,CampJ1,Grille)),
	not(testerCoup(ListeCoups,CampJ2,Grille)),
	moteurHHFin(Grille),!.

% cas : le joueur en cours n a plus de coups disponibles
moteurH1H2(Grille,ListeCoups,CampJ1):-
	nomJoueur1(J1),campJoueur1(CampJ1),campJoueur2(CampJ2),
	not(testerCoup(ListeCoups,CampJ1,Grille)),
	nl,write('Vous devez passer votre tour '),write(J1),write(' ( '),write(CampJ1),write(' )'),nl,
	moteurH2H1(Grille,ListeCoups,CampJ2).


% cas : cas general  - le joueur 1 doit jouer 
moteurH1H2(Grille,ListeCoups,CampJ1):-
    % gerer l alternance des coups
	campJoueur1(CampJ1),campJoueur2(CampJ2),nl,nomJoueur1(J1),nomJoueur2(J2),
	% verifier qu il y a bien des coups a jouer
	testerCoup(ListeCoups,CampJ1,Grille),
	% demander la saisie du coup
	write('A vous de jouer '),write(J1),write(' ( '),write(CampJ1),write(' )'),nl,
	saisieUnCoup(NomCol,NumLig),
	% jouer le coup dans la grille et mettre a jour la grille
	joueLeCoupDansGrille(CampJ1,[NomCol,NumLig],Grille,GrilleArr),
	% afficher la nouvelle grille
	afficheGrille(GrilleArr),nl,
	% afficher le score de chacun des joueurs
	score(GrilleArr,CampJ1,ScoreJ1),
	score(GrilleArr,CampJ2,ScoreJ2),
	nl,write(J1),write(' a '),write(ScoreJ1),write(' point(s)'),nl,
	write(J2),write(' a '),write(ScoreJ2),write(' point(s)'),nl,
	nl,write(J1),write(' a joue en ('),write(NomCol),write(','),write(NumLig),write(')'),nl,
	% mettre a jour la liste des coups
	duneListeALautre(ListeCoups,[NomCol,NumLig],NouvelleListeCoups),
	% lancer le moteur pour l autre joueur
	moteurH2H1(GrilleArr,NouvelleListeCoups,CampJ2).



%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% Moteur du joueur 2
%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Predicat: moteurH2H1/3
% Usage : moteurH2H1(Grille,ListeCoups,CampJ2) est le moteur de jeu du joueur 2
% Comme si dessus pour le second joueur

moteurH2H1(Grille,[],CampJ2):-
	campJoueur2(CampJ2),
	moteurHHFin(Grille),!.

moteurH2H1(Grille,ListeCoups,CampJ2):-
	ListeCoups \== [],
	campJoueur1(CampJ2),
	campJoueur2(CampJ1),
	not(testerCoup(ListeCoups,CampJ2,Grille)),
	not(testerCoup(ListeCoups,CampJ1,Grille)),
	moteurHHFin(Grille),!.

moteurH2H1(Grille,ListeCoups,CampJ2):-
	nomJoueur2(J2),campJoueur1(CampJ1),campJoueur2(CampJ2),
	not(testerCoup(ListeCoups,CampJ2,Grille)),
	nl,write('Vous devez passer votre tour '),write(J2),write(' ( '),write(CampJ2),write(' )'),nl,
	moteurH1H2(Grille,ListeCoups,CampJ1).

moteurH2H1(Grille,ListeCoups,CampJ2):-
	campJoueur1(CampJ1),campJoueur2(CampJ2),nl,nomJoueur1(J1),nomJoueur2(J2),
	testerCoup(ListeCoups,CampJ2,Grille),
	write('A vous de jouer '),write(J2),write(' ( '),write(CampJ2),write(' )'),nl,
	saisieUnCoup(NomCol,NumLig),
	joueLeCoupDansGrille(CampJ2,[NomCol,NumLig],Grille,GrilleArr),
	afficheGrille(GrilleArr),nl,
	score(GrilleArr,CampJ1,ScoreJ1),
	score(GrilleArr,CampJ2,ScoreJ2),
	nl,write(J1),write(' a '),write(ScoreJ1),write(' point(s)'),nl,
	write(J2),write(' a '),write(ScoreJ2),write(' point(s)'),nl,
	nl,write(J2),write(' a joue en ('),write(NomCol),write(','),write(NumLig),write(')'),nl,
	duneListeALautre(ListeCoups,[NomCol,NumLig],NouvelleListeCoups),
	moteurH1H2(GrilleArr,NouvelleListeCoups,CampJ1),!.



%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%% Gestion des fins de parties
%%% Quand il n y a plus de cases libres ou jouables
%%%%%%%%%%%%%%%%%%%%%%%%%%%%


% Predicat : moteurHHFin/1
% Usage : moteurHHFin(Grille)

%% la partie est terminee et c est le joueur 1 qui gagne
moteurHHFin(Grille):-
    campJoueur1(CampJ1),campJoueur2(CampJ2),nomJoueur1(J1),nomJoueurJ2(J2),
	score(Grille,CampJ1,ScoreJ1),
	score(Grille,CampJ2,ScoreJ2),
	ScoreJ1 > ScoreJ2,
	nl,write('La partie est terminee'),nl,
	nl,
	nl,write('Bravo '),write(J1),write(', vous avez gagne cette partie !!!'),nl,
	write('Voulez-vous une revanche, '),write(J2),write(' ? (o. pour OUI ou n. pour NON) : '),
	verifSaisie(Revanche),
	lanceRevancheHH(Revanche),!.


%% la partie est terminee et c est le joueur 2 qui gagne
moteurHHFin(Grille):-
	campJoueur1(CampJ1),campJoueur2(CampJ2),nomJoueur1(J1),nomJoueur2(J2),
	score(Grille,CampJ1,ScoreJ1),
	score(Grille,CampJ2,ScoreJ2),
	ScoreJ1 < ScoreJ2,
	nl,write('La partie est terminee'),nl,
	nl,
	nl,write('Bravo '),write(J2),write(', vous avez gagne cette partie !!!'),nl,
	write('Voulez-vous une revanche, '),write(J1),write(' ? (o. pour OUI ou n. pour NON) : '),
	verifSaisie(Revanche),
	lanceRevancheHH(Revanche),!.

%% la partie est terminee et il n y a pas de gagnant
moteurHHFin(Grille):-
	campJoueur1(CampJ1),campJoueur2(CampJ2),
	score(Grille,CampJ1,ScoreJ1),
	score(Grille,CampJ2,ScoreJ2),
	ScoreJ1 = ScoreJ2,
	nl,write('La partie est terminee'),nl,
	nl,
	nl,write('Vous etes aussi fort l un que l autre'),nl,
	write('Voulez-vous faire une nouvelle partie ? (o. pour OUI ou n. pour NON) : '),
	verifSaisie(Revanche),
	lanceRevancheHH(Revanche),!.


% choix de la fin de partie
% Predicat : lanceRevancheHH/1
% Usage : lanceRevancheHH(Choix)

lanceRevancheHH(o):-nl,
	afficheGrilleDep,
	grilleDeDepart(Grille),nl,
	toutesLesCasesDepart(ListeCoups),
	nomJoueur1(J1),
	nl,write('Voulez-vous commencer '),write(J1),write(' ? o. pour OUI ou n. pour NON : '),
	read(Commence),
	lanceMoteurHH(Commence,Grille,ListeCoups),!.

lanceRevancheHH(n):-
	nl,
	tab(10),write('Ca sera peut-etre pour une prochaine fois !'),nl,!.

