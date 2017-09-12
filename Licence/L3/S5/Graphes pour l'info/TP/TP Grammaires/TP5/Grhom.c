//Grhom=GRammaire HOMogène. Scrute une grammaire homogène puis génère son code équivalent en langage C ou utilise cette grammaire sur-le-champ.
#include "Outil.h"
#include "Grhom.h"
#include "Grammaire.h"
#define kuCaractereMaX kE2
#define kuLettreMaX 26
#define kuRegleMaX kuLettreMaX
#define kuTermeMaX kE1
#define kuTypE (kuTermeMaX+1)
#define kuNoM (kuTermeMaX+2)
int nGrhoM[1+kuRegleMaX][1+kuTermeMaX+2];
int nTablE[1+kuLettreMaX][1+kuTermeMaX+2];
FILE *fGramR;//nom du ficher destiné à recevoir le code compilé écrit en langage C
int bGrhomAmorceR;
int bGrhomCompileR;
//int nTypE[1+kuRegleMaX];
enum eRegleTypE {rtAlphA,rtTerminalE,rtET,rtOU,rtOmegA};
//struct eReglE{int index;int indexdebut;int indexfin;} lxmChainE[1+knLexemeMaX];//la chaîne lexicale est générée dans dans lxmChainE

void EcrirE(char *szQuoi);
void EcrirE3(char *sA,char *sB,char *sC);
void EcrirE7(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG);
void EnteteGenereR(char *sGrammaireHomogene,int nClassement[],int nRegleEnTout,char *sFichierCible);
int bFlechE(char *sGrhom,int nDebutExclu);
void GrhomAfficheR1(char *szQuoi,char *sGrohm,int nRegleEnTout);
void GrhomAfficheR0(char *szQuoi,char *sGrAlg,int nRegleEnTout);
int bGrhomDecideR(int uRegle,char sMot[],int iDebut,int *piFin,int bVoir,int *pnAppelEnTout);
void GrhomExpliciteR(char *sGrohm,int nRegleEnTout,char *szFichierCible);
int bGrhomHomogenE(char *sGrohm,int nSeparateur[]);
int bGrhomPlausiblE(char *sGrohm,int nRegleEnTout);
void GrhomTabuleR(char *sGrohm,int nRegleEnTout,int bVoir);
int bRegleET(int nRegle,char *sGrhom,int nDebut,int nFin);
void RegleEtGenereR(int nRegle);
int bRegleOU(int nRegle,char *sGrhom,int nDebut,int nFin);
void RegleOuGenereR(int nRegle);
int bRegleTerminalE(int nRegle,char *sGrhom,int nDebut,int nFin,int *pbA,int *pbB);
void RegleTerminaleGenereR(int nRegle);

void EcrirE(char *szQuoi){
        //printf("%s",szQuoi);
        fprintf(fGramR,"%s",szQuoi);
}//EcrirE

void EcrirE3(char *sA,char *sB,char *sC){
        EcrirE(sC3(sA,sB,sC));
}//EcrirE3

void EcrirE7(char *sA,char *sB,char *sC,char *sD,char *sE,char *sF,char *sG){
        EcrirE(sC7(sA,sB,sC,sD,sE,sF,sG));
}//EcrirE7

