#include "Outil.h"

#define kuAntiSlashZerO 1 //encombrement du caractère "\0" qui délimite les chaînes de caractères
#define kcEchappemenT1 -61
#define kcEchappemenT2 -59
#define knEcrisMaX 63
#define kuOctetGererMaX  kuByteMax
#define kuWhileMaX 5 //nb max de while imbriqués (si des appels récursifs imbriquent un grand nombre de while, augmenter sensiblement cette valeur)
//constantes et variables:
int bAppeL[1+knEcrisMaX];//dédié au contrôle des appels de routines Appel0() et Appel1()
int nAppeL=0;//initialisation vitale ici car OutilAmorcer n'a pas encore été appelé à l'appel de Appel0() en tête de main();dédié Appel0() et Appel1()
int nOctetGereR0;
long yOctetGereR0[1+kuOctetGererMaX];
int nOctetGereR1;
long yOctetGereR1[1+kuOctetGererMaX];
int zuOctetGereR;
int bOutilAmorceR;//ie le module a bien été amorcé
int uPremieR[1+kuPremierRgMax];
int ipWhilE=0;//index de pile dédié While() et bWhile()
long zWhilE[1+kuWhileMaX];
//prototypes de TOUTES les routines privées,ci-dessous,en .c,puisque le .h doit être réservé aux prototypes sde routines publiques appelées effectivement depuis l'extérieur. 
void AsserT(char *sContexte,int bAssertion1,int bAssertion2,int bAssertion3,int bAssertion4,int bAssertion5,int bAssertion6);
void AsserT0(char *sContexte,int bAssertion,int nParametre);
int bConsonnE2(char *sTexte,int *pnCodeCaractereRg);
int bLettrE2(char *sTexte,int *pnCodeCaractereRg);
void OctetGereR(char *sMalloc);//technique,gère les malloc et les free des chaînes de caractères
void PremierAmorceR();
int bVoyellE2(char *sTexte,int *pnCodeCaractereRg);

void t(char *sTexte){
	assert(sTexte!=0);
	printf("%s.\n",sTexte);
}//t

void tb(char *sTexte,int bBooleen){
	printf("%s:%s.\n",sTexte,(bBooleen!=0)?"vrai":"faux");
}//tb

void te(char *sTexte,long yEntier1){
	printf("%s:%li.\n",sTexte,yEntier1);
}//te

void tee(char *sTexte,long yEntier1,long yEntier2){
	printf("%s:%li, %ld.\n",sTexte,yEntier1,yEntier2);
}//tee

void teee(char *sTexte,long yEntier1,long yEntier2,long yEntier3){
	printf("%s:%li, %li, %li.\n",sTexte,yEntier1,yEntier2,yEntier3);
}//teee

void teeee(char *sTexte,long yEntier1,long yEntier2,long yEntier3,long yEntier4){
	printf("%s:%li, %li, %li, %li\n",sTexte,yEntier1,yEntier2,yEntier3,yEntier4);
}//teeee

void teeeee(char *sTexte,long yEntier1,long yEntier2,long yEntier3,long yEntier4,long yEntier5){
	printf("%s:%li, %li, %li, %li, %li\n",sTexte,yEntier1,yEntier2,yEntier3,yEntier4,yEntier5);
}//teeeee

void teeeeee(char *sTexte,long yEntier1,long yEntier2,long yEntier3,long yEntier4,long yEntier5,long yEntier6){
	printf("%s:%li, %li, %li, %li, %li, %li\n",sTexte,yEntier1,yEntier2,yEntier3,yEntier4,yEntier5,yEntier6);
}//teeeeee

void tr(char *sTexte,double dReel1){
	printf("%s:%lf.\n",sTexte,dReel1);//ou %8.3lf pr 8 caractères en tout et 3 décimales
}//tr

void trr(char *sTexte,double dReel1,double dReel2){
	printf("%s:%lf, %lf.\n",sTexte,dReel1,dReel2);
}//trr

void trrr(char *sTexte,double dReel1,double dReel2,double dReel3){
	printf("%s:%lf, %lf, %lf.\n",sTexte,dReel1,dReel2,dReel3);
}//trrr

void tt(char *sTexte1,char *sTexte2){
	Assert2("Routine tt",sTexte1!=0,sTexte2!=0);
	printf("%s, %s.\n",sTexte1,sTexte2);
}//tt

void ttt(char *sTexte1,char *sTexte2,char *sTexte3){
	Assert3("Routine ttt",sTexte1!=0,sTexte2!=0,sTexte3!=0);
	printf("%s, %s, %s.\n",sTexte1,sTexte2,sTexte3);
}//ttt

void tttt(char *sTexte1,char *sTexte2,char *sTexte3,char *sTexte4){
	Assert4("Routine tttt",sTexte1!=0,sTexte2!=0,sTexte3!=0,sTexte4!=0);
	printf("%s, %s, %s, %s.\n",sTexte1,sTexte2,sTexte3,sTexte4);
}//tttt

void ttttt(char *sTexte1,char *sTexte2,char *sTexte3,char *sTexte4,char *sTexte5){
	Assert5("Routine sssss",sTexte1!=0,sTexte2!=0,sTexte3!=0,sTexte4!=0,sTexte5!=0);
	printf("%s, %s, %s, %s, %s.\n",sTexte1,sTexte2,sTexte3,sTexte4,sTexte5);
}//ttttt

void AsserT(char *sContexte,int bAssertion1,int bAssertion2,int bAssertion3,int bAssertion4,int bAssertion5,int bAssertion6){
	//contrôle les assertions fournies en paramètres et indique toutes celles qui ne sont pas vérifiées
	int bAssertion=bAssertion1 && bAssertion2 && bAssertion3 && bAssertion4 && bAssertion5 && bAssertion6;
	if (!bAssertion){//si une assertion est fausse,afficher sContexte et le numéro de cette assertion ——afin de faciliter le débogage ultérieur.
		AsserT0(sContexte,bAssertion1,1); 
		AsserT0(sContexte,bAssertion2,2); 
		AsserT0(sContexte,bAssertion3,3);
		AsserT0(sContexte,bAssertion4,4);
		AsserT0(sContexte,bAssertion5,5);
		AsserT0(sContexte,bAssertion6,6);
	}
	assert(bAssertion);//si bAssertion est vrai,indolore;sinon,affiche un message système qui ne vous sera d'aucune utilité puis stoppe l'exécution.
}//AsserT

void AsserT0(char *sContexte,int bAssertion,int nParametre){
	if (!bAssertion){
		printf("    *** Assertion fausse (expression booléenne n°%d)",nParametre);
		if (strlen(sContexte)>0)
			printf(" dans \"%s\"",sContexte);
		printf(".\n");
	}
}//AsserT0

void Assert1(char *sContexte,int bAssertion1){
	AsserT(sContexte,bAssertion1,kV,kV,kV,kV,kV);
}//Assert1

void Assert2(char *sContexte,int bAssertion1,int bAssertion2){
	AsserT(sContexte,bAssertion1,bAssertion2,kV,kV,kV,kV);
}//Assert2

void Assert3(char *sContexte,int bAssertion1,int bAssertion2,int bAssertion3){
	AsserT(sContexte,bAssertion1,bAssertion2,bAssertion3,kV,kV,kV);
}//Assert3

void Assert4(char *sContexte,int bAssertion1,int bAssertion2,int bAssertion3,int bAssertion4){
	AsserT(sContexte,bAssertion1,bAssertion2,bAssertion3,bAssertion4,kV,kV);
}//Assert4

void Assert5(char *sContexte,int bAssertion1,int bAssertion2,int bAssertion3,int bAssertion4,int bAssertion5){
	AsserT(sContexte,bAssertion1,bAssertion2,bAssertion3,bAssertion4,bAssertion5,kV);
}//Assert5

void Assert6(char *sContexte,int bAssertion1,int bAssertion2,int bAssertion3,int bAssertion4,int bAssertion5,int bAssertion6){
	AsserT(sContexte,bAssertion1,bAssertion2,bAssertion3,bAssertion4,bAssertion5,bAssertion6);
}//Assert6

