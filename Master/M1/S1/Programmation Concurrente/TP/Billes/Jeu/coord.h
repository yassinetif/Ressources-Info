#ifndef _COORD_H_
#define _COORD_H_

#include <stdio.h>
#include <commun.h>
#include <erreur.h>

/*! 
 * \file  coord.h
 * \brief Type et primitives des coordonnees d'une case du damier
 */

/*
 * CONSTANTES
 */

/*!
 * \def COORD_NULL
 * \brief Coordonnee inexistante 
 */

#define COORD_NULL NULL 

/* Definition structure d'un coord */
/*!
 * \struct coord_t 
 * \brief Type d'une coordonn&eacute;e.
 * 
 * Les cases du damier et ls pieces sont rep&eacute;r&eacute;es par une coordonn&eacute;e
 */
typedef struct coord_s
{
  dim_t ligne   ;	/*!< Ordonnee */
  dim_t colonne ;	/*!< Abscisse */  
} coord_t ; 


/*
 * FONCTIONS 
 */

/*!
 * \name Methodes d'acces 
 * @{
 */


/*
 * FONCTIONS 
 */

/*!
 * \name Methodes d'acces 
 * @{
 */

/*!
 * \fn dim_t coord_lig_lire( const coord_t * coord )  
 * \brief Acces a l'ordonnee 
 * \param[in] coord : une coordonnee
 */
extern dim_t coord_lig_lire( const coord_t * coord ) ;

/*!
 * \fn dim_t coord_col_lire( const coord_t * coord )
 * \brief Acces a l'abscisse 
 * \param[in] coord : une coordonnee
 */
extern dim_t coord_col_lire( const coord_t * coord ) ;


/*!
 * @}
 * \name Methodes d'affectation
 * @{
 */

/*!
 * \fn  err_t coord_lig_ecrire( coord_t * coord , const dim_t ligne ) 
 * \brief Ecriture de l'ordonnee 
 * \param[in,out] coord : une coordonnee
 * \param[in] ligne : valeur de l'ordonn&eacute;e 
 */
extern err_t coord_lig_ecrire( coord_t * coord , const dim_t ligne ) ; 

/*!
 * \fn err_t coord_col_ecrire( coord_t * coord , const dim_t colonne ) 
 * \brief Ecriture de l'abscisse 
 * \param[in,out] coord : une coordonnee
 * \param[in] colonne : valeur de l'abscisse
 */
extern err_t coord_col_ecrire( coord_t * coord , const dim_t colonne )  ; 

/*! 
 * \fn err_t coord_ecrire( coord_t * coord , const dim_t ligne , const dim_t colonne ) 
 * \brief Ecriture globale 
 * \param[in,out] coord : une coordonnee
 * \param[in] ligne : valeur de l'ordonn&eacute;e 
 * \param[in] colonne : valeur de l'abscisse
 */
extern  err_t coord_ecrire( coord_t * coord , const dim_t ligne , const dim_t colonne )  ;

/*!
 * \name Affectation d'une coordonnee 
 * @{
 */

/*!
 * \fn err_t coord_copier( coord_t ** coord_cible , 
 * 			     const coord_t * coord_source )
 * \brief Affectation/copie de coordonnees 
 * \param[out] coord_cible : la coordonnee cible (cr&eacute;&eacute;e par la fonction)
 * \param[in] coord_source : la coordonnee source
 */
extern err_t coord_copier( coord_t ** coord_cible , 
			     const coord_t * coord_source ) ;

/*! Fonction de callback */
extern err_t cb_coord_copier( void * * coord_cible , 
			      const void * coord_source ) ; 


/*! Reference d'une coordonnees */
extern err_t coord_referencer( coord_t ** coord_cible , 
			       coord_t * coord_source ) ;

/*! Fonction de callback */
extern err_t cb_coord_referencer( void * * coord_cible , 
				  const void *  coord_source );

/*!
 * @}
 */

/*!
 * @}
 * \name Tests
 * @{
 */

/*!
 * \fn  booleen_t coord_existe( const coord_t * coord ) 
 * \brief Test d'existance d'une coordonnee 
 * \param[in] coord : coordonnee 
 */
