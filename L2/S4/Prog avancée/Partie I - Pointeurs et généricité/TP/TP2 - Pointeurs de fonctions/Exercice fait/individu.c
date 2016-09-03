#include <stdlib.h>
#include <string.h>
#include <individu.h>


/*
 * VARIABLE LOCALE
 */

unsigned long int individu_cpt = 0 ; 

/* 
 * FONCTIONS
 */

extern 
booleen_t individu_existe( individu_t * const individu )
{
  if( individu == NULL ) 
    return(FAUX) ;
  else
    return(VRAI) ; 
}

static 
err_t individu_detruire( individu_t ** individu ) 
{
  if(individu_existe(*individu)) {
    (*individu)->afficher = NULL;
    (*individu)->detruire = NULL;
    
    free((*individu)->nom);
    free((*individu)->prenom);
    free(*individu);
    
    individu_cpt--;
  }
  
  return(OK) ; 
}

static
void individu_afficher( individu_t * const individu ) 
{

  printf( "{" ) ; 
  if(  individu_existe(individu) ) 
    {
      printf( "%s %s" , individu->prenom , individu->nom ) ;
    }
  printf( "}" ) ; 
}

extern 
individu_t * individu_creer( char * const prenom , char * const nom ) 
{
  individu_t * individu = malloc(sizeof(individu_t));
  
  individu->nom = malloc(sizeof(char) * (strlen(nom) + 1));
  individu->prenom = malloc(sizeof(char) * (strlen(prenom) + 1));
  
  individu->afficher = individu_afficher;
  individu->detruire = individu_detruire;
  
  strcpy(individu->nom, nom);
  strcpy(individu->prenom, prenom);
  
  individu_cpt++;
  
  return( individu ) ;
}