long zAbs(long yEntier){
	//rend la valeur absolue positive ou déroute si yEntier est trop négatif;cache la fonction labs
	long zAbs;
	Assert1("zAbs",yEntier!=kyLongintMin);
	zAbs=labs(yEntier);//>=0 ssi yEntier!=kyLongintMin
	return(zAbs);
}//zAbs

void Appel0(char *sMessage){
	//affiche sMessage s'il est non vide;sinon,affiche "Programme en cours...". Puis passe à la ligne. Vérifie le parenthésage des appels.
	Assert2("Appel0a",sMessage!=0,nAppeL<knEcrisMaX);
	FlipFlop("Appel0b",1,&bAppeL[++nAppeL]);//vérifie que Appel0() ne suit pas un Appel0(), ie il y a 1 Appel1() entre eux
	if (strlen(sMessage)==0){
		printf("Programme en cours...\n");
	} else printf("%s%s: tâche en cours...\n",sE(2*nAppeL),sMessage);
}//Appel0

void Appel1(char *sMessage){
	//affiche sMessage s'il est non vide;sinon,affiche "Programme terminé.". Puis passe à la ligne. Vérifie le parenthésage des appels.
	int nMessageLg=strlen(sMessage);
	Assert2("Appel1a",sMessage!=0,nAppeL>0);
	FlipFlop("Appel1b",0,&bAppeL[nAppeL]);//vérifie que Appel1() ne suit pas un Appel1(), ie il y a 1 Appel0() entre eux
	if (nMessageLg)
		printf("%s%s: tâche terminée.\n",sE(2*nAppeL),sMessage);
	else printf("Programme terminé.\n");
	nAppeL--;
	Assert1("Appel1c",nAppeL>=0);
	if (!nMessageLg){
		Assert1("Appel1d",nAppeL==0);//ie Appel0() et Appel1() sont correctement parenthésés
		Assert1("Appel1e",ipWhilE>=0);//si ok,il y a bien 1° un appel à While() avant chaque while/do while et 2° un appel à bWhile() dans ladite boucle
	}
}//Appel1

int bBit(char cCaractere){
	int bBit=(cCaractere=='0') || (cCaractere=='1');
	assert(bBit==0 || bBit==1);
	return(bBit);
}//bBit

int bBool(long yEntier){
	int bBool=(yEntier==0) || (yEntier==1);
	assert(bBool==0 || bBool==1);
	return(bBool);
}//bBool

char *sBool(long yValeur){
	//rend en clair la valeur booléenne de yValeur
	if (yValeur)
		return("vrai");
	else return("faux");
}//sBool

int bByte(long yEntier){
	int bByte=bCroit(0,yEntier,kuByteMax);
	return(bByte);
}//bByte

char *sC(char cAlphaNumeriqueOuEspace){
	//convertit cA en string;cA est censé être un caractère alphanumérique (donc non accentué) ou un espace
	char *sAccu=malloc(1+kuAntiSlashZerO);
	char sMotif[2];
	assert(isalnum(cAlphaNumeriqueOuEspace) || isspace(cAlphaNumeriqueOuEspace));//isspace: espace,saut de page,fin de ligne,retour chariot,tabulation.
	sMotif[0]=cAlphaNumeriqueOuEspace;
	sMotif[1]='\0';
	strcpy(sAccu,sMotif);
	OctetGereR(sAccu);
	return(sAccu);
}//sC

char *sC1(char *sA){
	//rend sA après avoir vérifié que son pointeur n'est pas nul
	assert(sA!=0);
	return(sA);
}//sC1

char *sC1p(char *sA){
	//concatène sA et "."
	assert(sA!=0);
	char *sAccu=sC2(sA, ".");
	return(sAccu);
}//sC1p

char *sC2(char *sA,char *sB){
	//concatène sA et sB
	int uRequis;
	Assert2("routine sC2",sA!=0,sB!=0);
	uRequis=1+strlen(sA)+strlen(sB);
	char *sAccu=malloc(uRequis+kuAntiSlashZerO);
	strcpy(sAccu,sA);
	strcat(sAccu,sB);
	OctetGereR(sAccu);
	return(sAccu);
}//sC2

char *sC2b(char *sA,char *sB){
	//concatène sA à sB,avec un blanc intercalé si sA et sB sont de longueur non nulle
	int bBlancEnSus,nRequis;
	char *sAccu;
	Assert2("routine sC2b",sA!=0,sB!=0);
	nRequis=strlen(sA)+strlen(sB);
	assert(nRequis>=0);
	bBlancEnSus=(strlen(sA)>0) && (strlen(sB)>0);
	if (bBlancEnSus)
		nRequis++;
	sAccu=malloc(nRequis+kuAntiSlashZerO);//les accents aigus génèrent des codes caractères en sus qui sont ignorés par strlen...Le 4 minimise les dégâts
	strcpy(sAccu,sA);
	if (bBlancEnSus)
		strcat(sAccu," ");
	strcat(sAccu,sB);
	OctetGereR(sAccu);
	return(sAccu);
}//sC2b

char *sC2bp(char *sA,char *sB){
	//concatène sA,sB et "." en séparant les données de longueur non nulle par des blancs
	char *sAccu=sC2(sC2b(sA,sB),".");//sC2b vérifie que sA et sB sont définis
	return(sAccu);
}//sC3bp

char *sC2p(char *sA,char *sB){
	//concatène sA,sB et "."
	char *sAccu=sC2(sC2(sA, sB),".");//sC2 vérifie que sA et sB sont définis
	return(sAccu);
}//sC2p

char *sC2v(char *sA,char *sB){
	//concatène sA à sB,avec un blanc intercalé si sA et sB sont de longueur non nulle
	int bVirguleEnSus,nRequis;
	char *sAccu;
	Assert2("routine sC2v",sA!=0,sB!=0);
	nRequis=strlen(sA)+strlen(sB);
	assert(nRequis>=0);
	bVirguleEnSus=(strlen(sA)>0) && (strlen(sB)>0);
	if (bVirguleEnSus)
		nRequis++;
	sAccu=malloc(nRequis+kuAntiSlashZerO);//les accents aigus génèrent des codes caractères en sus qui sont ignorés par strlen...Le 4 minimise les dégâts
	strcpy(sAccu,sA);
	if (bVirguleEnSus)
		strcat(sAccu,",");
	strcat(sAccu,sB);
	OctetGereR(sAccu);
	return(sAccu);
}//sC2v

char *sC3(char *sA,char *sB,char *sC){
	//concatène sA,sB et sC
	char *sAccu=sC2(sC2(sA,sB),sC);//sC2 vérifie que les arguments sont définis
	return(sAccu);
}//sC3

char *sC3b(char *sA,char *sB,char *sC){
	//concatène sA,sB et sC en séparant les données de longueur non nulle par des blancs
	char *sAccu=sC2b(sC2b(sA,sB),sC);//sC2 vérifie que les arguments sont définis
	return(sAccu);
}//sC3b

