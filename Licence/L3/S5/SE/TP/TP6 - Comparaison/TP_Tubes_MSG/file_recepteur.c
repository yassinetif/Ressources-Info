#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <fcntl.h>
#include <signal.h>

#ifdef _LINUX_
#include <string.h>
#else
#include <strings.h>
#endif

#include <file_messages.h>

#define BIG_TAILLE MESSAGES_NB*MESSAGES_TAILLE
char big_buffer[BIG_TAILLE] ;



int 
main( int nb_arg , char * tab_arg[] )
{     
     char nomprog[128] ;
     
     /*-----*/
     strcpy( nomprog , tab_arg[0] );

     if( nb_arg != 1 )
       {
	 fprintf( stdout , "%s - Recepteur dans la communication par fichier\n\n" , nomprog ) ;
	 fprintf( stderr , "Usage : %s \n" , nomprog ) ;
	 exit(1) ; 
       }

     /*=============================*/
     /*           A FAIRE           */
     /*=============================*/
     
     exit(0);
}
