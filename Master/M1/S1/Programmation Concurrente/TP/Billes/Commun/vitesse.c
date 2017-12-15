#include <commun.h>
#include <vitesse.h>


/*
 * Fonction sur les vitesses 
 */

extern
void vitesse_afficher( vitesse_t v ) 
{
  printf(" %u ", v ) ; 
}

extern
vitesse_t vitesse_affecter( vitesse_t * v1 , const vitesse_t v2 ) 
{
  return( (*v1) = v2 ) ;
}
