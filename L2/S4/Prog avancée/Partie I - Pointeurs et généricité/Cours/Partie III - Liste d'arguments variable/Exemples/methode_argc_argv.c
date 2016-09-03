#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXARG 10 

void f( int argc , char * argv[]  ) 
{ 
  int i ; 

  for( i=0 ; i<argc ; i++ )
    {
      printf( "\tfoncton f : argv[%d] = %s\n" , i , argv[i] ) ; 
    }
  return ; 
}


int main( int argc , char * argv[] ) 
{
  int f_argc ;
  char * f_argv[MAXARG] ;
  int i ;

  /* Construction des parametres */
  f_argc = 3 ;
  f_argv[0] = malloc( sizeof(char) * strlen("azertyuiop")+1 ) ;
  strcpy( f_argv[0] , "azertyuiop" ) ;
  f_argv[1] = malloc( sizeof(char) * strlen("123")+1 ) ;
  strcpy( f_argv[1] , "123" ) ;
  f_argv[2] = malloc( sizeof(char) * strlen("45.67")+1 ) ;
  strcpy( f_argv[2] , "45.67" ) ;

  /* Appel de la fonction avec nombre variable de parametres */
  printf(" 1er appel de f avec 3 arguments\n");
  f( f_argc , f_argv ) ;

  for( i=0 ; i<3 ; i++ ) 
    free( f_argv[i] ) ; 

 /* Construction des parametres */
  f_argc = 2 ;
  f_argv[0] = malloc( sizeof(char)*strlen("WWW")+1 );
  strcpy( f_argv[0] , "WWW" ); 
  f_argv[1] = malloc( sizeof(char)*strlen("XXXXXXX")+1 );
  strcpy( f_argv[1] , "XXXXXXX" ); 

 /* Appel de la fonction avec nombre variable de parametres */
  printf(" 1er appel de f avec 2 arguments\n");
  f( f_argc , f_argv ) ;

  for( i=0 ; i<2 ; i++ ) 
    free(f_argv[i]) ; 
  
  return(0) ; 
}
