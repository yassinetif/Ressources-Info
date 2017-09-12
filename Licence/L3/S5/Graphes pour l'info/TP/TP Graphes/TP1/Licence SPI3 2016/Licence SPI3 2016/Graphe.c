#include "Outil.h"
#include "Deque.h"
#include "Graphe.h"
#include "Tas.h"
//structure de données du graphe courant G
#define kbCourtSinonLong 1
int bGrapheAmorceR;
int bGrapheCreeR;

void CoutInverseR(graf *pgG);
int bGrapheArqueR(graf *pgG,int sOrigine,int sDestination,int nCouleur);//O(A)
void GrapheChemiN(graf gG,int sDernier,int nEtape,int nEtapeMax);
void GrapheCheminE(graf gG,int sSource,int sTrappe,int bCheminer,int bCourtSinonLong);
int bGrapheCheminE(graf gG,int sSource,int sTrappe);
void GrapheChemineR (graf *pgG,int sSource,int sTrappe);
void GrapheRetireR(graf *pgG);
int bGrapheVidE(graf *pgG);
int nGrapheCouvriR(graf *pgG,int bLogn,int bTas);

int bArC(graf gG,int sOrigine,int sDestination){
	int bArc;
	int aK;
	bArc=kF;
	if (bGrapheSommet(&gG,sOrigine) && bGrapheSommet(&gG,sOrigine)){
		for (aK=gG.aHed[sOrigine];aK<gG.aHed[sOrigine+1];aK++)
			if (gG.sSuk[aK] == sDestination)
				bArc=kV;
	}
	Assert1("bArC1",bBool(bArc));
	return(bArc);
}//bArC

void CoutInverseR(graf *pgG){
	int aK;
	for (aK=1; aK<=pgG->nArcEnTout; aK++)
		pgG->nCout[aK] = - pgG->nCout[aK];
}//CoutInverseR

int bGraphe(graf *pgG){//O(A)
	//les champs de gG décrivent effectivement un graphe quelconque ——pr les quatre champs nSommetEnTout,nArcEnTout,aHed et sSuk de gG.
	int bGraphe,aK,sX;
	Assert1("bGraphe",bGrapheAmorceR);
	bGraphe=(pgG->nSommetEnTout>=0) && (pgG->nArcEnTout>=0) && (pgG->aHed[1]==1);
	bGraphe=bGraphe && (pgG->aHed[pgG->nSommetEnTout+1]==pgG->nArcEnTout+1);
	if (bGraphe)
		for (sX=1;sX<=pgG->nSommetEnTout;sX++)
			bGraphe=bGraphe && pgG->aHed[sX]<=pgG->aHed[sX+1];
	if (bGraphe)
		for (aK=1;aK<pgG->nArcEnTout;aK++)
			bGraphe=bGraphe && bGrapheSommet(pgG,pgG->sSuk[aK]);
	return(bGraphe);//noter qu'un graphe qui vérifie bGraphe n'est pas forcément un graphe simple
}//bGraphe

void GrapheAMORCER(){
	//amorce le présent module une fois pour toutes
	bGrapheAmorceR=kV;
	Assert2("GrapheAMORCER",knSommetLiM%8==0,knArcLiM%8==0);//frontières de 8 octets
}//GrapheAMORCER

int bGrapheArc(graf gG,int sOrigine,int sDestination){//O(S)
	//(sOrigine,sDestination) est un arc de gG
	int bArc;
	int aK;
	Assert3("bGrapheArc",bGraphe(&gG),bGrapheSommet(&gG,sOrigine),bGrapheSommet(&gG,sDestination));
		for (bArc=kF,aK=gG.aHed[sOrigine];aK<gG.aHed[sOrigine+1];aK++)
			if (gG.sSuk[aK]==sDestination)
				bArc=kV;//l'arc est effectivement présent dans gG
	return(bArc);
}//bGrapheArc

int nGrapheArc(graf gG,int sOrigine,int sDestination){//O(S)
	//si (sOrigine,sDestination) est un arc de gG,rend le numéro de cet arc (ce numéro est utilisé pour indexer sSuk[1..]);sinon,rend 0.
	int nArc;
	int aK;
	Assert3("nGrapheArc",bGraphe(&gG),bGrapheSommet(&gG,sOrigine),bGrapheSommet(&gG,sDestination));
		for (nArc=0,aK=gG.aHed[sOrigine];aK<gG.aHed[sOrigine+1];aK++)
			if (gG.sSuk[aK]==sDestination)
				nArc=aK;//l'arc est effectivement présent dans gG
	return(nArc);
}//nGrapheArc

void GrapheArquer(graf *pgG,int sOrigine,int sDestination){//O(A)
	//ajoute effectivement l'arc (sOrigine,sDestination) à pgG en modifiant les seuls champs nArcEnTout, aHed et sSuk.
	int bArquer=bGrapheArqueR(pgG,sOrigine,sDestination,0);
	Assert1("GrapheArquer",bArquer);
}//GrapheArquer

int bGrapheArqueR(graf *pgG,int sOrigine,int sDestination,int nCouleur){//O(A)
	//ajoute l'arc (sOrigine,sDestination) à pgG en modifiant les seuls champs nArcEnTout, aHed, sSuk et coulh.
	int bArquer,aK,sX;
	Assert3("bGrapheArqueR0",bGrapheAmorceR,bGraphe(pgG),bGrapheSimple(pgG));
	bArquer=bGrapheSommet(pgG,sOrigine) && bGrapheSommet(pgG,sDestination) && (!bGrapheArc(*pgG,sOrigine,sDestination));
	//Assert1("bGrapheArqueR5",bGrapheSommet(pgG,sOrigine));
	//Assert1("bGrapheArqueR6",bGrapheSommet(pgG,sDestination));
	//Assert1("bGrapheArqueR7",!bGrapheArc(*pgG,sOrigine,sDestination));
	//bArquer=bArquer && bArC(pgG,sOrigine,sDestination);ie arc effectivt présent
	if (bArquer){
		for (aK=pgG->nArcEnTout;aK>=pgG->aHed[sOrigine+1];aK--){
			pgG->sSuk[aK+1]=pgG->sSuk[aK];
			pgG->coulh[aK+1]=pgG->coulh[aK];
		}
		aK=pgG->aHed[sOrigine+1];
		pgG->sSuk[aK]=sDestination;
		pgG->coulh[aK]=nCouleur;
		for (sX=sOrigine;sX<=pgG->nSommetEnTout;sX++)
			pgG->aHed[sX+1]++;
		pgG->nArcEnTout++;
	}
	Assert2("bGrapheArqueR1",bGraphe(pgG),bGrapheSimple(pgG));
	return(bArquer);
}//bGrapheArqueR