void EnteteGenereR(char *sGrammaireHomogene,int nRang[],int nRegleEnTout,char *sFichierCible){
        //génère include,variables de module,protos des règles (ordre donné par nRang[]),leur code et celui de sFichierCibleAMORCER,INITIALISER,TESTER.
        int uR;
        int mPoint=mChainePos('.',sFichierCible);
        int nFichierLg=strlen(sFichierCible);
        char *sRacine=malloc(1+nFichierLg);
                strcpy(sRacine,sFichierCible);
                Assert3("EnteteGenereR",mPoint>0,sFichierCible[mPoint+1]=='c',mPoint+2==nFichierLg);
                sRacine[mPoint]='\0';
                EcrirE("#include \"Outil.h\"\n");
                EcrirE3("#include \"",sRacine,".h\"\n");
                EcrirE("char *sMOT;\n");
                EcrirE3("int b",sRacine,"AmorceR=kF;\n");
                GrhomAfficheR1("",sGrammaireHomogene,nRegleEnTout);
                //générer tous les prototypes associés aux règles ——à 1 règle T on associe bijectivement 1 routine bT().
                        for (uR=1;uR<=nRegleEnTout;uR++)
                                EcrirE(sC3("int b",sC(nGrhoM[nRang[uR]][kuNoM]),"(int iDebut,int *piFin);\n"));
                        EcrirE("\n");
                //générer le code des routines sFichierCibleAMORCER,INITIALISER et TESTER qui appelle bS() et dit si sMOT est engendré par la grammaire.
                        EcrirE3("void ",sRacine,"AMORCER(){\n");
                                EcrirE3("    b",sRacine,"AmorceR=kV;\n");
                        EcrirE3("}//",sRacine,"AMORCER\n\n");
                        EcrirE3("void ",sRacine,"INITIALISER(){\n");
                                EcrirE7("    Assert1(\"",sRacine,"INITIALISER\",b",sRacine,"AmorceR);","","\n");
                        EcrirE3("}//",sRacine,"INITIALISER\n\n");
                        EcrirE3("void ",sRacine,"TESTER(int iTest){\n");
                                EcrirE("    int bEngendre,iFin,bSucces;\n");
                                EcrirE7("    Assert1(\"",sRacine,"TESTER0\",b",sRacine,"AmorceR);","","\n");
                                EcrirE("    //sMOT:=mot à tester selon iTest\n");
                                EcrirE("        switch(iTest){\n");
                                EcrirE("            case 1: sMOT=\"aab\";break;\n");
                                EcrirE("            case 2: sMOT=\"aaba\";break;\n");
                                EcrirE3("            default:Assert1(\"",sRacine,"TESTER1\",0);break;\n");
                                EcrirE("        }\n");
                                EcrirE("    bSucces=bS(0,&iFin);\n");
                                EcrirE("    bEngendre=bSucces && strlen(sMOT)==iFin;\n");
EcrirE3("    printf(\"%s: %s %s engendré par la grammaire décrite dans \\\"",sFichierCible,"\\\".\\n\",(bEngendre)? \"SUCCES\": \"ECHEC \",sG(sMOT),sEst(bEngendre));\n");
                        EcrirE3("}//",sRacine,"TESTER\n\n");
        free(sRacine);
}//EnteteGenereR

int bFlechE(char *sGrhom,int nDebutExclu){
        int bFleche=(sGrhom[nDebutExclu+1]=='-') && (sGrhom[nDebutExclu+2]=='>');
        return(bFleche);
}//bFlechE

void GrhomAfficheR1(char *szQuoi,char *sGrhom,int nRegleEnTout){
        //affiche sur écran si szQuoi est non vide, et dans le fichier fGramR sinon, la grammaire décrite dans nGrhoM[][]
        int uR,uT,uTermeMax;
        char cListe[]={'a',' ','.','+','z'};
        char cOperateur;
        int bFichier=(nChaineLg(szQuoi)==0);
        //Assert2("GrhomAfficheR1",bGrhomAmorceR,bGrhomCompileR);
        if (!bFichier)
                printf("%s (%s):\n",szQuoi,sPluriel(nRegleEnTout,"règle"));
        for (uR=1;uR<=nRegleEnTout;uR++){
                if (bFichier){
                        EcrirE3("//Règle ",sEntier(uR),":");
                        EcrirE3(sC(nGrhoM[uR][kuNoM]),"->","");
                }else printf("    Règle %2d: %c->",uR,nGrhoM[uR][kuNoM]);
                for (cOperateur=cListe[nGrhoM[uR][kuTypE]],uTermeMax=nGrhoM[uR][0],uT=1;uT<=uTermeMax;uT++){
                        if (bFichier) EcrirE(sC(nGrhoM[uR][uT])); else printf("%c",nGrhoM[uR][uT]);
                        if (uT<uTermeMax){
                                if (bFichier)
                                        EcrirE(sC(cOperateur));
                                else
                                        printf("%c",cOperateur);
                        }
                }
                if (bFichier) EcrirE("\n"); else printf("\n");
        }
}//GrhomAfficheR1

void GrhomAfficheR0(char *szQuoi,char *sGrAlg,int nRegleEnTout){
        //affiche sur écran si szQuoi est non vide, et dans le fichier fGramR sinon, la grammaire décrite dans nGrhoM[][]
        int uR,uC=0;
        char cSeparateur = ';';

        printf("%s (%s):\n",szQuoi,sPluriel(nRegleEnTout,"règle"));
        for (uR=1;uR<=nRegleEnTout;uR++){
                printf("    Règle %2d: ",uR);
                do {
                        printf("%c", sGrAlg[uC]);
                        uC++;
                }while((uC <nChaineLg(sGrAlg)) && (sGrAlg[uC] != cSeparateur));
                uC++;
                printf("\n");
        }
}//GrhomAfficheR0

