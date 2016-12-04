#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> /* fcntl */
#include <unistd.h>
#include <fcntl.h>
#include <errno.h> /* errno */
#include <string.h>

#include <bateau.h>
#include <mer.h>

#define VERROUILLER 1
#define DEVERROUILLER 0
#define NB_MIN_BATEAUX 5

/*Verrous :
On verrouille toute la mer en écriture lorsqu'on place un nouveau bateau dedans. On ne doit pas lire la mer pendant qu'on y place un bateau, ni écrire dedans

On verrouille également en écriture les cases appartenant au bateau et correspondant au bouclier, puisqu'elles ne doivent pas pouvoir être prises pour cible par un autre bateau

Pour éviter que vision ne mette l'affichage de la mer à jour, on verrouille son en-tête en écriture, empêchant vision de lire ce header

Lorsqu'un bateau se déplace, on doit éviter qu'un autre bateau prenne cette même place pour cible de déplacement, donc on le verrouille encore en écriture

Lorsqu'on prend une case en particulier pour cible, on essaie d'y placer un verrou en écriture, puisqu'un tel verrou est incompatible avec tout autre on peut ainsi éviter toute autre interaction avec cette case par un autre processus.
*/

void BateauDetruire(int fd, int * nbBateaux, bateau_t * bateau) {
	mer_nb_bateaux_ecrire(fd, --(*nbBateaux));
	bateau_destroy(&bateau);
}

int MerVerrou(const int fd, bateau_t * bateau, int verrouiller) {
	// Verrouille tout le fichier mer
	struct flock verrou;
	
	verrou.l_whence = 0;
	verrou.l_start = 0;
	verrou.l_len = 0;
	
	if(verrouiller) {
		verrou.l_type = F_WRLCK;
		//printf("\n - Bateau %c : Pose verrou interne -\n", bateau_marque_get(bateau));
	} else {
		verrou.l_type = F_UNLCK;
		//printf("\n - Bateau %c : Levee verrou interne -\n", bateau_marque_get(bateau));
	}
	
	if(fcntl(fd, F_SETLKW, &verrou) == ERREUR) {
		if(verrouiller) {
			printf("Erreur lors de la pose du verrou ecrivain\n");
		} else {
			printf("Erreur lors de la levee du verrou ecrivain\n");
		}
		
		return ERREUR;
	}
	
	//printf("\n - Bateau %c a initialiser -\n", bateau_marque_get(bateau));
	
	return CORRECT;
}

int BouclierVerrou(const int fd, bateau_t * bateau, int verrouiller) {
	// Verrouille les cases appartenant au bateau
	int i;
	coords_t * bateauCellules = bateau_corps_get(bateau);
	coord_t * bateauCellule = bateauCellules->coords;
	
	struct flock verrou;
	
	verrou.l_whence = 0;
	verrou.l_len = MER_TAILLE_CASE;
	
	if(verrouiller) {
		verrou.l_type = F_WRLCK;
	} else {
		verrou.l_type = F_UNLCK;
	}
	
	for(i = 0; i < bateauCellules->nb; i++) {
		verrou.l_start = bateauCellule[i].pos;
		
		if(verrouiller) {
			//printf("\n - Bateau %c : Activation du bouclier en [%i, %i] -\n",
			//bateau_marque_get(bateau), bateauCellule[i].l, bateauCellule[i].c);
		} else {
			//printf("\n - Bateau %c : Désactivation du bouclier en [%i, %i] -\n",
			//bateau_marque_get(bateau), bateauCellule[i].l, bateauCellule[i].c);
		}
	
		if(fcntl(fd, F_SETLKW, &verrou) == ERREUR) {
			if(verrouiller) {
				printf("Erreur lors de la pose du verrou bouclier\n");
			} else {
				printf("Erreur lors de la levee du verrou bouclier\n");
			}
			
			return ERREUR;
		}
		
		if(verrouiller) {
			//printf("\n - Bateau %c : Bouclier pose -\n", bateau_marque_get(bateau));
		} else {
			//printf("\n - Bateau %c : Bouclier leve -\n", bateau_marque_get(bateau));
		}
	}

	return CORRECT;
}

