#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

#ifdef _LINUX_
#include <string.h>
#else
#include <strings.h>
#endif

#include <msg_messages.h>

int 
main( int nb_arg , char * tab_arg[] )
{     
     char nomprog[128] ;

     /*-----*/

     if( nb_arg !=1 )
       {
	 fprintf( stderr , "%s - Recepteur dans la communication par paquet\n\n" , tab_arg[0] );
	 fprintf( stderr , "usage : %s \n" , tab_arg[0] );
	 exit(-1);
       }
     strcpy( nomprog , tab_arg[0] );

     /*=============================*/
     /*           A FAIRE           */
     /*=============================*/

     
     exit(0);
}