void GrapheChemiN(graf gG,int sDernier,int nEtape,int nEtapeMax){
	//affiche le chemin qui va de la source au sommet sDernier;routine annexe de bGrapheCheminE
	if (gG.sPer[sDernier]!=sDernier)
		GrapheChemiN(gG,gG.sPer[sDernier],nEtape-1,nEtapeMax);
	printf("%d",sDernier);
	if (nEtape!=nEtapeMax)
		printf(",");
}//GrapheChemiN

void GrapheCheminE(graf gG,int sSource,int sTrappe,int bCheminer,int bCourtSinonLong){
	Assert1("GrapheCheminE",bBool(bCheminer));
	if (bCheminer){
		printf("    Chemin le plus %s du sommet %d au sommet %d: (",(bCourtSinonLong)?"court":"long",sSource,sTrappe);
			GrapheChemiN(gG,sTrappe,gG.nSommetEnTout,gG.nSommetEnTout);
		printf(")\n");
	}
	else printf("    Il n'existe pas de chemin entre les sommets %d et %d.\n",sSource,sTrappe);
}//GrapheCheminE

int bGrapheCheminE(graf gG,int sSource,int sTrappe){
	//détermine l'existence d'un chemin qui va de sSource au sommet sTrappe
	int bChemine;
	int nSommet;
	int sX,sY;
	//bChemine,nSommet soit 1° un booléen vrai ssi sTrappe a bien été atteint depuis sSource et 2° le nbre de sommets de sSource inclus à sTrappe inclus
		nSommet=1;
		bChemine=kF;
		sX=sTrappe;
		While(gG.nSommetEnTout);
		while (bWhile("bGrapheCheminE",(bChemine=bChemine || (sX==sSource),sX!=(sY=gG.sPer[sX]))) ) {
			nSommet++;
			sX=sY;
		}
	return(bChemine);
}//bGrapheCheminE

void GrapheChemineR (graf *pgG,int sSource,int sTrappe){//O(S2)
	//Algo plus court chemin, Dijkstra sans tas;coûts par arcs supposés d'office unitaires
	const int kuInfini=1e5;
	int nChallenger;
	int nD;//distance courante de sSource au sommet le plus proche de sSource
	int nDist[1+pgG->nSommetEnTout];
	int bFait[1+pgG->nSommetEnTout];
	int aK;
	int sProche;
	int uSommet;
	int sX;
	int sY;
	for (sX=1; sX<=pgG->nSommetEnTout; sX++)
		bFait[sX]=0;
	for (sX=1; sX<=pgG->nSommetEnTout; sX++)
		nDist[sX]=kuInfini;
	for (sX=1; sX<=pgG->nSommetEnTout; sX++)
		pgG->sPer[sX]=0;
	nDist[sSource]=0;//distance entre le sommet de départ et lui-même
	pgG->sPer[sSource]=sSource;//vital pour bGrapheCheminE()
	for (uSommet=1; uSommet<=pgG->nSommetEnTout; uSommet++) {
		//sProche:=numéro du sommet le plus proche de sSource, ou 0 si sa valeur est non définie (graphe non connexe ou bFait[] vrai partout)
			for (sProche=0,nD=kuInfini,sX=1; sX<=pgG->nSommetEnTout; sX++)
				if (!bFait[sX] && nD>nDist[sX])
					nD=nDist[sProche=sX];
		if (sProche!=0) {
			//printf("plus proche:%d\n",sProche);
			for (aK=pgG->aHed[sProche]; aK<pgG->aHed[sProche+1]; aK++) {
				if ( nDist[sY=pgG->sSuk[aK]]>(nChallenger=nDist[sProche]+pgG->nCout[aK]) ) {
					nDist[sY]=nChallenger;
					pgG->sPer[sY]=sProche;
				}
			}
			bFait[sProche]=kV;
		}
	}//chaque sProche coûte O(S) et chaque arc est consulté 1 fois,soit une complexité au pire égale à sup( O(S*S),O(A) ), dc O(S2)
	//VecteurVoir("sPer",&pgG->sPer[1],1,pgG->nSommetEnTout);
}//GrapheChemineR

int bGrapheCheminerCourt(graf *pgG,int sSource,int sTrappe,int bAfficher){//O(S2)
	//Algo plus court chemin, Dijkstra sans tas;coûts par arcs supposés d'office unitaires
	int bCheminerCourt=0;
	Assert1("bGrapheCheminerCourt",bBool(bAfficher));
	GrapheChemineR(pgG,sSource,sTrappe);
	bCheminerCourt=bGrapheCheminE(*pgG,sSource,sTrappe);
	if (bAfficher)
		GrapheCheminE(*pgG,sSource,sTrappe,bCheminerCourt,kbCourtSinonLong);
	return(bCheminerCourt);
}//bGrapheCheminerCourt

int bGrapheCheminerLong(graf *pgG,int sSource,int sTrappe,int bAfficher){//O(S2)
	//Algo plus court chemin, Dijkstra sans tas;coûts par arcs supposés d'office unitaires
	int bCheminerLong=kV;
	bCheminerLong=( GrapheInverser(pgG), !bGrapheCircuite(pgG) );
	if (bCheminerLong){
		CoutInverseR(pgG);//négative les coûts des arcs
			GrapheChemineR(pgG,sSource,sTrappe);
		CoutInverseR(pgG);//restaure les coûts des arcs
		bCheminerLong=bGrapheCheminE(*pgG,sSource,sTrappe);
		if (bAfficher)
			GrapheCheminE(*pgG,sSource,sTrappe,bCheminerLong,!kbCourtSinonLong);
	}
	else if (bAfficher)
		printf("Le chemin le plus long n'est pas calculable car le graphe contient un circuit.\n");
	return(bCheminerLong);
}//bGrapheCheminerLong