int HeaderVerrou(const int fd, bateau_t * bateau, int verrouiller) {
	// Bloque le header du fichier mer pour empecher vision de le lire
	struct flock verrou;
	
	verrou.l_whence = 0;
	verrou.l_start = 0;
	verrou.l_len = MER_TAILLE_ENTETE;
	
	if(verrouiller) {
		verrou.l_type = F_WRLCK;
	} else {
		verrou.l_type = F_UNLCK;
	}
	
	if(fcntl(fd, F_SETLKW, &verrou) == -1) {
		// Si un verrou est deja pose, on ne peut pas mettre celui-ci par dessus
		return ERREUR;
	}
	return CORRECT;
}

int VoisinsVerrou(const int fd, bateau_t * bateau, const coords_t listeVoisins, int verrouiller) {
	int i;
	case_t merCase;
	struct flock verrou;
	
	verrou.l_whence = 0;
	verrou.l_len = 0;
	
	if(verrouiller) {
		verrou.l_type = F_WRLCK;
	} else {
		verrou.l_type = F_UNLCK;
	}
	
	for(i = 0; i < listeVoisins.nb; i++) {
		mer_case_lire(fd, listeVoisins.coords[i], &merCase);
		if(merCase == MER_CASE_LIBRE) { // Si la case est libre, on la verrouille
			verrou.l_start = listeVoisins.coords[i].pos;
			if(verrouiller) {
				//printf("\n - Bateau %c : Pose verrou interne en [%i, %i] -\n",
				//bateau_marque_get(bateau), listeVoisins.coords[i].l, listeVoisins.coords[i].c);
			} else {
				//printf("\n - Bateau %c : Levee verrou interne en [%i, %i] -\n",
				//bateau_marque_get(bateau), listeVoisins.coords[i].l, listeVoisins.coords[i].c);
			}
			
			if(fcntl(fd, F_SETLK, &verrou) == -1) {
				if(verrouiller) {
					printf("Erreur lors de la pose du verrou pour les voisins\n");
				} else {
					printf("Erreur lors de la levee du verrou pour les voisins\n");
				}
				
				return ERREUR;
			}
		}
	}
	
	return CORRECT;
}

int CibleVerrou(const int fd, bateau_t * bateau, coord_t cible, int verrouiller) {
	// Pose un verrou sur une case en particulier
	struct flock verrou;
	
	verrou.l_whence = 0;
	verrou.l_start = cible.pos;
	verrou.l_len = MER_TAILLE_CASE;
	
	/*
	 * Verrou en ecriture pour etre exclusif a tout le monde
	 * et donc trouver tout verrou deja existant sur la case
	 */
	
	if(verrouiller) {
		verrou.l_type = F_WRLCK;
		//printf("\n - Bateau %c : Pose verrou en [%i, %i] -\n", bateau_marque_get(bateau), cible.l, cible.c);
	} else {
		verrou.l_type = F_UNLCK;
		//printf("\n - Bateau %c : Levee verrou en [%i, %i] -\n", bateau_marque_get(bateau), cible.l, cible.c);
	}
	
	
	
	if(fcntl(fd, F_SETLK, &verrou)) {
		if(verrouiller) {
			printf("Erreur lors de la pose du verrou\n");
		} else {
			printf("Erreur lors de la levee du verrou\n");
		}
		
		return ERREUR;
	}
	
	return CORRECT;
}


/* 
 *	Programme principal 
 */


