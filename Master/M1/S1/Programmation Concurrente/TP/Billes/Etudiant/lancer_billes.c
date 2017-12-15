#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>

#include <ecran.h>

booleen_t fini = FAUX ; 


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


/*
Pour qu'une bille se déplace, on utilise la fonction :

err_t ecran_bille_deplacer( ecran_t * ecran , 
          aire_t * aire ,
          bille_t * bille ) 

On a donc besoin d'avoir dans le thread une référence de l'écran, de l'aire et de la bille.
Une fonction thread ne pouvant avoir de paramètres a part un seul argument (void *arg), on utilise
une structure pour tout avoir
*/


typedef struct{
  int numBille;
  ecran_t * ecran; 
  aire_t * A;
  bille_t * bille;
} thread_args_t;




static
void fonc(void *args){

  char mess[ECRAN_LG_MESS] ;

  thread_args_t *donneesBille = (thread_args_t*) args;

  int numBille = donneesBille->numBille;
  aire_t *A = donneesBille->A;
  ecran_t *ecran = donneesBille->ecran;
  bille_t *bille = donneesBille->bille ;

  /*Entree section critique*/
  while( (pthread_mutex_lock(&mutex) == 0)) {

    if( ecran_bille_deplacer( ecran , A, bille ) ){
        ecran_message_afficher( ecran , "La bille de déplace" ) ;
        pthread_mutex_unlock( &mutex);
        return;
    }

    if( bille_active(bille) ){
        ecran_afficher( ecran , A );
        pthread_mutex_unlock(&mutex);
        /* Arret sur image de ce mouvement pendant une duree inversement proportionnelle a sa vitesse */
        ecran_bille_temporiser(bille) ; 
    }else{
        /* Desintegration de la bille */
        sprintf( mess , "Desintegration de la bille %d" , numBille ) ;
        ecran_message_afficher( ecran , mess ) ; 
        ecran_bille_desintegrer( ecran , bille ) ;

        /* On enleve cette bille de l'aire */
        if( aire_bille_enlever( A , bille ) ) {
          sprintf( mess , "Pb lors de l'enlevement de la bille %d sur l'aire", numBille ) ; 
          ecran_message_pause_afficher( ecran , mess ) ; 
          ecran_stderr_afficher( ecran ) ;
        }

        if( bille_detruire( &bille ) ) {
          sprintf( mess , "Pb lors de la destruction de la bille %d", numBille ) ; 
          ecran_message_pause_afficher( ecran , mess ) ; 
          ecran_stderr_afficher( ecran ) ;
        }

        /*Sortie section critique*/
        pthread_mutex_unlock(&mutex);
        return;
    }
  }


  /*Sortie section critique*/
  pthread_mutex_unlock(&mutex);

  return;
}

static
void arret( int sig ) 
{
  static int cpt = 0 ; 
  
  cpt++ ; 

  switch( cpt ) 
    {
    case 1 :
      break ; 
    case 2 :
      break ;
    case 3 :
      fini = VRAI ; 
      break ;
    default :
      break  ; 
    }
  return ; 
}

