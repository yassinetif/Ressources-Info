#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <case.h>
#include <liste.h>

#define NB_CASES 10 


int
main( int argc , char * argv[] ) 
{
  err_t cr = OK ; 
  liste_t * liste_cases = NULL ;
  case_t * tab_cases[NB_CASES] ;
  int i = 0 ;   
  liste_id_t nb_cases ;

  bille_t * tab_billes[NB_CASES] ;
  int b = 0 ;

  coord_t * hg = COORD_NULL ;
  coord_t * bd = COORD_NULL ;
  zone_t * zone = ZONE_NULL ;
  liste_t * zones = LISTE_NULL ; 

  printf("\n\n\n\t===========Debut %s==========\n\n" , argv[0] );
  
 /*----------------------------------*/

  srand(getpid()) ; 

  /* Creation d'une liste de une zone */
  hg = coord_creer( 10 , 10 ) ;
  bd = coord_creer( 99 , 99 ) ; 
  zone = zone_creer( hg , bd ) ;
  zones = liste_creer( cb_zone_referencer , cb_zone_reference_effacer ) ; 
  liste_enfiler( zones , zone ) ; 

  printf("Creation des variables de travail: Preparation du vecteur des cases\n") ; 
  for(i=0 ; i<NB_CASES ; i++ ) 
    {
      tab_cases[i] = case_creer() ;
      /* Pose eventuelle d'une bille sur cette case */
      if(rand()%2) 
	{		 
	  tab_billes[b] = bille_creer( direction_random() , 10+i , COORD_NULL , '*' ) ; 
	  b++ ; 
	  case_bille_poser( tab_cases[i] , tab_billes[b] ) ; 
	}
      /* Appartenance eventuelle de cette case a une zone */
      if(rand()%2) 
	{		 
	  case_zones_ecrire( tab_cases[i] , zones ) ; 
	}
    }

  /*----------------------------------*/

  printf("\n----- Test pour Liste NON PROPRIETAIRE des cases -----\n\n") ;

  printf("\nCreation d'une liste de cases (les cases sont referencees)\n") ; 
  if( (liste_cases = liste_creer( cb_case_referencer , cb_case_reference_effacer )) == NULL )
    printf("Pb lors de la creation de la liste de cases\n" ) ; 

  printf("\nAffectation de la liste des cases\n");
  for( i=0 ; i<NB_CASES ; i++ )
    if( (cr = liste_enfiler( liste_cases , tab_cases[i] )) ) 
      printf("Pb lors de l'affectation de l'element %d dans la liste des cases, cr = %d\n" , i , cr ) ;

  printf("\nTest des methodes d'acces:\n");
  printf("\tNombre des cases=%ld\n" , liste_taille( liste_cases )) ;

  printf("\tLecture element par element de la liste des cases\n");
  nb_cases = liste_taille(liste_cases) ; 
  for( i=0 ; i<nb_cases ; i++ )
    {
      case_struct_afficher((case_t *)liste_acceder( liste_cases  , i ) ) ;      
    }

  printf("\n\tAffichage de la liste des cases\n"); 
  liste_afficher( liste_cases , cb_case_struct_afficher , '\n' );

  printf("\n\tDestruction de la liste des cases (les cases ne sont pas detruites)\n") ; 
  if( (cr = liste_detruire( &liste_cases ) ) )
    printf("Pb lors de la destruction de la liste de cases, cr = %d\n" , cr ) ; 


 /*----------------------------------*/

  printf("\n----- Test pour Liste PROPRIETAIRE des cases -----\n\n") ;
  printf("\nCreation d'une liste de cases (les cases sont copiees)\n") ; 
  if( (liste_cases = liste_creer( cb_case_copier , cb_case_detruire )) == NULL )
    printf("Pb lors de la creation de la liste de cases\n" ) ; 

  printf("\nAffectation de la liste des cases\n");
  for( i=0 ; i<NB_CASES ; i++ )
    if( (cr = liste_enfiler( liste_cases , tab_cases[i] )) ) 
      printf("Pb lors de l'affectation de l'element %d dans la liste des cases, cr = %d\n" , i , cr ) ;

  printf("\nTest des methodes d'acces:\n");
  printf("\tNombre des cases=%ld\n" , liste_taille( liste_cases )) ;

  printf("\tLecture element par element de la liste des cases\n");
  nb_cases = liste_taille(liste_cases) ; 
  for( i=0 ; i<nb_cases ; i++ )
    {
      case_struct_afficher((case_t *)liste_acceder( liste_cases  , i ) ) ;      
    }

  printf("\n\tAffichage de la liste des cases\n"); 
  liste_afficher( liste_cases , cb_case_struct_afficher , '\n' );

  printf("\n\tDestruction de la liste des cases (les cases copiees sont detruites)\n") ; 
  if( (cr = liste_detruire( &liste_cases ) ) )
    printf("Pb lors de la destruction de la liste de cases, cr = %d\n" , cr ) ; 

  /*----------------------------------*/

  printf("\nDestruction des variables de travail: vecteur des cases\n");
  for(i=0 ; i<NB_CASES ; i++ ) 
    {
      if( ( cr = case_detruire( &(tab_cases[i]) ) ) )
	printf("Pb lors de la destruction de la  cases %d, cr = %d\n" , i , cr ) ; 
    }

  printf("\n\n\t===========Fin %s==========\n\n" , argv[0] );

  return(0) ;
}