void GrhomAMORCER(){
        //amorce le présent module une fois pour toutes (donc sa complexité n'est pas critique)
        bGrhomAmorceR=kV;
}//GrhomAMORCER

int bGrhomCompiler(char *sGrammaireAlgebrique,char *sGrammaireHomogene,int bAfficher,char *szFichierCible,int *pnRegleEnTout){
        //vrai ssi sGrammaireHomogene (règles ET,OU,Terminale entre ";",blancs facultatifs) est bien une grammaire homogène d'au plus kuRegleMaX règles.
        //Si oui,et si szFichierCible est non vide, le code en C qui explicite sGrammaireHomogene est stocké dans szFichierCible.
        //Les règles de sGrammaireHomogene sont affichées au besoin et pnRegleEnTout rend le nombre total de règles.
        int uC;//indexe le caractère courant de sGrammaireHomogene
        int bCompiler;
        int nGrammaireLg;
        int cPasse;
        int nRegleEnTout;
        int bSeparateur;
        int nSeparateur[1+1][1+kuRegleMaX];//indexe chaque kcSeparateur situé dans sGrammaireHomogene;un kcSeparateur final est ajouté au besoin.
        const char kcSeparateur=';';
        printf("Grammaire algébrique à compiler:%s\n",sG(sGrammaireAlgebrique));
        printf("Grammaire homogène à compiler:%s\n",sG(sGrammaireHomogene));
        Assert3("bGrhomCompiler1",bGrhomAmorceR,nChaineLg(sGrammaireAlgebrique)<kuCaractereMaX,nChaineLg(sGrammaireHomogene)<kuCaractereMaX);
        //********* partir de cPasse=0 ds le for ci-dessous
        for (cPasse=0;cPasse<=1;cPasse++){
                nGrammaireLg=(cPasse==0)? nChaineLg(sGrammaireAlgebrique): nChaineLg(sGrammaireHomogene);
                for (nRegleEnTout=0,nSeparateur[cPasse][1]=-2,uC=1;uC<=nGrammaireLg;uC++){
                        if (cPasse==0)
                                bSeparateur=(sGrammaireAlgebrique[uC]==kcSeparateur);
                        else bSeparateur=(sGrammaireHomogene[uC]==kcSeparateur);
                        if (bSeparateur){
                                //tee("cPasse0,nRegleEnTout0",cPasse,nRegleEnTout);
                                Assert1("bGrhomCompiler2",nRegleEnTout<kuRegleMaX);
                                nSeparateur[cPasse][++nRegleEnTout]=uC;
                        };
                }
                if (nSeparateur[cPasse][nRegleEnTout]<nGrammaireLg){
                        Assert1("bGrhomCompiler3",nRegleEnTout<kuRegleMaX);
                        nSeparateur[cPasse][++nRegleEnTout]=nGrammaireLg;
                        //tee("cPasse,nRegleEnTout",cPasse,nRegleEnTout);
                }
                Assert1("bGrhomCompiler4",nRegleEnTout<kuRegleMaX);
                nSeparateur[cPasse][nRegleEnTout+1]=nGrammaireLg;
                Assert1("bGrhomCompiler5",nRegleEnTout>0);//nombre total de règles strictes détectées dans sGrammaireHomogene
                nSeparateur[cPasse][0]=nRegleEnTout;//AVANT appel li+1
                if(cPasse == 1){
                        bCompiler=bGrhomHomogenE(sGrammaireHomogene,nSeparateur[cPasse]);//vrai ssi les règles entre séparateurs définissent bien une grammaire homogène
                        bGrhomCompileR=bCompiler;//AVANT GrhomAfficheR li+2;variable de module
                }
                if (bAfficher){
                        if (cPasse==0)
                                GrhomAfficheR0("Grammaire algébrique",sGrammaireAlgebrique,nRegleEnTout);
                        else
                                GrhomAfficheR1("Grammaire homogène",sGrammaireHomogene,nRegleEnTout);
                }
        }
        if ( bCompiler && nChaineLg(szFichierCible)>0 )
                GrhomExpliciteR(sGrammaireHomogene,nRegleEnTout,szFichierCible);//génère ds sFichierCible le code C qui explicite sGrammaireHomogene
        *pnRegleEnTout=nRegleEnTout;//nombre total de règles strictes détectées dans sGrammaireHomogene
        return(bCompiler);
}//bGrhomCompiler

