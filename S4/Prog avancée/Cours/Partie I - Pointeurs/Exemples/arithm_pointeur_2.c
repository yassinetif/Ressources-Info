#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct S 
{
  char s[10] ;
  int e ;
} ;

int 
main()
{
  /* Declarations */
  char * p = NULL ; 
  char * p2 = NULL ;

  int i = 11 ; 
  double d = 123.45 ; 
  struct S structure ; 
  strcpy( structure.s , "abcde" ); 
  structure.e = 22 ;
  char c = 'Z' ;
  float f = 67.89 ; 

  /* Reservation/affectation zone memoire */
  p = malloc( sizeof(int) + sizeof(double) + sizeof( struct S) + sizeof(char) + sizeof(float) ) ; 
  p2 = p ; 

  memcpy( p, &i, sizeof(int));
  printf( " Taille d'un entier = %lu\n" , sizeof(int) ) ;
  (int*)p = (int*)p + 1 ;

  memcpy( p, &d, sizeof(double));
  printf( " Taille d'un double = %lu\n" , sizeof(double) ) ;
  (double*)p = (double*)p + 1 ;

  memcpy( p, &structure, sizeof(struct S));
  printf( " Taille de la structure  = %lu\n" , sizeof(struct S) ) ;
  (struct S*)p = (struct S*)p + 1 ;

  memcpy( p, &c, sizeof(char));
  printf( " Taille d'un char  = %lu\n" , sizeof(char) ) ;
  (char*)p = (char*)p + 1  ;

  memcpy( p, &f, sizeof(float));
  printf( " Taille d'un float  = %lu\n" , sizeof(float) ) ;

  /* Test arithmetique pointeur avec 5 objets homogenes (int)*/
  p = p2 ; 

  memcpy( &i, p , sizeof(int));
  printf( " adresse de p = %p , contenu de p = %d\n" , p , (int)(*p) ) ; 
  printf( "              + %lu\n" , sizeof(int) ) ;
  (int*)p = (int*)p + 1 ;

  memcpy( &d, p, sizeof(double));
  printf( " adresse de p = %p , contenu de p = %G\n" , p , d ) ; 
  printf( "              + %lu\n" , sizeof(double) ) ;
  (double*)p  = (double*)p + 1 ;

  memcpy( &structure, p , sizeof(struct S));
  printf( " adresse de p = %p , contenu de p = { %s , %d } \n" , p , structure.s , structure.e ) ; 
  printf( "              + %lu\n" , sizeof(struct S) ) ;
  (struct S*)p = (struct S*)p + 1  ;

  memcpy( &c, p, sizeof(char));
  printf( " adresse de p = %p , contenu de p = %c\n" , p , c ) ; 
  printf( "              + %lu\n" , sizeof(char) ) ;
  (char*)p = (char*)p + 1 ;

  memcpy( &f, p , sizeof(float));
  printf( " adresse de p = %p , contenu de p = %f\n" , p , f ) ; 
  printf( "              + %lu\n" , sizeof(float) ) ;
  (float*)p = (float*)p + 1 ;

  printf( " adresse de p = %p\n" , p  ) ; 
  return(0);
}