int
main( int argc , char * argv[] ) 
{
  aire_t * A  = NULL ;
  err_t cr = OK ;
  ecran_t * ecran  = NULL ; 
  char mess[ECRAN_LG_MESS] ;

  signal( SIGINT , arret ) ; 

  printf("\n\n\n\t===========Debut %s==========\n\n" , argv[0] );

  if( argc != 4 ) 
    {
      printf( " Programme de test sur l'affichage de l'aire avec plusieurs billes\n" );
      printf( " usage : %s <Hauteur de l'aire> <Largeur de l'aire> <nb billes>\n" , argv[0] );
      exit(0); 
    }

  int Hauteur  = atoi( argv[1] ) ;
  int Largeur  = atoi( argv[2] ) ; 
  int NbBilles = atoi( argv[3] ) ; 
  printf( " \nTest sur une aire de %dX%d et %d billes\n" , Hauteur , Largeur , NbBilles );

  srand( getpid() ) ;

  /* Creation et affichage de l'aire */
  printf("Creation de l'aire %dX%d\n" , Hauteur , Largeur ) ;
  if( ( A = aire_creer( Hauteur , Largeur ) ) == AIRE_NULL )
    {
      printf("Pb creation aire\n");
      exit(-1) ;
    }

  aire_afficher(A) ; 

  /* Creation et affichage de l'ecran */
  if( ( ecran = ecran_creer(A) ) == ECRAN_NULL )
    {
      printf("Pb creation ecran\n");
      exit(-1) ;
    }

  ecran_afficher(  ecran , A )  ;
  ecran_message_afficher( ecran , "Envoyez un signal pour continuer" ) ;
  pause() ;

  /* Creation des billes */
  sprintf( mess , "Creation des %d billes\n" , NbBilles) ;
  ecran_message_pause_afficher( ecran , mess ); 

  bille_t ** tab_billes = (bille_t **)malloc( sizeof(bille_t *) * NbBilles ) ; 
  int b ;
  for( b=0 ; b<NbBilles ; b++ )
    {
      if( ( tab_billes[b] = bille_creer( direction_random() ,
					 rand()%BILLE_VITESSE_MAX , 
					 COORD_NULL , 
					 '*' ) ) == BILLE_NULL )
	{
	  sprintf( mess , "Pb creation bille bille %d\n" , b );
	  ecran_message_pause_afficher( ecran , mess  ) ; 
	  exit(-1) ;
	}
    }

  /* Positionnements et affichages des billes */
  ecran_message_pause_afficher( ecran , "Positionnements des billes sur l'ecran" ) ;
  for( b=0 ; b<NbBilles ; b++ ) 
    {
      sprintf( mess , "Pose de la bille %d\n" , b ) ; 
      ecran_message_afficher( ecran , mess ) ; 
      if( ( cr = ecran_bille_positionner( ecran , A , tab_billes[b] ) ) )
	{
	  sprintf( mess , "Pb lors de la pose de la bille %d" , b ) ; 
	  ecran_message_pause_afficher( ecran , mess ) ;
	  erreur_afficher(cr) ; 
	  ecran_stderr_afficher(ecran) ; 
	  exit(-1) ; 
	}
    }

  ecran_message_afficher( ecran , "Envoyez un signal pour continuer" ) ;
  pause() ;

  liste_t * liste_billes = aire_billes_lire(A) ;
  liste_id_t nb_billes = liste_taille(liste_billes) ;
  bille_t * bille = BILLE_NULL ;

  pthread_t pbilles[nb_billes];

  /*On creer les arguments de la fonction fonc (thread) en les plaçant dans une structure*/
  thread_args_t args;
  args.A = A;
  args.ecran = ecran;

  /*Entree section critique*/
  pthread_mutex_lock(&mutex);
  for(b=0; b<nb_billes; b++) {
    bille = liste_acceder( liste_billes , b ) ;
    args.bille = bille;
    args.numBille = b;
    pthread_create(&pbilles[b], NULL, (void*)fonc, (void*)&args);
    usleep(500);
  }

  /*Sortie section critique*/
  pthread_mutex_unlock(&mutex);

  ecran_message_pause_afficher( ecran , "Arret" ) ; 

  ecran_message_pause_afficher( ecran , "Fin des threads" ) ;
  for(b=0; b<nb_billes; b++) {
    pthread_join(pbilles[b], NULL);
  }


  ecran_message_pause_afficher( ecran , "Destruction de la structure ecran" ) ; 
  ecran_detruire(&ecran)  ;  

  printf("\nDestruction aire\n" ) ; 
  aire_detruire( &A)  ; 

  printf("\n\n\t===========Fin %s==========\n\n" , argv[0] );

  return(0) ;
}