int bGrapheCircuite(graf *pgG){
	//vrai ssi gG contient un circuit
	int bCircuite=kF;
	int nCard;//n comme Naturel,dc 0 ou plus
	int uE;//E comme Elément;u comme Un ou plus
	int aK;//a comme Arc
	int nMarq[1+pgG->nSommetEnTout];
	int nMarque;
	int nPred[1+pgG->nSommetEnTout];
	int nSucc[1+pgG->nSommetEnTout];
	int sX;//s comme Sommet
	int sY;
	//Appel0("bGrapheCircuite");
		Assert2("bGrapheCircuite1",bGrapheAmorceR,bCroit(1,pgG->nSommetEnTout,knSommetLiM));
		if (pgG->nSommetEnTout>1){//algo de MARIMONT
			//nSucc[sX],nPred[sX] et nMarq[sX] soit le nombre total de successeurs,de prédécesseurs ainsi que la marque du sommet courant sX
				for (sX=1;sX<=pgG->nSommetEnTout;sX++){//O(S)
					nSucc[sX]=pgG->aHed[sX+1]-pgG->aHed[sX];
					nPred[sX]=pgG->aDeh[sX+1]-pgG->aDeh[sX];
					nMarq[sX]=0;//ie sX n'est pas marqué
					Assert2("bGrapheCircuite2",nSucc[sX]>=0,nPred[sX]>=0);
				}
			DequeAllouer(pgG->nSommetEnTout);//raze;O(nSommetEnTout)
				//enfiler les sommets sources (ie sans prédécesseurs) et trappes (ie sans successeurs) en les marquant avec nMarque égal à 1
					for (nMarque=1,sX=1;sX<=pgG->nSommetEnTout;sX++)
						if ( !nPred[sX] || !nSucc[sX] )
							DequeEnfiler( (nMarq[sX]=nMarque, sX) );//O(1)
				While(pgG->nSommetEnTout);
				while (bWhile("bGrapheCircuite1",(nMarque++,nCard=nDequeCardinal())) ){//nDequeCardinal() est en O(1) et le while en O(A) ——justification en fin de while
					for (uE=1;uE<=nCard;uE++){//NB les appels à la deque ds ce for vont modifier nDequeCardinal() mais pas nCard évalué li-1 
						sX=sDequeDefiler();//O(1)/
						if (!nPred[sX])//si vrai,sX est une source;éliminer un arc (sX,sY),c'est retirer un prédécesseur de sY via "nPred[sY]--"
							for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){//O(degré sortant de sX)
								if (!nMarq[sY=pgG->sSuk[aK]]){
									nPred[sY]--;
									Assert1("bGrapheCircuite3",nPred[sY]>=0);
									if (!nPred[sY]) //enfiler sY après l'avoir marqué;parce qu'il est marqué,il ne pourra être enfilé à nouveau
										DequeEnfiler( (nMarq[sY]=nMarque,sY) );//O(1)
								}
							}
						else for (aK=pgG->aDeh[sX];aK<pgG->aDeh[sX+1];aK++)//O(degré entrant de sX)
								if (!nMarq[sY=pgG->sKus[aK]]){
									nSucc[sY]--;
									Assert1("bGrapheCircuite4",nSucc[sY]>=0);
									if (!nSucc[sY]) //enfiler sY après l'avoir marqué;parce qu'il est marqué,il ne pourra être enfilé à nouveau
										DequeEnfiler( (nMarq[sY]=nMarque,sY) );//O(1)
								}
					}//grâce à nMarq[],tt sommet est enfilé 1 fois Au plus,dc défilé 1 fois Au plus,dc ses arcs examinés 1 fois Au plus,dc while en O(A)
				}
			DequeAllouer(0);//O(1) Si vous ôtez cette ligne au vu du code de Deque,vous acceptez qu'une modification dudit code plante votre logiciel.
			for (bCircuite=0,sX=1;sX<=pgG->nSommetEnTout;sX++)//O(S);zéroter bCircuite ici initialise à l'évidence le bCircuite situé li+1 avant "||".
				bCircuite=bCircuite||!nMarq[sX];//quitter le for dès bCircuite vrai complique le code et n'améliore pas la borne O(A):mauvaise idée.
		}
	else bCircuite=kF;//redite,mais ainsi,li+1,bCircuite est l'évidence valué; chercher sa valeur initiale en déclarations est inutile,dc gain de temps.
	//Appel1("bGrapheCircuite");
	return(bCircuite);
}//bGrapheCircuite

void GrapheColorer(graf *pgG,int sOrigine,int sDestination,int nCouleur){
	//colore l'arc (sOrigine,sDestination) avec la nCouleur
	int aK;
	Assert4("GrapheColorer0",bGrapheSommet(pgG,sOrigine), bGrapheSommet(pgG,sDestination), sOrigine!=sDestination, bCroit(0,nCouleur,knGrapheCouleurMax));
		for (aK=pgG->aHed[sOrigine];aK<pgG->aHed[sOrigine+1];aK++){
			if (pgG->sSuk[aK] == sDestination)
				pgG->coulh[aK]=nCouleur;
		}
}//GrapheColorer

int nGrapheCouleur(graf gG,int sOrigine,int sDestination){//O(S)
	//rend la couleur réputée non nulle de l'arc(sOrigine,sDestination), ou 0 si arc inexistant
	int aK;
	int nCouleur;
	for (nCouleur=0,aK=gG.aHed[sOrigine];aK<gG.aHed[sOrigine+1];aK++)
		if (gG.sSuk[aK]==sDestination)
			nCouleur=gG.coulh[aK];
	return(nCouleur);
}//nGrapheCouleur

