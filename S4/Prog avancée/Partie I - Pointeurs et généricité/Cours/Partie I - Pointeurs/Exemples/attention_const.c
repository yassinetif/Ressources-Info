#include <stdio.h>

int
main()
{
  /* Declaration d'une constante qui ne devrait pas changer */
  const int x = 45 ;
  /* Pointeur sur cette constante */
  const int * p = &x  ;
  printf( "constante x AVANT = %d\n" , x ) ; 
  /* Or ceci passe: */
  (*(int *)p) = 67 ;
  printf( "constante x APRES = %d\n" , x ) ; 
  return(0) ; 
}
