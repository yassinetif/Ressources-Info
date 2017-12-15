#include <stdio.h>
#include <stdlib.h>

#include <zone.h>

#define N 10 


int
main( int argc , char * argv[] ) 
{
  zone_t * Zone  ;
  coord_t * hg = coord_creer(1,2) ;
  coord_t * bd = coord_creer(11,12 ) ;

  printf("\n\n\n\t===========Debut %s==========\n\n" , argv[0] );

  printf("Creation d'une zone [1,2] - [11,12]\n") ;
  Zone = zone_creer(hg,bd) ;
  printf("\tAffichage de la  zone creee\n") ;
  zone_struct_afficher( Zone ) ;
  printf("\n");

  coord_ecrire( hg , 3 , 4 ) ;
  coord_ecrire( bd , 33 , 44  ) ;
  zone_t * Zone2 = zone_creer(hg,bd) ;
  int cmp = zone_comparer( Zone , Zone2 ) ;
  if( cmp == 0 )
    {
      zone_struct_afficher(Zone) ;
      printf( " == " ) ;
      zone_struct_afficher(Zone2) ; 
      printf( " --> KO !!!! \n" ) ;
    }
  else
    {
      zone_struct_afficher(Zone) ;
      printf( " != " ) ;
      zone_struct_afficher(Zone2) ;
      printf( " --> OK\n" ) ;
    }

  zone_t * Zone3 = ZONE_NULL ;
  zone_copier( &Zone3 , Zone ) ; 
  cmp = zone_comparer( Zone , Zone3 ) ;
  if( cmp == 0 )
    {
      zone_struct_afficher(Zone) ; 
      printf( " == " ) ;
      zone_struct_afficher(Zone3) ; 
      printf( "--> OK\n" ) ;
    }
  else
    {
      zone_struct_afficher(Zone) ;
      printf( " != " ) ;
      zone_struct_afficher(Zone3) ;
      printf( " --> KO !!! \n" ) ;
    }
    

  printf("\nDestruction des zones\n" ) ;
  zone_detruire( &Zone )  ; 
  zone_detruire( &Zone2 )  ; 
  zone_detruire( &Zone3 )  ; 

  printf("\n\n\t===========Fin %s==========\n\n" , argv[0] );

  return(0) ;
}

