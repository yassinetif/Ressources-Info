#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <liste.h>


/*
 * Tests 
 */

extern 
booleen_t liste_existe( const liste_t * liste )
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
booleen_t liste_vide( const liste_t * liste )
{
  return( tab_existe( liste ) ) ;
}


/*
 * Methodes d'acces 
 */

/* Nombre d'elements */

extern 
liste_id_t liste_taille( const liste_t * liste )
{
  return(tab_nb_lire(liste) );
} 

/*  Acces a un element */

extern 
void * liste_acceder( const liste_t * liste  , const liste_id_t position )
{
  return( tab_lire(liste , position)  ) ;
}

/* Acces a la position de debut */
extern 
liste_id_t liste_debut( const liste_t * liste )
{
  return(0) ;
}

/* Acces a la sentinelle */
extern 
liste_id_t liste_sentinelle( const liste_t * liste )
{
  return( tab_nb_lire(liste) ) ;
}

/* Acces au premier &eacute;l&eacute;ment de la liste */
extern void * liste_premier( const liste_t * liste ) 
{
  return( tab_premier_lire(liste) ) ;
}

/* Acces au dernier &eacute;l&eacute;ment de la liste */
extern void * liste_dernier( const liste_t * liste ) 
{
  return( tab_dernier_lire(liste) ) ;
}

/*! Position de l'element suivant */
extern liste_id_t liste_suivant( const liste_t * liste , const liste_id_t position )
{
  return(position+1) ; 
}

/*
 * Methodes d'affectation 
 */

/* Ajout d'un element */
extern 
err_t liste_inserer( liste_t * liste , 
		     const void * elem ,
		     const liste_id_t position ) 
{
  return(tab_inserer( liste , elem , position ) ) ;
}


/* Ajout d'un element en debut de liste */
extern 
err_t liste_empiler( liste_t * liste , const void * elem ) 
{
  return(tab_debut_inserer( liste , elem ) ) ; 
}

/* Ajout d'un element en fin de liste */
extern 
err_t liste_enfiler( liste_t * liste , const void * elem ) 
{
  return(tab_fin_inserer( liste , elem ) ) ;
}

/* Suppression d'un element a une position */
extern 
void * liste_supprimer( liste_t * liste, 
			const liste_id_t position ) 
{
  return(tab_extraire( liste , position ) ) ; 
}

/* Depilement de l'element en debut de liste */
extern 
void * liste_depiler( liste_t * liste ) 
{
  return(tab_debut_extraire( liste  ) ) ; 
}

/*! Defilement de l'element en fin de liste */
extern 
void * liste_defiler( liste_t * liste ) 
{
  return(tab_fin_extraire( liste ) ) ; 
}
/*
 * Copie d'une liste  
 * La liste cible est créée par la fonction 
 */

extern
err_t liste_copier( liste_t ** liste_cible , const liste_t * liste_source )
{
  return(tab_copier( liste_cible , liste_source ) ) ; 
}

/*
 * Creation d'une liste 
 */
extern
liste_t * liste_creer( err_t (*fonction_affectation)( void ** e1 , const void * e2 ) ,
		       err_t (*fonction_destruction)(void ** e) )
{ 
  return(tab_creer( 0, fonction_affectation , fonction_destruction ) ) ;
}

/*
 * Destruction d'une liste 
 */

extern
err_t liste_detruire( liste_t ** liste )
{  
  return(tab_detruire(liste)) ;
}


/*
 * Affichage d'une liste sur la sortie standard
 */

extern 
void liste_afficher( const liste_t * liste ,
		     void (*fonction_affichage)(const void * e) , 
		     const char separateur )
{
  tab_afficher( liste , fonction_affichage , separateur );
}


/*
 * Affichage d'une liste dans une chaine de caracteres
 */

extern 
char *  liste_string_afficher( const liste_t * liste ,
			       char * (*fonction_string_affichage)(const void * e) , 
			       const char separateur )
{
  return( tab_string_afficher( liste , fonction_string_affichage , separateur ) ) ;
}

/*
 * Chargement d'une liste a partir d'un descripteur de fichier 
 */
extern 
err_t liste_fd_charger( liste_t ** liste  ,							/* liste d'elements a charger */
			FILE * const fd ,							/* descripteur fichier de chargement */
			err_t (*fonction_chargement)(void * * e, FILE * const desc ) ,		/* Fonction de chargement d'un element */
			err_t (*fonction_affectation)( void * * e1 , const void * e2 ) ,	/* Fonction d'affectation d'un element */
			err_t (*fonction_destruction)(void * * e) )				/* Fonction de destruction d'un element */
{
  return( tab_fd_charger( liste , fd , fonction_affectation , fonction_destruction , fonction_chargement ) ) ;
}


/*
 * Chargement d'une liste a partir d'un fichier 
 */
extern 
err_t liste_charger( liste_t ** liste  ,							/* liste d'elements a charger */
		     char * const nom_fichier ,							/* nom du fichier de chargement */
		     err_t (*fonction_chargement)(void ** e, FILE * const desc ) ,		/* Fonction de chargement d'un element */
		     err_t (*fonction_affectation)( void ** e1 , const void *  e2 ) ,		/* Fonction d'affectation d'un element */
		     err_t (*fonction_destruction)(void ** e) )				/* Fonction de destruction d'un element */
{
  return( tab_charger( liste , nom_fichier , 
		       fonction_affectation , fonction_destruction , fonction_chargement ) ) ;
}



/*
 * Sauvegarde d'une liste a partir d'un descripteur de fichier 
 */
extern 
err_t liste_fd_sauver( const liste_t * liste  ,		/* liste a sauvegarder */
		       FILE * const fd , 		/* descripteur fichier  */
		       err_t (*fonction_sauvegarde)(const void *  e, FILE * const desc) , /* Fonction de sauvegarde d'un element */
		       const char separateur ) /* Separateur d'elements */
{
  return(tab_fd_sauver( liste , fd, fonction_sauvegarde , separateur) ) ;
}

/*
 * Sauvegarde d'une liste dans un fichier 
 */
extern 
err_t liste_sauver( const liste_t * liste  ,						/* liste a sauvegarder */
		    char * const nom_fichier ,						/* nom du fichier de sauvegarde  */
		    err_t (*fonction_sauvegarde)(const void * e, FILE * const desc) ,	/* Fonction de sauvegarde d'un element */
		    const char separateur )						/* Separateur d'elements */
{
  return(tab_sauver( liste , nom_fichier, 
		     fonction_sauvegarde , separateur) ) ;
}


/*
 * Tri d'une liste selon la methode du tri bulles
 */

extern 
err_t liste_trier( liste_t * liste,
		   int (*fonction_comparaison)(const void *  e1 , const void * e2) )
{
  return(tab_trier(liste , fonction_comparaison));
}


/*
 * Recherche d'un element dans une liste 
 */

extern 
booleen_t liste_rechercher( const liste_t * liste,
			    const void * element,
			    int (*fonction_comparaison)(const void * e1 , const void * e2) ,
			    liste_id_t * position )
{
  return(tab_rechercher(liste,element,fonction_comparaison,position));
}
