#include <stdio.h>
#include <commun.h>
#include <time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

#include <mer.h>

#define LIGNES 5
#define COLONNES 5

int HeaderVerrou(int fd) {
	// Regarde si le header du fichier mer est verrouille
	struct flock verrou;
	
	verrou.l_whence = 0;
	verrou.l_start = 0;
	verrou.l_len = MER_TAILLE_ENTETE;
	
	fcntl(fd, F_GETLK, &verrou);
	
	if(verrou.l_type == F_RDLCK || verrou.l_type == F_WRLCK) {
		return 1;
	} else {
		return 0;
	}
}
 
int ModifRecente(char * nomFichier, int secMax) {
	// Regarde si le fichier a ete modifiee dans les dernieres secMax secondes
	struct stat buff;
	stat(nomFichier, &buff);
	
	return ((time(NULL) - buff.st_mtime) < secMax);
}

/*--------------------* 
 * Main demon 
 *--------------------*/
int
main( int nb_arg , char * tab_arg[] )
{
	char fich_mer[128] ;
	char nomprog[256] ;
 
	/*----------*/

	if( nb_arg != 2 )
	{
		fprintf( stderr , "Usage : %s <fichier mer>\n", 
			 tab_arg[0] );
		exit(-1);
	}

	strcpy( nomprog , tab_arg[0] );
	strcpy( fich_mer , tab_arg[1] );
	
	// Variables
	time_t derniereModif = time(NULL);
	int tpsModifRecente = 1; 			// En secondes
	int fd;								// Descripteur du fichier mer
	int fin = 0;						// Arrete vision quand un bateau a gagne
	int initFait = 0;
	int nbBateaux;


	printf("\n%s : ----- Debut de l'affichage de la mer ----- \n", nomprog );
	
	mer_initialiser(tab_arg[1], LIGNES, COLONNES);
	
	if( ( fd = open( fich_mer , O_RDONLY | O_CREAT , 0666)) == -1 ) {
		printf("Erreur lors de l'ouverture du fichier mer\n");
		return(ERREUR);
	}
	mer_afficher(fd);
	

	// On ne fait quelque chose que si le fichier mer a ete recemment modifie
	while(!fin || !initFait) {
		if(ModifRecente(tab_arg[1], tpsModifRecente) && derniereModif != time(NULL)) {
			while(HeaderVerrou(fd));
			
			mer_afficher(fd);

			derniereModif = time(NULL);
			
			mer_nb_bateaux_lire(fd, &nbBateaux);
			
			initFait = (nbBateaux >= 2 || initFait);
			fin = (nbBateaux == 1); 
		}
	}
	
	close(fd);

	printf("\n%s : --- Arret de l'affichage de la mer ---\n", nomprog );

	exit(0);
}