void GrhomDecideR(char *sGrammaireAlgebrique,char *sGrammaireHomogene,char *sMot){
        //dit (printf) si sMot est engendré ou non par sGrammaireHomogene
        int nAppel=0,bCompiler,bDecider;
        int iFin;
        int nRegleEnTout;
        //Appel0("GrhomDecideR");
                bCompiler=bGrhomCompiler(sGrammaireAlgebrique,sGrammaireHomogene,k1Voir,"",&nRegleEnTout);
                if (bCompiler){
                        //GrhomAfficher("Grammaire reformulée",sGrammaireHomogene);
                        GrhomTabuleR(sGrammaireHomogene,nRegleEnTout,!k1Voir);//remplit la variable de module nTablE[][0]
                        bDecider=bGrhomDecideR('S'-'@',sMot,0,&iFin,!k1Voir,&nAppel) && (iFin==nChaineLg(sMot));//lit nTablE[][0]
                        printf("%s: le mot %s %s engendré %s.\n",(bDecider)?"SUCCES":"ECHEC ",sG(sMot),sEst(bDecider),sP(sPluriel(nAppel,"appel$ en tout")));
                }
        //Appel1("GrhomDecideR");
}//GrhomDecideR

int bGrhomDecideR(int uRegle,char *sMot,int iDebut,int *piFin,int bVoir,int *pnAppelEnTout){
        //dit si sMot[iDebut,iFin] est engendré ou non par la grammaire décrite dans nTablE[];pnAppelEnTout compte les appels à cette routine récursive
        const int kuAppelMax=kE4;
        int bDecider=kF;
        int uT,uTermeMax,nType;
        int iDebute,iFinit;
        Assert2("bGrhomDecideR1",bGrhomAmorceR,*pnAppelEnTout<kuAppelMax);
        *pnAppelEnTout+=1;
        uTermeMax=nTablE[uRegle][0];
        nType=nTablE[uRegle][kuTypE];
        Assert1("bGrhomDecideR2",uTermeMax>0);
        if (bVoir)
                printf("Règle %c de type ",'@'+uRegle);
        switch (nType) {
                case  rtET:                        for (bDecider=kV,iDebute=iDebut,uT=1;uT<=uTermeMax && bDecider;uT++){
                                                                if (bVoir)
                                                                        printf("ET, appel du terme %d: la règle %c.\n",uT,nTablE[nTablE[uRegle][uT]][kuNoM]);
                                                                bDecider=bDecider && bGrhomDecideR(nTablE[uRegle][uT],sMot,iDebute,&iFinit,bVoir,pnAppelEnTout);
                                                                iDebute=iFinit;
                                                        }
                                                        *piFin=(bDecider)? iFinit : iDebut;
                                                        break;
                case  rtOU:                        for (bDecider=kF,uT=1;uT<=uTermeMax && !bDecider;uT++){
                                                                if (bVoir)
                                                                        printf("OU, appel du terme %d: la règle %c.\n",uT,nTablE[nTablE[uRegle][uT]][kuNoM]);
                                                                bDecider=bGrhomDecideR(nTablE[uRegle][uT],sMot,iDebut,&iFinit,bVoir,pnAppelEnTout);
                                                        }
                                                        *piFin=(bDecider)? iFinit : iDebut;
                                                        break;
                case  rtTerminalE:        bDecider=(sMot[iDebut]==nTablE[uRegle][1]+'@');
                                                        if (bVoir)
                                                                printf("Terminale, sMot[%d] %s reconnu.\n",iDebut,sEst(bDecider));
                                                        *piFin=(bDecider)? iDebut+1 : iDebut;
                                                        break;
                default:                        Assert1("bGrhomDecideR3",0);break;
        }
        return(bDecider);
}//bGrhomDecideR

