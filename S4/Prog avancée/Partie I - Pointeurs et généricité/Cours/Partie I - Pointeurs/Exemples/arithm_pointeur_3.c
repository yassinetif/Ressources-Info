#include <stdio.h>
#include <stdlib.h>


int 
main()
{
  /* Declarations */
  int  * p  = NULL ;
  int  * p1 = NULL ; 
  char * p2 = NULL ; 
  int  * p3 = NULL ; 

  /* Reservation/affectation zone memoire */
  p = malloc( sizeof(int) * 5 ) ; 
  *p = 11 ;
  *(p+1) = 22 ; 
  *(p+2) = 33 ; 
  *(p+3) = 44 ; 
  *(p+4) = 55 ;


  /* Test operateurs de l'arithmetique des pointeurs */
  p1 = p ;
  printf( " \nTest addition \n"); 
  printf( " p1 = %p , p1+3 = %p , contenu de p1+3 = %d\n" , p1 , p1+3 , *(p1+3) ) ; 
  p1 = p1+3 ; 

  printf( " \nTest soustraction \n"); 
  printf( " p1 = %p , p1-2 = %p , contenu de p1-2 = %d\n" , p1 , p1-2 , *(p1-2) ) ; 


  printf( " \nTest comparaison de 2 pointeurs\n"); 
  p2 = p ;
  p3 = p ; 
  printf( " p == p2 ? --> %s , p == p3 ? --> %s \n" , 
	  (p==p2 ? "VRAI":"FAUX") , (p==p3 ? "VRAI" : "FAUX")  ) ; 

  printf( " p+1 == p2+1 ? --> %s , p+1 == p3+1 ? --> %s \n" , 
	  ((p+1)==(p2+1) ? "VRAI":"FAUX") , ((p+1)==(p3+1) ? "VRAI" : "FAUX")  ) ; 

  printf( " \nTest soustraction de 2 pointeurs\n"); 
  p1 = p+1 ;
  p3 = p+4 ;
  printf( " avec pointeurs meme type et appartenant au meme tableau: p3-p1 == %d (= nombre d'elements entre les 2 pointeurs)\n" , 
	  p3-p1 ) ; 

  printf( " avec pointeurs differents: p3-p2 == %d (n'importe quoi)\n" , 
	  (void *)p3-(void *)p2 ) ; 

  return(0);
}
