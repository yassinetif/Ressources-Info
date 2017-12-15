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
      break ;
    default :
      fini = VRAI ; 
      break ;
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

  dim_t lhg = rand()%Hauteur ;
  dim_t chg = rand()%Largeur ; 
  coord_t * hg = coord_creer( lhg , chg ) ;
  coord_t * bd = coord_creer( lhg+(rand()%(Hauteur-lhg)) , chg+(rand()%(Largeur-chg)) ) ;
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
  ecran_message_afficher( ecran , mess ); 

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
  ecran_message_afficher( ecran , "Positionnement des billes sur l'aire" ) ;
  for( b=0 ; b<NbBilles ; b++ ) 
    {
      sprintf( mess , "Positionnement de la bille %d\n" , b ) ; 
      ecran_message_afficher( ecran , mess ) ; 
      if( ( cr = ecran_bille_positionner( ecran , A , tab_billes[b] ) ) )
	{
	  sprintf( mess , "Pb lors du positionnement de la bille %d" , b ) ; 
	  ecran_message_pause_afficher( ecran , mess ) ;
	  erreur_afficher(cr) ; 
	  ecran_stderr_afficher(ecran) ; 
	  exit(-1) ; 
	}
      sprintf( mess , "Positionnement de la bille numero %d en [%d,%d]"  , 
	       b , coord_lig_lire(bille_coord_lire(tab_billes[b])) , coord_col_lire(bille_coord_lire(tab_billes[b])) ) ; 
      ecran_message_afficher( ecran ,  mess ) ;
    }

  ecran_message_afficher( ecran , "Envoyez un signal pour continuer" ) ;
  pause() ;

  /* Deplacements des billes l'une apres l'autre */
  ecran_message_pause_afficher( ecran , "Test deplacement des billes, (Deplacements jusqu'a un signal)" ) ;

  liste_t * liste_billes = LISTE_NULL ; 
  liste_id_t nb_billes = 0 ;  
  bille_t * bille = BILLE_NULL ; 
  while( ! aire_vide(A) )
    { 
      liste_billes = aire_billes_lire(A) ; 
      nb_billes = liste_taille(liste_billes) ; 

      for( b=0 ; b<nb_billes ; b++ )
	{
	  /* Deplacement d'une bille */
	  bille = liste_acceder( liste_billes , b ) ;

	  if( ecran_bille_deplacer( ecran , A, bille ) ) 
	    {
	      sprintf( mess ,  "Pb lors du deplacement de la bille %d", b ) ;
	      ecran_message_pause_afficher( ecran , mess ) ; 
	      ecran_stderr_afficher( ecran ) ;
	      goto fin ;
	    }	
	  
	  if( bille_active(bille) )
	    {
	      /* Arret sur image de ce mouvement pendant une duree inversement proportionnelle a sa vitesse */
	      ecran_bille_temporiser(bille) ; 
	    }
	  else
	    {
	      /* Desintegration de la bille */
	      sprintf( mess , "Desintegration de la bille %d" , b ) ;
	      ecran_message_afficher( ecran , mess ) ; 
	      ecran_bille_desintegrer( ecran , bille ) ;

	      /* On enleve cete bille de l'aire */
	      if( aire_bille_enlever( A , bille ) )
		{
		  sprintf( mess , "Pb lors de l'enlevement de la bille %d", b ) ; 
		  ecran_message_pause_afficher( ecran , mess ) ; 
		  ecran_stderr_afficher( ecran ) ;
		  goto fin ;
		}

	      if( bille_detruire( &bille ) )
		{
		  sprintf( mess , "Pb lors de la destruction de la bille %d", b ) ; 
		  ecran_message_pause_afficher( ecran , mess ) ; 
		  ecran_stderr_afficher( ecran ) ;
		  goto fin ;
		}
	      
	    }
	}
    }
 
 fin : 
  ecran_message_pause_afficher( ecran , "Arret" ) ; 

  ecran_message_pause_afficher( ecran , "Destruction de la structure ecran" ) ; 
  ecran_detruire(&ecran)  ; 

  printf("\nDestruction aire\n" ) ; 
  aire_detruire( &A)  ; 

  printf("\n\n\t===========Fin %s==========\n\n" , argv[0] );

  return(0) ;
}

