#include "Outil.h"
#include "Tas.h"
//NB:pour créer un minimier contenant 20 éléments au plus,encadrer tous les accès au tas par TasAllouer(20) et TasAllouer(0);
//NB:les constantes de garde (modifiables) sont knEffectifLiM et knPoidsMaX
#define knEffectifLiM 32768 //nb max d'éléments admissible physiquement dans le tas; k comme constante;n comme entier naturel.
#define knEffectifMaX knEffectifLiM-1 //nb max d'éléments admissible physiquement dans le tas; k comme constante;n comme entier naturel.
#define knPoidsMaX 9999 
int bTasAmorceR;//ie le module a effectivement été amorcé
int ukTasHauteurMaX;//u:un ou plus,k:constante.uk désigne une variable>1 vue comme une constante après initialisation. ku désignerait une vraie constante>1.
int bTasOuverT;//flipflop;b comme booléen;un flipflop est une bascule à 2 états;vrai ssi un tas est actuellement alloué
int nTasVoiR;//dédié TasVoir();numéro du tas affiché
struct Tas{//ci-dessous,l'indice 0 est inutilisé;partir de l'index 1 facilite l'implémentation du tas.
	int nObjet[knEffectifLiM];//numéro de l'objet stocké dans le tas; ce numéro est censé être un entier dans [1..knEffectifMaX] 
	int nPoids[knEffectifLiM];//poids positif ou nul associé à l'objet considéré.
	int iPlace[knEffectifLiM];//-iPlace[E]>0 donne l'emplacement de l'objet C dans le tas. Si iPlace[C]=0,alors C n'est pas dans le tas.
	int nCardinal;//nombre maximal de noeuds stockés actuellement dans le tas
	int nVolume;//nombre de noeuds stockés actuellement dans le tas
}TaS,*pTaS;

void TasDescendrE(int uObjet);
void TasMonteR(int uObjet);
void TasPlausiblE(char *sAppelant);
void TasSatureR();
void TasTesterExhaustivemenT(int uEffectifMax);

void TasAllouer(int nEffectifMax){//O(1)
	//si nEffectifMax>0, alloue un tas à nEffectifMax objets;si nEffectifMax=0, restitue le tas.
	if (nEffectifMax>0)
		printf("   ** Demande d'allocation d'un tas à %d éléments.\n",nEffectifMax);
	Assert2("TasAllouer",bTasAmorceR,bCroit(0,nEffectifMax,knEffectifMaX));
	FlipFlop("TasAllouer",bVrai(nEffectifMax>0),&bTasOuverT);
	if (nEffectifMax>0){
		pTaS=malloc(sizeof(TaS));
		pTaS->nCardinal=nEffectifMax;
	}else free(pTaS);
	if (bTasOuverT)
		TasRazer();//dc en O(nEffectifMax) et pas en O(knEffectifMaX),ce qui changerait la complexité des petits tas
}//TasAllouer

void TasAMORCER(){
	//amorce le présent module une fois pour toutes
	ukTasHauteurMaX=1+mPoidsFort(knEffectifMaX);//affectation définitive indiquée par le préfixe qui contient un "k" comme constante
	nTasVoiR=0;
	bTasAmorceR=kV;
	bTasOuverT=kF;
	Assert1("TasAMORCER",(knEffectifMaX+1)%8==0);//frontière de 8 octets
}//TasAMORCER

int bTasContient(int uObjet){//O(1)
	//vrai ssi uObjet désigne un objet qui est actuellement présent dans le tas
	int bContient;
	Assert3("bTasContient",bTasAmorceR,bTasOuverT,bCroit(1,uObjet,knEffectifMaX));
	bContient=bCroit(1,uObjet,pTaS->nCardinal) && (pTaS->iPlace[uObjet]<0);
	return(bContient);
}//bTasContient

