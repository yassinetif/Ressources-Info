#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <liste_objet.h>



/*
 * VARIABLE LOCALE
 */

unsigned long int liste_objet_cpt = 0 ; 

/*
 * Methodes d'acces 
 */

/* Nombre d'elements */

extern 
int liste_objet_nb_lire( liste_objet_t * const liste )
{
  return(liste->nb );
} 

/* -- Acces individuel a un element */

extern 
objet_t * liste_objet_elem_lire( liste_objet_t * const liste  , const int ind )
{
  if( (ind < 0) || (ind > liste_objet_nb_lire(liste)-1 ) )
    {
      fprintf( stderr , "liste_objet_elem_lire: mauvais indice d'element [%d] (devrait etre dans [%d..%d])\n",
	       ind , 0 , liste_objet_nb_lire(liste)-1 );
      return(NULL);
    }

  return( liste->liste[ind] ) ;
}

/*
 * Tests 
 */

extern 
booleen_t liste_objet_existe( liste_objet_t * const liste )
{
  if( liste == NULL )
    {
      return(FAUX) ; 
    }
  else
    {
      return(VRAI) ; 
    }
}

extern 
booleen_t liste_objet_vide( liste_objet_t * const liste )
{
  if( liste->nb == 0 )
    {
      return(VRAI) ; 
    }
  else
    {
      return(FAUX) ; 
    }
}

/*
 * Methodes d'affectation 
 */


/* -- Acces individuel a un element */
extern 
err_t liste_objet_elem_ecrire( liste_objet_t * liste , 
			 objet_t * const elem ,
			 const int ind ) 
{

#ifdef _DEBUG_
  if( (ind < 0) || (ind > liste_objet_nb_lire(liste) ) )
    {
      fprintf( stderr , "liste_objet_elem_ecrire: mauvais indice d'element [%d] (devrait etre dans [%d..%d]\n",
	       ind , 0 , liste_objet_nb_lire(liste) );
      return(ERR_LISTE_IND_ELEM);
    }
#endif
  liste->liste[ind] = elem ;

  return(OK) ;
}


/*
 * Destruction d'une liste 
 */

extern
err_t liste_objet_detruire( liste_objet_t ** liste )
{
  int i;
  
  if(liste_objet_existe(* liste)) { /* On vide la liste */
    for(i = 0; i < (*liste)->nb; i++) {
      if((*liste)->liste[i] != NULL) {
        (*liste)->liste[i]->detruire(&(*liste)->liste[i]);
      }
    }
    
    (*liste)->nb = 0;
    free((*liste)->liste);
    free(*liste);
    
    liste_objet_cpt--;
  }

  return(OK) ;
}


/*
 * Affichage d'une liste sur la sortie standard
 * avec un caractere de separation entre 
 * l'affichage de 2 elements 
 */

extern 
void liste_objet_afficher( liste_objet_t * const liste_objet ,
		     const char separateur )
{
  int i;
  
  if(liste_objet_existe(liste_objet)) {
    for(i = 0; i < liste_objet->nb; i++) {
      if(liste_objet->liste[i] != NULL) {
        liste_objet->liste[i]->afficher(liste_objet->liste[i]);
        printf("%c", separateur);
      }
    }
  } 
}


/*
 * Creation d'une liste 
 */
extern
liste_objet_t * liste_objet_creer( const int nb )
{
  liste_objet_t * liste =NULL;
  int i;
  
  if(( liste= malloc(sizeof(liste_objet_t))) == NULL )
    {
      fprintf( stderr , "liste_objet_creer: debordement memoire lors de la creation d'une liste\n");
      return((liste_objet_t *)NULL);
    }
    
  /* Appel des mŽthodes */
  
  liste->nb_lire = liste_objet_nb_lire;
  liste->elem_lire = liste_objet_elem_lire;
  liste->vide = liste_objet_vide;
  liste->elem_ecrire = liste_objet_elem_ecrire;
  liste->detruire = liste_objet_detruire;
  liste->afficher = liste_objet_afficher;
	
  liste->nb = nb ;
  liste->liste = (objet_t**)NULL ;
  
  if(nb > 0) {
    if((liste->liste = malloc( sizeof(objet_t *) * nb ) ) == NULL ) {
	  fprintf( stderr , "liste_objet_creer: debordement memoire lors de la creation d'une liste\n");
	  free( liste ) ;
	  return((liste_objet_t *)NULL);
	} else { /* Initialisation de la liste - sinon erreur pour le liste_objet_afficher */
      for(i = 0;i < nb; i++) {
        liste->liste[i] = NULL;
      }
    }
  }

  liste_objet_cpt++ ; 

  return(liste);
}
