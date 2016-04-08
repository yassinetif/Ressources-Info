#include <stdio.h>
#include <stdlib.h>

#include <entier.h>

/* Fonction de comparaison de 2 entiers */
extern
int comparer_int( const int * i1 , const int * i2 )
{
  return( (*i1) - (*i2) ) ;
}

extern
int comparer_int_cb( const void * v1 , const void * v2 )
{
  const int * i1 = v1 ;
  const int * i2 = v2 ;

  return( comparer_int( i1 , i2 ) ) ;
}

/* Fonction d'affichage d'un tableau d'entiers */
extern
void afficher_int( int * T , const int N )
{
  int i = 0 ; 
  for( i=0 ; i<N ; i++ ) 
      printf( "%d " , T[i] ) ;
  printf("\n" ); 
}
