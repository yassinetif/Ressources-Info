#include <stdio.h>

int main( int argc , char * argv[] , char * env[] ) 
{
  int i = 0 ;
  
  
  printf( "\nNombre d'arguments : %d \n" , argc ) ; 

  printf( "\nListe des arguments:\n") ; 
  for( i=0 ; i<argc  ; i++ )
    printf( "\targv[%d] = %s\n" , i , argv[i] ) ; 

  printf( "\nListe des variables d'environnement:\n") ; 
  for( i=0 ; env[i] != NULL ; i++ ) 
    printf( "\tenv[%d] = %s\n" , i  , env[i]) ;

  return(0); 
}
