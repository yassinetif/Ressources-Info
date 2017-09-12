meme_maison(X,[X|_],Y,[Y|_]).
meme_maison(X,[_|LX],Y,[_|LY]) :- meme_maison(X,LX,Y,LY).
 
maison_a_cote(X,[X|_],Y,[_,Y|_]).				% Soit X est à droite
maison_a_cote(X,[_,X|_],Y,[Y|_]). 				% Soit X est à gauche
maison_a_cote(X,[_|LX],Y,[_|LY]) :- maison_a_cote(X,LX,Y,LY).
 
maison_a_droite(X,Y,[X,Y|_]).
maison_a_droite(X,Y,[_|L]) :- maison_a_droite(X,Y,L).
 
zebre(C,N,B,A,P,PossZebre,BoitVin) :-
	C=[_,_,_,_,_],
	N=[norvegien,_,_,_,_],						%Le norvégien habite la première maison à gauche
	B=[_,_,lait,_,_],							%On boit du lait dans la maison du milieu
	A=[_,_,_,_,_],
	P=[_,_,_,_,_],
	meme_maison(anglais,N,rouge,C),				%L'anglais habite la maison rouge
	meme_maison(chien,A,espagnol,N),			%L'espagnol possède un chien
	meme_maison(japonais,N,peintre,P),			%Le japonais est peintre
	meme_maison(italien,N,the,B),				%L’italien boit du thé
	meme_maison(verte,C,cafe,B),				%Le propriétaire de la maison verte boit du café
	maison_a_droite(blanche,verte,C),			%La maison verte est juste à droite de la blanche
	meme_maison(sculpteur,P,escargots,A),		%Le sculpteur élève un escargot
	meme_maison(diplomate,P,jaune,C),			%Le diplomate habite la maison jaune
	maison_a_cote(norvegien,N,bleu,C),			%Le norvégien habite à coté de la maison bleue
	meme_maison(violoniste,P,jus_de_fruit,B),	%Le violoniste boit du jus de fruit
	maison_a_cote(renard,A,medecin,P),			%Le renard est dans une maison voisine du médecin
	maison_a_cote(cheval,A,diplomate,P),		%Le cheval est à coté de la maison du diplomate
	meme_maison(PossZebre,N,zebre,A),			%Possesseur du zèbre
	meme_maison(BoitVin,N,vin,B). 				%Buveur de vin

%zebre(C,N,B,A,P,PossZebre,BoitVin)