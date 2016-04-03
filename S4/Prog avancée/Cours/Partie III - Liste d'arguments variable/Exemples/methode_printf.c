#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdarg.h>


void f( char * format, ...  ) 
{ 
  va_list ap ;
  int i = 0 ; 
  int nb_arg = 0 ; 

  printf( "Arguments formels\n" )  ; 
  printf( "\tformat = %s\n" , format ) ; 

  va_start( ap , format ) ; 

  printf("Arguments en surnombre\n") ; 
  nb_arg = strlen(format) ; 
  for(i=0 ; i<nb_arg ; i++) 
    {
      printf("\t numero %d " , i ); 
      switch(format[i])
	{ 
	case 'd' :  /* C'est un int */      
	  printf( "(int) = %d\n" , va_arg( ap , int ) ); 
	  break ;
	case 'f' : /* C'est un float mais on il a ete converti en double */
	  printf( "(float) = %G\n" , va_arg( ap , double ) ) ;
	  break ;
	case 'D' : /* C'est un double */
	  printf( "(double) = %G\n" , va_arg( ap , double ) ) ; 
	  break ; 
	case 's' : /* C'est un char * */
	  printf( "(char *) = %s\n" , va_arg( ap , char * ) ) ; 
	  break ;
	default :
	  printf( "format inconnu\n" ); 
	  break ;
	}
    }
  va_end(ap) ;

  return ; 
}

int main( int argc , char * argv[] ) 
{

  /* Appel de la fonction avec nombre variable de parametres */

  printf("\n\nAppel de f_nb( \"dfDs\" , 12 , 34.56 , 12E-10 , \"azertyuiop\" , NULL ) \n") ; 
  f( "dfDs" , 12 , 34.56 , 12E-10 , "azertyuiop" ) ;

  printf( "\n\nAppel de   f( \"sds\" , \"coucou\" , 99 , \"bonjour\" ) ; \n") ; 
  f( "sds" , "coucou" , 99 , "bonjour" ) ;
  

  return(0) ; 
}