void GrapheCreer(int iSommet,graf **ppgG){
	//si iSommet!=0, alloue un espace pour pgG puis,si iSommet>0,ajoute des arcs via GrapheDecrire(); si iSommet est nul,libère l'espace
	int sX;
	FlipFlop("GrapheCreer",iSommet!=0,&bGrapheCreeR);//ie tout graphe alloué est ensuite désalloué via GrapheCreer(0,…) avant une nouvelle allocation. 
	if (iSommet!=0){
		*ppgG=(graf *) malloc(sizeof(graf));
		(*ppgG)->nSommetEnTout=abs(iSommet);
		(*ppgG)->nArcEnTout=0;
		if (iSommet>0){
			Assert1("GrapheCreer01",iSommet<knSommetLiM);
			GrapheDecrire(*ppgG);
		}else for (sX=1;sX<=(*ppgG)->nSommetEnTout+1;sX++)
				(*ppgG)->aHed[sX]=1;//des sommets et aucun arc
		Assert1("GrapheCreer02",bGrapheSimple(*ppgG));
	}
	else free(*ppgG);
}//GrapheCreer

void GrapheCreer2(graf **ppgG,int nSommet,int nArc,int nArcOrigine[],int nArcDestination[]){
	//crée un graphe simple à nSommet sommets et nArc arcs listés dans nArcOrigine[] et nArcDestination[]
	int sDestination;
	int aK;
	int sOrigine;
	Assert4("GrapheCreer20",nSommet>=0, nArc>=0, nArcOrigine!=0, nArcDestination!=0);
	GrapheCreer(-nSommet,ppgG);
		for (aK=1;aK<=nArc;aK++){
			sOrigine=nArcOrigine[aK];
			sDestination=nArcDestination[aK];
			//tee("création de l'arc",sOrigine,sDestination);
			GrapheArquer(*ppgG,sOrigine,sDestination);//actualise notamment pgG->nArcEnTout
		}
	Assert1("GrapheCreer22",bGrapheSimple(*ppgG));
}//GrapheCreer2

void GrapheDecrire(graf *pgG){
	//rend un graphe simple à pgG->nSommetEnTout sommets
	int uArc,aK,sX,sY,nPas;
	int sSucc[1+pgG->nSommetEnTout];
	//Appel0("GrapheDecrire");
		Assert2("GrapheDecrire",bGrapheAmorceR,bCroit(1,pgG->nSommetEnTout,knSommetLiM-1));
		pgG->aHed[0]=0;//zèle
		for (sX=1;sX<=pgG->nSommetEnTout;sX++)
			pgG->aHed[sX]=0;
		for (aK=1;sX<=pgG->nSommetEnTout;aK++)
			pgG->sSuk[aK]=0;
		pgG->nArcEnTout=0;
		pgG->aHed[1]=1;
		nPas=0;
		for (sX=1;sX<=pgG->nSommetEnTout;sX++){
			for (sY=1;sY<=pgG->nSommetEnTout;sY++)
				sSucc[sY]=0;
			pgG->aHed[sX+1]=pgG->aHed[sX];
			sY=sX;
			nPas++;
			for (uArc=1;uArc<=nPas;uArc++)
				if ( sY=uModulo1(sY+nPas,pgG->nSommetEnTout), (sY!=sX) && bGrapheSommet(pgG,sY) && (sSucc[sY]==0) ){
					pgG->nArcEnTout++;
					pgG->sSuk[aK=pgG->nArcEnTout]=sY;
					pgG->nCapa[aK]=1;
					pgG->nCout[aK]=1;
					sSucc[sY]++;
					pgG->aHed[sX+1]++;
				}
		}
		//GrapheInverser(pgG);//affecte en O(A) les tableaux aDeh[] et sKus[] qui décrivent le graphe inverse du graphe défini par aHed[] et aSuK[]
		Assert1("GrapheDecrire",bGrapheSimple(pgG));
	//Appel1("GrapheDecrire");
}//GrapheDecrire

void GrapheDedoubler(graf *pgG){//O(A)
	//remplace chaque sommet par un couple de sommets (sommet entrant, sommet sortant). Le graphe final est donc biparti.
	int aK;
	int nSommet;
	int sX;
	//remplacer chaque sommet cible sY par un nouveau sommet de rang sY+pgG->nSommetEnTout,lequel aura un seul successeur:sY
		nSommet=pgG->nSommetEnTout;
		for (aK=1; aK<=pgG->nArcEnTout; aK++)
			pgG->sSuk[aK]+=nSommet;
		for (sX=1; sX<=nSommet; sX++)
			pgG->sSuk[pgG->nArcEnTout+sX]=sX;
		for (sX=1; sX<=nSommet; sX++)
			pgG->aHed[nSommet+sX+1]=pgG->aHed[nSommet+sX]+1;
		pgG->nArcEnTout+=nSommet;
		pgG->nSommetEnTout+=nSommet;
	Assert1("GrapheDedoubler",bGrapheSimple(pgG));
}//GrapheDedoubler

void GrapheDelimiter(graf *pgG,int uArcIndex,int *psOrigine,int *psDestination){
	//rend les sommets qui délimitent l'arc considéré
	int sX,aK;
	Assert3("GrapheDelimiteR1",bGrapheAmorceR,bGraphe(pgG),bGrapheSimple(pgG));
	Assert1("GrapheDelimiteR2",bCroit(1,uArcIndex,pgG->nArcEnTout));
		*psDestination=0;
		for (sX=1;sX<=pgG->nSommetEnTout;sX++){
			for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)
				if (aK==uArcIndex){
					*psOrigine=sX;
					*psDestination=pgG->sSuk[aK];
				}
		}
	Assert1("GrapheDelimiteR3",*psDestination>0);
}//GrapheDelimiter

int bGrapheDesarquer(graf *pgG,int sOrigine,int sDestination){//O(A)
	//supprime si possible l'arc (sOrigine,sDestination) de pgG;rend vrai ssi l'arc était présent et a été supprimé
	int aK,aL,sX;
	Assert3("bGrapheDesarquer0",bGrapheAmorceR,bGraphe(pgG),bGrapheSimple(pgG));
	int bDesarquer=bGrapheSommet(pgG,sOrigine) && bGrapheSommet(pgG,sDestination);
	if (bDesarquer){
		//aL soit la place de l'arc dans sSuk[]
			aL=0;
			for (aK=pgG->aHed[sOrigine];aK<pgG->aHed[sOrigine+1];aK++)
				if (pgG->sSuk[aK]==sDestination)
					aL=aK;//unique vu Assert3(bGrapheDesarquer0,…,bGrapheSimple(pgG));
		bDesarquer=(aL>0);
	}
	if (bDesarquer){
		for (aK=aL;aK<pgG->nArcEnTout;aK++)
			pgG->sSuk[aK]=pgG->sSuk[aK+1];
		pgG->sSuk[pgG->nArcEnTout]=0;
		for (sX=sOrigine;sX<=pgG->nSommetEnTout;sX++)
			pgG->aHed[sX+1]--;
		pgG->nArcEnTout--;
	}
	Assert3("bGrapheDesarquer1",bGraphe(pgG),bGrapheSimple(pgG),bBool(bDesarquer));
	return(bDesarquer);
}//bGrapheDesarquer

