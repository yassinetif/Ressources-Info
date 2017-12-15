#include <commun.h>
#include <direction.h>

int
main() 
{
  direction_t dir = NULLE_PART ; 
  direction_t dir_opp = NULLE_PART ; 
  obstacle_t obst = INFORME ; 

  for( dir = DIR_PREMIER ; dir != DIR_SENTINELLE ; dir=direction_suivante(dir) )
    {
      printf( "Direction = [" ) ;
      direction_afficher(dir)  ; 
      printf( "] , valeur = %d\n" , dir ) ;
    }

  printf("\n\n Test affectation d'une direction\n\n" ); 
  direction_t s  = NORD_OUEST ;
  direction_t c = NULLE_PART ; 
  direction_t r = NULLE_PART ; 
  printf( " Avant affectation c = " ); direction_afficher( c ) ; 
  printf( " ; s = " ); direction_afficher( s ) ; 
  printf("\n") ;
  r = direction_affecter( &c , s ) ;
  printf(" Retour de c <-- s : ") ; direction_afficher(r) ; printf("\n" ); 
  printf( " Apres affectation c = " ); direction_afficher( c ) ; 
  printf( " ; s = " ); direction_afficher( s ) ; 
  printf("\n") ;

  printf( "\n\nTest TOUTES les directions opposees \n") ;  
  for( dir = DIR_PREMIER ; dir != DIR_SENTINELLE ; dir=direction_suivante(dir) )
    {
      for( obst = OBSTACLE_PREMIER ; obst != OBSTACLE_SENTINELLE ; obst=obstacle_suivant(obst) ) 
	{
	  direction_afficher(dir)  ; 
	  printf( "/") ;
	  obstacle_afficher(obst) ;
	  printf( " --> " ) ;
	  for( dir_opp=direction_opposee_premier(obst,dir) ; dir_opp != DIR_SENTINELLE ; dir_opp=direction_opposee_suivante(obst,dir,dir_opp) )
	    {
	      direction_afficher( dir_opp ) ;
	      printf(" " ) ;
	    }
	  printf("\n");
	}
      printf("\n");
    }


  printf( "\n\nTest TOUTES les directions opposees avec un DEPART ALEATOIRE\n") ; 
  int i = 0 ;
  for( dir = DIR_PREMIER ; dir != DIR_SENTINELLE ; dir=direction_suivante(dir) )
    {
      for( obst = OBSTACLE_PREMIER ; obst != OBSTACLE_SENTINELLE ; obst=obstacle_suivant(obst) ) 
	{
	  direction_afficher(dir)  ; 
	  printf( "/") ;
	  obstacle_afficher(obst) ;
	  printf( " --> " ) ;
	  dir_opp = direction_opposee_random(obst,dir) ;
	  for( i=0 ; i<direction_opposee_nb(obst,dir) ; i++ )
	    {
	      direction_afficher( dir_opp ) ;
	      printf(" " ) ;
	      dir_opp =direction_opposee_random_suivante(obst,dir,dir_opp) ;
	    }
	  printf("\n");
	}
      printf("\n");
    }
  
  return(0) ; 
}

