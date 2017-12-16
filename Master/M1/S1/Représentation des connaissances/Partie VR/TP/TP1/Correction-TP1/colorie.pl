couleur(vert).
couleur(jaune).
couleur(rouge).

coloriage1(C1,C2,C3,C4):-couleur(C1),couleur(C2),C1\==C2,couleur(C3),C1\==C3, C2\==C3,couleur(C4),C1\==C4, C3\==C4.

accueil:-write('Bonjour '),nl,
		menu(X),
		mode(X),
		nl.
			
		
menu(X):-write('1. Choisir une couleur sur une position'), nl,
		write('2. Colorier la carte'),nl,
		read(X).
		
mode(1):-write('Donnez la case (c1, c2, c3 ou c4)'),nl,
		read(Pos),
		write('Donnez la couleur (vert, jaune, rouge)'), nl,
		read(Couleur),
		memoriseChoix(Pos,Couleur).

memoriseChoix(c1,Couleur):- coloriage1(Couleur,C2,C3,C4), write(Couleur), write(C2), write(C3), write(C4),nl,fail.
memoriseChoix(c2,Couleur):- coloriage1(C1,Couleur,C3,C4), write(C1), write(Couleur), write(C3), write(C4),nl,fail.
memoriseChoix(c3,Couleur):- coloriage1(C1,C2,Couleur,C4), write(C1), write(C2), write(Couleur), write(C4),nl,fail.
memoriseChoix(c4,Couleur):- coloriage1(C1,C2,C3,Couleur), write(C1), write(C2), write(C3), write(Couleur),nl,fail.
		
mode(2):-coloriage1(C1,C2,C3,C4), write(C1 ), write(C2 ), write(C3 ), write(C4 ),nl,fail.

		

		