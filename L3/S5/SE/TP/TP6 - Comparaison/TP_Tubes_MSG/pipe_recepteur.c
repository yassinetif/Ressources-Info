#include <stdio.h>
#include <unistd.h>	/* close, read, write */
#include <stdlib.h>	/* exit */
#include <sys/types.h>	/*open */
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/time.h>
#ifdef _LINUX_
#include <string.h>
#else
#include <strings.h>
#endif
#include <pipe_messages.h>

int
main( int nb_arg , char * tab_arg[])
{
     char nomprog[128] ;

     /*-----*/
     strcpy( nomprog , tab_arg[0] );

     if( nb_arg != 1 )
     {
	  fprintf( stderr , "%s - Recepteur dans la communication par flot\n\n" , tab_arg[0] );
	  fprintf( stderr , "usage : %s \n" , nomprog );
	  exit(-1);
     }


     /*=============================*/
     /*           A FAIRE           */
     /*=============================*/

     exit( 0 );
}
