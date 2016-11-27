#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>
#include <assert.h>
#include <time.h>
#define kF 0 //booléen FALSE
#define kV 1 //booléen TRUE
#define kuByteMax 255
#define kuByteLim 256
#define  kB0 1
#define  kB1 2
#define  kB2 4
#define  kB3 8
#define  kB4 16
#define  kB5 32
#define  kB6 64
#define  kB7 128
#define  kB8 256
#define  kB9 512
#define kB10 1024
#define kB11 2048
#define kB12 4096
#define kB13 8192
#define kB14 16384
#define kB15 32768
#define kB16 65536
#define kB17 131072
#define kB18 262144
#define kB19 524288
#define kB20 1048576
#define  kE0 1
#define  kE1 10
#define  kE2 100
#define  kE3 1000
#define  kE4 10000
#define  kE5 100000
#define  kE6 1000000
#define  kE7 10000000
#define  kE8 100000000
#define  kE9 1000000000
#define kE10 10000000000
#define kE11 100000000000
#define kE12 1000000000000
#define kE13 10000000000000
#define kE14 100000000000000
#define kE15 1000000000000000
#define kE16 10000000000000000
#define kE17 100000000000000000
#define kE18 1000000000000000000
#define kE19 10000000000000000000
#define kE20 100000000000000000000
#define kE21 1000000000000000000000
#define kE22 10000000000000000000000
#define kE23 100000000000000000000000
#define kE24 1000000000000000000000000
#define kE25 10000000000000000000000000
#define kE26 100000000000000000000000000
#define kE27 1000000000000000000000000000
#define kE28 10000000000000000000000000000
#define kE29 100000000000000000000000000000
#define kE30 1000000000000000000000000000000
#define kE31 10000000000000000000000000000000
#define kE32 100000000000000000000000000000000
#define kdEpsilon 0.00001l
#define kuIntegerMax INT_MAX //constante prédéfinie déclarée dans la bibliothèque <limits.h>.
#define kxLongintMax LONG_MAX //constante prédéfinie déclarée dans la bibliothèque <limits.h>.
#define kyLongintMin LONG_MIN //constante prédéfinie déclarée dans la bibliothèque <limits.h>.
#define kuMajusculeOffset 1 //A est la 1ère lettre de l'alphabet.
#define kuMinusculeOffset 27 //a est la 27ème lettre de l'alphabet à 52 lettres obtenu en complétant les majuscules par les minuscules.
#define kuPremierRgMax 100 //rang1 du dernier nombre premier stocké dans le tableau de nombres premiers uPremieR[] accessible par nPremier().
//les routines en minuscules ci-dessous cachent les printf(),ajoutent un point final et passent à la ligne;b=booléen, e=entier, r=réel, t=texte.
	void t(char *sTexte);//affiche sTexte.
	void tb(char *sTexte,int bBooleen);//affiche sTexte puis "vrai" ou "faux" selon bBooleen.
	void te(char *sTexte,long yEntier1);//affiche sTexte puis yEntier1: te("eA",eA) affiche "eA:2" si eA vaut 2.
	void tee(char *sTexte,long yEntier1,long yEntier2);
	void teee(char *sTexte,long yEntier1,long yEntier2,long yEntier3);
	void teeee(char *sTexte,long yEntier1,long yEntier2,long yEntier3,long yEntier4);
	void teeeee(char *sTexte,long yEntier1,long yEntier2,long yEntier3,long yEntier4,long yEntier5);
	void teeeeee(char *sTexte,long yEntier1,long yEntier2,long yEntier3,long yEntier4,long yEntier5,long yEntier6);
	void tr(char *sTexte,double dReel1);//affiche la valeur de sTexte puis celle du réel dReel1: tr("dA",dA) affiche dA:2.5 si dA vaut 2,5.
	void trr(char *sTexte,double dReel1,double dReel2);
	void trrr(char *sTexte,double dReel1,double dReel2,double dReel3);
	void tt(char *sTexte1,char *sTexte2);//affiche sTexte1 et sTexte2 entre virgules.
	void ttt(char *sTexte1,char *sTexte2,char *sTexte3);
	void tttt(char *sTexte1,char *sTexte2,char *sTexte3,char *sTexte4);
	void ttttt(char *sTexte1,char *sTexte2,char *sTexte3,char *sTexte4,char *sTexte5);
