#include "Outil.h"
#include "Deque.h"
//NB1: comme tout module, Deque doit être amorcé avant d'être utilisé ——via un appel à DequeAMORCER() à ajouter à la routine ModuleAmorcer() du main.
//NB2: pour accéder à une deque de 25 sommets,encadrer les accès à la deque en question par DequeOuvrir(25) et DequeOuvrir(0).
//NB3: utiliser la deque après ouverture soit comme une pile soit comme une file. L'usage mixte est repéré et dénoncé par assertions (cf tModePilE).

#define knDequeCardinalMaX 100 //nb max de sommets admissible physiqt ds la deque; k comme constante;n comme entier naturel,donc 0 et plus. 
int nCarD;//nombre de sommets stockés actuellt dans la deque.
int nCardMaX;//nombre total de sommets demandé lors de l'allocation de la deque (la dernière allocation);n comme entier naturel,donc 0 et plus.
int bDequeOuvertE;//flipflop;b comme booléen;un flipflop désigne en anglais une bascule à 2 états (état flip,d'abord, puis état flop,d'où le nom)
int bDequeAmorceR;//ie le présent module a effectivement été amorcé
int tModePilE;//>0 si usage en pile,<0 en file, =0 si usage encore indéterminé. t comme trit,ie 3 états. 
int sLasT;//si strictt positif, index sur le sommet de pile mais aussi valeur de fond de pile; cet index est un numéro de sommet, d'où le préfixe s.
struct DequE{
	int sNexT[1+knDequeCardinalMaX];//s comme sommet;soit 1+knDequeCardinalMaX puisque l'indice 0 est inutilisé
}DequE,*pDequE;

void DequeAllouer(int nCardinalMax){//O(1)
	//appelé avec nCardinalMax>0 pr allouer une deque;devra être appelé ensuite avec nCardinalMax=0 pr restituer la deque
	Assert2("DequeAllouer",bDequeAmorceR,bCroit(0,nCardinalMax,knDequeCardinalMaX));
	FlipFlop("DequeAllouer",bVrai(nCardinalMax>0),&bDequeOuvertE);
	nCardMaX=nCardinalMax;
	nCarD=0;
	sLasT=0;
	tModePilE=0;//mode pile ou file indéterminé
	if (nCardinalMax>0)
		pDequE=malloc(sizeof(DequE));
	else free(pDequE);
	if (bDequeOuvertE)//ie FlipFlop() ci-dessus a été appelé avec un nCardinalMax strictt positif raisonnable,ie knDequeCardinalMaX ou moins.
		DequeRazer(nCardMaX);//dc en O(nCardMaX) et pas en O(knDequeCardinalMaX),ce qui changerait la complexité algorithmQ pour les petits graphes.
}//DequeAllouer

void DequeAMORCER(){
	//amorce le présent module une fois pour toutes (donc sa complexité n'est pas critique a priori)
	//caractériser la deque avec des valeurs aberrantes qui seront dénoncées par les assertions
		pDequE=0;
		nCarD=-knDequeCardinalMaX;//cette valeur négative impropre déclenchera immanquablt une assertion si l'appel à DequeOuvrir() est oublié.
		sLasT=-knDequeCardinalMaX;
		tModePilE=0;//mode pile ou file indéterminé
	bDequeOuvertE=kF;//vital
	bDequeAmorceR=kV;
}//DequeAMORCER

int nDequeCardinal(){//O(1)
	int nCardinal=nCarD;
	Assert2("nDequeCardinal",bDequeAmorceR,bCroit(0,nCardinal,nCardMaX));
	return(nCardinal);
}//nDequeCardinal

int bDequeContient(int sSommeT){//O(1)
	int bContient;
	Assert3("bDequeContient",bDequeAmorceR,bDequeOuvertE,bCroit(1,sSommeT,nCardMaX));
	bContient=(pDequE->sNexT[sSommeT]!=0);//ce code peut être compacté. Mais est-ce plus clair?
	return(bContient);//le coût d'exécution des contrôles (ici, Assert3) dépasse le coût de la seule instruction "utile" (bContient=). C'est fréquent.
}//nDequeCardinal