void GrhomDeclineR(char *sGrammaireAlgebrique,char *sGrammaireHomogene,int uMotLgMax){
        //liste tous les mots engéndrés par sGrammaireHomogene qui ont jusqu'à uMotLgMax caractères.
        const int kuMotLgMax=20;
        const int kuTab=1;
        int nAppel,nAppelMax;
        int nBit;
        int bCompiler,bDecliner,nMotEngendreh;
        int iFin;
        char sMot[1+uMotLgMax];
        int nM,nMot,nMotLg,nMotMax,nMotEnTout;
        int nRegleEnTout;
        Assert2("GrhomDeclineR",bGrhomAmorceR,bCroitStrict(0,uMotLgMax,kuMotLgMax));//aucune grammaire homogène ne peut engendrer le mot vide
        if (bCompiler==(bGrhomCompiler(sGrammaireAlgebrique,sGrammaireHomogene,k1Voir,"",&nRegleEnTout))){
                //GrhomAfficher("Grammaire reformulée",sGrammaireHomogene);
                GrhomTabuleR(sGrammaireHomogene,nRegleEnTout,!k1Voir);
                printf("%sMots engendrés ayant de 1 à %s:\n",sTab(kuTab),sPluriel(uMotLgMax,"lettre"));
                for (nMotEngendreh=0,nMotEnTout=0,nMotLg=0;nMotLg<=uMotLgMax;nMotLg++){
                        nMotMax=zPuissance(2,nMotLg);
                        sMot[nMotLg]='\0';
                        for (nMot=0;nMot<nMotMax;nMot++){
                                for (nM=2*nMot,nBit=0;nM=nM/2,nBit<nMotLg;nBit++)
                                        sMot[nBit]='a'+nM%2;
                                bDecliner=bGrhomDecideR('S'-'@',sMot,0,&iFin,!k1Voir,(nAppel=0,&nAppel)) && (iFin==nChaineLg(sMot));
                                nAppelMax=iMax(nAppelMax,nAppel);
                                //printf("%s: le mot %s %s engendré.\n",(bDecliner)?"SUCCES":"ECHEC ",sG(sMot),sEst(bDecliner));
                                nMotEngendreh+=bDecliner;
                                if (bDecliner)
                                        printf("%s%s %s %s\n",sTab(1+kuTab),sG(sMot),sE(kuMotLgMax+4-nMotLg),sP(sPluriel(nMotLg,"lettre")));
                        }//for nMot
                        nMotEnTout+=nMotMax;
                }//for nMotLg
                if (nMotEngendreh<=0)
                        printf("%sAucun mot n'est engendré",sTab(kuTab));
                else printf("%s%d mots sur %d sont engendrés",sTab(kuTab),nMotEngendreh,nMotEnTout);
                printf(" par la grammaire (pire cas: %s pour décider un mot).\n",sPluriel(nAppelMax,"dérivation"));
        }
//Appel1("GrhomDecideR");
}//GrhomDeclineR

void GrhomExpliciteR(char *sGrammaireHomogene,int nRegleEnTout,char *sFichierCible){
        //génère ds sFichierCible le code C qui décide si la variable de module sMOT est engendrée ou non par la sGrammaireHomogene
        int nListe[1+kuRegleMaX];
        int nRang[1+kuRegleMaX];
        int uR,nRg;
        int iErreur;
        Assert4("GrhomExpliciteR0",bGrhomAmorceR,bGrhomCompileR,nRegleEnTout>0,nChaineLg(sFichierCible)>0);
        //nRang[]=rang des noms de routines classés par ordre alphabétique croissant ——afin de déclarer bA() avant bB(),lui-même avant bS(), etc.
                for (uR=1;uR<=nRegleEnTout;uR++)
                        nListe[uR]=nGrhoM[uR][kuNoM];
                VecteurTrier2(nListe,1,nRegleEnTout,nRang);
        fGramR=fopen(sFichierCible,"w");
        Assert1("GrhomExpliciteR1",fGramR!=0);
                EnteteGenereR(sGrammaireHomogene,nRang,nRegleEnTout,sFichierCible);
                for (uR=1;nRg=nRang[uR],uR<=nRegleEnTout;uR++)
                        switch (nGrhoM[nRg][kuTypE]) {
                                case  rtET:                        RegleEtGenereR(nRg);break;
                                case  rtOU:                        RegleOuGenereR(nRg);break;
                                case  rtTerminalE:        RegleTerminaleGenereR(nRg);break;
                                default:                        Assert1("GrhomExpliciteR",0);break;
                        }
        iErreur=fclose(fGramR);
        Assert1("GrhomExpliciteR2",iErreur==0);
        printf("La traduction en code C de cette grammaire est disponible dans le fichier %s.\n",sG(sFichierCible));
}//GrhomExpliciteR

int bGrhomHomogenE(char *sGrohm,int nSeparateur[]){
        //vrai ssi sGrohm décrit une liste point-virgulée de règles homogènes contenant A->a et B->b et ayant des membres gauches distincts, dont S.
        int bA=kF,bB=kF;//bA vrai ssi A->a est une règle de la grammaire homogène
        int nDebut,nFin,bHomogene,uR,nRegleEnTout;
        Assert1("bGrhomHomogenE",bGrhomAmorceR);
        for (bHomogene=kV,nRegleEnTout=nSeparateur[0],nDebut=0,uR=1;uR<=nRegleEnTout;uR++){
                nFin=nSeparateur[uR+0]-1;
                bHomogene=bHomogene && (bRegleET(uR,sGrohm,nDebut,nFin) || bRegleOU(uR,sGrohm,nDebut,nFin) || bRegleTerminalE(uR,sGrohm,nDebut,nFin,&bA,&bB));
                nDebut=nFin+2;
        };
        bHomogene=bHomogene && bA && bB && bGrhomPlausiblE(sGrohm,nSeparateur[0]);//ie contient A->a et B->b, et ayant des membres gauches distincts, dont S.
        return(bHomogene);
}//bGrhomHomogenE

