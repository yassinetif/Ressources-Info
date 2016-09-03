#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdarg.h>

/* Variante avec le nombre d'arguments */
void f_nb( int x , int y , int nb_arg , ...  ) 
{ 
  int i = 0 ; 
  /* ap est une va_list qui pointera successivement sur chacun des arguments en surnombre */
  va_list ap ;

  printf( "Arguments formels\n" )  ; 
  printf( "\tx = %d\n" , x ) ; 
  printf( "\ty = %d\n" , y ) ; 
  printf( "\tnb_arg = %d\n" , nb_arg ) ; 
    
  /* on initialise ap pour qu'il pointe sur le 1er argument en surnombre  */
  va_start( ap , nb_arg ) ; 

  printf("Arguments en surnombre\n") ; 
  for( i=0 ; i<nb_arg ; i++ ) 
    {
      /* 
       * a chaque appel va_arg renvoie un arguments
       * il faut  lui preciser le type de cet argument attendu 
       */
      printf( "\t numero %d = %s\n" , i , va_arg( ap , char * ) ) ;
    }

  /* Pour terminer proprement, d'apres la norme */
  va_end(ap) ;

  return ; 
}

/* Variante sans le nombre d'arguments */
void f_sentinelle( int x , int y , ...  ) 
{ 
  int i = 0 ; 
  char * arg ;
  va_list ap ;

  printf( "Arguments formels\n" )  ; 
  printf( "\tx = %d\n" , x ) ; 
  printf( "\ty = %d\n" , y ) ; 
    
  /* on initialise ap pour qu'il pointe sur le 1er argument en surnombre  */
  va_start( ap , y ) ; 
  arg = va_arg( ap , char * ) ;

  printf("Arguments en surnombre\n") ; 
  while( arg != NULL ) 
    {
      printf( "\t numero %d = %s\n" , i ,  arg ) ;
      i++ ;
      arg = va_arg( ap , char * ); 
    }

  va_end(ap) ;

  return ; 
}


int main( int argc , char * argv[] ) 
{
  int bidon1 = 99 ;
  int bidon2 = 88 ; 

  /* Appel de la fonction avec nombre variable de parametres */
  printf("\n\n1er appel de f en precisant le nombre  d'arguments\n");
  f_nb( bidon1 , bidon2 , 5 , "aaaaa" , "bbbb" , "ccc" , "dd" , "e" ) ;

  /* Appel de la fonction avec nombre variable de parametres */
  printf("\n\n2ieme appel de f sans le nombre d'arguments\n");
  f_sentinelle( bidon1 , bidon2 , "aaaaa" , "bbbb" , "ccc" , "dd" , "e" , NULL ) ;
  
  return(0) ; 
}
