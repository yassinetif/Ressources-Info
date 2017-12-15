#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <liste.h>
#include <aire.h>

#define NB_AIRES 10 


int
main( int argc , char * argv[] ) 
{
  err_t cr = OK ; 
  liste_t * liste_aires = NULL ;
  aire_t * tab_aires[NB_AIRES] ;
  int i = 0 ; 
  liste_id_t nb_aires ;
  bille_t * bille = bille_creer( NULLE_PART , 0 , COORD_NULL , '?' ) ; 

  printf("\n\n\n\t===========Debut %s==========\n\n" , argv[0] );

  srand(getpid() ) ;
 
  /*----------------------------------*/

  printf( "\nCreation des variables de travail: preparation vecteur des aires\n");
  for(i=0 ; i<NB_AIRES ; i++ ) 
    {
      tab_aires[i] = aire_creer( AIRE_HAUTEUR_MIN+(rand()%(AIRE_HAUTEUR_MAX-AIRE_HAUTEUR_MIN)) ,
				 AIRE_LARGEUR_MIN+(rand()%(AIRE_LARGEUR_MAX-AIRE_LARGEUR_MIN)) ) ;
      bille_ecrire( bille , 
		    direction_random() , 
		    10+i , 
		    COORD_NULL , 'A'+i ) ;
      aire_bille_poser( tab_aires[i] , 
			(dim_t)(aire_hauteur_lire(tab_aires[i]) / 2) , 
			(dim_t)(aire_largeur_lire(tab_aires[i]) / 2) , 
			bille ) ;
    }

  /*----------------------------------*/

  printf("\nCreation d'une liste de aires\n") ; 
  if( (liste_aires = liste_creer( cb_aire_referencer , cb_aire_reference_effacer )) == NULL )
    printf("Pb lors de la creation de la liste de aires\n" ) ; 

  printf("\nAffectation de la liste des aires\n");
  for( i=0 ; i<NB_AIRES ; i++ )
    if( (cr = liste_enfiler( liste_aires , tab_aires[i] )) ) 
      printf("Pb lors de l'affectation de l'element %d dans la liste des aires, cr = %d\n" , i , cr ) ;

  printf("\nTest des methodes d'acces:\n");
  printf("\tNombre des aires=%ld\n" , liste_taille( liste_aires )) ;

  printf("\tLecture element par element de la liste des aires\n");
  nb_aires = liste_taille(liste_aires) ; 
  for( i=0 ; i<nb_aires ; i++ )
    {
      aire_afficher((aire_t *)liste_acceder( liste_aires  , i ) ) ;      
    }

  printf("\tAffichage de la liste des aires\n"); 
  liste_afficher( liste_aires , cb_aire_afficher , '\n' );

  printf("\tDestruction de la liste des aires\n") ; 
  if( (cr = liste_detruire( &liste_aires ) ) )
    printf("Pb lors de la destruction de la liste de aires, cr = %d\n" , cr ) ; 

  /*----------------------------------*/

  printf( "\nDestruction des variables de travail: destruction du vecteur des aires\n");
  for(i=0 ; i<NB_AIRES ; i++ ) 
    {
      if( ( cr = aire_detruire( &tab_aires[i] ) ) )
	{
	  printf( "Pb lors de la destruction de l(aire %d, cf = %d\n" , i , cr ) ; 
	}
    }

  printf("\n\n\t===========Fin %s==========\n\n" , argv[0] );

  return(0) ;
}