void GrapheDesarquerTout(graf *pgG,int sAccroche){
	//retire de pgG tous les arcs liés à sAccroche
	int aK,bLien,nLien0,nLien1;
	int sX,sY;
	Assert3("GrapheDesarquerTout1",bGrapheAmorceR,bGraphe(pgG),bGrapheSimple(pgG));
	//retirer ts les arcs qui ont pour origine sAccroche
		nLien0=0;
		While(pgG->nSommetEnTout);
		do {
			bLien=kF;
			for (aK=pgG->aHed[sAccroche];aK<pgG->aHed[sAccroche+1]; aK++){
				sY=pgG->sSuk[aK];
				bLien=bGrapheDesarquer(pgG,sAccroche,sY) || bLien;
			}
			nLien0++;
		} while (bWhile("GrapheDesarquerTout11",bLien));
	Assert3("GrapheDesarquerTout2",bGrapheAmorceR,bGraphe(pgG),bGrapheSimple(pgG));
	//retirer ts les arcs qui ont pour destination sAccroche
		nLien1=0;
		While(pgG->nSommetEnTout);
		do {
			bLien=kF;
			for (sX=1; sX<=pgG->nSommetEnTout; sX++)
				for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1]; aK++){
					sY=pgG->sSuk[aK];
					if (sY==sAccroche){
						bLien=bGrapheDesarquer(pgG,sX,sAccroche) || bLien;
					}
			}
			nLien1++;
		} while (bWhile("GrapheDesarquerTout22",bLien));
	Assert3("GrapheDesarquerTout3",bGrapheAmorceR,bGraphe(pgG),bGrapheSimple(pgG));
}//GrapheDesarquerTout

void GrapheEtager(graf *pgG){
	//déroule pgG de façon à obtenir un dag
	int uEtage,aK,aKlim,sX;
	Appel0("GrapheEtager");
		Assert3("GrapheEtager1",bGrapheAmorceR,pgG->nSommetEnTout>0,pgG->nSommetEnTout<10);
		//chague arc a pour destination un sommet situé non pas à l'étage courant mais à l'étage suivant
			for (uEtage=pgG->nSommetEnTout-1;uEtage>0;uEtage--)
				for (aK=pgG->nArcEnTout;aK>=1;aK--)
					pgG->sSuk[aK+(uEtage-1)*pgG->nArcEnTout]=pgG->sSuk[aK]+uEtage*pgG->nSommetEnTout;
		//chague sommet est lié à l'étage suivant sauf les sommets du dernier étage qui n'ont aucun successeur
			for (uEtage=2;uEtage<=pgG->nSommetEnTout-1;uEtage++)
				for (sX=1;sX<=pgG->nSommetEnTout;sX++)
					pgG->aHed[sX+(uEtage-1)*pgG->nSommetEnTout]=pgG->aHed[sX+(uEtage-2)*pgG->nSommetEnTout]+pgG->nArcEnTout;
			aKlim=pgG->nArcEnTout*(pgG->nSommetEnTout-1)+1;
			for (sX=pgG->nSommetEnTout;sX>=1;sX--)
				pgG->aHed[sX+(pgG->nSommetEnTout-1)*pgG->nSommetEnTout]=aKlim;
			pgG->aHed[pgG->nSommetEnTout+(pgG->nSommetEnTout-1)*pgG->nSommetEnTout+1]=aKlim;
			pgG->nArcEnTout=aKlim-1;
			pgG->nSommetEnTout=pgG->nSommetEnTout*pgG->nSommetEnTout;
		Assert1("GrapheEtager1",bGrapheSimple(pgG));
	Appel1("GrapheEtager");
}//GrapheEtager

int bGrapheEulerien(graf *pgG,int szSource,int szTrappe){
	//tout sommet est de degré pair, hormis szSource et szTrappe qui, s'ils sont non nuls, peuvent être de degré pair ou pas, peu importe.
	int nDegreh[1+pgG->nSommetEnTout];
	int bEulerien;
	int bImporte;
	int aK;
	int bStrict;
	int sX;
	Assert4("bGrapheEulerien",bGrapheAmorceR,pgG->nSommetEnTout>0,pgG->aDeh[1]>0,(szSource==0)==(szTrappe==0));//ie "il y a 1 source" <=> à "il y a 1 trappe"
	if (szSource!=0)
		Assert2("bGrapheEulerien",bGrapheSommet(pgG,szSource),bGrapheSommet(pgG,szTrappe));
	bEulerien=kV;
	for (sX=1;sX<=pgG->nSommetEnTout;sX++)
		nDegreh[sX]=0;
	for (sX=1;sX<=pgG->nSommetEnTout;sX++){
		for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)
			nDegreh[pgG->sSuk[aK]]++;//degré sortant
		for (aK=pgG->aDeh[sX];aK<pgG->aDeh[sX+1];aK++)
			nDegreh[pgG->sKus[aK]]++;//degré entrant
	}
	bStrict=(szSource!=0);
	for (sX=1;sX<=pgG->nSommetEnTout;sX++){
		bImporte=(!bStrict || (sX!=szSource) && (sX!=szTrappe));
		if ( bImporte && bImpair(nDegreh[sX]) )
			bEulerien=kF;
	}
	return(bEulerien);
}//bGrapheEulerien

void GrapheINITIALISER(){//O(?)
	//relance le présent module
	Assert1("GrapheINITIALISER",bGrapheAmorceR);
}//GrapheINITIALISER

