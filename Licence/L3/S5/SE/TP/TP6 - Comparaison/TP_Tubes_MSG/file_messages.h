#ifndef _FILE_MESSAGES_H_
#define _FILE_MESSAGES_H_

#include <messages.h>

#ifndef _MSG_MESSAGES_H_
#define _MSG_MESSAGES_H_

#include <messages.h>

#define MSG_TYPE_RECEPTEUR 22

/* Structure message */


/*
 * Definition des fonctions 
 */

/* Affichage d'un message */
extern
void file_afficher( char * const message );

/* Remplissage d'un message */
extern
void file_remplir( char * message , const char val ) ;

#endif


#endif
