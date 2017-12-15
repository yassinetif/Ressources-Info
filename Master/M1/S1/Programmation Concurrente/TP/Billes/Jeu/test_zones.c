#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <zone.h>
#include <liste.h>

#define NB_ZONES 10 


int
main( int argc , char * argv[] ) 
{
  err_t cr = OK ; 
  liste_t * liste_zones = NULL ;
  zone_t * tab_zones[NB_ZONES] ;
  coord_t * hg = COORD_NULL ;
  coord_t * bd = COORD_NULL ;
  int i = 0 ; 
  liste_id_t nb_zones ;

  printf("\n\n\n\t===========Debut %s==========\n\n" , argv[0] );
  
  /*----------------------------------*/

  srand(getpid()) ; 

  printf("Creation des variables de travail: Preparation du vecteur des zones\n");
  hg = coord_creer(0,0) ;
  bd = coord_creer(0,0) ;
  for(i=0 ; i<NB_ZONES ; i++ ) 
    {
      coord_ecrire( hg , i , i+10 ) ;
      coord_ecrire( bd , i+10 , i+100 ) ;
      tab_zones[i] = zone_creer( hg , bd ) ;
    }

  /*----------------------------------*/

  printf("\n----- Test pour Liste NON PROPRIETAIRE des zones -----\n\n") ;
  printf("\nCreation d'une liste de zones (les zones sont referencees)\n") ; 
  if( (liste_zones = liste_creer( cb_zone_referencer , cb_zone_reference_effacer )) == NULL )
    printf("Pb lors de la creation de la liste de zones\n" ) ; 

  printf("\nAffectation de la liste des zones\n");
  for( i=0 ; i<NB_ZONES ; i++ )
    if( (cr = liste_enfiler( liste_zones , tab_zones[i] )) ) 
      printf("Pb lors de l'affectation de l'element %d dans la liste des zones, cr = %d\n" , i , cr ) ;

  printf("\nTest des methodes d'acces:\n");
  printf("\tNombre des zones=%ld\n" , liste_taille( liste_zones )) ;

  printf("\tLecture element par element de la liste des zones\n");
  nb_zones = liste_taille(liste_zones) ; 
  for( i=0 ; i<nb_zones ; i++ )
    {
      zone_struct_afficher((zone_t *)liste_acceder( liste_zones  , i ) ) ;      
    }

  printf("\n\tAffichage de la liste des zones\n"); 
  liste_afficher( liste_zones , cb_zone_struct_afficher , '\n' );

  printf("\n\tDestruction de la liste des zones (les zones ne sont pas detruites)\n") ; 
  if( (cr = liste_detruire( &liste_zones ) ) )
    printf("Pb lors de la destruction de la liste de zones, cr = %d\n" , cr ) ; 


 /*----------------------------------*/

  printf("\n----- Test pour Liste PROPRIETAIRE des zones -----\n\n") ;
  printf("\nCreation d'une liste de zones (les zones sont copiees)\n") ; 
  if( (liste_zones = liste_creer( cb_zone_copier , cb_zone_detruire )) == NULL )
    printf("Pb lors de la creation de la liste de zones\n" ) ; 

  printf("\nAffectation de la liste des zones\n");
  for( i=0 ; i<NB_ZONES ; i++ )
    if( (cr = liste_enfiler( liste_zones , tab_zones[i] )) ) 
      printf("Pb lors de l'affectation de l'element %d dans la liste des zones, cr = %d\n" , i , cr ) ;

  printf("\nTest des methodes d'acces:\n");
  printf("\tNombre des zones=%ld\n" , liste_taille( liste_zones )) ;

  printf("\tLecture element par element de la liste des zones\n");
  nb_zones = liste_taille(liste_zones) ; 
  for( i=0 ; i<nb_zones ; i++ )
    {
      zone_struct_afficher((zone_t *)liste_acceder( liste_zones  , i ) ) ;      
    }

  printf("\n\tAffichage de la liste des zones\n"); 
  liste_afficher( liste_zones , cb_zone_struct_afficher , '\n' );

  printf("\n\tDestruction de la liste des zones (les zones copiees sont detruites)\n") ; 
  if( (cr = liste_detruire( &liste_zones ) ) )
    printf("Pb lors de la destruction de la liste de zones, cr = %d\n" , cr ) ; 

  /*----------------------------------*/

  printf("\nDestruction des variables de travail: vecteur des zones\n");
  for(i=0 ; i<NB_ZONES ; i++ ) 
    {
      if( ( cr = zone_detruire( &(tab_zones[i]) ) ) )
	printf("Pb lors de la destruction de la  zones %d, cr = %d\n" , i , cr ) ; 
    }

  printf("\n\n\t===========Fin %s==========\n\n" , argv[0] );

  return(0) ;
}

