#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

#include <aire.h>

#define N 10 


int
main( int argc , char * argv[] ) 
{
  aire_t * A  = NULL ;
  err_t cr = OK ; 

  printf("\n\n\n\t===========Debut %s==========\n\n" , argv[0] );

  srand(getpid());

 
  printf("Creation d'une aire de 20X10\n") ;
  if( ( A = aire_creer( 10 , 20 ) ) == AIRE_NULL )
    {
      printf("Erreur sur la creation de l'aire\n") ; 
      exit(-1);
    }

  aire_afficher(A) ;

  printf("Creation d'une zone sur l'aire\n") ;
  coord_t * hg = coord_creer( 2 , 2 ) ;
  coord_t * bd = coord_creer( 5 , 15 ) ;
  
  if( ( cr = aire_zone_creer( A , hg , bd ) ) ) 
    {
      printf("Erreur sur la creation d'une zone sur l'aire, cr = %d\n" , cr ) ;
      erreur_afficher(cr) ; 
      printf("\n") ; 
      exit(-1);
    }
  aire_afficher(A) ;

  printf("Creation d'une deuxieme zone sur l'aire\n") ;
  coord_ecrire( hg , 4, 10 ) ;
  coord_ecrire( bd , 8, 18 ) ;
  if( ( cr = aire_zone_creer( A , hg , bd ) ) ) 
    {
      printf("Erreur sur la creation d'une zone sur l'aire, cr = %d\n" , cr ) ;
      erreur_afficher(cr) ; 
      printf("\n") ; 
      exit(-1);
    }
  aire_afficher(A) ; 
  
  if( ( aire_detruire( &A ) ) )
    {
      printf("Erreur sur la destruction de l'aire\n") ; 
      exit(-1);
    }
  
  printf("\n\n\t===========Fin %s==========\n\n" , argv[0] );

  return(0) ;
}