void GrapheInverser(graf *pgG){//O(A)
	//affecte aDeh[] et sKus[]
	int aK;
	int nPred[1+pgG->nSommetEnTout];
	int sX;
	int sY;
	Assert1("GrapheInverser",bGrapheAmorceR);
	//nPred[sY]:=degré entrant du sommet sY
		for (sY=1;sY<=pgG->nSommetEnTout;sY++)
			nPred[sY]=0;
		for (aK=1;aK<=pgG->nArcEnTout;aK++){
			sY=pgG->sSuk[aK];
			nPred[sY]++;
		}
		//VoirVecteur("nPred",&nPred[1],1,nSommetEnTout);
	//aDeh[sX]:=1+nombre total d'arcs qui auront pour extrémité les sommets 1 à sX (inclus)
		pgG->aDeh[0]=1;//technique
		for (sX=1;sX<=pgG->nSommetEnTout;sX++)
			pgG->aDeh[sX]=pgG->aDeh[sX-1]+nPred[sX];
		pgG->aDeh[pgG->nSommetEnTout+1]=pgG->nArcEnTout+1;
		//VoirVecteur("aDeH0",&pgG->aDeh[1],1,pgG->nSommetEnTout+1);
	//sKus[] et aInv[] soient affectés
		for (sX=1;sX<=pgG->nSommetEnTout;sX++)
			for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
				sY=pgG->sSuk[aK];
				Assert1("GrapheInverser1",sY>0);
				pgG->aDeh[sY]--;
				Assert1("GrapheInverser2",pgG->aDeh[sY]>0);
				pgG->sKus[pgG->aDeh[sY]]=sX;
				pgG->aInv[pgG->aDeh[sY]]=aK;
			}
		//VoirVecteur("aDeH1",&pgG->aDeh[1],1,pgG->nSommetEnTout+1);
	}//GrapheInverser

void GraphePonderer(graf *pgG){//O(A)
	//intialiser pgG avec des valeurs unitaires pour les 3 champs nCapa,nCout et nPoids
	int aK;
	for (aK=1;aK<=pgG->nArcEnTout;aK++){
		pgG->nCapa[aK]=1;
		pgG->nCout[aK]=1;
		pgG->nPoids[aK]=1;
	}
}//GraphePonderer

void GraphePolariser(graf *pgG,int *psSource,int *psTrappe){//O(A)
	//ajoute à pgG une source unique et une trappe unique,transformant ainsi pgG en dipôle
	int bArquer;
	int nPred[knSommetLiM];
	int nSommet;
	int aK;
	int sX;
	Assert1("GraphePolariser0",bGrapheSimple(pgG));
	nSommet=pgG->nSommetEnTout;
	*psSource=nSommet+1;
	*psTrappe=nSommet+2;
	pgG->nSommetEnTout+=2;//avant l'appel de bGrapheArqueR pr valider les assertions au début du code de bGrapheArqueR()
	pgG->aHed[nSommet+2]=pgG->aHed[nSommet+1];
	pgG->aHed[nSommet+3]=pgG->aHed[nSommet+2];
	Assert1("GraphePolariser1",bGrapheSimple(pgG));
	bArquer=kV;
	//sSource soit reliée à tous les sommets sans prédécesseur
		for (sX=1;sX<=nSommet;sX++)
			nPred[sX]=0;
		for (sX=1;sX<=nSommet;sX++)
			for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)
				nPred[pgG->sSuk[aK]]++;
		for (sX=1;sX<=nSommet;sX++)
			if (nPred[sX]==0)
				bArquer=bArquer && bGrapheArqueR(pgG,*psSource,sX,0);//confronte sSource à pgG->nSommetEnTout
	//sTrappe soit ciblée par tous les sommets sans successeur
		for (sX=1;sX<=nSommet;sX++)
			if (pgG->aHed[sX]==pgG->aHed[sX+1])
				bArquer=bArquer && bGrapheArqueR(pgG,sX,*psTrappe,0);//confronte sSource à pgG->nSommetEnTout
	Assert2("GraphePolariser2",bArquer,bGrapheSimple(pgG));
}//GraphePolariser

void GrapheRetireR(graf *pgG){
	//retire les sommets sX qui vérifient aHed[sX]<0 et retire également tous les arcs incidents aux sommets retirés
	int aK;
	int sX;
	int sY;
	Assert2("GrapheRetireR",bGrapheAmorceR,bGrapheSimple(pgG));
	//retirer les arcs successeurs
		for (sX=1;sX<=pgG->nSommetEnTout;sX++)
			if (pgG->aHed[sX]<0){
				for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)
					pgG->sSuk[aK]=-abs(pgG->sSuk[aK]);
			}
	//retirer les arcs prédécesseurs
		for (sX=1;sX<=pgG->nSommetEnTout;sX++)
			for (aK=abs(pgG->aHed[sX]);aK<abs(pgG->aHed[sX+1]);aK++){
				sY=pgG->sSuk[aK];
				if (pgG->aHed[sY]<0)
					pgG->sSuk[aK]=-abs(pgG->sSuk[aK]);
			}
	Assert1("GrapheRetireR",bGrapheSimple(pgG));
}//GrapheRetireR

int bGrapheSimple(graf *pgG){
	//ni boucle,ni plus d'un arc d'un sommet origine à un sommet destination
	int aK;
	int sX;
	int sY;
	int bSimple;
	int nSucc[1+pgG->nSommetEnTout];
	Assert2("bGrapheSimple",bGrapheAmorceR,bGraphe(pgG));
	bSimple=kV;
	for (sX=1;sX<=pgG->nSommetEnTout;sX++){
		for (sY=1;sY<=pgG->nSommetEnTout;sY++)
			nSucc[sY]=0;
		for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)
			if ( sY=pgG->sSuk[aK] , !bGrapheSommet(pgG,sY) || (sX==sY) || (++nSucc[sY]>1) )
				bSimple=kF;
	}
	return(bSimple);
}//bGrapheSimple