void TasDescendrE(int uObjet){//O(1)
	int uFils,uFilsMax,uPere;
	Assert1("TasDescendrE1",bCroit(1,uObjet,knEffectifMaX));
	uPere=-pTaS->iPlace[uObjet];
	//tee("uObjet,Place>0",uObjet,uPere);
	Assert1("TasDescendrE2",bCroit(1,uPere,pTaS->nCardinal));
	uFils=2*uPere;
	uFilsMax=pTaS->nVolume;
	if (uFils<uFilsMax && pTaS->nPoids[pTaS->nObjet[uFils+1]]<pTaS->nPoids[pTaS->nObjet[uFils]])
		uFils++;
	While(1+ukTasHauteurMaX);
	while (bWhile("TasDescendrE3",uFils<=uFilsMax && pTaS->nPoids[pTaS->nObjet[uFils]]<pTaS->nPoids[uObjet])) {
		//tee("père et fils",uPere,uFils);
		//faire remonter de 1 niveau l'élément indexé par uFils pour que uObjet puisse descendre
			pTaS->nObjet[uPere]=pTaS->nObjet[uFils];
			pTaS->iPlace[pTaS->nObjet[uFils]]=-uPere;
		//descendre de 1 niveau
			uPere=uFils;
			uFils=2*uPere;
			if (uFils<uFilsMax && pTaS->nPoids[pTaS->nObjet[uFils+1]]<pTaS->nPoids[pTaS->nObjet[uFils]])
				uFils++;
	};//while
	//placer uObjet dans le tas à l'index uPere
		pTaS->nObjet[uPere]=uObjet;
		pTaS->iPlace[uObjet]=-uPere;
}//TasDescendrE

int eTasExtraire(){//O(lg(N))
	//rend l'élément situé à la racine du tas,ou déroute si extraction non définie;l'objet extrait est supprimé réellement.
	int eExtraire;//élément pour lequel la valeur associée est minimale;le tas étant un minimier, cet élément est situé à la racine, d'index 1.
	int nDernier;
	//Appel0("eTasExtraire");
	Assert1("eTasExtraire1",pTaS->nVolume>0);
	eExtraire=pTaS->nObjet[1];
	if (pTaS->nVolume>0) {
		nDernier=pTaS->nObjet[pTaS->nVolume];
		//tee("eExtraire et nDernier",eExtraire,nDernier);
		pTaS->iPlace[eExtraire]=0;
		pTaS->nVolume--;
		pTaS->iPlace[nDernier]=-1;
		TasDescendrE(nDernier);
		//TasVoir("eTasExtraire");
	}
	else eExtraire=0;//aucun élément extrait par défaut
	Assert2("eTasExtraire2",bCroit(1,eExtraire,knEffectifMaX),pTaS->nVolume>=0);
	TasPlausiblE("eTasExtraire");
	//Appel1("eTasExtraire");
	return(eExtraire);
}//eTasExtraire

void TasInsererValuer(int uObjet,int nPoids){
	//insère (uObjet,nPoids) dans le tas si uObjet est absent et s'il reste de la place dans le tas;si uObjet est déjà présent,ne fait rien.
	Assert4("TasInsererValuer",bTasAmorceR,bTasOuverT,bCroit(1,uObjet,knEffectifMaX),nPoids>=0);
	if (!bTasContient(uObjet)){
		pTaS->nVolume++;
		pTaS->iPlace[uObjet]=-pTaS->nVolume;
		pTaS->nObjet[pTaS->nVolume]=uObjet;
		pTaS->nPoids[pTaS->nVolume]=nPoids;
		TasMonteR(uObjet);
	}
}//TasInsererValuer

void TasINITIALISER(){//O(?)
	//relance le présent module
	Assert2("TasINITIALISER",bTasAmorceR,!bTasOuverT);
}//TasINITIALISER

void TasMonteR(int uObjet){//O(1)
	int uFils,nPere;
	Assert3("TasMonteR1",bTasAmorceR,bTasOuverT,uObjet>0);
	uFils=-pTaS->iPlace[uObjet];
	nPere=uFils/2;
	While(ukTasHauteurMaX);
	while (bWhile("TasMonteR",uFils>1 && pTaS->nPoids[pTaS->nObjet[nPere]]>pTaS->nPoids[uObjet])) {
		//faire descendre de 1 niveau l'élément indexé par nPere pour que uObjet puisse monter
			pTaS->nObjet[uFils]=pTaS->nObjet[nPere];
			pTaS->iPlace[pTaS->nObjet[nPere]]=-uFils;
		//monter
			uFils=nPere;
			nPere=uFils/2;
	}//while
	Assert2("TasMonteR2",bCroit(1,uFils,pTaS->nVolume),bCroit(0,nPere,uFils-1));
	//installer uObjet au rang uFils
		pTaS->nObjet[uFils]=uObjet;
		pTaS->iPlace[uObjet]=-uFils;
}//TasMonteR