void GrhomINITIALISER(){
        //relance le présent module
        Assert1("GrhomINITIALISER",bGrhomAmorceR);
}//GrhomINITIALISER

int bGrhomPlausiblE(char *sGrohm,int nRegleEnTout){
        //tous les membres gauches sont des majuscules distinctes 2 à 2 et la règle S est présente.
        int uL,nLettre,bPlausible,uR;
        int nMajuscule[1+kuLettreMaX];//comptabilise les occurrences des majuscules situées en membre gauche de règle
        Assert1("bGrhomPlausiblE1",bGrhomAmorceR);
        for (uL=1;uL<=kuLettreMaX;uL++)
                nMajuscule[uL]=0;
        for (uR=1;uR<=nRegleEnTout;uR++){
                nLettre=nGrhoM[uR][kuNoM]-'@';
                Assert1("bGrhomPlausiblE2",bCroit(1,nLettre,kuLettreMaX));
                //teee("uR,nDebut,nLettre",uR,nDebut,nLettre);
                nMajuscule[nLettre]+=1;
        }
        //VecteurVoir("nMajuscule",&nMajuscule[0],1,kuLettreMax);
        for (bPlausible=kV,uL=1;uL<=kuLettreMaX;uL++)
                bPlausible=bPlausible && (nMajuscule[uL]<=1);
        bPlausible=bPlausible && (nMajuscule['S'-'@']==1);
        return(bPlausible);
}//bGrhomPlausiblE

void GrhomTabuleR(char *sGrohm,int nRegleEnTout,int bVoir){
        //remplit nTablE[]. La règle de nom N de nGrhoM est renommée N-'@' dans nTablE. L'offset '@' transforme la règle A en règle 1 dans nTablE[].
        int uL,uR,uRegle,nT,nTermeMax;
        Assert2("GrhomTabuleR",bGrhomAmorceR,bGrhomCompileR);
        for (uL=1;uL<=kuLettreMaX;uL++)
                for (nT=0;nT<=kuTermeMaX;nT++)
                        nTablE[uL][nT]=0;
        for (uR=1;uR<=nRegleEnTout;uR++){
                uRegle=nGrhoM[uR][kuNoM]-'@';//la règle A sera la règle 1 dans nTablE[]
                nTablE[uRegle][kuTypE]=nGrhoM[uR][kuTypE];//type en fin de ligne
                nTablE[uRegle][kuNoM]=nGrhoM[uR][kuNoM];//nom en quasi fin de ligne
                nTablE[uRegle][0]=nGrhoM[uR][0];//nb termes en tête de ligne
                for (nTermeMax=nGrhoM[uR][0],nT=1;nT<=nTermeMax;nT++)
                        nTablE[uRegle][nT]=nGrhoM[uR][nT]-'@';//toute référence à un nom de règle devient une référence au n° de la ligne contenant cette règle.
        }
        if (bVoir)
                for (uL=1;uL<=kuLettreMaX;uL++)
                        for (nT=0;nT<=kuTypE || !bLigne();nT++)
                                printf("%3d",nTablE[uL][nT]);
}//GrhomTabuleR

