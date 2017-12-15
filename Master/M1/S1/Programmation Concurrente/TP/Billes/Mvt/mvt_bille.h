#ifndef _MVT_BILLE_H_
#define _MVT_BILLE_H_

#include <aire.h>

/*! 
 * \file  mvt_bille.h
 * \brief Fonctions effectuant les d&eacute;placements d'une bille sur une aire
 */


/*
 * CONSTANTES 
 */

/*
 * TYPES 
 */



/*
 * FONCTIONS 
 */

/*!
 * \fn err_t  mvt_bille_deplacer( bille_t * bille ,
				  aire_t * aire  ) 
 * \brief  D&eacute;placement d'un pas d'une bille sur l'aire en fonction
 * \li de la direction de la bille 
 * \li des limites de l'aire 
 * \param[in,out] aire  : aire dans laquelle la bille s'est d&eacute;plac&eacute;e
 * \param[in,out] bille : bille dont les coordonn&eacute;es ont &eacute;t&eacute; mises &agrave; jour
 */
extern err_t  mvt_bille_deplacer( bille_t * bille ,
				  aire_t * aire   )  ;

/*!
 *@}
 */



/*! @} */

#endif
