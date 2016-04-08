#include <stdio.h>

int 
main()
{
  /* Declarations */
  char x = 'A' ;
  char * p = &x ;
  char ** p2 = &p ; 

  /* Test adressage indirect */
  printf( " adresse de x  = %p , contenu de x  = %c\n" , &x , x ) ; 
  printf( " adresse de p  = %p , contenu de p  = %p , adressage indirect de p  = %c\n" , &p , p , *p ) ; 
  printf( " adresse de p2 = %p , contenu de p2 = %p , adressage indirect de p2 = %p , double adressage indirect de p2 = %c\n" , 
	  &p2 , p2 , *p2 , **p2 ) ; 

  return(0);
}
