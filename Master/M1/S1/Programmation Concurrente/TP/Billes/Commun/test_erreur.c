#include <stdio.h>
#include <erreur.h>


int
main( int argc , char * argv[] ) 
{
  err_t i = OK ; 

  printf("\n\n\n\t===========Debut %s==========\n\n" , argv[0] );

  for( i=ERR_ERREUR_FIN ; i<OK ; i++ ) 
    {
      erreur_afficher( i ) ; 
    }

  printf("\n\n\t===========Fin %s==========\n\n" , argv[0] );

  return(0) ;
}

