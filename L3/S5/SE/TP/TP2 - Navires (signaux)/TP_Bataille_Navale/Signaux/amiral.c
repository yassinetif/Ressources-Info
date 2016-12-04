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


/* 
 * VARIABLES GLOBALES (utilisees dans les handlers)
 */

char Nom_Prog[256] ;

/*
 * FONCTIONS LOCALES
 */


/*
 * Programme Principal
 */
int
main( int nb_arg , char * tab_arg[] )
{
     char fich_mer[128] ;

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

     strcpy( Nom_Prog , tab_arg[0] );
     strcpy( fich_mer , tab_arg[1] );
     
     /*
      * Affichage pid bateau amiral 
      */
     
     printf(" PID bateau amiral = %d\n" , getpid() ) ;

     /* Initialisation de la generation des nombres pseudo-aleatoires */
     srandom((unsigned int)getpid());
 
     /***********/
     /* A FAIRE */
     /***********/

     printf("\n\n\t----- Fin du jeu -----\n\n");
     
     exit(0);
}