void TasPlausiblE(char *sAppelant){
	int uX,iY;
	int nDistinct[1+knEffectifMaX];
	//vérifie pTaS->iPlace[pTaS->nObjet[E]]=E pour tout objet E
		for (uX=1;uX<=pTaS->nVolume;uX++){
			iY=-pTaS->iPlace[pTaS->nObjet[uX]];
			Assert1(sAppelant,iY==uX);
		}
	//vérifie que pTaS->nObjet[] ne contient que des objets distincts
		for (uX=1;uX<=knEffectifMaX;uX++)
			nDistinct[uX]=0;
		for (uX=1;uX<=pTaS->nVolume;uX++)
			nDistinct[pTaS->nObjet[uX]]++;
		for (uX=1;uX<=knEffectifMaX;uX++)
			Assert1("TasPlausiblE",nDistinct[uX]<=1);
}//TasPlausiblE

void TasRazer(){//O(nCardinalMax)
	int uE;
	Assert2("TasRazer",bTasAmorceR,bTasOuverT);
	for (uE=1;uE<=knEffectifMaX;uE++)
		pTaS->nObjet[uE]=0;
	for (uE=1;uE<=knEffectifMaX;uE++)
		pTaS->iPlace[uE]=0;
	for (uE=1;uE<=knEffectifMaX;uE++)
		pTaS->nPoids[uE]=0;
	pTaS->nVolume=0;
}//TasRazer

void TasSatureR(){//O(knEffectifMaX)
	//remplit le tas avec knEffectifMaX éléments uE de poids 10*uE
	int uE;
	Assert2("TasSatureR",bTasAmorceR,bTasOuverT);
	for (uE=1;uE<=knEffectifMaX;uE++)
		pTaS->nObjet[uE]=uE;
	for (uE=1;uE<=knEffectifMaX;uE++)
		pTaS->iPlace[uE]=-uE;
	for (uE=1;uE<=knEffectifMaX;uE++)
		pTaS->nPoids[uE]=10*uE;
	pTaS->nVolume=knEffectifMaX;
}//TasSatureR

int eTasSommet(){//O(1)
	//rend l'élément situé à la racine du tas, ou 0 si le tas est vide
	int eSommet;
	Assert2("eTasSommet1",bTasAmorceR,bTasOuverT);
	if (bTasVide())
		eSommet=0;
	else eSommet=pTaS->nObjet[1];
	Assert2("eTasSommet2",bCroit(0,eSommet,knEffectifMaX),(eSommet==0)==bTasVide());
	return(eSommet);
}//eTasSommet