int sDequeDefiler(){//O(1)
	int sDefiler=0;
	Assert5("sDequeDefiler",bDequeAmorceR,bDequeOuvertE,bCroit(1,nCardMaX,knDequeCardinalMaX),bCroit(1,sLasT,nCardMaX),tModePilE<=0);
	tModePilE=-1;
	if (nCarD>0) {
		sDefiler=pDequE->sNexT[sLasT];//lit la tête de file
		pDequE->sNexT[sLasT]=pDequE->sNexT[sDefiler];
		pDequE->sNexT[sDefiler]=0;//vital vu les tests tels que "if (!sNexT[sSommeT])" ds DequeEmpiler
		nCarD--;
	}
	Assert2("sDequeDefiler",bCroit(1,sDefiler,knDequeCardinalMaX),nCarD>=0);
	return(sDefiler);
}//sDequeDefiler

int sDequeDepiler(){//O(1)
	int sDepiler=0;
	Assert5("sDequeDepiler",bDequeAmorceR,bDequeOuvertE,bCroit(1,nCardMaX,knDequeCardinalMaX),bCroit(1,sLasT,nCardMaX),tModePilE>=0);
	tModePilE=+1;
	if (nCarD>0) {
		sDepiler=pDequE->sNexT[sLasT];//lit le sommet de pile (alias la tête de file)
		pDequE->sNexT[sLasT]=pDequE->sNexT[sDepiler];
		pDequE->sNexT[sDepiler]=0;//vital vu les tests tels que "if (!sNexT[sSommeT])" ds DequeEmpiler
		nCarD--;
	}
	Assert2("sDequeDepiler",bCroit(1,sDepiler,knDequeCardinalMaX),nCarD>=0);
	return(sDepiler);
}//sDequeDepiler

void DequeEmpiler(int sSommeT){//O(1)
	//empile sSommeT si celui-ci n'est pas déjà dans la deque
	Assert5("DequeEmpiler",bDequeAmorceR,bDequeOuvertE,bCroit(0,nCardMaX,knDequeCardinalMaX-1),bCroit(1,sSommeT,nCardMaX),tModePilE>=0);
	tModePilE=+1;
	if (!pDequE->sNexT[sSommeT]) {//le sommet en question,défini,ne figure pas déjà dans la deque ——allouée et non saturée vu Assert4()
		if (nCarD>0) {
			pDequE->sNexT[sSommeT]=pDequE->sNexT[sLasT];//case mémoire disponible vu li-2
			pDequE->sNexT[sLasT]=sSommeT;
			nCarD++;//ne peut déborder vu le dernier opérande de Assert4 (li -5)
			}
		else {
			pDequE->sNexT[sSommeT]=sSommeT;
			nCarD=1;
			sLasT=sSommeT;//seule différence avec le code de DequeEnfiler()
		}
	}
}//DequeEmpiler

void DequeEnfiler(int sSommeT){//O(1)
	//enfile sSommeT si celui-ci n'est pas déjà dans la deque
	Assert5("DequeEnfiler",bDequeAmorceR,bDequeOuvertE,bCroit(0,nCardMaX,knDequeCardinalMaX-1),bCroit(1,sSommeT,nCardMaX),tModePilE<=0);
	tModePilE=-1;
	if (!pDequE->sNexT[sSommeT]) {
		if (nCarD>0) {
			pDequE->sNexT[sSommeT]=pDequE->sNexT[sLasT];//case disponible vu li-2
			pDequE->sNexT[sLasT]=sSommeT;
			nCarD++;//ne peut déborder vu le dernier opérande de Assert4 (li -5)
			}
		else {
			pDequE->sNexT[sSommeT]=sSommeT;
			nCarD=1;
		}
		sLasT=sSommeT;//seule différence avec le code de DequeEmpiler()
	}
}//DequeEnfiler

void DequeINITIALISER(){//O(?)
	//relance le présent module
	Assert2("DequeINITIALISER",bDequeAmorceR,!bDequeOuvertE);
}//DequeINITIALISER

int sDequeQueue(){//O(1)
	int sQueue=0;
	Assert5("sDequeQueue",bDequeAmorceR,bDequeOuvertE,bCroit(1,nCardMaX,knDequeCardinalMaX),bCroit(1,nCarD,nCardMaX),tModePilE<0);
	if (nCarD>0)//ce test évite de retourner une valeur flottante (copie de LasT) au lieu d'une constante (0) quand les assertions sont désactivées
		sQueue=sLasT;
	Assert1("sDequeQueue",bCroit(1,sQueue,nCardMaX));
	return(sQueue);
}//sDequeQueue

