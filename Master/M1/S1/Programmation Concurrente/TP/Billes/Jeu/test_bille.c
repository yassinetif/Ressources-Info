#include <stdio.h>
#include <stdlib.h>

#include <bille.h>

#define N 10 


int
main( int argc , char * argv[] ) 
{
  bille_t * Bille  ;
  
  printf("\n\n\n\t===========Debut %s==========\n\n" , argv[0] );

  printf("Creation d'une bille\n") ;
  Bille = bille_creer( NORD_OUEST , 11 , COORD_NULL , 'A' ) ;
  printf("\tAffichage de la  bille creee\n") ;
  bille_struct_afficher( Bille ) ;
  printf("\n");


  printf("Ecriture d'une bille\n") ;
  coord_t * coord = coord_creer( 5, 6 ) ;
  bille_ecrire( Bille , SUD_EST , 22 , coord , 'B' ) ;
  printf("\tAffichage de la  bille affectee\n") ;
  bille_struct_afficher( Bille ) ;
  printf("\n");
 
  printf("Comparaison de 2 billes\n") ;
  bille_t * Bille2 = bille_creer( SUD_OUEST , 33 , COORD_NULL , 'C' ) ;
  int cmp = bille_comparer( Bille , Bille2 ) ;   
  if( cmp == 0 ) 
    {
      bille_struct_afficher(Bille) ;
      printf( " = \n" ) ; 
      bille_struct_afficher( Bille2 ) ;
      printf( " --> KO !!! \n" ) ;
    }
  else
    {
      bille_struct_afficher(Bille) ;
      printf( " != \n" ) ; 
      bille_struct_afficher( Bille2 ) ;
      printf( " --> OK\n" ) ;
    }

  
  bille_ecrire( Bille2 , SUD_EST , 22 , coord , 'B' ) ;
  cmp = bille_comparer( Bille , Bille2 ) ;
  if( cmp == 0 ) 
    {
      bille_struct_afficher(Bille) ;
      printf( " = \n" ) ; 
      bille_struct_afficher( Bille2 ) ;
      printf( " --> OK \n" ) ;
    }
  else
    {
      bille_struct_afficher(Bille) ;
      printf( " != \n" ) ; 
      bille_struct_afficher( Bille2 ) ;
      printf( " --> KO !!! \n" ) ;
    }  



  printf("\nDestruction des billes\n" ) ;
  bille_detruire( &Bille )  ; 
  bille_detruire( &Bille2 )  ; 


  printf("\n\n\t===========Fin %s==========\n\n" , argv[0] );

  return(0) ;
}