void TasTESTER(int iTest){
	//teste le présent module
	int eExtrait,uE,bContient;
	int nEffectifMax;
	int nPoids,nPoids0;
	Appel0(sC2("TasTESTER,test n°",sEntier(iTest)));
		TasAllouer(knEffectifMaX);
			switch (iTest) {
				case 1:
					nEffectifMax=14;
					nEffectifMax=10;
					TasAllouer(0);
					TasAllouer(nEffectifMax);
					for (uE=1;uE<=nEffectifMax;uE++){
						nPoids=uHasard(9);
						nPoids=uE;
						//printf("Insertion de (c%d,p%d):\n",uE,nPoids);
						TasInsererValuer(uE,nPoids);
						//TasVoir("");
					}
					TasVoir("initialisation");
					TasPlausiblE("après initialisation");
					nPoids=0;
					eExtrait=eTasSommet();
					//tee("objet extrait et Volume",eExtrait,pTaS->nVolume);
					for (uE=pTaS->nVolume;uE>0;uE--){
						nPoids0=nPoids;
						nPoids=pTaS->nPoids[pTaS->nObjet[1]];
						//tee("nPoids0,nPoids",nPoids0,nPoids);
						Assert1("TasTESTER case 1",nPoids0<=nPoids);
						eExtrait=eTasExtraire();//qui décrémente pTaS->nVolume, mais lu 1 fois au début du for
						//TasVoir(sC2b("extraction de l'élément",sEntier(eExtrait)));
						TasVoir(sC4b("extraction de l'élément",sG(sEntier(eExtrait)),"de poids",sEntier(nPoids)));
						TasPlausiblE("après extraction");
						// ******* Assert1("TasTESTERanormal",!bTasContient(eExtrait));
					}
					break;
				case 2:
					TasSatureR();
					TasVoir("TasSatureR");
					break;
				case 3:
					TasTesterExhaustivemenT(6);
					break;
				case 4:
					TasSatureR();
					TasVoir("TasSatureR");
					nPoids=pTaS->nPoids[1];
					eExtrait=eTasSommet();
					tee("sommet et volume A",eExtrait,pTaS->nVolume);
					for (uE=pTaS->nVolume;uE>0;uE--){
						nPoids0=nPoids;
						nPoids=pTaS->nPoids[1];
						tee("nPoids0,nPoids",nPoids0,nPoids);
						//Assert1("TasTESTER case 1",nPoids0<=nPoids);
						eExtrait=eTasExtraire();//qui décrémente pTaS->nVolume, mais lu 1 fois au début du for
						TasVoir(sC4b("extraction de l'élément",sG(sEntier(eExtrait)),"de poids",sEntier(pTaS->nPoids[1])));
					}
					eExtrait=eTasSommet();
					tee("sommet et volume B",eExtrait,pTaS->nVolume);//affiche 0 et 0
					bContient=bTasContient(2);tb("bContient 2",bContient);
					TasInsererValuer(2,50);TasVoir("insertion (2,50)");
					bContient=bTasContient(2);tb("bContient 2",bContient);
					bContient=bTasContient(4);tb("bContient 4",bContient);
					TasInsererValuer(4,20);TasVoir("insertion (4,20)");
					bContient=bTasContient(4);tb("bContient 4",bContient);
					TasInsererValuer(3,80);TasVoir("insertion (3,80)");
					TasInsererValuer(6,90);TasVoir("insertion (6,90)");
					TasInsererValuer(5,50);TasVoir("insertion (5,50)");
					TasInsererValuer(5,50);TasVoir("insertion (5,50)");
					TasInsererValuer(5,50);TasVoir("insertion (5,50)");
					TasInsererValuer(5,50);TasVoir("insertion (5,50)");
					eExtrait=eTasSommet();//non défini puisque tas vide
					tee("sommet et volume C",eExtrait,pTaS->nVolume);
					break;
				default:
					Assert1("TasTESTER",0);
					break;
			}
		TasAllouer(0);
	Appel1(sC2("TasTESTER,test n°",sEntier(iTest)));
}//TasTESTER	

void TasTesterExhaustivemenT(int uEffectifMax){
	//génère 2**uEffectifMax configurations d'éléments distinctes;construit chaque fois le tas correspondant puis le vide par extractions successives.
	#define kuPoidsMax kE2
	float rEffectifMax;
	long zEffectifMax;
	int asConfig[1+knEffectifMaX];
	long zGeant;
	int iPlace;
	long zReste;
	int eRetrait;
	int uRetrait;
	Assert1("TasTesterExhaustivemenT",uEffectifMax>0);
	rEffectifMax=zPuissance(2,uEffectifMax)-1;
	for (zGeant=zEffectifMax=trunc(rEffectifMax);zGeant>=0;zGeant--){
		//i(zGeant);
		//décomposer zGeant en base zCardinalMax sur uEffectifMax digits
			for(zReste=zGeant,iPlace=1;iPlace<uEffectifMax;iPlace++){
				asConfig[iPlace]=1+zReste % uEffectifMax;
				zReste=zReste/uEffectifMax;
			}
		//construire le tas décrit par la configuration asConfig[] ——et le voir
			TasRazer();
			for(iPlace=1;iPlace<uEffectifMax;iPlace++)
				if (!bTasContient(asConfig[iPlace])){
					TasInsererValuer(asConfig[iPlace],uHasard(kuPoidsMax));
				}
			TasVoir(sC2("Tas généré n°",sEntier(zGeant)));
		//vider le tas par extractions successives --et voir le tas résultant
			for(uRetrait=1;uRetrait<=pTaS->nVolume;uRetrait++){
				eRetrait=eTasExtraire();
				TasVoir(sC2b("retrait de l'élément",sEntier(eRetrait)));
			}
	}
}//TasTesterExhaustivemenT

