#ifndef _ZONE_H_
#define _ZONE_H_

#include <coord.h>

/*! 
 * \file  zone.h
 * \brief Type et primitives d'une zone
 */


/*
 * CONSTANTES 
 */
/*!
 * \def ZONE_NULL 
 * \brief Zone inexistante
 */
#define ZONE_NULL NULL

/*
 * TYPES 
 */


/*!
 * \struct zone_t 
 * \brief D&eacute;finition d'une zone
 */
typedef struct zone_s 
{
  coord_t * coin_hg ;	/*!< Coordonnees du coin sup&eacute;rieur gauche de la zone sur l'aire */
  coord_t * coin_bd ;	/*!< Coordonnees du coin inf&eacute;rieur droit de la zone sur l'aire */
} zone_t ; 

/*
 * FONCTIONS 
 */

/*!
 * \name Methodes d'acces 
 * @{
 */

/* Acces au coin supérieur gauche */
extern coord_t * zone_coin_hg_lire( const zone_t * zone ) ;

/* Acces au coin inférieur droit */
extern coord_t * zone_coin_bd_lire( const zone_t * zone ) ;

/*!
 * @}
 * \name Tests 
 * @{
 */

extern booleen_t zone_existe( const zone_t * zone ) ;

/*!
 * @}
 * \name Methodes d'affectations
 * @{
 */

/* Affectation du coin en haut à gauche */
extern
err_t zone_coin_hg_ecrire( zone_t * zone , const coord_t * coin_hg );

/* Affectation du coin en bas à droite */
extern
err_t zone_coin_bd_ecrire( zone_t * zone , const coord_t * coin_bd ) ;

/* Affectation globale d'une zone */
extern 
err_t zone_ecrire( zone_t * zone , 
		   const coord_t * coin_hg, 
		   const coord_t * coin_bd ) ;

/*!
 * @}
 */

/* Copie profonde d'une zone */
extern 
err_t zone_copier( zone_t ** z1 , const zone_t * z2 ) ;

extern 
err_t cb_zone_copier( void * * z1 , const void * z2 ) ;

/* Referencement d'une zone */
extern 
err_t zone_referencer( zone_t ** z1 , zone_t * z2 ) ;

extern 
err_t cb_zone_referencer( void * * z1 , const void * z2 ) ;

/*! 
 * @}
 * \name Cr&eacute;ation
 * @{
 */
extern
zone_t * zone_creer( const coord_t * coin_hg , 
		     const coord_t * coin_bd ) ;
/*!
 *@}
 */


/*! 
 * @}
 * \name Destruction
 * @{
 */
/* 
 * Destruction physique d'une zone 
 */

extern
err_t zone_detruire( zone_t ** zone ) ;

extern
err_t cb_zone_detruire( void * * zone ) ;

/*
 * Effacement d'une reference sur une zone 
 */

extern
err_t zone_reference_effacer( zone_t ** zone ) ;

extern
err_t cb_zone_reference_effacer( void * * zone ) ;
/*!
 *@}
 */

/*! 
 * \name Affichage d'une zone 
 * @{
 */
/* Debuggage */

extern
void zone_struct_afficher( const zone_t * zone ) ;

extern
void cb_zone_struct_afficher( const void * zone ) ;

/* Dans une chaine de caracteres */
extern 
char * zone_string_afficher( const zone_t * zone ) ;

/*!
 *@}
 */

/*!
 * @}
 * \name M&eacute;thode de Comparaison
 * @{
 */

extern 
int zone_comparer( const zone_t * z1 , const zone_t * z2 );

extern 
int cb_zone_comparer( const void * z1 , const void * z2 ) ;

/*! @} */

#endif
