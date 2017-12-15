#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <liste.h>
#include <bille.h>

#define NB_BILLES 10 


int
main( int argc , char * argv[] ) 
{
  err_t cr = OK ; 
  liste_t * liste_billes = NULL ;
  bille_t * tab_billes[NB_BILLES] ;
  int i = 0 ; 
  liste_id_t nb_billes ;

  printf("\n\n\n\t===========Debut %s==========\n\n" , argv[0] );

  srand(getpid() ) ;

  printf(" Creation des variables de travail: Preparation du vecteur des billes\n");
  coord_t * coord = coord_creer( 0 , 0 ) ; 
  for(i=0 ; i<NB_BILLES ; i++ ) 
    {
      coord_ecrire( coord , i , i ) ;
      tab_billes[i] = bille_creer((NORD+i)%8 , i , coord , 'A'+i ) ;
    }

  /*----------------------------------*/

  printf("\n----- Test pour Liste NON PROPRIETAIRE des billes -----\n\n") ;
  printf("\nCreation d'une liste de billes (les billes sont referencees)\n") ; 
  if( (liste_billes = liste_creer( cb_bille_referencer , cb_bille_reference_effacer )) == NULL )
    printf("Pb lors de la creation de la liste de billes\n" ) ; 

  printf("\nAffectation de la liste des billes\n");
  for( i=0 ; i<NB_BILLES ; i++ )
    if( (cr = liste_enfiler( liste_billes , tab_billes[i] )) ) 
      printf("Pb lors de l'affectation de l'element %d dans la liste des billes, cr = %d\n" , i , cr ) ;

  printf("\nTest des methodes d'acces:\n");
  printf("\tNombre des billes=%ld\n" , liste_taille( liste_billes )) ;

  printf("\tLecture element par element de la liste des billes\n");
  nb_billes = liste_taille(liste_billes) ; 
  for( i=0 ; i<nb_billes ; i++ )
    {
      bille_struct_afficher((bille_t *)liste_acceder( liste_billes  , i ) ) ;      
    }

  printf("\n\tAffichage de la liste des billes\n"); 
  liste_afficher( liste_billes , cb_bille_afficher , '\n' );

  printf("\n\tDestruction de la liste des billes (les billes ne sont pas detruites)\n") ; 
  if( (cr = liste_detruire( &liste_billes ) ) )
    printf("Pb lors de la destruction de la liste de billes, cr = %d\n" , cr ) ; 


 /*----------------------------------*/

  printf("\n----- Test pour Liste PROPRIETAIRE des billes -----\n\n") ;
  printf("\nCreation d'une liste de billes (les billes sont copiees)\n") ; 
  if( (liste_billes = liste_creer( cb_bille_copier , cb_bille_detruire )) == NULL )
    printf("Pb lors de la creation de la liste de billes\n" ) ; 

  printf("\nAffectation de la liste des billes\n");
  for( i=0 ; i<NB_BILLES ; i++ )
    if( (cr = liste_enfiler( liste_billes , tab_billes[i] )) ) 
      printf("Pb lors de l'affectation de l'element %d dans la liste des billes, cr = %d\n" , i , cr ) ;

  printf("\nTest des methodes d'acces:\n");
  printf("\tNombre des billes=%ld\n" , liste_taille( liste_billes )) ;

  printf("\tLecture element par element de la liste des billes\n");
  nb_billes = liste_taille(liste_billes) ; 
  for( i=0 ; i<nb_billes ; i++ )
    {
      bille_struct_afficher((bille_t *)liste_acceder( liste_billes  , i ) ) ;      
    }

  printf("\n\tAffichage de la liste des billes\n"); 
  liste_afficher( liste_billes , cb_bille_afficher , '\n' );

  printf("\n\tDestruction de la liste des billes (les billes copiees sont detruites)\n") ; 
  if( (cr = liste_detruire( &liste_billes ) ) )
    printf("Pb lors de la destruction de la liste de billes, cr = %d\n" , cr ) ; 

  /*----------------------------------*/

  printf("\nDestruction des variables de travail: vecteur des billes\n");
  for(i=0 ; i<NB_BILLES ; i++ ) 
    {
      if( ( cr = bille_detruire( &(tab_billes[i]) ) ) )
	printf("Pb lors de la destruction de la  billes %d, cr = %d\n" , i , cr ) ; 
    }

  printf("\n\n\t===========Fin %s==========\n\n" , argv[0] );

  return(0) ;
}