int bTasVide(){//O(1)
	int bVide;
	Assert2("bTasVide",bTasAmorceR,bTasOuverT);
	bVide=(pTaS->nVolume==0);
	return(bVide);
}//bTasVide

void TasVoir(char *sMessage){//O(nCardMaX)
	const int kbAffichageCensurer=kF;
	const int kncCouple=15;
	char cCouple[1+kncCouple];//description en caractères d'un couple (élément,poids de l'élément)
	int nbDeport;//nombre de blancs insérés entre les couples pour simuler visuellement un tas binaire
	int bDernier;
	const int kuEtageLargeurMax=kE3-1;
	char cEtage[1+kuEtageLargeurMax];//suite des caractères qui décrit l'étage courant du tas
	int nEtage,nEtageMax;
	int uIndex;
	int nPoids;
	int bPremiere;
	Assert3("TasVoir1",bTasAmorceR,bTasOuverT,sMessage!=0);
	nTasVoiR++;
	printf("Tas n°%d après %s:",nTasVoiR,sMessage);
	if (0){
		printf("\nIndex:");
		for (uIndex=1;uIndex<=pTaS->nCardinal;uIndex++)
			printf("%4d",uIndex);
		printf("\nPlace:");
		for (uIndex=1;uIndex<=pTaS->nCardinal;uIndex++)
			printf("%4d",pTaS->iPlace[uIndex]);
		printf("\nObjet:");
		for (uIndex=1;uIndex<=pTaS->nCardinal;uIndex++)
			printf("%4d",pTaS->nObjet[uIndex]);
		printf("\nPoids:");
		for (uIndex=1;uIndex<=pTaS->nCardinal;uIndex++)
			printf("%4d",pTaS->nPoids[uIndex]);
		printf("\n");
	}
	else printf("\n");
	if (!kbAffichageCensurer)
		if (pTaS->nVolume>0)
			for (nEtageMax=mPoidsFort(pTaS->nVolume),nEtage=0;nEtage<=nEtageMax;nEtage++){
				nbDeport=zPuissance(2,nEtageMax-nEtage)-1;
				strcpy(cEtage,sE(kncCouple*nbDeport));
				for (bPremiere=kV,uIndex=zPuissance(2,nEtage);uIndex<=yInf(zPuissance(2,nEtage+1)-1,pTaS->nVolume);uIndex++){
					//sprintf(cCouple,"(\"%d\",%d)",pTaS->nObjet[uIndex],pTaS->nPoids[pTaS->nObjet[uIndex]]);
					sprintf(cCouple,"(%d,%d)",pTaS->nObjet[uIndex],nPoids=pTaS->nPoids[pTaS->nObjet[uIndex]]);
					if (strlen(cCouple)<kncCouple)
						strcat(cCouple,sE(kncCouple-strlen(cCouple)));
					Assert1("TasVoir2",strlen(cCouple)==kncCouple);
					strcat(cEtage,cCouple);
					if (bPremiere)
						nbDeport=2*nbDeport+1;
					bPremiere=kF;
					bDernier=(uIndex==yInf(zPuissance(2,nEtage+1)-1,pTaS->nVolume));
					if (!bDernier)
						strcat(cEtage,sE(kncCouple*nbDeport));
				}
				printf("  %s\n",cEtage);
			}
		else printf("    Le tas est vide.\n");
	else  printf("    Le tas n'est pas affiché.\n");
	if (0)
		Pause();
}//TasVoir


void TasActualiser(int uElement,int nPoids){
	//Met à jour un sommet déjà présent; O(lg(S))
	//Modifier le poids de l'arc de nSommet avec la nouvelle distance nDist
	//Faire un affichage et vérifier que le tas s'est maj correctement
	if(bTasContient(uElement))
		pTaS->nPoids[uElement] = nPoids;
	
	TasVoir("Contenu du tas : ");
	
	//if(pTaS->nPoids[uElement] < pTaS->nPoids[uElement])
	//	TasMonteR(pTaS->nObjet[uElement]);
	
}//TasActualiser