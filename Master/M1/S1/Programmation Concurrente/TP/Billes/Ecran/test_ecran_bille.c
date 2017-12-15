#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include <ecran.h>

booleen_t fini = FAUX ; 

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
  char suite[8] ; 

  signal( SIGINT , arret ) ; 

  printf("\n\n\n\t===========Debut %s==========\n\n" , argv[0] );

  if( argc != 3 ) 
    {
      printf( " Programme de test sur l'affichage de l'aire avec ncurses\n" );
      printf( " usage : %s <Hauteur de l'aire> <Largeur de l'aire>\n" , argv[0] );
      exit(0); 
    }

  int Hauteur = atoi( argv[1] ) ;
  int Largeur = atoi( argv[2] ) ; 

  srand( getpid() ) ;

  printf("Creation de l'aire %dX%d\n" , Hauteur , Largeur ) ;
  if( ( A = aire_creer( Hauteur , Largeur ) ) == AIRE_NULL )
    {
      printf("Pb creation aire\n");
      exit(-1) ;
    }


  coord_t * hg = coord_creer( 3 , 3 ) ;
  coord_t * bd = coord_creer( Hauteur-3 , Largeur-3 ) ;
  printf("Creation d'une zone sur l'aire:") ;
  printf(" coin haut-gauche : ") ; coord_afficher(hg) ; 
  printf(" coin bas-droite  : ") ; coord_afficher(bd) ;
  printf("\n") ; 
  if( ( cr = aire_zone_creer( A , hg , bd ) ) ) 
    {
      printf("Erreur sur la creation d'une zone sur l'aire, cr = %d\n" , cr ) ;
      erreur_afficher(cr) ; 
      printf("\n") ; 
      exit(-1);
    }

  printf("Creation de la bille\n" ) ;
  bille_t * bille = BILLE_NULL ; 
  if( ( bille = bille_creer( direction_random() ,
			     rand()%BILLE_VITESSE_MAX , 
			     COORD_NULL , 
			     '*' ) ) == BILLE_NULL )
    {
      printf("Pb creation bille\n");
      exit(-1) ;
    }

  printf( "Positionnement de  la bille sur l'aire\n") ; 
  if( ( cr = aire_bille_positionner( A , bille ) ) )
    {
      printf( "Pb lors du positionnement de la bille") ; 
      erreur_afficher(cr) ; 
      exit(-1) ; 
    }

  printf("Affichage de l'aire\n");
  aire_afficher(A) ; 
  printf("Tapez sur une touche pour continuer..." ) ;
  scanf( "%s" , suite ) ; 
 
  if( ( ecran = ecran_creer(A) ) == ECRAN_NULL )
    {
      printf("Pb creation ecran\n");
      exit(-1) ;
    }

  ecran_afficher(  ecran , A )  ;
  ecran_message_afficher( ecran , "Envoyez un signal pour continuer" ) ;

  pause() ;

  /* Affichage des messages avec temporisation pour avoir le temps de les voir */
  ecran_message_pause_afficher( ecran , "Test deplacement d'une bille: creation de la bille" ) ;

  ecran_message_afficher( ecran , "Deplacement jusqu'a un signal") ;

  /* Deplacement de la bille de l'aire */
  while( (!fini) && bille_active(bille) ) 
    {
      if( ecran_bille_deplacer( ecran , A, bille ) ) 
	{
	  ecran_message_pause_afficher( ecran , "Pb lors du deplacement de la bille") ; 
	  ecran_stderr_afficher( ecran ) ;
	  goto fin ;
	}	
      
      if( bille_active(bille) )
	{
	  /* Arret sur image de ce mouvement pendant une duree inversement proportionnelle a sa vitesse */
	  ecran_bille_temporiser(bille) ; 
	}
    }
  
  /* Desintegration */
  ecran_message_afficher( ecran , "Desintegration de la bille" ) ; 
  ecran_bille_desintegrer( ecran , bille ) ;

 fin : 
  ecran_message_pause_afficher( ecran , "Arret" ) ; 


  ecran_message_pause_afficher( ecran , "Destruction de la structure ecran" ) ; 
  ecran_detruire(&ecran)  ; 

  printf("\nDestruction aire\n" ) ; 
  aire_detruire(&A)  ; 

  printf("\n\n\t===========Fin %s==========\n\n" , argv[0] );

  return(0) ;
}