char *sC3bp(char *sA,char *sB,char *sC){
	//concatène sA,sB,sC et "." en séparant les données de longueur non nulle par des blancs
	char *sAccu=sC2(sC3b(sA,sB,sC),".");//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC3bp

char *sC3p(char *sA,char *sB,char *sC){
	//concatène sA,sB,sC et "."
	char *sAccu=sC4(sA,sB,sC, ".");//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC3p

char *sC3v(char *sA,char *sB,char *sC){
	//concatène sA,sB et sC en séparant les données de longueur non nulle par des virgules
	char *sAccu=sC2v(sC2v(sA,sB),sC);//sC2 vérifie que les arguments sont définis
	return(sAccu);
}//sC3v

char *sC4(char *sA,char *sB,char *sC,char *sD){
	//concatène sA,sB,sC et sD
	char *sAccu=sC2(sC3(sA,sB,sC),sD);//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC4

char *sC4b(char *sA,char *sB,char *sC,char *sD){
	//concatène sA,sB,sC et sD en séparant les données de longueur non nulle par des blancs
	char *sAccu=sC2b(sC3b(sA,sB,sC),sD);//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC4b

char *sC4bp(char *sA,char *sB,char *sC,char *sD){
	//concatène sA,sB,sC,sD et "." en séparant les données de longueur non nulle par des blancs
	char *sAccu=sC2b(sC4b(sA,sB,sC,sD),".");//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC4bp

char *sC4p(char *sA,char *sB,char *sC,char *sD){
	//concatène sA,sB,sC,sD et "."
	char *sAccu=sC2(sC4(sA,sB,sC,sD),".");//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC4p

char *sC5(char *sA,char *sB,char *sC,char *sD,char *sE){
	//concatène sA,sB,sC,sD et sE
	char *sAccu=sC2(sC4(sA,sB,sC,sD),sE);//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC5

char *sC5b(char *sA,char *sB,char *sC,char *sD,char *sE){
	//concatène sA,sB,sC,sD et sE en séparant les données de longueur non nulle par des blancs
	char *sAccu=sC2b(sC4b(sA,sB,sC,sD),sE);//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC5b

char *sC5bp(char *sA,char *sB,char *sC,char *sD,char *sE){
	//concatène sA,sB,sC,sD,sE et "." en séparant les données de longueur non nulle par des blancs
	char *sAccu=sC2(sC5b(sA,sB,sC,sD,sE),".");//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC5bp

char *sC5p(char *sA,char *sB,char *sC,char *sD,char *sE){
	//concatène sA,sB,sC,sD,sE,sF et "."
	char *sAccu=sC2(sC5(sA,sB,sC,sD,sE),".");//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC5p

char *sC6(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF){
	//concatène sA,sB,sC,sD,sE et sF
	char *sAccu=sC2(sC5(sA,sB,sC,sD,sE),sF);//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC6

char *sC6b(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF){
	//concatène sA,sB,sC,sD,sE et sF en séparant les données de longueur non nulle par des blancs
	char *sAccu=sC2b(sC5b(sA,sB,sC,sD,sE),sF);//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC6b

char *sC6bp(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF){
	//concatène sA,sB,sC,sD,sE,sF et "." en séparant les données de longueur non nulle par des blancs
	char *sAccu=sC2(sC6b(sA,sB,sC,sD,sE,sF),".");//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC6bp

char *sC6p(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF){
	//concatène sA,sB,sC,sD,sE,sF et "."
	char *sAccu=sC2(sC6(sA,sB,sC,sD,sE,sF),".");//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC6p

char *sC7(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG){
	//concatène sA,sB,sC,sD,sE,sF et sG
	char *sAccu=sC2(sC6(sA,sB,sC,sD,sE,sF),sG);//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC7

char *sC7b(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG){
	//concatène sA,sB,sC,sD,sE,sF et sG en séparant les données de longueur non nulle par des blancs
	char *sAccu=sC2b(sC6b(sA,sB,sC,sD,sE,sF),sG);//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC7b

char *sC7bp(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG){
	//concatène sA,sB,sC,sD,sE,sF,sG et "." en séparant les données de longueur non nulle par des blancs
	char *sAccu=sC2(sC7b(sA,sB,sC,sD,sE,sF,sG),".");//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC7bp

char *sC7p(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG){
	//concatène sA,sB,sC,sD,sE,sF,sG et "."
	char *sAccu=sC2(sC7(sA,sB,sC,sD,sE,sF,sG),".");//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC7p

char *sC8(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG,char *sH){
	//concatène sA,sB,sC,sD,sE,sF,sG et sH
	char *sAccu=sC2(sC7(sA,sB,sC,sD,sE,sF,sG),sH);//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC8

char *sC8b(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG,char *sH){
	//concatène sA,sB,sC,sD,sE,sF,sG et sH en séparant les données de longueur non nulle par des blancs
	char *sAccu=sC2b(sC7b(sA,sB,sC,sD,sE,sF,sG),sH);//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC8b

char *sC8bp(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG,char *sH){
	//concatène sA,sB,sC,sD,sE,sF,sG,sH et "." en séparant les données de longueur non nulle par des blancs
	char *sAccu=sC2(sC8b(sA,sB,sC,sD,sE,sF,sG,sH),".");//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC8bp

char *sC8p(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG,char *sH){
	//concatène sA,sB,sC,sD,sE,sF,sG,sH et "."
	char *sAccu=sC2(sC8(sA,sB,sC,sD,sE,sF,sG,sH),".");//sC2 vérifiera que les arguments sont définis
	return(sAccu);
}//sC8p

int nCaractere(char *sTexte){
	//rend le nombre de caractères de sTexte (et non pas le nombre de codes caractères,contrairt à strlen() qui renvoie 2 pour un seul "à")
	int nC=0;//index sur le code caractère courant de sTexte
	int nCaractere=0;
	int nChaineLg;
	char cCode;
	assert(sTexte!=0);
	for (nChaineLg=strlen(sTexte),nC=0;nC<nChaineLg;nC++){
		cCode=sTexte[nC];
		if ( isalpha(cCode) || isdigit(cCode) || bLettrE2(sTexte,&nC) ) //dernier terme: voyelle ou consonne avec un signe diacritique
			nCaractere++;
	}
	assert(nCaractere>=0);
	return(nCaractere);
}//nCaractere

int nChainePos(char cQuoi,char *sDansQuoi){
	//rend le rang0 de cQuoi dans sDansQuoi, ou -1 si échec
	int nC;
	int nPos=-1;
	for (nC=0; nC<strlen(sDansQuoi) && (nPos<0); nC++)
		if (cQuoi==sDansQuoi[nC])
			nPos=nC;
	return(nPos);
}//nChainePos

int bChiffre(char cCaractere){
	//cCaractere est un chiffre décimal
	int bChiffre=bDecit(cCaractere);
	return(bChiffre);
}//bChiffre

char *sChoix0(int bOption,char *sOption){
	//rend sOption si bOption est vrai;sinon,rend une chaîne vide.
	int nRequis;
	assert(sOption!=0);
	nRequis = bOption? strlen(sOption) : 0;
	char *sCopie=malloc(nRequis+kuAntiSlashZerO);
	sCopie[0]='\0';
	if (bOption)
		strcpy(sCopie,sOption);
	OctetGereR(sCopie);
	return(sCopie);
}//sChoix0

char *sChoix(int bOptionSinonAlternative,char *sOption,char *sAlternative){
	//rend sOption si bOptionSinonAlternative est vrai; sinon,rend sAlternative.
	int nRequis;
	Assert2("sCoix",sOption!=0,sAlternative!=0);
	nRequis = bOptionSinonAlternative? strlen(sOption) : strlen(sAlternative);
	char *sCopie=malloc(nRequis+kuAntiSlashZerO);
	if (bOptionSinonAlternative)
		strcpy(sCopie,sOption);
	else strcpy(sCopie,sAlternative);
	OctetGereR(sCopie);
	return(sCopie);
}//sChoix

void Confirmer(char *sMessage){
	char cCar;
	printf("%s Valider SVP (touche entrée)",sMessage);
	scanf("%c",&cCar);
	printf(" Merci d'avoir validé.\n");
}//Confirmer

int bConsonnE2(char *sTexte,int *pnCodeCaractereRg){
	//sTexte[*pnCodeCaractereRg] ou Chaine[*pnCodeCaractereRg..*pnCodeCaractereRg+1] code une consonne;si vrai et 2 codes, passe au code suivant
	int nCar;
	char cCode;
    #define knConsonne1LiM 21
    #define knConsonne2LiM 04
	int nConsonne1[knConsonne1LiM]={64,65,66,67,69,70,71,73,74,75,76,77,79,80,81,82,83,85,86,87,89};//consonnes sans signe diacritique
	int nConsonne2[knConsonne2LiM]={79,89,111,121};//ççÑñ";
	int bConsonne2=0;
	Assert2("bConsonnE2a",sTexte!=0,pnCodeCaractereRg!=0);
	Assert1("bConsonnE2b",bCroit(0,2,strlen(sTexte)));
	Assert1("bConsonnE2c",bCroit(0,*pnCodeCaractereRg,strlen(sTexte)));
	cCode=sTexte[*pnCodeCaractereRg];
	bConsonne2=isalpha(cCode);//consonne ou voyelle sans signe diacritique (accents,cédille,tilde...)
	if (bConsonne2){//consonne?
		assert(0);//ie code actuellt non exécuté vu le contexte des appels à bConsonnE2()
		for (bConsonne2=0,nCar=0; nCar<knConsonne1LiM; nCar++)
			bConsonne2=bConsonne2||(cCode==-nConsonne1[nCar]);
		}
	else if (*pnCodeCaractereRg<strlen(sTexte)) {//l'accès à sTexte[nCodeCaractereRg+1] est valide
		if (cCode==kcEchappemenT1){
			cCode=sTexte[*pnCodeCaractereRg+1];
			for (nCar=0; nCar<knConsonne2LiM; nCar++)
				bConsonne2=bConsonne2||(cCode==-nConsonne2[nCar]);
			if (bConsonne2)
				(*pnCodeCaractereRg)++;
		}
	}
	return(bConsonne2);
}//bConsonnE2

char *sCouple(long yEntierA,long yEntierB){
	//rend la chaîne (yEntierA,yEntierB)	
	char *sCouple=sP(sC3(sEntier(yEntierA),",",sEntier(yEntierB)));
	OctetGereR(sCouple);
	return(sCouple);
}//sCouple

void Croissant(double dMinInclus,double dDedans,double dMaxInclus){
	if (!bCroissant(dMinInclus,dDedans,dMaxInclus))
		printf("BUG ds bCroissant():%lf≤%lf≤%lf est FAUX\n",dMinInclus,dDedans,dMaxInclus);
	assert(bCroissant(dMinInclus,dDedans,dMaxInclus));
}//Croissant

int bCroissant(double dMinInclus,double dDedans,double dMaxInclus){
	int bCroissant=(dMinInclus<=dDedans) && (dDedans<=dMaxInclus);
	return(bCroissant);
}//bCroissant

int bCroissantStrict(double dMinExclu,double dDedans,double dMaxExclu){
	int bCroissantStrict=(dMinExclu<dDedans) && (dDedans<dMaxExclu);
	return(bCroissantStrict);
}//bCroissantStrict

void CroissantStrict(double dMinExclu,double dDedans,double dMaxExclu){
	if (!bCroissantStrict(dMinExclu,dDedans,dMaxExclu))
		printf("BUG ds bCroissantStrict():%lf<%lf<%lf est FAUX\n",dMinExclu,dDedans,dMaxExclu);
	assert(bCroissantStrict(dMinExclu,dDedans,dMaxExclu));
}//CroissantStrict

int bCroit(long yMinInclus,long yDedans,long yMaxInclus){
	int bCroit=(yMinInclus<=yDedans) && (yDedans<=yMaxInclus);
	return(bCroit);
}//bCroit

int bCroit4(long yA,long yB,long yC,long yD){//rend yA≤yB≤yC<=yD
	int bCroit4=bCroit(yA,yB,yC) && (yC<=yD);
	return(bCroit4);
}//bCroit4


int bCroitStrict(long yMinExclu,long yDedans,long yMaxExclu){
	int bCroitStrict=(yMinExclu<yDedans) && (yDedans<yMaxExclu);
	return(bCroitStrict);
}//bCroit

int bDecit(char cCaractere){
	//cCaractere est un chiffre décimal;cache la fonction isdigit()
	int bDecit=isdigit(cCaractere);
	return(bDecit);
}//bDecit

char *sE(int nEspace){
	//nEspace blancs juxtaposés
	char *sE=sFois(nEspace,' ');
	return(sE);
}//sE

char *sEntier(long yEntier){
	//convertit yEntier en chaîne de chiffres décimaux: 24 donne "24", -5 donne "-5".
	char *sEntier=malloc(23+kuAntiSlashZerO);//2**64=4 milliards au carré = 16*(10**18) dc "4"+18 zéros=19 chiffres; ajouter 1 caractère pr le signe "-".
	sprintf(sEntier,"%ld",yEntier);//yEntier tient forcément ds sEntier vu allocation généreuse: 4 octets alloués là où 21 suffisent.
	return(sEntier);
}//sEntier

char *sEntier2(long yEntier){
	//convertit yEntier en chaîne de chiffres décimaux: 24 donne "24", -5 donne "-5".
	char *sEntier2=malloc(23+kuAntiSlashZerO);//2**64=4 milliards au carré = 16*(10**18) dc "4"+18 zéros=19 chiffres; ajouter 1 caractère pr le signe "-".
	sprintf(sEntier2,"%2ld",yEntier);//yEntier tient forcément ds sEntier vu allocation généreuse: 4 octets alloués là où 21 suffisent.
	return(sEntier2);
}//sEntier2

char *sEntier3(long yEntier){
	//convertit yEntier en chaîne de chiffres décimaux: 24 donne "24", -5 donne "-5".
	char *sEntier3=malloc(23+kuAntiSlashZerO);//2**64=4 milliards au carré = 16*(10**18) dc "4"+18 zéros=19 chiffres; ajouter 1 caractère pr le signe "-".
	sprintf(sEntier3,"%2ld",yEntier);//yEntier tient forcément ds sEntier vu allocation généreuse: 4 octets alloués là où 21 suffisent.
	return(sEntier3);
}//sEntier3

char *sEntierAvecSigne(long yEntier){
	//// "+5" ou "-5" ou " 0"
	char *sEntier=malloc(23+kuAntiSlashZerO);//2**64=4 milliards au carré = 16*(10**18) dc "4"+18 zéros=19 chiffres; ajouter 1 caractère pr le signe "-".
	sprintf(sEntier,"%+ld",yEntier);//yEntier tient forcément ds sEntier vu allocation généreuse: 4 octets alloués là où 21 suffisent.
	return(sEntier);
}//sEntierAvecSigne

char *sEst(int bAssertion){
	//rend "est" tel quel,ou négativé avec "n'"..."pas" si bAssertion est faux 
	#define kuEstLg 3//"est"
	#define kuNestPasLg 4//"n'est pas"
	char *sEst=malloc( kuAntiSlashZerO + (bAssertion)? kuEstLg : kuNestPasLg);
	sEst[0]='\0';
	if (bAssertion)
		strcat(sEst,"est");
	else strcpy(sEst,"n'est pas");
	OctetGereR(sEst);
	return(sEst);
}//sEst

int bFaux(int iEntier){
	//rend la constante entière kV (vrai) si iEntier==0 et la constante kF (faux) sinon
	int bFaux=(iEntier==0) ? 1 : 0;
	return(bFaux);
}//bFaux

//FlipFlop,placé en tête d'une routine R(bMode,…),permet de vérifier que les appels successifs à R sont: R(true,…),R(false,…),R(true,…),R(false,…),etc.
//Le paramère pbAvant est censé être déclaré soit en variable de module soit en static dans R(), et être initialisé une fois pour toutes à false.
void FlipFlop(char* sContexte,int bApres,int *pbAvant){
	//si bApres≠*pbAvant,mémorise bApres dans pbAvant;sinon,déroute après avoir affiché sContexte.
	Assert1(sContexte,bApres!=*pbAvant);
	*pbAvant=bApres;
}//FlipFlop

long zFib(int nIndex){//fonction de Fibonacci définie par F(n)=F(n-1)+F(n-2) avec F(1)=F(2)=1, n>0
	#define kuFibMax 50
	long zFib=0;
	double rPhi,rPhiBarre,rFib;
	Assert1("nFib",bCroit(0,nIndex,kuFibMax));
	rPhi=(1.0+sqrt(5.0))/2.0;
	rPhiBarre=(1.0-sqrt(5.0))/2.0;
	rFib=(pow(rPhi,nIndex)-pow(rPhiBarre,nIndex))/sqrt(5.0);
	//printf("rFib(%d)=%lf....",nIndex,rFib);
	zFib=trunc(rFib);
	return(zFib);
}//zFib

char *sFois(int nFois,char cMotif){
	//juxtapose nFois cMotif
	int uF;
	char *sFwa;
	char cFwa[2];
	Assert2("sFois",nFois>=0,isprint(cMotif));//implique 1 code caractère par caractère,dc cMotif ne peut coder un "é" car il est occupe 2 codes caractères.
	sFwa=malloc(nFois+kuAntiSlashZerO);
	cFwa[0]=cMotif;
	cFwa[1]='\0';
	strcpy(sFwa,"");
	for (uF=1;uF<=nFois;uF++)
		strcat(sFwa,cFwa);
	OctetGereR(sFwa);
	return(sFwa);
}//sFois

char *sG(char* sTexte){
	//nEspace blancs juxtaposés
	//char *sG=sC3('"',sEntreGuillemet,'"');
	char *sG=malloc(1+strlen(sTexte)+1);
	char cGuillemet[2];
	cGuillemet[0]='"';
	cGuillemet[1]='\0';
	sG[0]='\0';
	strcat(sG,cGuillemet);
	strcat(sG,sTexte);
	strcat(sG,cGuillemet);
	OctetGereR(sG);
	return(sG);
}//sG

int nHasard(int uBorneLim){
	//rend un nombre aléatoire ds [0..uBorneLim[
	int nHasard;
	Assert1("nHasard1",bCroit(1,uBorneLim,kuIntegerMax-1));
	nHasard=rand()%uBorneLim;
	Assert1("nHasard2",bCroit(0,nHasard,uBorneLim-1));
	return(nHasard);
}//nHasard

int uHasard(int uBorneMax){
	//rend un nombre aléatoire ds [1..nBorneMax]
	int uHasard;
	Assert1("uHasard1",bCroit(1,uBorneMax,kuIntegerMax));
	uHasard=1+rand()%uBorneMax;
	Assert1("uHasard2",bCroit(1,uHasard,uBorneMax));
	return(uHasard);
}//uHasard

int bImpair(int iEntier){
	int bImpair=bVrai(iEntier%2);
	assert(bBool(bImpair));
	return (bImpair);
}//bImpair

double rInf(double dA,double dB){
	//rend inf(dA,dB)
	double rInf=(dA<dB)?dA:dB;
	return(rInf);
}//rInf

long yInf(long yA,long yB){
	//rend inf(yA,yB);identique à yMin(yA,yB)
	long yInf=(yA>yB)?yB:yA;
	return(yInf);
}//yInf

int bLettre(char cCaractere){
	//cCaractere est une lettre sans signe diacritique (accent,cédille,tilde...);cache la fonction isalpha()
	int bLettre=isalpha(cCaractere);
	return(bLettre);
}//bLettre

int bLettrE2(char *sTexte,int *pnCodeCaractereRg){
	//sTexte[*pnCodeCaractereRg] ou Chaine[*pnCodeCaractereRg..*pnCodeCaractereRg+1] code une consonne;si vrai et 2 codes, passe au code suivant
	char cCode;
	int bLettrE2=0;
	assert(sTexte!=0);
	Assert1("bLettrE2",bCroit(0,*pnCodeCaractereRg,strlen(sTexte)));
	cCode=sTexte[*pnCodeCaractereRg];
	bLettrE2=isalpha(cCode);//vrai si consonnes ou voyelles sans signe diacritique (accent,cédille,tilde...)
	if ( !bLettrE2 && (*pnCodeCaractereRg<strlen(sTexte)) ) {//l'accès à sTexte[nCodeCaractereRg+1] est valide
		bLettrE2=bVoyellE2(sTexte,pnCodeCaractereRg) || bConsonnE2(sTexte,pnCodeCaractereRg);
	}
	return(bLettrE2);
}//bLettrE2

void Ligne(){
	printf("\n");
}//Ligne

int bLigne(){
	Ligne();
	return(1);
}//bLigne

double rLog(double rN){
	//logarithme népérien
	double rLog=log(rN);
	return(rLog);
}//rLog

double rLog2(double rN){
	//logarithme en base 2
	double rLog2=log2(rN);
	return(rLog2);
}//rLog2

double rMax(double dA,double dB){
	//rend sup(dA,dB)
	double rMax=(dA>dB)?dA:dB;
	return(rMax);
}//rMax

long yMax(long yA,long yB){
	//rend max(yA,yB);identique à ySup(yA,yB)
	long yMax=(yA>yB)?yA:yB;
	return(yMax);
}//yMax

void MemIntRaz(int piMemOrigine[],int nItemEnTout){
	Assert2("MemIntRaz",piMemOrigine!=0,nItemEnTout>=0);
	MemIntValuer(piMemOrigine,nItemEnTout,0);
}//MemIntRaz

void MemIntValuer(int piMemOrigine[],int nItemEnTout,int iValeur){
	int nItem;
	Assert2("MemIntValuer",piMemOrigine!=0,nItemEnTout>=0);
	for (nItem=0; nItem<nItemEnTout; nItem++){
		piMemOrigine[nItem]=iValeur;
	}
}//MemIntValuer

void MemLongRaz(int pyMemOrigine[],int nItemEnTout){
	Assert2("MemLongRaz",pyMemOrigine!=0,nItemEnTout>=0);
	MemLongValuer(pyMemOrigine,nItemEnTout,0);
}//MemLongRaz

void MemLongValuer(int pyMemOrigine[],int nItemEnTout,long yValeur){
	int nItem;
	Assert2("MemLongValuer",pyMemOrigine!=0,nItemEnTout>=0);
	for (nItem=0; nItem<nItemEnTout; nItem++){
		pyMemOrigine[nItem]=yValeur;
	}
}//MemLongValuer

double rMin(double dA,double dB){
	//rend inf(dA,dB)
	double rMin=(dA<dB)?dA:dB;
	return(rMin);
}//rMin

long yMin(long yA,long yB){
	//rend min(yA,yB);identique à yInf(yA,yB)
	long yMin=(yA>yB)?yB:yA;
	return(yMin);
}//yMin

int bMajuscule(char cCaractere){
	//cCaractere est une lettre majuscule sans signe diacritique (accent,cédille,tilde...);cache la fonction isupper()
	int bMajuscule=isupper(cCaractere);
	return(bMajuscule);
}//bMajuscule

int bMinuscule(char cCaractere){
	//cCaractere est une lettre minuscule signe diacritique (accent,cédille,tilde...);cache la fonction islower()
	int bMinuscule=islower(cCaractere);
	return(bMinuscule);
}//bMinuscule

int uModulo1(int uDividende,int uDiviseur){
	//rend le modulo standard à ceci près que le résultat 0 éventuel est remplacé par uDiviseur: uModulo1(12,4)=4 
	int nModulo;
	Assert2("uModulo1a",uDividende>0,uDiviseur>0);
	nModulo=uDividende%uDiviseur;
	if (nModulo==0)
		nModulo=uDiviseur;
	if (0)//ou 1 pr que li+1 soit exécutée 
		teee("uModulo1",uDividende,uDiviseur,nModulo);
	Assert1("uModulo1b",bCroit(1,nModulo,uDiviseur));
	return(nModulo);
}//uModulo1

char *sNie(char *sVerbe,int bNegativer,char *sAffirmation,char *sNegation){
	//rend sVerbe suivi de sAffirmation,ou négativé avec "ne" et sNegation si bNegativer
	#define kuNegationEtBlancLgMax 4
	Assert4("sNie",sVerbe!=0,bBool(bNegativer),sAffirmation!=0,sNegation!=0);
	char *sNie=malloc(strlen(sVerbe)+ySup(strlen(sAffirmation),strlen(sNegation))+kuNegationEtBlancLgMax);
	if (bNegativer){
		strcpy(sNie,sChoix(bVoyelle(sVerbe,0),"n'","ne "));
		strcat(sNie,sVerbe);
	}
	else strcpy(sNie,sVerbe);
	strcat(sNie," ");
	if (bNegativer)
		strcat(sNie,sNegation);
	else strcat(sNie,sAffirmation);
	OctetGereR(sNie);
	return(sNie);
}//sNie

int bNul(double dNombre){
	//vrai ssi la donnée est assimilable à 0.0
	int bNul;
	double dPositif;
	dPositif=dNombre;
	if (dPositif<0.0)
		dPositif=-dPositif;
	if (dPositif<=kdEpsilon)
		bNul=kV;
	else bNul=kF;
	return(bNul);
}//bNul

void OctetGereR(char *sMalloc){
	//prend note de l'allocation de sMalloc sur l'espace courant et libère le demi-espace le plus ancien si cette allocation sature l'espace courant
	const int kbConfirmer=kF;
	int nAlloc;
	char *sAlloc;
	if (zuOctetGereR==0){
		yOctetGereR0[nOctetGereR0++]=(long) sMalloc;
		if (nOctetGereR0>=kuOctetGererMaX){
			if (kbConfirmer)
				Confirmer("Changement de demi-espace de chaînes de caractères (0 vers 1)");//mettre en commentaire après mise au point
			for (nAlloc=0; nAlloc<=kuOctetGererMaX; nAlloc++) {
				sAlloc=(char *) yOctetGereR1[nAlloc];
				if (sAlloc!=0)
					free(sAlloc);
				yOctetGereR1[nAlloc]=0;
			}
			zuOctetGereR=1-zuOctetGereR;//change de demi-espace
			nOctetGereR1=0;//premier index valide sur le futur demi-espace 
		}
	} else {
		yOctetGereR1[nOctetGereR1++]=(long) sMalloc;
		if (nOctetGereR1>=kuOctetGererMaX){
			if (kbConfirmer)
				Confirmer("Changement de demi-espace de chaînes de caractères (1 vers 0)");//mettre en commentaire après mise au point
			for (nAlloc=0; nAlloc<=kuOctetGererMaX; nAlloc++) {
				sAlloc=(char *) yOctetGereR0[nAlloc];
				if (sAlloc!=0)
					free(sAlloc);
				yOctetGereR0[nAlloc]=0;
			}
			zuOctetGereR=1-zuOctetGereR;//change de demi-espace
			nOctetGereR0=0;//premier index valide sur le futur demi-espace
		}
	}
}//OctetGereR

void OutilAMORCER(){
	//amorce le présent module une fois pour toutes
	//NB ne toucher ni à nAppeL ni à bAppeL[] utilisés avant l'amorçage;
	assert(nAppeL==1);//dédié Appel0() et Appel1();vérifie que Appel0() a bien été exécuté 1 fois ——Appel0("") est censé débuter le main().
	assert(strlen("à")>1);//ATTENTION: strlen("à")==2 et strlen("a")==1. strlen() ne compte plus des caractères mais des codes caractères,d'où le 2.
	PremierAmorceR();
	bOutilAmorceR=kV;
}//OutilAMORCER

void OutilINITIALISER(){
	//relance le présent module
	Assert1("OutilINITIALISER",bOutilAmorceR);
}//OutilINITIALISER

void OutilTESTER(int iTest){
	long zBof;
	int nIndex=0;
	long yIndex;
	int uFois;
	int nT[1+10];
	#define kuConsonneEnTout 44
	#define kuVoyelleEnTout 47
	Appel0(sC2("OutilTESTER,test n°",sEntier(iTest)));
		char *skConsonne="çÇñÑbcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZ";
		char *skVoyelle="ÃãaeiouyéàèùâêîôûäïöüÿAEIOUYÂÊÎÔÛÉÀÙÂÊÎÔÛÄËÏÖÜŸ";
		char *skLettre="çÇñÑbcdfghjklmnpqrstvwxzBCDFGHJKLMNPQRSTVWXZÃãaeiouyéàèùâêîôûäïöüÿAEIOUYÂÊÎÔÛÉÀÙÂÊÎÔÛÄËÏÖÜŸ";
		switch (iTest) {
			case 01:	printf("Le graphe %s un circuit\n",sPas("contient",1)); break;
			case 02:	printf("Le graphe %s un circuit\n",sPas("contient",0)); break;
			case 03:	printf("Il %s circuit\n",sNie("y a",1,"un","aucun")); break;
			case 04:	printf("Il %s boucle\n",sNie("y a",0,"une","aucune")); break;
			case 10:	printf("test des fonctions de concaténation:\n");
			case 11:	printf("11AVANT%sAPRES\n",sC1("a"));
			case 12:	printf("12AVANT%sAPRES\n",sC2("b","c"));
			case 13:	printf("13AVANT%sAPRES\n",sC2b("d","e"));
			case 14:	printf("14AVANT%sAPRES\n",sC2b("f",""));
			case 15:	printf("15AVANT%sAPRES\n",sC2b("","g"));
			case 16:	printf("16AVANT%sAPRES\n",sC2b("",""));
			case 17:	printf("17AVANT%sAPRES\n",sC2bp("",""));
			case 18:	printf("18AVANT%sAPRES\n",sC1p(sC2bp("h", "i")));
			case 19:	printf("19AVANT%sAPRES\n",sC7bp("1","2","3","4","5","6","7"));break;
			case 30:	assert(strlen("étagé")>6);break;//e aigu occupe 2 codes caractères,vu strlen()
			case 50:	assert(nCaractere(skVoyelle)==kuVoyelleEnTout);break;
			case 51:	assert(nCaractere(skConsonne)==kuConsonneEnTout);break;
			case 52:	assert(nCaractere(skLettre)==kuVoyelleEnTout+kuConsonneEnTout);break;
			case 55:	for (nIndex=0;nIndex<kuVoyelleEnTout;nIndex++)
							printf("test de bVoyellE2[%d] %d\n",nIndex,bVoyellE2("aeiouyéàèùâêîôûäïöüÿAEIOUYÂÊÎÔÛÉÀÙÂÊÎÔÛÄËÏÖÜŸã",&nIndex));break;
			case 60:	for (uFois=1;uFois<10;uFois++)
							printf("Tirage aléatoire dans [0..3]: %d.\n",nHasard(3));
						for (uFois=1;uFois<10;uFois++)
							printf("Tirage aléatoire dans [1..4]: %d.\n",uHasard(4));
						break;
			case 61:	zBof=zPgcd(60,32);
						zBof=zPgcd(170,153);
						zBof=zPpcm(60,32);
						zBof=zPpcm(170,153);
						break;
			case 62:	yIndex=-4;printf("%ld=%s\n",yIndex,sPar3(yIndex));
						yIndex=-169;printf("%ld=%s\n",yIndex,sPar3(yIndex));
						yIndex=-1234;printf("%ld=%s\n",yIndex,sPar3(yIndex));
						for (yIndex=1;yIndex<kE16;yIndex*=13)
							printf("%ld=%s\n",yIndex,sPar3(yIndex));
						for (yIndex=1;yIndex<kE16;yIndex*=13)
							printf("%ld=%s\n",-yIndex,sPar3(-yIndex));
						yIndex=kxLongintMax;printf("%ld=%s\n",yIndex,sPar3(yIndex));
						yIndex=kyLongintMin+1;printf("%ld=%s\n",yIndex,sPar3(yIndex));
						break;
			case 70:	Titrer("salut");
						Titrer("");
						Titrer("solo");
						break;
			case 80:	printf("Texte: %s.\n",sFois(4,'z'));
						break;
			case 90:	for (uFois=1;uFois<10;uFois++)
							nT[uFois]=5;
						MemIntRaz(nT,10);
						break;
			case 95:	for (nIndex=0;nIndex<=50;nIndex++)
							printf("zFib(%d)=%ld\n",nIndex,zFib(nIndex));
						break;
			default:
				break;
		}
	Appel1(sC2("OutilTESTER,test n°",sEntier(iTest)));
}//OutilTESTER

int bPair(int iEntier){
	int bPair=bFaux(iEntier%2);
	assert(bBool(bPair));
	return (bPair);
}//bPair

char *sP(char *sEntreParenthese){
	//rend sEntreParenthese précédé de "(" et suivi de ")"
	assert(sEntreParenthese!=0);	
	char *sP=sC3("(",sEntreParenthese,")");
	OctetGereR(sP);
	return(sP);
}//sP

char *sPar3(long yEntier){
	//convertit yEntier en chaîne dans laquelle les groupes de 3 chiffres sont séparés par des kcSeparateur qui sont des blancs,eg 12 345.
	int uC,nChiffre,nD,nDecit,nCar;
	char kcSeparateur=' ';
	char *sEntier;
	long zEntier;
	int bSigne;
	sEntier=malloc(31+kuAntiSlashZerO);//2**64=4 milliards au carré = 16*(10**18) dc "4"+18 zéros=19 chiffres; ajouter 1 caractère pr le signe "-".
	bSigne=(yEntier<0);
	zEntier=zAbs(yEntier);//oui,on peut faire mieux, mais ça prend plus de temps...
	sprintf(sEntier,"%ld",zEntier);//yEntier tient forcément ds sEntier vu allocation généreuse: 4 octets alloués là où 21 bits suffisent.
	nChiffre=strlen(sEntier);
	nDecit=nChiffre+(nChiffre-1)/3;
	nCar=0;
	sEntier[bSigne+nDecit]='\0';
	for (nD=bSigne+nDecit,uC=1;uC<=nChiffre;uC++){
		sEntier[--nD]='0'+zEntier%10;
		if (nD>=bSigne && (uC%3==0))
			sEntier[--nD]=kcSeparateur;
		zEntier=zEntier/10;
		nCar++;
	}
	Assert2("sPar3",zEntier==0,nD+1>=bSigne);
	if (bSigne)
		sEntier[0]='-';
	OctetGereR(sEntier);
	return(sEntier);
}//sPar3

char *sPas(char *sVerbe,int bNegativer){
	//rend sVerbe tel quel,ou négativé avec "ne"..."pas" si bNegativer 
	#define kuNeLg 3//"n'" ou "ne "
	#define kuPasLg 4//" pas"
	char *sPas=malloc(kuNeLg+strlen(sVerbe)+kuPasLg+kuAntiSlashZerO);
	if (bNegativer){
		strcpy(sPas,sChoix(bVoyelle(sVerbe,0),"n'","ne "));
		strcat(sPas,sVerbe);
		strcat(sPas, " pas");
	}
	else strcpy(sPas,sVerbe);
	OctetGereR(sPas);
	return(sPas);
}//sPas

void Pause(){//suspend l'exécution et attend une frappe clavier minimale
	char cCar;
	printf(" Pause affichage... valider SVP (touche entrée) ou stopper l'exécution en tapant autre chose ");
	scanf("%c",&cCar);
	if (cCar!='\n')
		Stop(1);
	//printf("\n");
}//Pause

long zPgcd(long xA,long xB){
	//rend le Plus Grand Commun Diviseur de xA et xB strictement positifs;en O(lg(Sup(xA,xB))
	long zPgcd;
	long xGrand,xPetit,zReste;
	Assert2("zPgcd1",xA>0,xB>0);
	xGrand=ySup(xA,xB);
	xPetit=yInf(xA,xB);
	while (zPgcd=xPetit,zReste=xGrand % xPetit,zReste>0){
		//teee("zPgcd,xGrand et xB",zPgcd,xGrand,xB);
		xGrand=xPetit;
		xPetit=zReste;
	};
	//printf("Le pgcd de %ld et %ld vaut %ld.\n",xA,xB,zPgcd);
	Assert3("zPgcd2", zPgcd>0, zPgcd>0 && xA % zPgcd==0, zPgcd>0 && xB % zPgcd==0);
	return(zPgcd);
}//zPgcd

char *sPluriel(long zEffectif,char *sSingulier){
	//(3,"fruit") rend "3 fruits" et (3,"fruit$ rouge$") rend "3 fruits rouges"
	int nC,nD;
	int nChaineLg;
	char *sPluriel;
	int nPosition;
	Assert2("sPluriel",zEffectif>=0,sSingulier!=0);
	sPluriel=sC2b(sPar3(zEffectif),sSingulier);
	nChaineLg=strlen(sPluriel);
	nPosition=nChainePos('$',sPluriel);
	if (nPosition>=0){//si zEffectif>1,remplacer les '$' par des 's';sinon, retirer ts les '$'.
		if (zEffectif>1){
			while (nPosition=nChainePos('$',sPluriel),nPosition>=0)
				sPluriel[nPosition]='s';
			}
		else {for (nD=0,nC=0;nC<nChaineLg;nC++)
				if (sPluriel[nC]!='$')
					sPluriel[nD++]=sPluriel[nC];
			sPluriel[nD++]='\0';
		}
	}
	else if (zEffectif>1)
		sPluriel=sC2(sPluriel,"s");
	return(sPluriel);//rend "3 s" si (nCardinal=3 et sSingulier est la chaîne vide)
}//sPluriel

int mPoidsFort(long yEntier){
	//rend le bit de poids fort de yEntier,eg 3 si yEntier=13 puisque 13 s'écrit 1101 en base 2;rend -1 si non défini
	int yE,mPoidsFort;
	mPoidsFort=-1;
	if (yEntier>0){
		yE=yEntier;
		while (yE>0){
			yE=yE/2;
			mPoidsFort++;
		}
	}
	Assert1("mPoidsFort",bCroit(-1,mPoidsFort,63));
	return(mPoidsFort);
}//mPoidsFort

long zPpcm(long xA,long xB){
	//rend le Plus Petit Commun Multiple de xA et xB strictement positifs
	long zPpcm=0;
	//tee("xA,xB",xA,xB);
	Assert2("zPpcm1",xA>0,xB>0);
	zPpcm=(xA*xB)/zPgcd(xA,xB);
	//printf("Le ppcm de %ld et %ld vaut %ld.\n",xA,xB,zPpcm);
	Assert1("zPpcm2",zPpcm>0);
	return(zPpcm);
}//zPpcm

int nPremier(int nRangDuNombrePremier){
	//rend le nombre premier de rang1 nRangDuNombrePremier. Puisque le 1er nombre premier est 2,ie nPremier(1)=2, nPremier(2)=3, nPremier(3)=5...
	int nPremier;
	Assert2("zPremier",bOutilAmorceR,bCroit(1,nRangDuNombrePremier,kuPremierRgMax));
	nPremier=uPremieR[nRangDuNombrePremier];
	return(nPremier);
}//nPremier;

void PremierAmorceR(){
	//remplit une fois pour toutes le tableau uPremieR[] avec les kuPremierMax 1ers nombres premiers 
	int uE,uFois,uMultiple,ipPremier;
	int bVoir=kF;
	#define knPremierUltime 1000
	int nPremier[1+knPremierUltime];
	//remplir nPremier[] avec les entiers consécutifs depuis 2 et rayer les multiples de chaque entier (algorithme dit du "crible d'Eratosthène")
		for (uE=2;uE<=knPremierUltime;uE++)
			nPremier[uE]=uE;
		if (bVoir) VecteurVoir("nPremier",&nPremier[0],1,knPremierUltime);//entiers consécutifs depuis 1
		for (uFois=2;uFois<=knPremierUltime;uFois++){
			uMultiple=uFois+uFois;//si uFois=2, le 1er multiple à rayer est 4 qui est bien le 1er multiple de 2 strictement supérieur à 2
			while (uMultiple<knPremierUltime){
				nPremier[uMultiple]=0;
				uMultiple=uMultiple+uFois;
			};
		}
		if (bVoir) VecteurVoir("nPremier",&nPremier[0],1,knPremierUltime);
	//uPremieR[] soit la copie des kuPremierMax nombres non nuls qui figurent dans le tableau nPremier[] 
		for (ipPremier=0,uE=1;uE<=knPremierUltime && ipPremier<kuPremierRgMax;uE++)
			if (nPremier[uE]!=0)
				uPremieR[++ipPremier]=nPremier[uE];
		if (bVoir) te("ipPremier",ipPremier);
		if (bVoir) VecteurVoir("uPremieR",&uPremieR[0],1,kuPremierRgMax);
	Assert2("PremierAmorceR",uPremieR[1]==2,uPremieR[kuPremierRgMax]>uPremieR[1]);
}//PremierAmorceR

long zPuissance(long yOperande,int nExposant){
	long zPuissance;
	Assert2("zPuissance1",nExposant>=0,yOperande!=0 || nExposant!=0);
	zPuissance=pow(yOperande,nExposant);
	Assert1("zPuissance2",zPuissance>=0);
	return(zPuissance);
}//zPuissance;

char *sSigne(long yEntier){
	//"+" ou "-" ou " " selon que yEntier est positif ou nul, ou non.
	char *sSigne=sChoix(yEntier>=0,"+","-");
	return(sSigne);
}//sSigne

long muSigne(int bSigneInverser,long yValeur){
	long muSigne;
	muSigne=(bSigneInverser)? -yValeur: yValeur;
	return(muSigne);
}//muSigne

void Stop(int byMassacre){
	Assert1("Stop",bByte(byMassacre));
	printf("Arrêt de l'exécution, exit %d.\n",byMassacre);
	exit(byMassacre);//affiche le paramètre de exit() puis arrête l'exécution. Cache la fonction système exit().
}//Stop

double rSup(double dA,double dB){
	//rend sup(dA,dB)
	double rSup=(dA>dB)?dA:dB;
	return(rSup);
}//rSup

long ySup(long yA,long yB){
	//rend sup(yA,yB);identique à yMax(yA,yB)
	long ySup=(yA>yB)?yA:yB;
	return(ySup);
}//ySup

void Titrer(char *sTitre){
	//affiche sTitre centré sur une ligne de kuTitreLargeur caractères de type kcMotif
	const int kuTitreLargeur=80;//où ce que vous voulez
	const char kcMotif='*';//où ce que vous voulez
	#define kUnBlancDeChaqueCoteh 2
	assert(sTitre!=0);
	int nTitreLg=nCaractere(sTitre);
	assert(nTitreLg<kuTitreLargeur);
	int nMotifDeChaqueCoteh=(kuTitreLargeur-nTitreLg-kUnBlancDeChaqueCoteh)/2;//oui,division entière
	int bUnMotifEnSus=bImpair(nTitreLg);//ie un kcMotif est ajouté lorsque la longueur du titre est impaire
	assert(nMotifDeChaqueCoteh+nTitreLg+kUnBlancDeChaqueCoteh+nMotifDeChaqueCoteh+bUnMotifEnSus==kuTitreLargeur);
	printf("%s %s %s\n",sFois(nMotifDeChaqueCoteh,kcMotif),sTitre,sFois(nMotifDeChaqueCoteh+bUnMotifEnSus,kcMotif));
}//Titrer

int bVecteurContient(int nEnquis,int nCardinal,int iVecteur[]){
	//nEnquis dans iVecteur[1..nCardinal] 
	int uE;
	int bContient=kF;
	Assert1("bVecteurContient",nCardinal>0);
	for (uE=1;uE<=nCardinal;uE++)
		if (nEnquis==iVecteur[uE])
			 bContient=kV;
	return(bContient);
}//bVecteurContient

void VecteurVoir(char *sNom,int piQuelVecteur[],int nIndexMin,int nIndexMax){
	//affiche piQuelVecteur[nIndexMin..nIndexMax],dc bornes incluses
	int nE;
	Assert2("VecteurVoir1",sNom!=0,piQuelVecteur!=0);
	Assert1("VecteurVoir2",bCroit(0,nIndexMin,nIndexMax));
	printf("%s:",sNom);
		for (nE=nIndexMin;nE<=nIndexMax;nE++)
			printf("%4d",piQuelVecteur[nE]);
	printf("\n");
}//VecteurVoir

int bVoyelle(char *sTexte,int nCodeCaractereRg){
	//sTexte[nCodeCaractereRg] ou Chaine[nCodeCaractereRg..nCodeCaractereRg+1] code une voyelle
	int nRg=nCodeCaractereRg;
	Assert2("bVoyelle",sTexte!=0,nCodeCaractereRg>=0);
	int bVoyelle=bVoyellE2(sTexte,&nRg);
	return(bVoyelle);
}//bVoyelle

int bVoyellE2(char *sTexte,int *pnCodeCaractereRg){
	//sTexte[*pnCodeCaractereRg] ou Chaine[*pnCodeCaractereRg..*pnCodeCaractereRg+1] code une voyelle;si vrai et 2 codes, passe au code suivant
	//pour le seul ŸaeiouyéàèùâêîôûäïöüÿAEIOUYÂÊÎÔÛÉÀÙÂÊÎÔÛÄËÏÖÜŸã";//piqûre Haüy;nValide2[1] pour le seul Ÿ
	int nCar;
	char cCode;
    #define knVoyelle1LiM 12
    #define knVoyelle2LiM 33
    #define knVoyelle3LiM 01
	//nVoyelle1 dédié voyelles sans signes diacritiques";
	int nVoyelle1[knVoyelle1LiM]={'A','E','I','O','U','Y','a','e','i','o','u','y'};
	//nVoyelle2 dédié dans l'ordre à éàèùâêîôûäïöüÿÂÊÎÔÛÉÀÙÂÊÎÔÛÄËÏÖÜã";
	int nVoyelle2[knVoyelle2LiM]={87,96,88,71,94,86,82,76,69,92, 81,74,68,65,126,118,114,108,101,119, 128,103,126,118,114,108,101,124,117,113, 106,100,93};
	//nVoyelle3 pour le seul Ÿ
	int nVoyelle3[knVoyelle3LiM]={72};
	int bVoyellE2=0;
	assert(sTexte!=0);
	Assert1("bVoyellE2",(0,*pnCodeCaractereRg,strlen(sTexte)));
	cCode=sTexte[*pnCodeCaractereRg];
	bVoyellE2=isalpha(cCode);
	if (bVoyellE2){//voyelle ou consonne?
		for (bVoyellE2=0,nCar=0; nCar<knVoyelle1LiM; nCar++)
			bVoyellE2=bVoyellE2||(cCode==nVoyelle1[nCar]);
		}
	else if (*pnCodeCaractereRg<strlen(sTexte)) {//l'accès à sTexte[nCodeCaractereRg+1] est valide
		if (cCode==kcEchappemenT1){
			cCode=sTexte[*pnCodeCaractereRg+1];
			for (nCar=0; nCar<knVoyelle2LiM; nCar++)
				bVoyellE2=bVoyellE2||(cCode==-nVoyelle2[nCar]);
			if (bVoyellE2)
				(*pnCodeCaractereRg)++;//2 codes pour un seul caractère
		}
		else if (cCode==kcEchappemenT2) {
			cCode=sTexte[*pnCodeCaractereRg+1];
			for (nCar=0; nCar<knVoyelle3LiM; nCar++)
				bVoyellE2= bVoyellE2 || (cCode==-nVoyelle3[nCar]);
			if (bVoyellE2)
				(*pnCodeCaractereRg)++;//2 codes pour un seul caractère
		}
	}
	return(bVoyellE2);
}//bVoyellE2

int bVrai(int iEntier){
	//rend vrai ssi iEntier!=0
	int bVrai=(iEntier!=0) ? 1 : 0;
	return(bVrai);
}//bVrai

void While(long zIterationMax){
	//prend note du nombre maximum d'itérations acceptable dans le while ou le do while qui suit immédiatement l'appel de cette routine
//ATTENTION:l'utilisation de cette routine est incompatible avec des sorties de boucles intempestives telles que exit(), return, etc.
	Assert1("While",zIterationMax>=0);//le nombre maximum d'itérations est censé être positif
	ipWhilE++;
	Assert1("While",ipWhilE<=kuWhileMaX);//trop de boucles while/do while imbriquées (la constante kuWhileMaX est déclarée en haut de ce module)
	zWhilE[ipWhilE]=zIterationMax;
}//While

int bWhile(char *sContexte,int bExpressionBooleenne){
	//rend bExpressionBooleenne tout en gérant l'itération en cours (ie son rang ne dépasse pas zIterationMax spécifié dans l'appel à While() qui précède
//ATTENTION:l'utilisation de cette routine est incompatible avec des sorties de boucles intempestives telles que exit(), return,etc
	long zIterationRestante;
	Assert1("bWhile",bCroit(0,ipWhilE,kuWhileMaX));//la constante kuWhileMaX est déclarée en haut de ce module
	zWhilE[ipWhilE]--;//décrémente le nombre d'itérations de la boucle imbriquée de rang ipWhilE
	zIterationRestante=zWhilE[ipWhilE];
	if (zIterationRestante<0){
		printf("    *** Boucle \"while\" ou \"do while\" interrompue dans \"%s\". Le maximum spécifié a été dépassé.\n",sContexte);
		assert(zIterationRestante>=0);
	}
	if (bExpressionBooleenne==0){//la sortie imminente du while courant ramène le contexte ds la boucle imbriquée englobante,de rang ipWhilE-1
		zWhilE[ipWhilE]=0;//superflu mais ce nettoyage facilite la mise au point
		ipWhilE--;//vital
		if (ipWhilE<0){
			printf("    *** Manque un While() devant la boucle \"while\" ou \"do while\" de \"%s\" ou devant une boucle exécutée avant.\n",sContexte);
			assert(ipWhilE>=0);
		}
	}//Chaque boucle while est donc contrôlée via 1° un appel à While() avant le while et 2° un appel à bWhile() dans l'expression booléenne qui est...
	return(bExpressionBooleenne);//...attachée au while; Appel1("") à la fin du main() vérifie le bon ordonnancement des while,cf Appel1d et Appel1e.
}//bWhile