void GrhomTESTER(int iTest){
        //teste le présent module
        int bCompiler;
        char *skFichier="Grammaire.c";//reçoit le code C qui explicite la grammaire homogène compilée par bGrhomCompiler()
        int nRegleEnTout;
        if (iTest<=0){
                Appel0(sC2("GrhomTESTER,test n°",sEntier(-iTest)));
                        Assert1("GrhomTESTER",bGrhomAmorceR);
                                switch (-iTest) {
                                        case  0:        GrhomDeclineR("S->Aa+Ab;A->a","S->A.U;U->A+B;A->a;B->b",4);
                                                                break;
                                        case  1:        bCompiler=bGrhomCompiler("S->aa+ab","S->A.U;U->A+B;A->a;B->b",k1Afficher,skFichier,&nRegleEnTout);
                                                                break;
                                        case  11: //Module pour G1 avec L1={b}
                                                                                GrhomDeclineR("S->a+b","S->B+B;B->b;A->a",4);
                                                                break;
                                        case 12:        //Module pour G2 avec L2={a,b}
                                                                                GrhomDeclineR("S->a+b","S->A+B;B->b;A->a",6);
                                                                break;
                                        case 13:        //Module pour G3 avec L3={b.a}
                                                                                GrhomDeclineR("S->a+b","S->B.A;B->b;A->a",6);
                                                                break;
                                        case 14:        //Module pour G4 avec L4={b^+.a}
                                                                                GrhomDeclineR("S->a+b","S->K.A;K->L+B;L->B.K;A->a;B->b",15);
                                                                break;
                                        default:break;
                                }
                Appel1(sC2("GrhomTESTER,test n°",sEntier(-iTest)));
        }else GrammaireTESTER(iTest);
}//GrhomTESTER

int bRegleET(int nRegle,char * sGrhom,int nDebut,int nFin){
        int uC;
        int bEt;
        int cOperateur;
        int bRegle;
        int nTerme;
        bRegle=(nDebut+3<=nFin) && bMajuscule(sGrhom[nDebut]) && bFlechE(sGrhom,nDebut);
        for (cOperateur=' ',uC=nDebut;uC<=nFin;uC++)
                if (sGrhom[uC]=='+' || sGrhom[uC]=='.')
                        cOperateur=sGrhom[uC];
        bEt=bRegle && (cOperateur=='.');
        if (bEt){
                for (nTerme=0,uC=nDebut+3;uC<=nFin;uC++){
                        //tc("sGrhom[uC]",sGrhom[uC]);
                        if (bMajuscule(sGrhom[uC])){
                                Assert1("bRegleET1",nTerme<kuTermeMaX);
                                nGrhoM[nRegle][++nTerme]=sGrhom[uC];
                        }
                        else Assert1("bRegleET2",sGrhom[uC]==cOperateur);
                }
                //te("****************************bET:nTerme",nTerme);
                nGrhoM[nRegle][kuTypE]=rtET;
                nGrhoM[nRegle][0]=nTerme;
                nGrhoM[nRegle][kuNoM]=sGrhom[nDebut];
        }
        //tb("bEt",bEt);
        return(bEt);
}//bRegleET

void RegleEtGenereR(int nRegle){
        int uT;
        int nTermeMax=nGrhoM[nRegle][0];
        EcrirE3("int b",sC(nGrhoM[nRegle][kuNoM]),"(int iDebut,int *piFin){\n");
                //recopier en commentaire le libellé de la règle
                        EcrirE3("    //",sC(nGrhoM[nRegle][kuNoM]),"->");
                        for (uT=1;uT<=nTermeMax;uT++){
                                EcrirE(sC(nGrhoM[nRegle][uT]));
                                if (uT<nTermeMax)
                                        EcrirE(".");
                        }
                        EcrirE("\n");
                //déclarer les variables locales autres que bSucces
                        for (EcrirE("    int iA=iDebut,"),uT=1;uT<=nTermeMax;uT++){
                                EcrirE3("i",sC('@'+uT+1),"");//commence avec iB
                                EcrirE((uT<nTermeMax)? ",":";\n");
                        }
                EcrirE("    int bSucces=");
                for (uT=1;uT<=nTermeMax;uT++){
                        EcrirE7("b",sC(nGrhoM[nRegle][uT]),"(i",sC('@'+uT),",&i",sC('@'+uT+1),")");
                        if (uT<nTermeMax)
                                EcrirE(" && ");
                }
                EcrirE(";\n");
                EcrirE3("    *piFin=(bSucces)?i",sC('@'+nTermeMax+1),":iDebut;\n");
                EcrirE("    return(bSucces);\n");
        EcrirE3("}//b",sC(nGrhoM[nRegle][kuNoM]),"\n\n");
}//RegleEtGenereR