void GrapheSommer(graf *pgG,int bEmpilerSinonDepiler){//O(1)
	//si bEmpilerSinonDepiler,empile un sommet;sinon,élimine tous les arcs liés au dernier sommet (n° pgG->nSommetEnTout) puis dépile ce sommet
	Assert3("GrapheSommer1",bGrapheAmorceR,bGrapheSimple(pgG),bBool(bEmpilerSinonDepiler));
	if (bEmpilerSinonDepiler) {
		Assert1("GrapheSommer2",pgG->nSommetEnTout+1<knSommetLiM);
		(pgG->nSommetEnTout)++;
		pgG->aHed[pgG->nSommetEnTout+1]=pgG->aHed[pgG->nSommetEnTout];
	}
	else {
		Assert1("GrapheSommer3",pgG->nSommetEnTout>0);
		GrapheDesarquerTout(pgG, pgG->nSommetEnTout);
		pgG->aHed[pgG->nSommetEnTout+1]=0;
		(pgG->nSommetEnTout)--;
	}
	Assert2("GrapheSommer5",bGraphe(pgG),bGrapheSimple(pgG));
}//GrapheSommer

int bGrapheSymetrique(graf gG){
	//à tout arc (X,Y) présent dans gG correspond un arc inverse (Y,X) présent dans gG
	int bArc;
	int aK;
	int sX;
	int sY;
	int bSymetrique;
	Assert2("bGrapheSymetrique",bGrapheAmorceR,bGraphe(&gG));
	bSymetrique=kV;
	for (sX=1;sX<=gG.nSommetEnTout;sX++)
		for (aK=gG.aHed[sX];aK<gG.aHed[sX+1];aK++){
			sY=gG.sSuk[aK];
			bArc=bGrapheArc(gG,sY,sX);
			bSymetrique=bSymetrique && bArc;
		}
	return(bSymetrique);
}//bGrapheSymetrique

void GrapheSymetriser(graf *pgG){
	//transforme pgG en graphe simple symétrique en ajoutant les arcs inverses et en actualisant le champ aInv;indolore si arc inverse déjà présent.
	int bArquer;
	int nCouleur;
	int aK;
	int sX;
	int sY;
	Assert2("GrapheSymetriser",bGrapheAmorceR,bGraphe(pgG));
	for (sX=1;sX<=pgG->nSommetEnTout;sX++)
		for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
			sY=pgG->sSuk[aK];
			nCouleur=pgG->coulh[aK];
			bArquer=bGrapheArqueR(pgG,sY,sX,nCouleur);//ajoute l'arc inverse
			if (bArquer && sY<sX)
				aK++;
		}
	GrapheInverser(pgG);//remplit le champ aInv qui donne la correspondance entre arc direct et arc inverse via aK=pgG->aInv[pgG->aDeh[sY]].
	Assert2("GrapheSymetriser",bGrapheSimple(pgG),bGrapheSymetrique(*pgG));
}//GrapheSymetriser

void GrapheTESTER(int iTest){
	int bEulerien;
	graf *pgG;
	int  bCheminer,bCircuit,uSommet;
	int kbAfficher=1;
	const int ksSource=1;
	int bSimple;
	Appel0(sC2("GrapheTESTER,test n°",sEntier(iTest)));
		switch (iTest) {
			case 1: GrapheCreer(1,&pgG);
					GrapheDecrire( (pgG->nSommetEnTout=8,pgG) );
					bSimple=bGrapheSimple(pgG);
					printf( "Le graphe à %s %s simple.\n",sPluriel(pgG->nSommetEnTout,"sommet"),sPas("est",!bSimple) );
					GrapheCreer(0,&pgG);
					break;
			case 2: GrapheCreer(1,&pgG);
					GrapheDecrire( (pgG->nSommetEnTout=8,pgG) );
					bEulerien=bGrapheEulerien(pgG,2,4);
					printf( "Le graphe à %s %s eulérien.\n",sPluriel(pgG->nSommetEnTout,"sommet"),sPas("est",!bEulerien) );
					GrapheCreer(0,&pgG);
					break;
			case 3: ;
					break;
			case 4: if (0) for (uSommet=1;uSommet<10;uSommet++){
						GrapheCreer(uSommet,&pgG);
							GrapheVoir(pgG,sC4b("Graphe à",sPluriel(pgG->nSommetEnTout,"sommet"),"et",sPluriel(pgG->nArcEnTout,"arc")));
							bCheminer=bGrapheCheminerCourt(pgG,ksSource,pgG->nSommetEnTout,kbAfficher);
							if (!kbAfficher)
								printf("Il %s un chemin.\n",sPas("y a vraiment",!bCheminer));
						GrapheCreer(0,&pgG);
					}
					if (0) for (uSommet=10;uSommet<=10;uSommet++){
						GrapheCreer(uSommet,&pgG);
							GrapheArquer(pgG, 1, 4);
							bGrapheDesarquer(pgG, 4, 2);
							GrapheVoir(pgG,sC4b("Graphe à",sPluriel(pgG->nSommetEnTout,"sommet"),"et",sPluriel(pgG->nArcEnTout,"arc")));
							bCheminer=bGrapheCheminerLong(pgG,ksSource,pgG->nSommetEnTout,kbAfficher);
							if (!kbAfficher)
								printf("Il %s un chemin.\n",sPas("y a vraiment",!bCheminer));
						GrapheCreer(0,&pgG);
					}
					if (0) for (uSommet=3;uSommet<10;uSommet++){
						GrapheCreer(uSommet, &pgG);
							GrapheInverser(pgG);
							GrapheVoir2(pgG,sC4b("Graphe à",sPluriel(pgG->nSommetEnTout,"sommet"),"et",sPluriel(pgG->nArcEnTout,"arc")));
							bCircuit=bGrapheCircuite(pgG);
							t(sC3bp("Il",sNie("y a",!bCircuit,"un","aucun"),"circuit"));
						GrapheCreer(0,&pgG);
					}
					if (0){
						GrapheCreer(4,&pgG);
							GrapheEtager(pgG);
							GrapheVoir(pgG,sC4b("Le graphe étagé a",sPluriel(pgG->nSommetEnTout,"sommet"),"et",sPluriel(pgG->nArcEnTout,"arc")));
						GrapheCreer(0,&pgG);
					}
					break;
			default:break;
		}
	Appel1(sC2("GrapheTESTER,test n°",sEntier(iTest)));
}//GrapheTESTER

int bGrapheVidE(graf *pgG){
	int bVide;
	Assert2("bGrapheVidE0",bGrapheAmorceR,bGraphe(pgG));
	bVide=(pgG->nSommetEnTout==0);
	if (bVide)
		Assert1("bGrapheVidE1",pgG->nArcEnTout==0);//sinon,savoir pourquoi
	return(bVide);
}//bGrapheVidE

