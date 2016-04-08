#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdarg.h>

void f( int x , int y , ...  ) 
{ 
  va_list ap ;

  printf( "Arguments formels\n" )  ; 
  printf( "\tx = %d\n" , x ) ; 
  printf( "\ty = %d\n" , y ) ; 


  va_start( ap , y ) ; 

  printf("Arguments en surnombre\n") ; 
  /* Le 1er doit etre un int */
  printf( "\t1er (int) = %d\n" , va_arg( ap , int ) ); 
  /* 
   * Le 2ieme un float MAIS 
   * float est promu en double quand c'est passe par ... 
   * si pas traite comme un double alors plantage 
   */
  printf( "\t2ieme (float) = %G\n" , va_arg( ap , double ) ) ; /* OK */
  /*   printf( "\t2ieme (float) = %G\n" , va_arg( ap , float ) ) ; /\* KO *\/ */
  /* Le 3ieme un double */
  printf( "\t3ieme (double) = %G\n" , va_arg( ap , double ) ) ; 
  /* Le 4ieme un char * */
  printf( "\t4ieme (char *) = %s\n" , va_arg( ap , char * ) ) ; 

  va_end(ap) ;

  return ; 
}

int main( int argc , char * argv[] ) 
{
  int bidon1 = 99 ;
  int bidon2 = 88 ; 

  /* Appel de la fonction avec nombre variable de parametres */
  printf("\n\n1er appel de f avec des arguments heterogenes\n");
  printf(" Appel de f( bidon1 , bidon2 , 12 , 34.56 , 12E-10 , \"azertyuiop\" , NULL ) \n") ; 
  f( bidon1 , bidon2 , 12 , 34.56 , 12E-10 , "azertyuiop" , NULL ) ;
  
  return(0) ; 
}