int bRegleOU(int nRegle,char *sGrhom,int nDebut,int nFin){
        int uC;
        int bRegle;
        int bOu;
        int cOperateur;
        int nTerme;
        bRegle=(nDebut+3<=nFin) && bMajuscule(sGrhom[nDebut]) && bFlechE(sGrhom,nDebut);
        for (cOperateur=' ',uC=nDebut;uC<=nFin;uC++)
                if (sGrhom[uC]=='+' || sGrhom[uC]=='.')
                        cOperateur=sGrhom[uC];
        bOu=bRegle && (cOperateur=='+');
        if (bOu){
                for (nTerme=0,uC=nDebut+3;uC<=nFin;uC++)
                        if (bMajuscule(sGrhom[uC])){
                                Assert1("bRegleOU1",nTerme<kuTermeMaX);
                                nGrhoM[nRegle][++nTerme]=sGrhom[uC];
                        }
                        else Assert1("bRegleOU2",sGrhom[uC]==cOperateur);
                //te("****************************bOU:nTerme",nTerme);
                nGrhoM[nRegle][kuTypE]=rtOU;
                nGrhoM[nRegle][0]=nTerme;
                nGrhoM[nRegle][kuNoM]=sGrhom[nDebut];
        }
        return(bOu);
}//bRegleOU

void RegleOuGenereR(int nRegle){
        int uT;
        int nTermeMax=nGrhoM[nRegle][0];
        EcrirE3("int b",sC(nGrhoM[nRegle][kuNoM]),"(int iDebut,int *piFin){\n");
                //rappel de la règle
                        EcrirE3("    //",sC(nGrhoM[nRegle][kuNoM]),"->");
                        for (uT=1;uT<=nTermeMax;uT++){
                                EcrirE(sC(nGrhoM[nRegle][uT]));
                                if (uT<nTermeMax)
                                        EcrirE("+");
                        }
                        EcrirE("\n");
                //code interne
                        EcrirE("    int iFin;\n");
                        EcrirE("    int bSucces=");
                        for (uT=1;uT<=nTermeMax;uT++){
                                EcrirE3("b",sC(nGrhoM[nRegle][uT]),"(iDebut,&iFin)");
                                if (uT<nTermeMax)
                                        EcrirE(" || ");
                        }
                        EcrirE(";\n");
                        EcrirE("    *piFin=(bSucces)?iFin:iDebut;\n");
                        EcrirE("    return(bSucces);\n");
        EcrirE3("}//b",sC(nGrhoM[nRegle][kuNoM]),"\n\n");
}//RegleOuGenereR

int bRegleTerminalE(int nRegle,char *sGrhom,int nDebut,int nFin,int *pbA,int *pbB){
        int uC;
        int cOperateur;
        int bRegle;
        int nTerme;
        int bTerminale;
        bRegle=(nDebut+3<=nFin) && bMajuscule(sGrhom[nDebut]) && bFlechE(sGrhom,nDebut);
        for (cOperateur=' ',uC=nDebut;uC<=nFin;uC++)
                if (sGrhom[uC]=='+' || sGrhom[uC]=='.')
                        cOperateur=sGrhom[uC];
        bTerminale=bRegle && (cOperateur==' ');
        if (bTerminale){
                for (nTerme=0,uC=nDebut+3;uC<=nFin;uC++)
                        if (bMinuscule(sGrhom[uC])){
                                Assert1("bRegleTerminalE1",nTerme<kuTermeMaX);
                                nGrhoM[nRegle][++nTerme]=sGrhom[uC];
                                //teee("nRegle,nTerme,char",nRegle,nTerme,sGrhom[uC]);
                                if (sGrhom[nDebut]=='A' && sGrhom[uC]=='a')
                                        *pbA=kV;
                                if (sGrhom[nDebut]=='B' && sGrhom[uC]=='b')
                                        *pbB=kV;
                        }
                        else Assert1("bRegleTerminalE2",sGrhom[uC]==cOperateur);
                //te("bTerminale:nTerme",nTerme);
                nGrhoM[nRegle][kuTypE]=rtTerminalE;
                nGrhoM[nRegle][0]=nTerme;
                nGrhoM[nRegle][kuNoM]=sGrhom[nDebut];
        }
        return(bTerminale);
}//bRegleTerminalE

void RegleTerminaleGenereR(int nRegle){
        EcrirE3("int b",sC(nGrhoM[nRegle][kuNoM]),"(int iDebut,int *piFin){\n");
                //recopier en commentaire le libellé de la règle
                        EcrirE3("    //",sC(nGrhoM[nRegle][kuNoM]),"->");
                        EcrirE(sC(nGrhoM[nRegle][1]));
                        EcrirE("\n");
                EcrirE3("    int bSucces = sMOT[iDebut]=='",sC(nGrhoM[nRegle][1]),"';\n");
                EcrirE("    *piFin = (bSucces) ? iDebut+1 : iDebut;\n");
                EcrirE("    return(bSucces);\n");
        EcrirE3("}//b",sC(nGrhoM[nRegle][kuNoM]),"\n\n");
}//RegleTerminaleGenereR


