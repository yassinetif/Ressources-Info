#include <stdio.h>
#include <stdlib.h>

#include <case.h>
#include <zone.h>

#define N 10 


int
main( int argc , char * argv[] ) 
{
  case_t * Case = CASE_NULL ;


  printf("\n\n\n\t===========Debut %s==========\n\n" , argv[0] );

  printf("Creation d'une case libre hors zone\n") ;
  Case = case_creer() ;
 
  case_afficher( Case ) ;
  printf("\n");

  printf("Ecriture d'une case avec une bille hors zone\n") ;
  coord_t * coord = coord_creer( 10, 10  ) ;
  bille_t * bille = bille_creer( NORD , 99 , coord , '*' ) ;
  case_bille_poser( Case , bille ) ;

  case_afficher( Case ) ;
  printf("\n");

  case_detruire( &Case) ;

  printf("Creation d'une case libre dans zone\n") ;
  Case = case_creer() ;
  
  coord_t * hg = coord_creer( 11 , 11 ) ; 
  coord_t * bd = coord_creer( 99 , 99 ) ; 
  zone_t * zone = zone_creer( hg , bd ) ; 
  liste_t * zones = liste_creer( cb_zone_referencer , cb_zone_reference_effacer ) ; 
  liste_enfiler( zones , zone ) ; 

  case_zones_ecrire( Case , zones ) ; 

  case_afficher( Case ) ;
  printf("\n");


  printf("Ecriture d'une case avec une bille dans zone\n") ;
  case_bille_poser( Case , bille ) ;
  case_afficher( Case ) ;
  printf("\n");


  
  printf("Comparaison de 2 cases\n") ;
  case_t * Case2 = CASE_NULL ; 
  case_copier( &Case2 , Case ) ; 

  int cmp = case_comparer( Case , Case2 ) ;
  if( cmp == 0 )
    {
      case_afficher(Case) ; 
      printf( " == " ) ;
      case_afficher(Case2) ; 
      printf( " --> OK \n" ) ;
    }
  else
    {
      case_afficher(Case) ;
      printf( " != " ) ;
      case_afficher(Case2) ;
      printf( " --> KO !!! \n" ) ;
    }

  
  case_bille_enlever( Case2 ) ;
  cmp = case_comparer( Case , Case2 ) ;
  if( cmp == 0 )
    {
      case_afficher(Case) ; 
      printf( " == " ) ;
      case_afficher(Case2) ; 
      printf( "--> KO !!! \n" ) ;
    }
  else
    {
      case_afficher(Case) ;
      printf( " != " ) ;
      case_afficher(Case2) ;
      printf( " --> OK \n" ) ;
    }
    

  printf("\nDestruction de la case\n" ) ;
  bille_detruire( &bille ) ; 
  case_detruire( &Case )  ; 
  case_detruire( &Case2 )  ; 

  printf("\n\n\t===========Fin %s==========\n\n" , argv[0] );

  return(0) ;
}

