/* 
 * Programme pour processus navire :
 */

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <mer.h>
#include <bateaux.h>

/* 
 * VARIABLES GLOBALES (utilisees dans les handlers)
 */

int energie; 

/*
 * Handlers 
 */
void SignalRecevoir(int signal, void * context){
  energie -= BATEAU_MAX_ENERGIE / 4;
}

/*
 * Programme Principal 
 */

int
main( int nb_arg , char * tab_arg[] )
{
  char nomprog[128] ;
  pid_t pid_amiral ;
  pid_t pid_bateau = getpid()  ;

  /*----------*/

  /* 
   * Capture des parametres 
   */

  if( nb_arg != 2 )
    {
      fprintf( stderr , "Usage : %s <pid amiral>\n", 
	       tab_arg[0] );
      exit(-1);
    }

  /* Nom du programme */
  strcpy( nomprog , tab_arg[0] );
  sscanf( tab_arg[1] , "%d" , &pid_amiral ) ; 

  /* Initialisation de la generation des nombres pseudo-aleatoires */
  srandom((unsigned int)pid_bateau);


  /* Affectation du niveau d'energie */
  energie = BATEAU_MAX_ENERGIE ;
  
  printf( "\n\n--- Debut bateau [%d]---\n\n" , pid_bateau );
  
  printf("Energie du bateau %i : %i\n", pid_bateau, energie);

  /*
   * Deroulement du jeu 
   */

  struct sigaction action;
  action.sa_flags = 0;
  action.sa_handler = SignalRecevoir;
  sigaction(SIGUSR2, &action, NULL);

  while(energie){
    kill(pid_amiral, SIGUSR1); //Envoie d'un signal à l'amiral   
    sleep(2);
  }

  printf( "\n\n--- Arret bateau (%d) ---\n\n" , pid_bateau );

  exit(0);
}