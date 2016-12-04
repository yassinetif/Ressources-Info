#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

// clear && clear && gcc tempsmoy.c -o tempsmoy
// ./tempsmoy 1000 "ls | ./poubelle.txt" 5

int comparaison(const void * a, const void * b) {
	int const *a2 = a;
	int const *b2 = b;
	
	return *a2 - *b2;
}

void initTab(int tab[], int tailleTab, int initialisateur) {
	int i;
	
	for(i = 0; i < tailleTab; i++) {
		tab[i] = initialisateur;
	}
}

void initMatrice( int * matrice[], int tailleTab, int initialisateur) {
	int i, j;
	
	for(i = 0; i < tailleTab; i++) {
		for(j = 0; j < 2; j++) {
			matrice[i][j] = initialisateur;
		}
	}
}

int main(int argc, char * argv[]) {
	if(argc != 4) {
		printf("Utilisation : %s <nbExecutions> <commande> <nbProcessus>\n", argv[0]);
		exit(-1);
	}
	
	int nbExecutions = atoi(argv[1]);
	int nbProcessus = atoi(argv[3]);
	int nbFils;
	
	int tube[nbProcessus][2];
	for(nbFils = 0; nbFils < nbProcessus; nbFils++) {
		pipe(tube[nbFils]);
	}
	
	int tabTemps[nbProcessus];
	int nbExecutionsFaites;
	int pidFils;
	struct timeval tpsDepart;
	struct timeval tpsArrivee;
	int tpsTotal;
	int cr = 0;
	int tpsRetenu;
	int estPere = 1;
	int premierTempsBon = 0;
	
	// Initialisation des tableaux
	//initMatrice(tabTemps, nbProcessus, -1);
	initTab(tabTemps, nbProcessus, 0);
	
	nbFils = 0;
	while(nbFils < nbProcessus && estPere) {
		switch(estPere = fork()) {
			case -1:
				printf("Erreur lors du fork\n");
				exit(-1);
			
			case 0:
				printf("Fils n° : %i\n", nbFils);
				
				// Les fils ecrivent mais ne lisent pas
				close(tube[nbFils][0]);
				
				// Execution de la commande et calcul du temps d'execution
				if(gettimeofday(&tpsDepart, NULL)) {
					printf("Erreur lors de la recuperation du temps\n");
				}
				
				for(nbExecutionsFaites = 0; nbExecutionsFaites < nbExecutions && WIFEXITED(cr); nbExecutionsFaites++) {
					cr = system(argv[2]);
				}
				
				if(gettimeofday(&tpsArrivee, NULL)) {
					printf("Erreur lors de la recuperation du temps\n");
				}
				
				tpsTotal = tpsArrivee.tv_sec * 1000 + tpsArrivee.tv_usec / 1000 -
							tpsDepart.tv_sec * 1000 + tpsDepart.tv_usec / 1000;

				if(cr) {
					printf("Interruption du fils n°%i lors de l'execution de %s : ", nbFils, argv[2]);
					if(WEXITSTATUS(cr) > 128) {
						printf("SIGNAL");
					} else {
						printf("EXIT");
					}
					tpsTotal = -cr;
					write(tube[nbFils][1], &tpsTotal, sizeof(int));
					printf("\n");
				} else {
					// Ecriture du dit temps d'execution
					write(tube[nbFils][1], &tpsTotal, sizeof(int));
				}
				
				close(tube[nbFils][1]);
				
				exit(0);
		}
		nbFils++;
	}
	
	for(nbFils = 0; nbFils < nbProcessus; nbFils++) {
		close(tube[nbFils][1]);
		read(tube[nbFils][0], &(tabTemps[nbFils]), sizeof(int));
		close(tube[nbFils][0]);
	}
	
		
	
	printf("AVANT TRI\n");
	for(nbFils = 0; nbFils < nbProcessus; nbFils++) {
		if(tabTemps[nbFils] <= 0) {
			printf("Erreur pour l'execution du fils n°%i\n", nbFils);
			premierTempsBon++;
		} else {
			printf("Temps n°%i : %i\n", nbFils, tabTemps[nbFils]);
		}
	}
	
	qsort(tabTemps, nbProcessus, sizeof(int), comparaison);
	
	printf("APRES TRI\n");
	for(nbFils = 0; nbFils < nbProcessus; nbFils++) {
		if(tabTemps[nbFils] > 0) {
			printf("Temps n°%i : %i", nbFils, tabTemps[nbFils]);
		} else {
			cr = (-tabTemps[nbFils]) / 256;
			if(cr > 128) {
				printf(" Interruption par le signal %i\n", cr - 128);
			}
			switch(cr) {
				case 127 :
					printf(" - Commande non trouvee");
					break;
				
				case 1 :
					printf(" - exit(1)");
					break;
			
				case 0 :
					printf(" - Interruption du processus avant qu'il ne puisse envoyer quoi que ce soit");
					break;
			
				default :
					printf(" - Interruption par le signal %i", cr);
					break;
			}
		}
		
		printf("\n");
	}
	
	tpsRetenu = tabTemps[(nbProcessus + premierTempsBon)/2];
	
	if(tpsRetenu > 0) {
		printf("Temps retenu : %i ms\n", tpsRetenu);
		printf("La commande \"%s\" necessite donc %i millisecondes pour etre executee\n", argv[2], tpsRetenu / nbExecutions);
	} else {
		printf("Aucune execution ne s'est bien deroulee\n");
	}
		
	
	return 0;
}