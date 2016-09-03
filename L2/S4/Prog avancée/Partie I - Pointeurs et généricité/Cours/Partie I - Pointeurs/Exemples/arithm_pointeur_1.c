#include <stdio.h>
#include <stdlib.h>


int 
main()
{
  /* Declarations */
  int * p ;

  /* Reservation/affectation zone memoire */
  p = malloc( sizeof(int) * 5 ) ; 
  *p = 11 ;
  *(p+1) = 22 ; 
  *(p+2) = 33 ; 
  *(p+3) = 44 ; 
  *(p+4) = 55 ;


  /* Test arithmetique pointeur avec 5 objets homogenes (int)*/
  printf( " Taille d'un int = %lu\n\n" , (long unsigned int)sizeof(int) ) ;
  printf( " adresse de p = %p , contenu de p = %d\n" , p , *p ) ; 
  p++ ; 
  printf( " adresse de p = %p , contenu de p = %d\n" , p , *p ) ; 
  p++ ; 
  printf( " adresse de p = %p , contenu de p = %d\n" , p , *p ) ; 
  p++ ; 
  printf( " adresse de p = %p , contenu de p = %d\n" , p , *p ) ; 
  p++ ; 
  printf( " adresse de p = %p , contenu de p = %d\n" , p , *p ) ; 
  
  return(0);
}