//les routines ci-dessous cachent les fonctions systèmes, gèrent le contexte des appels de routines, les chaîne de caractère et les boucles sans fin
long zAbs(long yEntier);//valeur absolue;déroute si le résultat est non défini,contrairement à la fonction abs() du C qui rend une valeur négative
void Appel0(char *sMessage);//doit toujours être associé à Appel1;à placer en tête de routine (affiche le nom de la routine au début de son exécution)
void Appel1(char *sQuoi);//doit toujours être associé à Appel0;à placer en fin de routine (affiche le nom de la routine à la fin de son exécution)
void Assert1(char *sContexte,int bAssertion1);//comme assert() du langage C, mais affiche sContexte si bAssertion1 est faux
void Assert2(char *sContexte,int bAssertion1,int bAssertion2);//comme assert(bAssertion1 && bAssertion2);affiche sContexte si une assertion est fausse.
void Assert3(char *sContexte,int bAssertion1,int bAssertion2,int bAssertion3);
void Assert4(char *sContexte,int bAssertion1,int bAssertion2,int bAssertion3,int bAssertion4);
void Assert5(char *sContexte,int bAssertion1,int bAssertion2,int bAssertion3,int bAssertion4,int bAssertion5);
void Assert6(char *sContexte,int bAssertion1,int bAssertion2,int bAssertion3,int bAssertion4,int bAssertion5,int bAssertion6);
int bBit(char cCaractere);//rend vrai ssi cCaractere est '0' ou '1'.
int bBool(long yEntier);//rend vrai ssi yEntier vaut 0 ou 1.
char *sBool(long yValeur);//rend "faux" si yValeur est nul, et "vrai" sinon.
int bByte(long yEntier);//0 ≤ yEntier ≤ 255.
char *sC(char cAlphaNumeriqueOuEspace);//convertit un char en string.
char *sC1(char *sA);//vérifie sA!=0 puis rend sA.
char *sC1p(char *sA);//complète sA par un point terminal.
char *sC2(char *sA,char *sB);
char *sC2b(char *sA,char *sB);//concatène en ajoutant un blanc entre sA et sB.
char *sC2bp(char *sA,char *sB);//blanc entre sA et sB et point terminal.
char *sC2p(char *sA,char *sB);//point terminal.
char *sC2v(char *sA,char *sB);//concatène en ajoutant une virgule entre sA et sB.
char *sC3(char *sA,char *sB,char *sC);
char *sC3b(char *sA,char *sB,char *sC);
char *sC3bp(char *sA,char *sB,char *sC);
char *sC3p(char *sA,char *sB,char *sC);
char *sC3v(char *sA,char *sB,char *sC);
char *sC4(char *sA,char *sB,char *sC,char *sD);
char *sC4b(char *sA,char *sB,char *sC,char *sD);
char *sC4bp(char *sA,char *sB,char *sC,char *sD);
char *sC4p(char *sA,char *sB,char *sC,char *sD);
char *sC5(char *sA,char *sB,char *sC,char *sD,char *sE);
char *sC5b(char *sA,char *sB,char *sC,char *sD,char *sE);
char *sC5bp(char *sA,char *sB,char *sC,char *sD,char *sE);
char *sC5p(char *sA,char *sB,char *sC,char *sD,char *sE);
char *sC6(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF);
char *sC6b(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF);
char *sC6bp(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF);
char *sC6p(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF);
char *sC7(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG);
char *sC7b(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG);
char *sC7bp(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG);
char *sC7p(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG);
char *sC8(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG,char *sH);
char *sC8b(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG,char *sH);
char *sC8bp(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG,char *sH);
char *sC8p(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG,char *sH);
int nCaractere(char *sTexte);//rend le nombre de caractères (1 pour "é") contrairement à strlen() qui rend le nombre de CODES caractères (2 pour "é"). 
int bChiffre(char cCaractere);//'0'..'9',comme bDecit
int nChainePos(char cQuoi,char *sDansQuoi);//rend le rang0, c'est-à-dire la position en commençant par 0, de cQuoi dans sDansQuoi;rend -1 si échec.
char *sChoix(int bOptionSinonAlternative,char *sOption,char *sAlternative);//cf (bOptionSinonAlternative)? sOption: sAlternative
char *sChoix0(int bOption,char *sOption);//si bOption,rend sOption;sinon, rend une chaîne vide
void Confirmer(char *sMessage);//affiche sMessage et demande à l'utilisateur de valider
char *sCouple(long yEntierA,long yEntierB);//eg "(3,5)" 
void Croissant(double dMinInclus,double dDedans,double dMaxInclus);//vérifie dMinInclus ≤ dDedans ≤ dMaxInclus
int bCroissant(double dMinInclus,double dDedans,double dMaxInclus);//rend vrai ssi dMinInclus ≤ dDedans ≤ dMaxInclus
int bCroissantStrict(double dMinExclu,double dDedans,double dMaxExclu);//vérifie dMinInclus < dDedans < dMaxInclus
void CroissantStrict(double dMinExclu,double dDedans,double dMaxExclu);
int bCroit(long yMinInclus,long yDedans,long yMaxInclus);//évalue et rend yMinInclus ≤ yDedans ≤ yMaxInclus
int bCroit4(long yA,long yB,long yC,long yD);//rend yA≤yB≤yC<=yD
int bCroitStrict(long yMinExclu,long yDedans,long yMaxExclu);//évalue et rend yMinInclus < yDedans < yMaxInclus
int bDecit(char cCaractere);//alias bChiffre
char *sE(int nEspace);//rend nEspace blancs consécutifs
char *sEntier(long yEntier);
char *sEntier2(long yEntier);//résultat sur 2 caractères.
char *sEntier3(long yEntier);//résultat sur 3 caractères.
char *sEntierAvecSigne(long yEntier);// "+5" ou "-5" ou " 0".
char *sEst(int bAssertion);//rend "est" ou "n'est pas".
int bFaux(int iEntier);//vrai ssi iEntier==0.
long zFib(int nIndex);//fonction de Fibonacci définie par F(n)=F(n-1)+F(n-2) avec F(1)=F(2)=1, n>0.
void FlipFlop(char* sContexte,int bApres,int *pbAvant);// "pb"="pointeur sur booléen";si bApres≠pbAvant,mémorise bApres dans pbAvant; sinon,déroute.
//FlipFlop,placé en tête d'une routine R(bMode,…),permet de vérifier que les appels successifs à R sont R(true,…),R(false,…),R(true,…),R(false,…),etc.
char *sFois(int nFois,char cMotif);//rend cMotif juxtaposé nFois.
char *sG(char* sTexte);//rend sTexte entre guillemets.
int nHasard(int uBorneLim);//rend un entier dans [0..uBorneLim[.
int uHasard(int uBorneMax);//rend un entier dans [1..uBorneMax].
int bImpair(int iEntier);
double rInf(double dA,double dB);//inf(dA,dB).
long yInf(long yA,long yB);//identique à yMin(yA,yB).
int bLettre(char cCaractere);
void Ligne();//passe à la ligne.
int bLigne();//passe à la ligne et rend vrai.
double rLog(double dN);//logarithme népérien;rend par exemple 1.0 pour rLog(2.718).
double rLog2(double dN);//logarithme en base 2;rend par exemple 4.0 pour rLog2(16).
double rMax(double dA,double dB);//sup(dA,ddB).
long yMax(long yA,long yB);//sup(yA,yB).
void MemIntRaz(int piMemOrigine[],int nItemEnTout);
void MemIntValuer(int piMemOrigine[],int nItemEnTout,int iValeur);
void MemLongRaz(int pyMemOrigine[],int nItemEnTout);
void MemLongValuer(int pyMemOrigine[],int nItemEnTout,long yValeur);
int bMajuscule(char cCaractere);
double rMin(double dA,double dB);//inf(dA,dB).
long yMin(long yA,long yB);//inf(yA,yB).
int bMinuscule(char cCaractere);
int uModulo1(int uDividende,int uDiviseur);//résultat dans [1..uDiviseur];calcule un modulo classique puis remplace le résultat éventuel 0 par uDiviseur.
char *sNie(char *sVerbe,int bNegativer,char *sAffirmation,char *sNegation);//encadre sVerbe avec "ne" et sNegation, ou le complète avec sAffirmation.
int bNul(double dNombre);//dNombre est très proche de zéro
void OutilAMORCER();
void OutilINITIALISER();
void OutilTESTER(int iTest);
char *sP(char *sEntreParenthese);//rend sEntreParenthese entre 2 parenthèses,eg sP("oui") rend "(oui)".
int bPair(int iEntier);
char *sPar3(long yEntier);//convertit yEntier en chaîne en groupant les chiffres par 3, eg sPar3(12345) rend "12 345".
char *sPas(char *sVerbe,int bNegativer);//encadre avec "ne" et "pas" si bNegativer.
void Pause();//suspend l'exécution et attend une frappe clavier minimale.
long zPgcd(long xA,long xB);//plus grand commun diviseur.
char *sPluriel(long zEffectif,char *sSingulier);//sPluriel(3,"fruit") rend "3 fruits" et sPluriel(3,"fruit$ rouge$") rend "3 fruits rouges".
long zPpcm(long xA,long xB);//plus petit commun multiple.
int mPoidsFort(long yEntier);//rend le bit de poids fort de yEntier,eg 3 si yEntier=13 puisque 13 s'écrit 1101 en base 2.
int nPremier(int nRangDuNombrePremier);//rend le nombre premier de rang1 nRangDuNombrePremier,ie nPremier(1)=2, nPremier(2)=3, nPremier(3)=5...
long zPuissance(long yOperande,int nExposant);//nExposant positif ou nul.
char *sSigne(long yEntier);//"+" ou "-" ou " " selon le signe de yEntier ("+" pour yEntier=0).
long muSigne(int bSigneInverser,long yValeur);//si bSigneInverser est vrai,rend -yValeur;sinon,rend +yValeur.
void Stop(int byMassacre);//sortie catastrophe;affiche byMassacre compris entre 0 et 255 puis stoppe l'exécution.
double rSup(double dA,double dB);//identique à rMax(dA,dB).
long ySup(long yA,long yB);//identique à yMax(yA,yB).
void Titrer(char *sTitre);//affiche sTitre centré sur 40 caractères et passe à la ligne.
int bVecteurContient(int nEnquis,int nCardinal,int iVecteur[]);
void VecteurVoir(char *sNom,int piQuelVecteur[],int nIndexMin,int nIndexMax);//affiche les valeurs du vecteurs d'entiers de type integer.
int bVoyelle(char *sTexte,int nCodeCaractereRg);//vrai ssi sTexte[nCodeCaractereRg] est une voyelle.
int bVrai(int iEntier);//rend 1 ssi iEntier est non nul;rend 0 sinon.
void While(long zIterationMax);//prend note du nombre maximum d'itérations à exécuter dans le while qui suit l'appel de cette routine.
int bWhile(char *sContexte,int bExpressionBooleenne);//rend bExpressionBooleenne après avoir vérifié que l'itération en cours ne dépasse pas zIterationMax spécifié li-1.

