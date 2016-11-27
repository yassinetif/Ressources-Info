#define knGrapheCouleurMax 6
#define knSommetLiM 24
#define knSommetMaX (knSommetLiM-1)
#define knArcLiM (knSommetLiM*knSommetLiM)
#define knArcMaX (knArcLiM-1)
typedef struct{
	int nSommetEnTout;
	int nArcEnTout;
	int aHed[knSommetLiM];//numéros d'arcs
	int sSuk[knArcLiM];//sommet destination de l'arc courant
	int aDeh[knSommetLiM];//numéros d'arcs ds le graphe inverse
	int sKus[knArcLiM];//sommet origine de l'arc courant;ATTENTION si A=(X,Y) sSuk[A]=Y n'implique pas sKus[A]=X
	int aInv[knArcLiM];//arc inverse aL associé à l'arc direct aK
	int nCapa[knArcLiM];//capacité maximale de l'arc courant
	int nCout[knArcLiM];//poids ou coût n°1 associé à l'arc courant
	int nPoids[knArcLiM];//poids ou coût n°2 associé à l'arc courant
	int aArcTo[knArcLiM];
	int nAugVal[knArcLiM];
	int coulh[knArcLiM];
	int sPer[knSommetLiM];
	int nPhi[knArcLiM];//disponible
	int nVal[knArcLiM];//disponible
} graf;
int bGraphe(graf *pgG);//O(A)
void GrapheAMORCER();
int bGrapheArc(graf gG,int sOrigine,int sDestination);//O(S)
int nGrapheArc(graf gG,int sOrigine,int sDestination);//O(S)
void GrapheArquer(graf *pgG,int sOrigine,int sDestination);//O(A)
int bGrapheCheminerCourt(graf *pgG,int sSource,int sTrappe,int bAfficher);//O(S2)
int bGrapheCheminerLong(graf *pgG,int sSource,int sTrappe,int bAfficher);//O(S2)
int bGrapheCircuite(graf *pgG);//O(A)
void GrapheColorer(graf *pgG,int sOrigine,int sDestination,int nCouleur);
int nGrapheCouleur(graf gG,int sOrigine,int sDestination);//O(S)
void GrapheCreer(int nSommet,graf **ppgG);
void GrapheCreer2(graf **ppgG,int nSommet,int nArc,int nArcOrigine[],int nArcDestination[]);
void GrapheDecrire(graf *pgG);//O(A)
void GrapheDedoubler(graf *pgG);//O(A)
void GrapheDelimiter(graf *pgG,int uArcIndex,int *psOrigine,int *psDestination);//rend les sommets qui délimitent l'arc considéré
int bGrapheDesarquer(graf *pgG,int sOrigine,int sDestination);//O(A)
void GrapheDesarquerTout(graf *pgG,int sAccroche);//retire tout arc lié à sAccroche
void GrapheEtager(graf *pgG);//O(SA)
int bGrapheEulerien(graf *pgG,int szSource,int szTrappe);//O(A);sz:sommet ou 0
void GrapheINITIALISER();
void GrapheInverser(graf *pgG);//O(A)
void GraphePolariser(graf *pgG,int *psSource,int *psTrappe);//O(A)
void GraphePonderer(graf *pgG);//O(A)
int bGrapheSimple(graf *pgG);//O(A)
void GrapheSommer(graf *pgG,int bEmpilerSinonDepiler);//O(1)
int bGrapheSommet(graf *pgG,int sSommet);
int bGrapheSymetrique(graf gG);
void GrapheSymetriser(graf *pgG);
void GrapheTESTER(int iTest);
void GrapheVoir(graf *pgG,char *sMessage);//affiche tous les arcs
void GrapheVoir0(graf *pgG,char *sMessage);//affiche les arcs (X,Y) tels que X<Y de pgG supposé symétrique
void GrapheVoir1(graf *pgG,int bDontCouleur,char *sMessage);
void GrapheVoir2(graf *pgG,char *sMessage);
void GrapheVoir3(graf *pgG,char *sMessage);
