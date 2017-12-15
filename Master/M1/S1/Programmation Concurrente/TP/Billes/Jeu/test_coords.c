#include <stdio.h>
#include <stdlib.h>

#include <coord.h>
#include <liste.h>

#define NB_COORDS 10 


int
main( int argc , char * argv[] ) 
{
  err_t cr = OK ; 
  liste_t * liste_coords = NULL ;
  coord_t * tab_coords[NB_COORDS] ;
  int i = 0 ;   
  liste_id_t nb_coords ;

  printf("\n\n\n\t===========Debut %s==========\n\n" , argv[0] );
  

  /*----------------------------------*/

  printf("Creation des variables de travail: Preparation du vecteur des coords\n");
  for(i=0 ; i<NB_COORDS ; i++ ) 
    {
      tab_coords[i] = coord_creer( i , NB_COORDS-i ) ;
    }

  /*----------------------------------*/

  printf("\n----- Test pour Liste NON PROPRIETAIRE des coords -----\n\n") ;
  printf("\nCreation d'une liste de coords (les coords sont referencees)\n") ; 
  if( (liste_coords = liste_creer( cb_coord_referencer , cb_coord_reference_effacer )) == NULL )
    printf("Pb lors de la creation de la liste de coords\n" ) ; 

  printf("\nAffectation de la liste des coords\n");
  for( i=0 ; i<NB_COORDS ; i++ )
    if( (cr = liste_enfiler( liste_coords , tab_coords[i] )) ) 
      printf("Pb lors de l'affectation de l'element %d dans la liste des coords, cr = %d\n" , i , cr ) ;

  printf("\nTest des methodes d'acces:\n");
  printf("\tNombre des coords=%ld\n" , liste_taille( liste_coords )) ;

  printf("\tLecture element par element de la liste des coords\n");
  nb_coords = liste_taille(liste_coords) ; 
  for( i=0 ; i<nb_coords ; i++ )
    {
      coord_afficher((coord_t *)liste_acceder( liste_coords  , i ) ) ;      
    }

  printf("\n\tAffichage de la liste des coords\n"); 
  liste_afficher( liste_coords , cb_coord_afficher , '\n' );

  printf("\n\tDestruction de la liste des coords (les coords ne sont pas detruites)\n") ; 
  if( (cr = liste_detruire( &liste_coords ) ) )
    printf("Pb lors de la destruction de la liste de coords, cr = %d\n" , cr ) ; 


 /*----------------------------------*/

  printf("\n----- Test pour Liste PROPRIETAIRE des coords -----\n\n") ;
  printf("\nCreation d'une liste de coords (les coords sont copiees)\n") ; 
  if( (liste_coords = liste_creer( cb_coord_copier , cb_coord_detruire )) == NULL )
    printf("Pb lors de la creation de la liste de coords\n" ) ; 

  printf("\nAffectation de la liste des coords\n");
  for( i=0 ; i<NB_COORDS ; i++ )
    if( (cr = liste_enfiler( liste_coords , tab_coords[i] )) ) 
      printf("Pb lors de l'affectation de l'element %d dans la liste des coords, cr = %d\n" , i , cr ) ;

  printf("\nTest des methodes d'acces:\n");
  printf("\tNombre des coords=%ld\n" , liste_taille( liste_coords )) ;

  printf("\tLecture element par element de la liste des coords\n");
  nb_coords = liste_taille(liste_coords) ; 
  for( i=0 ; i<nb_coords ; i++ )
    {
      coord_afficher((coord_t *)liste_acceder( liste_coords  , i ) ) ;      
    }

  printf("\n\tAffichage de la liste des coords\n"); 
  liste_afficher( liste_coords , cb_coord_afficher , '\n' );

  printf("\n\tDestruction de la liste des coords (les coords copiees sont detruites)\n") ; 
  if( (cr = liste_detruire( &liste_coords ) ) )
    printf("Pb lors de la destruction de la liste de coords, cr = %d\n" , cr ) ; 

  /*----------------------------------*/

  printf("\nDestruction des variables de travail: vecteur des coords\n");
  for(i=0 ; i<NB_COORDS ; i++ ) 
    {
      if( ( cr = coord_detruire( &(tab_coords[i]) ) ) )
	printf("Pb lors de la destruction de la  coords %d, cr = %d\n" , i , cr ) ; 
    }

  printf("\n\n\t===========Fin %s==========\n\n" , argv[0] );

  return(0) ;
}

