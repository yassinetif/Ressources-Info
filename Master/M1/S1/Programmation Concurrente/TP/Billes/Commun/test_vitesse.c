#include <commun.h>
#include <vitesse.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>


int
main() 
{
  vitesse_t v ; 

  srand(getpid()) ; 

  for( v = rand()%126 ; v ; v--  )
    {
      printf( "Vitesse = [" ) ;
      vitesse_afficher(v)  ; 
      printf( "] \n" ) ;
    }


  printf("\n\n Test affectation d'une vitesse\n\n" ); 
  vitesse_t s = 126 ;
  vitesse_t c = 0 ; 
  vitesse_t r = 0 ; 
  printf( " Avant affectation c = " ); vitesse_afficher( c ) ; 
  printf( " ; s = " ); vitesse_afficher( s ) ; 
  printf("\n") ;
  r = vitesse_affecter( &c , s ) ;
  printf(" Retour de c <-- s : ") ; vitesse_afficher(r) ; printf("\n" ); 
  printf( " Apres affectation c = " ); vitesse_afficher( c ) ; 
  printf( " ; s = " ); vitesse_afficher( s ) ; 
  printf("\n") ;


  return(0) ; 
}