void DequeRazer(int nCardinalMax){//O(nCardinalMax)
	int uS;
	Assert4("DequeRazer",bDequeAmorceR,bDequeOuvertE,bCroit(0,nCardMaX,knDequeCardinalMaX),bCroit(0,nCardinalMax,nCardMaX));
	for (uS=1;uS<=nCardinalMax;uS++)
		pDequE->sNexT[uS]=0;
	nCarD=0;
	sLasT=0;
}//DequeRazer

int sDequeSommet(){//O(1)
	int sSommet;
	Assert5("sDequeSommet",bDequeAmorceR,bDequeOuvertE,bCroit(1,nCardMaX,knDequeCardinalMaX),bCroit(1,sLasT,nCardMaX),tModePilE>0);
	sSommet=pDequE->sNexT[sLasT];
	Assert1("sDequeSommet",bCroit(1,sSommet,nCardMaX));
	return(sSommet);
}//sDequeSommet

int sDequeSuivant(int sX){//O(1)
	int sY;
	sY=pDequE->sNexT[sX];
	Assert1("sDequeSuivant",bCroit(1,sY,nCardMaX));
	return(sY);
}//sDequeSuivant

void DequeTESTER(int iTest){
	//teste le présent module
	int sSource;
	Appel0(sC2("DequeTester,test n°",sEntier(iTest)));
		switch (iTest) {
			case 1:
				DequeAllouer(4);
					DequeVoir("Deque allouée et vide, censée être utilisée en mode pile.");
					DequeEmpiler(4);
					DequeEmpiler(2);
					DequeVoir("Deque pleine:");
					sSource=sDequeDepiler();
					te("Sommet dépilé",sSource);
					DequeVoir("Deque résultante:");
					sSource=sDequeDepiler();
					te("Sommet dépilé",sSource);
					DequeVoir("Deque finale:");
				DequeAllouer(0);
				DequeAllouer(12);
					DequeVoir("Deque allouée et vide, censée être utilisée en mode file.");
					DequeEnfiler(5);
					DequeEnfiler(3);
					DequeVoir("Deque pleine:");
					sSource=sDequeDefiler();
					DequeVoir("Deque finale:");
				DequeAllouer(0);
				break;
			default:
				DequeAllouer(12);
					DequeVoir("Deque vide");
					DequeEmpiler(5);
					DequeEnfiler(3);//déclenche une assertion car la deque censée implémenter une pile vu li-1 est utilisée maintenant en file.
				DequeAllouer(0);
				break;
		}
	Appel1(sC2("DequeTester,test n°",sEntier(iTest)));
}//DequeTESTER	

int sDequeTete(){//O(1)
	int sTete;
	sTete=sDequeSommet();//la tête de file est toujours le sommet de pile ds la présente implémentation de la deque
	return(sTete);
}//sDequeTete

int bDequeVide(){//O(1)
	int bVide;
	Assert4("bDequeVide",bDequeAmorceR,bDequeOuvertE,bCroit(0,nCardMaX,knDequeCardinalMaX),bCroit(0,nCarD,nCardMaX));
	bVide=(nCarD==0);
	return(bVide);//exemple de routine où les contrôles (ici, des assertions) sont plus coûteux que le code utile.
}//bDequeVide

void DequeVoir(char *sMessage){//O(nCardMaX)
	int uS;
	Assert3("DequeVoir",bDequeAmorceR,bDequeOuvertE,sMessage!=0);
	printf("%s\n",sMessage);
	//afficher nCarD après affichage des index de sNexT[]
		printf("index = ");
		for (uS=1;uS<=nCardMaX;uS++)
			printf(" %2d  ",uS);
		printf("  nCarD=%d\n",nCarD);
	//afficher sLasT après affichage des valeurs de sNexT[]
		printf("valeur= ");
		for (uS=1;uS<=nCardMaX;uS++)
			printf(" %2d  ",pDequE->sNexT[uS]);
		printf("  sLasT=%d\n",sLasT);
}//DequeVoir

