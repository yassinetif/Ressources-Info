#include <stdio.h>


static 
int * f( int v ) 
{
  int i = v ;
  printf( "Dans pile de f (%p)\n" , f ) ;
  printf( " [%p] : %d\n" , &i , i ) ;
  return( &i ) ; 
}

void chamboule() 
{
  char * s = "abcdefghijklmnopqrstuvwxyz" ; 
  int i ;
  printf( "Dans pile de chamboule (%p):\n" , chamboule ) ;
  for( i=25 ; i>=0 ; i-- ) 
    printf(" [%p] : %c\n" , s+i , *(s+i) ); 

  return ; 
}

int main()
{
  int * p1 = NULL ; 

  p1 = f(11) ;

  /* On chamboule un peu la pile */
  chamboule() ;

  printf( "\nDans le main : p1 = %p , (*p1) = %d\n" , p1 , (*p1) );
  
  return(0) ; 
}
