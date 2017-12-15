#ifndef _VITESSE_H_
#define _VITESSE_H_

/*! 
 * \file  vitesse.h
 * \brief D&eacute;finition et Types des vitesses 
 */
/*
 * TYPES 
 */

/*! 
 * \typedef vitesse_t
 * \brief Type d'une vitesse 
 */ 
typedef unsigned short int vitesse_t ; 

/*! 
 * \fn  void vitesse_afficher( vitesse_t d ) 
 * \brief Affiche sur la sortie la valeur d'une vitesse
 * \param[in] d : vitesse &agrave; afficher 
 */
extern void vitesse_afficher( vitesse_t d ) ; 

/*! 
 * \fn   vitesse_t vitesse_affecter( vitesse_t * v1 , const vitesse_t t2 )
 * \brief Affectation d'une vitesse
 * \param[out] d1 : vitesse cible
 * \param[in] d1 : vitesse source
 */
extern vitesse_t vitesse_affecter( vitesse_t * v1 , const vitesse_t v2 ) ;
/*! @} */

#endif



