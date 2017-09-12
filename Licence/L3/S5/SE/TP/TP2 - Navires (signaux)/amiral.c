/* 
 * Programme pour processus navire-amiral :
 */

#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>


#include <mer.h>
#include <bateaux.h>

#define TAILLE_B 50
#define NB_COLONNES 5
#define NB_LIGNES 5

/* 
 * VARIABLES GLOBALES (utilisees dans les handlers)
 */

char nomProg[256] ;
char marqueActuelle = 'A';
char marqueDetruite = '*';

int fd;
int nbBateaux = 0;
int debutPartie = 1;
int nbBateauxTotal = 0;
int nbBateauxMax = NB_COLONNES * NB_LIGNES / 4;

bateau_t * bt[TAILLE_B];

/*
 * FONCTIONS LOCALES
 */

void SignalRecevoir(int signal, siginfo_t * info, void * context){
	mer_afficher(fd);
	int pid = info->si_pid;
	bateau_t * bateau = NULL;  
	booleen_t ok = VRAI ;
	coords_t * listeVoisins = NULL ;
	int i;
	int insert = 0;
	
	for(i = 0; i<TAILLE_B && bateau == NULL; i++){
		if(bt[i] != NULL && bt[i]->pid == pid){ // Si le bateau existe déjà
			bateau = bt[i];
		}
	}
	
	if(bateau != NULL){
		sleep(1);
	
		printf("\n\n\n\n --- BATEAU %i : %c ---\n\n", pid, bateau->marque);
	
		if(nbBateaux == 1 && !debutPartie){
			fprintf(stdout, "Victoire du navire %i : '%c'\n", pid, bateau->marque);
			kill(pid, SIGKILL);
			exit(0);
		}
	
		if(debutPartie && nbBateaux){
			debutPartie = 0;
		}	
	
	
		booleen_t coule;
		mer_bateau_est_touche(fd, bateau, &coule);

		if(coule == VRAI){
			fprintf(stdout, "Bateau : %i '%c' - Touche\n", pid, bateau->marque);
			marqueDetruite = bateau->marque;
			mer_bateau_couler(fd, bateau);
			bateau_destroy(&bateau);
			mer_nb_bateaux_ecrire(fd, --nbBateaux);
			bateau = NULL;
			kill(pid, SIGKILL);
		} else {
			if(bateau != NULL && marqueDetruite != bateau->marque) { // Risque de segfault sinon
				coords_printf( bateau->corps);
				printf( "  marque= %c\n", bateau->marque);
				printf("pas touché %i\n", coule);

				/*Recherche des voisins*/
				if((mer_voisins_rechercher(fd, bateau, &listeVoisins)) != CORRECT){
					fprintf( stderr, "erreur dans mer_voisins_rechercher\n");
					exit(1);
				}

				if((mer_bateau_deplacer(fd, bateau, listeVoisins, &ok ))!= CORRECT){
					fprintf( stderr, "erreur dans mer_bateau_deplacer\n");
					exit(1);
				}
				kill(pid, SIGUSR2); //Envoi d'un signal faisant perdre de l'energie
				booleen_t success;
				coord_t cible;
				mer_bateau_cible_acquerir(fd, bateau, &success, &cible);
				if(success == VRAI){
					mer_bateau_cible_tirer(fd, cible);
				}
			}
		}
	} else {
		if(nbBateauxTotal < nbBateauxMax) {
			for(i=0; i<TAILLE_B && !insert; i++){
				if(bt[i] == NULL){
					bateau = bateau_new(NULL, marqueActuelle, pid); // Creation du bateau
					if(mer_bateau_initialiser(fd, bateau) == CORRECT){
						marqueActuelle++;
						bt[i] = bateau;
						mer_nb_bateaux_ecrire(fd, ++nbBateaux);
						nbBateauxTotal++;
					} else {
						nbBateauxMax = nbBateauxTotal;
						bateau_destroy(&bateau);
						kill(pid, SIGKILL);
					}
					insert = 1; //Bateau inseré, sort de la boucle
			
				}
			}
		} else {
			printf("\nNombre de bateau maximal atteint (%i)\n", nbBateauxMax);
			kill(pid, SIGKILL);
		}
	}
}


/*
 * Programme Principal
 */
int
main( int nb_arg , char * tab_arg[] )
{
	 char fichierMer[128] ;
	 /*----------*/

	 /* 
	  * Capture des parametres 
	  */

	 if( nb_arg != 2 )
	 {
	  fprintf( stderr , "Usage : %s <fichier mer> \n", 
		   tab_arg[0] );
	  exit(-1);
	 }

	 strcpy( nomProg , tab_arg[0] );
	 strcpy( fichierMer , tab_arg[1] );
	 
	 /*
	  * Affichage pid bateau amiral 
	  */
	 
	 printf(" PID bateau amiral = %d\n" , getpid() ) ;

	 /* Initialisation de la generation des nombres pseudo-aleatoires */
	 srandom((unsigned int)getpid());
 
	 struct sigaction action;
	 sigemptyset(&action.sa_mask);
	 sigaddset(&action.sa_mask, SIGUSR1); // On masque SIGUSR1 pour ne pas recevoir de signal concurrent
	 action.sa_flags = SA_SIGINFO;
	 action.sa_sigaction = SignalRecevoir;
	 sigaction(SIGUSR1, &action, NULL);
	 mer_initialiser(fichierMer, NB_COLONNES, NB_LIGNES);
	 fd = open(fichierMer, O_RDWR, 0666);

	 while(1);

	 printf("\n\n\t----- Fin du jeu -----\n\n");
	 
	 close(fd);
	 
	 exit(0);
}
