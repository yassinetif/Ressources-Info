#include <stdio.h>
#include <stdlib.h>

#include <string.h>

/* 
 * ------------
 * Objet de base (hérité de tous les objets)
 * ------------
 */

/* Attributs */
typedef enum message_s { AFFICHER } message_t ;

typedef struct objet_s objet_t ;

struct objet_s
{
  void (*switching)(objet_t * , message_t) ;
} ;

/* Methodes */
static
void message_envoyer( objet_t * objet , message_t message )
{
  objet->switching( objet , message ) ; 
}

/* 
 * ------------
 * Objet ENTIER 
 * ------------
 */

/* Attributs */

typedef struct entier_s entier_t ;

struct entier_s
{
  void (*switching)(objet_t * , message_t) ;
  int i ; 
  void (*afficher)(entier_t *) ;
} ;

/* Methodes */
static
void afficher_int( entier_t * entier ) 
{
  printf( "%d\n" , entier->i ) ; 
} 

static
void switching_int( objet_t * self , message_t message ) 
{
  switch(message)
    {
    case AFFICHER :
      ((entier_t *)self)->afficher((entier_t *)self) ;
    }
} 


static
entier_t * creer_entier( const int val ) 
{
  entier_t * obj = malloc(sizeof(entier_t)) ; 
  obj->switching = switching_int ;
  obj->i = val ; 
  obj->afficher = afficher_int ;
  return(obj) ; 
}

/* 
 * ------------
 * Objet STRUCTURE 
 * ------------
 */

/* Attributs */
typedef struct S_s S_t ; 

struct S_s
{
  void (*switching)(objet_t * , message_t) ;
  char c[10] ;
  int i ;
  void (*afficher)(S_t *) ;  
} ;

/* Methodes */

static
void afficher_struct( S_t * structure ) 
{
  printf( "{ %s , %d } \n" , structure->c  , structure->i) ; 
} 

static
void switching_struct( objet_t * self , message_t message ) 
{
  switch(message)
    {
    case AFFICHER :
      ((S_t *)self)->afficher((S_t *)self) ;
    }
} 

static
S_t * creer_struct( char * const string , const int val ) 
{
  S_t * obj = malloc(sizeof(S_t)) ;
  obj->switching = switching_struct ;
  strcpy( obj->c , string ) ;
  obj->i = val ; 
  obj->afficher = afficher_struct ;
  return(obj) ; 
}

/*
 *---------------------------------------------- 
 * Programme d'appel de la "methode" afficher 
 * sur les 2 objets 
 *---------------------------------------------- 
 */
int 
main()
{

  entier_t * entier = creer_entier( 10 ) ;
  S_t * S = creer_struct( "abcdef" , 99 ) ; 

  /* entier>afficher transforme dans l'envoie du message: */
  message_envoyer( (objet_t*)entier , AFFICHER ) ;

  /* S>afficher transforme dans l'envoie du message: */
  message_envoyer( (objet_t*)S , AFFICHER ) ;

  return(0);
}
