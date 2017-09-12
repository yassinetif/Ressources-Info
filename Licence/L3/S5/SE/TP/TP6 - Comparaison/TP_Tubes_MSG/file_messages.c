#include <stdio.h>
#include <unistd.h>
#include <file_messages.h>


/*
 * Affichage d'un message 
 */
extern
void
file_afficher( char * const message )
{
  int i;
  
  /* Affichage du buffer */
  printf("\tBuffer =\n") ;
  for(i=0 ; i<MESSAGES_TAILLE ; i++ )
    {
      if( i % 80 == 0 ) 
	{
	  printf("\n");
	}
      printf("%c" , message[i] );
    }
  printf("\n");
}

/*
 * Remplissage d'un message 
 */
extern
void
file_remplir( char * message , const char val )
{
     int i ;

     /* Buffer */
     for(i=0 ; i<MESSAGES_TAILLE ; i++ )
     {
	  message[i] = val ;
     }
}