int bGrapheSommet(graf *pgG,int sSommet){
	int bGrapheSommet=bCroit(1,sSommet,pgG->nSommetEnTout);
	return(bGrapheSommet);
}//bGrapheSommet

void GrapheVoir(graf *pgG,char *sMessage){
	//énumère les arcs de gG sous la forme de couples (origine,destination)
	int aK,sX;
	Assert2("GrapheVoir",bGrapheAmorceR,sMessage!=0);
	printf("%s%c(%s et %s):\n   ",sMessage,' ',sPluriel(pgG->nSommetEnTout, "sommet"),sPluriel(pgG->nArcEnTout, "arc"));
	if (pgG->nArcEnTout>0){
		for (sX=1;sX<=pgG->nSommetEnTout;sX++){
			for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)
				printf("  (%d,%d)",sX,pgG->sSuk[aK]);
			//printf("\n");
		}
	} else printf(" Aucun arc");
	printf(".\n");
}//GrapheVoir

void GrapheVoir0(graf *pgG,char *sMessage){
	//énumère les aretes de gG supposé symétrisé sous la forme de couples (origine,destination)
	int aK,sX,sY;
	Assert2("GrapheVoir",bGrapheAmorceR,sMessage!=0);
	printf("%s à %s et %s spécifiées par des triplets (sommet,sommet:poids):\n   ",sMessage,sPluriel(pgG->nSommetEnTout, "sommet"),sPluriel((pgG->nArcEnTout)/2, "arête"));
	if (pgG->nArcEnTout>0){
		for (sX=1;sX<=pgG->nSommetEnTout;sX++){
			for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
				sY=pgG->sSuk[aK];
				if (sX<sY)
					printf("  (%d,%d:%d)",sX,sY,pgG->nCout[aK]);
			}
			//printf("\n");
		}
	} else printf(" Aucune arête");
	printf(".\n");
}//GrapheVoir0

void GrapheVoir1(graf *pgG,int bDontCouleur,char *sMessage){
	//énumère les arcs de gG sous la forme de couples (origine,destination,couleur)
	#define kbLitteral 1
	int aK,sX;
	char cOrigine,cDestination;
	char cCouleur[1+knGrapheCouleurMax]={'z','v','r','b','j','n','f'};//zéro,vert,rouge,bleu,jaune,facultatif
	Assert2("GrapheVoir",bGrapheAmorceR,sMessage!=0);
	printf("%s%c (%s)\n   ",sMessage,':',sPluriel(pgG->nArcEnTout, "arc"));
	if (pgG->nArcEnTout>0){
		for (sX=1;sX<=pgG->nSommetEnTout;sX++){
			for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++){
				if (kbLitteral){
					//printf(" (%d,%d,%c)",sX,pgG->sSuk[aK],cCouleur[pgG->coulh[aK]]);
					cOrigine=(bCroit(1,sX,kuMinusculeOffset-1))? 'A'+sX-kuMajusculeOffset : 'a'+sX-kuMinusculeOffset;
					cDestination=(bCroit(1,pgG->sSuk[aK],kuMinusculeOffset-1))? 'A'+pgG->sSuk[aK]-kuMajusculeOffset : 'a'+pgG->sSuk[aK]-kuMinusculeOffset;
					if (bDontCouleur)
						printf(" (%c,%c,%c)",cOrigine,cDestination,cCouleur[pgG->coulh[aK]]);
					else printf(" (%c,%c)",cOrigine,cDestination);
				} else if (bDontCouleur)
					printf(" (%d,%d,%c)",sX,pgG->sSuk[aK],cCouleur[pgG->coulh[aK]]);
				else printf(" (%c,%c)",cOrigine,cDestination);
			}
			//printf("\n");
		}
	} else printf(" Aucun arc");
	printf(".\n");
}//GrapheVoir1

void GrapheVoir2(graf *pgG,char *sMessage){
	//énumère les arcs de gG et de son graphe inverse sous la forme de couples (origine,destination)
	int aK,sX;
	Assert2("GrapheVoir2",bGrapheAmorceR,sMessage!=0);
	printf("%s%c (%s)\n   ",sMessage,':',sPluriel(pgG->nArcEnTout, "arc"));
	printf(" direct:");
	if (pgG->nArcEnTout>0){
		for (sX=1;sX<=pgG->nSommetEnTout;sX++){
			for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)
				printf("  (%d,%d)",sX,pgG->sSuk[aK]);
			//printf("\n");
		}
	} else printf(" Aucun arc");
	printf(" inverse:");
	if (pgG->nArcEnTout>0){
		for (sX=1;sX<=pgG->nSommetEnTout;sX++){
			for (aK=pgG->aDeh[sX];aK<pgG->aDeh[sX+1];aK++)
				printf("  (%d,%d)",sX,pgG->sKus[aK]);
			//printf("\n");
		}
	} else printf(" Aucun arc");
	printf(".\n");
}//GrapheVoir2

void GrapheVoir3(graf *pgG,char *sMessage){
	//énumère les arcs de gG et de son graphe inverse sous la forme de couples (origine,destination)
	int aK,sX;
	Assert2("GrapheVoir3",bGrapheAmorceR,sMessage!=0);
	GrapheVoir2(pgG,sMessage);
	printf("%s%c (%s)\n   ",sMessage,':',sPluriel(pgG->nArcEnTout, "arc"));
	printf(" cout:");
	if (pgG->nArcEnTout>0){
		for (sX=1;sX<=pgG->nSommetEnTout;sX++){
			for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)
				printf("  (%d,%d:%d)",sX,pgG->sSuk[aK],pgG->nCout[aK]);
			//printf("\n");
		}
	} else printf(" Aucun arc");
	printf(" prix:");
	if (pgG->nArcEnTout>0){
		for (sX=1;sX<=pgG->nSommetEnTout;sX++){
			for (aK=pgG->aHed[sX];aK<pgG->aHed[sX+1];aK++)
				printf("  (%d,%d:%d)",sX,pgG->sSuk[aK],pgG->nPoids[aK]);
			//printf("\n");
		}
	} else printf(" Aucun arc");
	printf(".\n");
}//GrapheVoir3
