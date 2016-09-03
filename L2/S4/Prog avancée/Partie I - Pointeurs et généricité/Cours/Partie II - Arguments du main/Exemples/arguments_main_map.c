#include <stdio.h>

int main( int argc , char * argv[] ) 
{
  int i = 0 ;
  int n = 0 ; 
  
  printf( "\nNombre d'arguments : %d \n" , argc ) ; 

  printf( "\nCarte de la memoire pour les arguments:\n") ; 
  for( i=0 ; ; i++ )
    {
      if( argv[i] != NULL ) 
	{
	  printf( "\t[%d] = %s\n" , i , argv[i] ) ; 
	}
      else
	{
	  printf( "\n\t[%d] = NULL ----- separation ----\n\n" , i ) ;
	  n++ ;
	  if( n == 3 ) break ; 
	}
    }
  return(0); 
}
