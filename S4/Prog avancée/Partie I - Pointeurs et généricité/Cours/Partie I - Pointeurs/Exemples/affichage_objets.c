#include <stdio.h>
#include <stdlib.h>

#include <string.h>

/* 
 * ------------
 * Objet ENTIER 
 * ------------
 */

/* Attributs */
typedef struct entier_s entier_t ;

struct entier_s
{
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
entier_t * creer_entier( const int val ) 
{
  entier_t * obj = malloc(sizeof(entier_t)) ; 
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
S_t * creer_struct( char * const string , const int val ) 
{
  S_t * obj = malloc(sizeof(S_t)) ; 
  strcpy( obj->c , string ) ;
  obj->i = val ; 
  obj->afficher = afficher_struct ;
  return(obj) ; 
}

/*
 * ------------------------------------------- 
 * Programme d'appel de la "methode" afficher
 * sur les 2 objets
 * -------------------------------------------
 */
int 
main()
{

  entier_t * entier = creer_entier( 10 ) ;
  entier->afficher(entier) ;
  
  S_t * S = creer_struct( "abcdef" , 99 ) ; 
  S->afficher(S) ;

  return(0);
}