extern booleen_t coord_existe( const coord_t * coord ) ; 

/*!
 * \fn  booleen_t coord_egal( const coord_t * coord1 , const coord_t * coord2 ) 
 * \brief Test d'egalite de deux coordonnees
 *
 * Pas de relation d'ordre entre les coordonnees
 * \param[in] coord1 : coordonnee 1
 * \param[in] coord2 : coordonnee 2
 */
extern booleen_t coord_egal( const coord_t * coord1 , const coord_t * coord2 ) ;  

/*!
 * \name Comparaison 
 * @{
 */
/*! 
 * \fn  int coord_comparer( const coord_t * coord1 , const coord_t * coord2 ) 
 * \brief Comparaison de 2 coordonnees 
 * \param[in] coord1 : coordonnee 1 
 * \param[in] coord2 : coordonnee 2 
 * \return 
 * \li valeur < 0 si coord1 < coord2
 * \li 0 si coord1 = coord2 
 * \li valeur > 0 si coord1 > coord2 
 */
extern int coord_comparer( const coord_t * coord1 , const coord_t * coord2 ) ;

/*! Fonction de callback */
extern int cb_coord_comparer( const void * coord1 , const void * coord2 ) ;
/*!
 * @}
 */

/*!
 * @}
 * \name Primitives 
 * @{
 */

/*!
 * \fn coord_t * coord_creer(const dim_t ligne , const dim_t colonne) 
 * \brief Creation d'une coordonnee
 * \param[in] ligne : ordonnee 
 * \param[in] colonne : abscisse 
 */

extern coord_t * coord_creer( const dim_t ligne , const dim_t colonne ) ;


/*!
 * \name Destruction d'une coordonnee 
 * @{
 */

/*!
 * \fn err_t coord_detruire( coord_t ** coord )
 * \brief Destruction d'une coordonnee
 */

extern err_t coord_detruire( coord_t ** coord )  ; 

/*! Fonction de callback pour la destruction */
extern err_t cb_coord_detruire( void * * coord ) ; 

/*!
 * \fn err_t coord_reference_effacer( coord_t ** coord ) 
 *  \brief Effacement d'une reference 
 */
extern err_t coord_reference_effacer( coord_t ** coord )  ;

/*! Fonction de callback pour l'effacement d'une reference */
extern err_t cb_coord_reference_effacer( void * * coord ) ;

/*!
 * @}
 */

/*!
 * \fn err_t coord_saisir( coord_t ** coord ) 
 * \brief Saisie d'une coordonnee sur l'entree standard
 * 
 * La fonction creer la coordonnee ::coordonnnee. On peut arreter la saisie d'une coordonnee en tapant un 'X' dans l'indice de ligne ou de colonne.
 * \param[out] coord : coordonnee saisie 
 * \return 
 * \li OK : fin correcte, coordonne valide
 * \li FIN_SAISIE : fin correcte et arret de la saisie, coordonnee non valide
 * \li ERR_SAISIE : erreur de saisie, coordonnee incorrecte
 * \li ERR_DEB_MEMOIRE : pb de creation de la coordonnee saisie, coordonnee non valide
 */
extern err_t coord_saisir( coord_t ** coord ) ;

/*! 
 * \name Affichage d'une coordonnee
 * @{
 */

/*!
 * \fn void coord_afficher( const coord_t * coord )
 * \brief Affichage d'une coordonnee sur la sortie standard  
 */
extern void coord_afficher( const coord_t * coord ) ;

/*! Fonction de callback Affichage d'une coord sur sortie standard */
extern void cb_coord_afficher( const void * coord ) ; 

/*!
 * \fn char * coord_string_afficher( const coord_t * coord ) 
 * \brief Affichage d'une coordonnee dans une chaine de caracteres
 */

extern char * coord_string_afficher( const coord_t * coord ) ;

/*! Fonction de callback dans une chaine de caracteres */
extern char * cb_coord_string_afficher( const void * coord ) ;

/*!
 * @}
 */

/*!
 * @}
 * \name M&eacute;thode de Sauvegarde/Restauration
 * @{
 */

/*!
 * @}
 */

/*! @} */

#endif
