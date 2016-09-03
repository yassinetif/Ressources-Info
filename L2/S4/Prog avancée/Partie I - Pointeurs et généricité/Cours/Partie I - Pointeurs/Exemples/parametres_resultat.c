#include <stdio.h>

static 
void F_bad(int x) 
{
  printf( "\tF_bad : variable x [%p] AVANT = %d\n" , &x , x ) ; 
  x = 11 ;
  printf( "\tF_bad : variable x [%p] APRES = %d\n" , &x , x ) ; 
}

static
void F_good( int * x ) 
{
  printf( "\tF_good : variable x [%p] AVANT = %d\n" , x , *x ) ; 
  (*x) = 22 ;
  printf( "\tF_good : variable x [%p] APRES = %d\n" , x , *x ) ; 
}

int
main()
{
  int i = 5 ;

  printf( "MAIN : variable i [%p] AVANT= %d\n" , &i , i ) ; 
  F_bad(i) ; 
  printf( "MAIN : variable i [%p] APRES F_bad = %d\n" , &i , i ) ; 
  F_good(&i) ;
  printf( "MAIN : variable i [%p] APRES F_good = %d\n" , &i , i ) ; 

  return(0) ; 
}
