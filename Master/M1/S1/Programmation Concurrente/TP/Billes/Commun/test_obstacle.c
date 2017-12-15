#include <commun.h>
#include <obstacle.h>

int
main() 
{
  obstacle_t i = INFORME ; 

  for( i = OBSTACLE_PREMIER ; i != OBSTACLE_SENTINELLE ; i=obstacle_suivant(i) )
    {
      printf( "Obstacle = [" ) ;
      obstacle_afficher(i)  ; 
      printf( "] , valeur = %d\n" , i ) ;
    }

  printf("\n\n Test affectation d'une obstacle\n\n" ); 
  obstacle_t s  = VERTICAL ;
  obstacle_t c = INFORME ; 
  obstacle_t r = INFORME ; 
  printf( " Avant affectation c = " ); obstacle_afficher( c ) ; 
  printf( " ; s = " ); obstacle_afficher( s ) ; 
  printf("\n") ;
  r = obstacle_affecter( &c , s ) ;
  printf(" Retour de c <-- s : ") ; obstacle_afficher(r) ; printf("\n" ); 
  printf( " Apres affectation c = " ); obstacle_afficher( c ) ; 
  printf( " ; s = " ); obstacle_afficher( s ) ; 
  printf("\n") ;

  printf( "\n\nTest parcours liste de tous les obstacles\n") ;  
  for( i = OBSTACLE_PREMIER ; i != OBSTACLE_SENTINELLE ; i=obstacle_suivant(i) )
    {
      obstacle_afficher(i)  ; 
      printf( " " ) ;
    }
  printf("\n\n");

  return(0) ; 
}

