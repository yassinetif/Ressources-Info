#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <mvt_bille.h>

int
main( int argc , char * argv[] ) 
{
  aire_t * aire  = NULL ;
  err_t cr = OK ;
  char suite[8] ; 

  printf("\n\n\n\t===========Debut %s==========\n\n" , argv[0] );

  if( argc != 4 ) 
    {
      printf( " Programme de test de mouvements de plusieurs billes sur une aire\n" );
      printf( " usage : %s <Hauteur de l'aire> <Largeur de l'aire> <nb billes>\n" , argv[0] );
      exit(0); 
    }

  int Hauteur  = atoi( argv[1] ) ;
  int Largeur  = atoi( argv[2] ) ; 
  int NbBilles = atoi( argv[3] ) ; 
  printf( " \nTest sur une aire de %dX%d et %d billes\n" , Hauteur , Largeur , NbBilles );

  srand( getpid() ) ;

  printf("Creation de l'aire %dX%d\n" , Hauteur , Largeur ) ;
  if( ( aire = aire_creer( Hauteur , Largeur ) ) == AIRE_NULL )
    {
      printf("Pb creation aire\n");
      exit(-1) ;
    }

  printf("Creation des %d billes\n" , NbBilles) ;
  bille_t ** tab_billes = (bille_t **)malloc( sizeof(bille_t *) * NbBilles ) ; 
  int b ;
  for( b=0 ; b<NbBilles ; b++ )
    {
      if( ( tab_billes[b] = bille_creer( direction_random() ,
					 rand()%BILLE_VITESSE_MAX , 
					 COORD_NULL , 
					 '*' ) ) == BILLE_NULL )
	{
	  printf("Pb creation bille bille %d\n" , b );
	  exit(-1) ;
	}
    }

  for( b=0 ; b<NbBilles ; b++ ) 
    {
      printf( "Positionnement de la  copie de la bille %d\n" , b ) ; 
      if( ( cr = aire_bille_positionner( aire , tab_billes[b] ) ) )
	{
	  printf( "Pb lors du positionnement de la bille %d" , b ) ; 
	  erreur_afficher(cr) ; 
	  exit(-1) ; 
	}
    }

  printf("Affichage de l'aire\n");
  aire_afficher(aire) ; 
  printf("Tapez sur une touche pour continuer..." ) ;
  scanf( "%s" , suite ) ; 
 
  /* Recuperation des billes de l'aire */
  liste_t * liste_billes = LISTE_NULL ; 
  liste_id_t nb_billes = 0 ;  
  bille_t * bille = BILLE_NULL ; 
  while( ! aire_vide(aire) )
    { 
      liste_billes = aire_billes_lire(aire) ; 
      nb_billes = liste_taille(liste_billes) ; 

      for( b=0 ; b<nb_billes ; b++ )
	{
	  /* Deplacement d'une bille */
	  bille = liste_acceder( liste_billes , b ) ;

	  if( ( cr = mvt_bille_deplacer( bille , aire ) ) )
	    {
	      fprintf( stderr, "Pb lors du deplacement de la bille %d\n", b ) ;
	      aire_afficher( aire ) ;
	      goto fin ;
	    }

	  if( bille_active(bille) )
	    {
	      printf( "Bille %d : ACTIVE - Vitesse = %d , nb deplacements = %d\n" , 
		      b , bille_vitesse_lire(bille) , bille_nb_deplacements_lire(bille) ) ;
	    }
	  else
	    {
	      printf( "Bille %d : DESINTEGRATION\n" , b ) ;

	      if( aire_bille_enlever( aire , bille ) )
		{
		  fprintf( stderr, "Pb lors de la l'enlevement de la bille %d", b ) ; 
		  aire_afficher( aire ) ; 
		  goto fin ;
		}

	      if( bille_detruire(&bille) )
		{
		  fprintf( stderr, "Pb lors de la destruction de la bille %d", b ) ; 
		  aire_afficher( aire ) ; 
		  goto fin ;
		}

	      aire_afficher(aire) ; 
	    }
	}
    }
 
  printf( "PLus de billes sur l'aire\n" ); 
  aire_afficher(aire) ; 

 fin : 
  printf("\nDestruction aire\n" ) ; 
  aire_detruire( &aire)  ; 

  printf("\n\n\t===========Fin %s==========\n\n" , argv[0] );

  return(0) ;
}

