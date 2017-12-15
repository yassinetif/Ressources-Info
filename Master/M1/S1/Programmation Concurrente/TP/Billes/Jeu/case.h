#ifndef _CASE_H_
#define _CASE_H_

#include <bille.h>
#include <zone.h>
#include <liste.h>

/*! 
 * \file  case.h
 * \brief Type et primitives des cases
 */

/*
 * CONSTANTES
 */

/*!
 * \def CASE_NULL 
 * \brief Case inexistante
 */
#define CASE_NULL NULL

/*
 * TYPES
 */

/*! 
 * \struct case_t 
 * \brief Definition d'une case
 */
typedef struct case_s
{
  bille_t * bille ;	/*!< Bille positionnee sur la case (eventuellement vide) */
  liste_t * zones ;	/*!< Zones a qui appartient cette case (eventuellement vide) */
} case_t  ;

/*!
 * \typedef case_id_t 
 * \brief Type d'index pour les  cases (indices, compteurs...)
 */
typedef unsigned int  case_id_t  ;

/*!
 * \name M&eacute;thodes d'acces 
 * @{
 */

/*! Acces a la bille d'une case */
extern bille_t * case_bille_lire( const case_t * c ) ;

/*! Acces a la liste des zones qui contiennent la case */
extern liste_t * case_zones_lire( const case_t * c ) ;

/*!
 * @}
 * \name M&eacute;thodes d'affectation
 * @{
 */

/*! Affectation d'une bille par reference */
extern err_t case_bille_poser( case_t * c  , bille_t * const bille ) ;
/*! Saut pour une bille d'une case a une autre */
extern err_t case_bille_deplacer( case_t * c_depart  , case_t * c_arrivee , const coord_t * coord_arrivee )  ;
/*! Effacement d'une bille  */
extern err_t case_bille_enlever( case_t * c ) ;
/*! Affectation de la liste des zones */
extern err_t case_zones_ecrire( case_t * c  , const liste_t * zones ) ;
/*! Ajout d'une zone pour laquelle la case appartient */
extern err_t case_zone_ajouter( case_t * c , const zone_t * zone ) ;
/*! Afectation globale d'une case  */
extern err_t case_ecrire( case_t * c ,  bille_t * const bille , const liste_t * zones )  ; 

/*!
 * @}
 * \name Affectation d'une case par une autre
 * @{
 */
/*! Fonction standard */
extern err_t case_copier( case_t ** c1 , const case_t * c2 ) ; 
/*! Fonction de callback */
extern err_t cb_case_copier( void * * c1 , const void * c2 ) ; 
/*! @} */

/*!
 * @}
 * \name Affectation d'une reference de case 
 * @{
 */
/*! Fonction standard */
extern err_t case_referencer( case_t ** c1 , case_t * c2 ) ; 
/*! Fonction de callback */
extern err_t cb_case_referencer( void * * c1 , const void * c2 ) ; 
/*! @} */


/*!
 * @}
 * \name Tests
 * @{
 */

/*! Teste si une case existe */
extern booleen_t case_existe( const case_t * c ) ;


/*! Teste si une case comporte une bille */
extern booleen_t case_bille( const case_t * c ) ;

/*! Teste si une case est libre */
extern booleen_t case_libre( const case_t * c ) ;

/*! Teste si une case appartient a au moins une zone */
extern booleen_t case_zones( const case_t * c ) ;

/*! Teste si une case est libre et n'appartient a aucune zone */
extern booleen_t case_aire_libre( const case_t * c ) ;

/*! Teste si une case contient une bille et n'appartient a aucune zone */
extern booleen_t case_aire_bille( const case_t * c ) ;

/*! Teste si une case est libre et appartient a une zone */
extern booleen_t case_zone_libre( const case_t * c ) ;

/*! Teste si une case contient une bille et appartient a une zone */
extern booleen_t case_zone_bille( const case_t * c ) ;

/*!
 * @}
 * \name Primitives 
 * @{
 */

/*!
 * \fn case_t case_creer()
 * \brief Creation d'une case 
 *
 * Renvoie la valeur d'initialisation d'une case<br>
 * Une case est  initialisee avec la valeur #CASE_NULL
 */
extern case_t * case_creer() ;

/*!
 * \name Destructions de cases
 * @{
 */
/*!
 * \fn err_t case_detruire( case_t ** c )
 * \brief Destruction d'une case 
 *
 */
extern err_t case_detruire( case_t ** c ) ;

/*!
 * \fn err_t cb_case_detruire( elemen_t ** c )
 * \brief Fonction de callback pour Destruire une case 
 *
 */
extern err_t cb_case_detruire( void * * c ) ;

/*!
 * \fn err_t case_reference_effacer( case_t ** c )
 * \brief Destruction d'une case 
 *
 */
extern err_t case_reference_effacer( case_t ** c ) ;

/*!
 * \fn err_t cb_case_reference_effacer( elemen_t ** c )
 * \brief Fonction de callback pour Destruire une case 
 *
 */
extern err_t cb_case_reference_effacer( void * * c ) ;

/*! @} */

/*! 
 * \fn void case_afficher( const case_t * c )
 * \brief affichage du contenu d'une case sur la sortie standard 
 * \param[in] c : une case
 */
extern void case_afficher( const case_t * c )  ; 

/*! 
 * \fn void void cb_case_afficher( const void * c )
 * \brief fonction de callback pour afficher une case sur la sortie standard 
 * \param[in] c : une case
 */
extern void cb_case_afficher( const void * c ) ; 

/*! 
 * \fn void case_struct_afficher( const case_t * c )
 * \brief affichage du contenu de la tsructure d'une case sur la sortie standard 
 * \param[in] c : une case
 */
extern void case_struct_afficher( const case_t * c )  ; 

/*! 
 * \fn void void cb_case_struct_afficher( const void * c )
 * \brief fonction de callback pour afficher la structure d'une case sur la sortie standard 
 * \param[in] c : une case
 */
extern void cb_case_struct_afficher( const void * c ) ; 

/*! 
 * \fn char * case_string_afficher( const case_t * c )
 * \brief affichage du contenu d'une case dans une chaine de caracteres
 * \param[in] c : une case
 */
extern char *  case_string_afficher( const case_t * c )  ; 

/*!
 * @}
 * \name M&eacute;thode de Sauvegarde/Restauration
 * @{
 */

/*!
 * @}
 * \name M&eacute;thodes de comparaisons
 * @{
 */

/*!
 * \fn int case_comparer( const case_t * c1 , const case_t * c2 )
 * \brief Comparaison de 2 cases
 * \param[in] c1 : case 1 
 * \param[in] c2 : case 2
 * \return 
 * \li valeur < 0 si c1 < c2 
 * \li 0 si c1 = c2
 * \li valeur > 0 si c1 > c2
 */
extern int case_comparer( const case_t * c1 , const case_t * c2 ) ;

/*! Fonction de callback */
extern int cb_case_comparer( const void * c1 , const void * c2 ) ; 

/*! @} */

#endif