int main( int nb_arg , char * tab_arg[] ) {
	char fich_mer[128] ;
	case_t marque = MER_CASE_LIBRE ;
	char nomprog[128] ;
	float energie = 0.0 ;

	/*----------*/

	strcpy( nomprog , tab_arg[0] ) ;

	if( nb_arg != 4 )
		{
			fprintf( stderr , "Usage : %s <fichier mer> <marque> <energie>\n", 
				 nomprog );
			exit(-1);
		}

	if( strlen(tab_arg[2]) !=1 ) 
		{
			fprintf( stderr , "%s : erreur marque <%s> incorrecte \n",
				 nomprog , tab_arg[2] );
			exit(-1) ;
		}


	strcpy( fich_mer , tab_arg[1]);
	marque = tab_arg[2][0] ;
	sscanf( tab_arg[3] , "%f" , &energie );
	
	/* Initialisation de la generation des nombres pseudo-aleatoires */
	srandom((unsigned int)getpid());



	printf( "\n\n%s : ----- Debut du bateau %c (%d) -----\n\n ", 
	nomprog , marque , getpid() );
	
	/* 
	 * INITIALISATION DE LA MER
	 */
	bateau_t * bateau = BATEAU_NULL ;
	int nbBateaux = 0 ; 
	int fd;								// Descripteur du fichier mer
	int no_error;
	
	if( ( fd = open( fich_mer , O_RDWR | O_CREAT , 0666)) == -1 ) {
		printf("Erreur lors de l'ouverture du fichier mer");
		return(ERREUR);
	}
	
	bateau	= bateau_new(NULL, marque, energie);
	
	/* Initialisation du bateau dans la mer */
	if((no_error = MerVerrou(fd, bateau, VERROUILLER))) {
		printf("Erreur dans le verrouillage de la mer\n");
		
		exit(no_error);
	}
	
	if((no_error = mer_bateau_initialiser(fd, bateau))) {
		printf("Erreur dans l'initialisation de la mer\n");
	
		exit(no_error);
	}
	
	mer_nb_bateaux_lire(fd, &nbBateaux);
	mer_nb_bateaux_ecrire(fd, ++nbBateaux);

	MerVerrou(fd, bateau, DEVERROUILLER);
	
	/*
	 * INITIALISATION DU BOUCLIER
	 */
	if(energie >= BATEAU_SEUIL_BOUCLIER) {
		if((no_error = BouclierVerrou(fd, bateau, 1))) {
			printf("Erreur lors du placement du bouclier\n");
			
			exit(no_error);
		}
	}
	
	/*
	 * BOUCLE PRINCIPALE
	 */
	
	booleen_t coule = FAUX;
	booleen_t deplacement = VRAI;
	booleen_t acquisition;
	coords_t * listeVoisins = NULL;
	coord_t cible;
	char bateauMarque;
		
	while(1) {
		sleep((rand() % 3) + 1); // Entre 1 et 3 secondes
		
		bateauMarque = bateau_marque_get(bateau);
		
		/* VERIFICATIONS SUR L'ETAT DES BATEAUX */
		printf("\n - Bateau %c -\n", bateauMarque);
		
		if((no_error = mer_bateau_est_touche(fd, bateau, &coule))) {
			// Destruction d'un bateau si on a un probleme lors de l'acces a ses donnees
			printf("Erreur dans la vérification de l'attaque sur un bateau\n");
			BateauDetruire(fd,&nbBateaux, bateau);
			
			exit(no_error);
		}
		
		mer_nb_bateaux_lire(fd, &nbBateaux);
		
		if(coule && energie < BATEAU_SEUIL_BOUCLIER) {
			// Destruction du bateau si touche par un autre
			printf("\n - Bateau %c : Destruction -\n", bateauMarque);
			mer_nb_bateaux_ecrire(fd, --nbBateaux);
			mer_bateau_couler(fd, bateau);
			bateau_destroy(&bateau);
			close(fd);
			
			exit(0);
		}
				
		if(nbBateaux == 1) {
			// Condition de victoire : Un seul bateau restant
			printf("\n - Bateau %c : Vainqueur -\n", bateauMarque);
			printf("\n - Bateau %c : Fin -\n", bateauMarque);
			sleep(1);
			//BateauDetruire(fd,&nbBateaux, bateau);
			close(fd);
			
			exit(0);
		}
		
		listeVoisins = coords_new();
		if((no_error = mer_voisins_rechercher(fd, bateau, &listeVoisins))) {
			printf("Erreur lors de la recherche de voisins\n");
			BateauDetruire(fd,&nbBateaux, bateau);
			
			exit(no_error);
		}
		
		/* DEPLACEMENT D'UN BATEAU */
		if(energie > 0) {
			if(VoisinsVerrou(fd, bateau, *listeVoisins, 1) == ERREUR) {
				// On verifie que le bateau peut se deplacer et que les cases autour sont libres
				printf("Erreur lors du deplacement du bateau %c\n", marque);
				deplacement = FAUX;
			} else {
				if((no_error = BouclierVerrou(fd, bateau, 0))) {
					printf("Erreur lors de la desactivation du bouclier\n");
					BateauDetruire(fd,&nbBateaux, bateau);
				
					exit(no_error);
				}
			}
		
			// On empeche la lecture du fichier
			HeaderVerrou(fd, bateau, 1);
		
			if((no_error = mer_bateau_deplacer(fd, bateau, listeVoisins, &deplacement))) {
				// On deplace enfin le bateau
				printf("Erreur dans le deplacement du bateau sur la mer\n");
				BateauDetruire(fd,&nbBateaux, bateau);
			
				exit(no_error);
			} else {
				energie -= BATEAU_MAX_ENERGIE * 0.05;
			}
		
			// On permet la lecture
			HeaderVerrou(fd, bateau, 0);
		}
		
		printf("\n - Bateau %c : %f d'energie restante -\n", bateauMarque, energie);
		
		if(energie >= BATEAU_SEUIL_BOUCLIER) {
			// On verifie si l'energie du bateau est suffisante pour reactiver les boucliers
			if((no_error = BouclierVerrou(fd, bateau, 1))) {
				printf("Erreur lors de l'activation du bouclier\n");
				BateauDetruire(fd,&nbBateaux, bateau);
				
				exit(no_error);
			}
		}
		
		if(VoisinsVerrou(fd, bateau, *listeVoisins, 0) == ERREUR) {
			printf("Erreur lors du deverouillage des cases adjacentes au bateau %c", marque);
			BateauDetruire(fd,&nbBateaux, bateau);
			
			exit(no_error);
		}
		
		if(deplacement) {
			printf("\n Deplacement acheve\n");
		}
		else {
			printf("\n Deplacement annule\n");
		}
	
		coords_destroy(&listeVoisins);
		
		/*
		 * ACQUISITION D'UN BATEAU
		 */
		 
		if((no_error = mer_bateau_cible_acquerir(fd, bateau, &acquisition, &cible))) {
			printf("Erreur lors de l'acquisition d'un bateau");
			BateauDetruire(fd,&nbBateaux, bateau);
	
			exit(no_error);
		}
		 
		if(acquisition) { // Si on peut tirer sur la cible
			// La cible est-elle deja verrouillee (bouclier) ?
			if(CibleVerrou(fd, bateau, cible, 1) != ERREUR) { // On peut tirer
				CibleVerrou(fd, bateau, cible, 0);
				if((no_error = mer_bateau_cible_tirer(fd, cible))) {
					printf("Erreur lors du tir du bateau %c\n", marque);
					BateauDetruire(fd,&nbBateaux, bateau);
					 
					exit(no_error);
				}
			
				if(CibleVerrou(fd, bateau, cible, 0) == ERREUR) {
					printf("Erreur lors du deverouillage du bateau %c\n", marque);
					BateauDetruire(fd,&nbBateaux, bateau);
					 
					exit(no_error);
				}
			} else {
				printf("Erreur lors du verouillage de la cible en [%i, %i]\n", cible.l, cible.c);
			}
		} else {
			printf("Erreur lors de l'acquisition d'une cible pour le bateau %c\n", marque);
		}
		
		printf("\n\n");
	}
	
	

	printf( "\n\n%s : ----- Fin du navire %c (%d) -----\n\n ", 
	nomprog , marque , getpid() );

	exit(0);
}