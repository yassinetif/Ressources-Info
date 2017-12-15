#ifndef _DIRECTION_H_
#define _DIRECTION_H_

#include <obstacle.h>

/*! 
 * \file  direction.h
 * \brief D&eacute;finition et Types des directions 
 */
/*
 * TYPES 
 */


/*! 
 * \typedef direction_t
 * \brief Type d'une direction sur une aire
 * 
 * Les directions sont dans les 4 points cardinaux et les 4 diagonales: 
 * \li Nord
 * \li Nord-Ouest 
 * \li Ouest 
 * \li Nord-Est 
 * \li Est 
 * \li Sud-Est 
 * \li Sud
 * \li Sud-Ouest 
 */ 
typedef enum direction_s { NULLE_PART , NORD , NORD_EST , EST , SUD_EST , SUD , SUD_OUEST , OUEST , NORD_OUEST , FIN_DIRECTION_T } direction_t ; 
 
 
/*! 
 * \def DIR_PREMIER
 * \brief Premiere direction de la liste des directions 
 * 
 * La premiere direction est arbitrairement celle du Nord-Ouest 
 */
#define DIR_PREMIER NORD

/*! 
 * \def DIR_SENTINELLE
 * \brief Sentinelle de la liste des directions
 * 
 * C'est une direction fictive 
 */
#define DIR_SENTINELLE FIN_DIRECTION_T

/*! 
 * \def DIR_NB
 * \brief Nombre de directions d&eacute;finies
 */
#define DIR_NB 8

/*! 
 * \fn  direction_t direction_suivante( direction_t d )
 * \brief Donne la direction suivante dans la liste des directions
 * \param[in] d : direction courante 
 * \return direction suivante 
 */
extern direction_t direction_suivante( direction_t d )  ;

/*! 
 * \fn  void direction_afficher( direction_t d ) 
 * \brief Affiche sur la sortie standard le nom d'une direction
 * \param[in] d : direction &agrave; afficher 
 */
extern void direction_afficher( direction_t d ) ; 

/*! 
 * \fn  void direction_string_afficher( direction_t d ) 
 * \brief Affiche dans une cha&icirc;ne de caract&egrave;res le nom d'une direction
 * \param[in] d : direction &agrave; afficher 
 */
extern char * direction_string_afficher( direction_t d ) ;

/*! 
 * \fn  void direction_affecter( direction_t * d1 , const direction_t d2 )
 * \brief Affectation d'une direction
 * \param[out] d1 : direction cible
 * \param[in] d2 : direction source 
 * \return resultat de l'affectation 
 */
extern direction_t direction_affecter( direction_t * d1 , const direction_t d2 ) ; 

/*! Fonction de callback */
extern err_t cb_direction_affecter( void * * d1 , void * const d2 ) ;

/*!
 * \fn direction_t direction_random()  
 * \brief Donne une direction au hasard
 */
extern direction_t direction_random()  ; 

/*!
 * \fn direction_t direction_opposee_random( const obstacle_t obstacle ,
 *                                           const direction_t direction )
 * \brief Donne une direction opposee aleatoire
 */
extern direction_t direction_opposee_random( const obstacle_t obstacle ,
					     const direction_t direction )  ; 

/*!
 * \fn direction_t direction_opposee_suivante( const obstacle_t obstacle, 
 *					       const direction_t direction , 
 *					       const direction_t direction_opposee )
 * \brief Donne la direction opposee suivante 
 * \param[in] obstacle : type de l'obstacle sur lequel on butte
 * \param[in] direction : direction pour laquelle on cherche l'opposee
 * \param[in] direction_opposee : direction opposee courante 
 */
direction_t direction_opposee_suivante( const obstacle_t obstacle, 
					const direction_t direction , 
					const direction_t direction_opposee ) ;

/*!
 * \fn int direction_opposee_nb( const obstacle_t obstacle ,
 *			         const direction_t direction ) 
 * \brief Donne le nombre de directions opposees pour une direction donnee
 * \param[in] obstacle : obstacle sur lequel on butte
 * \param[in] direction : direction pour laquelle on cherche l'opposee
 */
int direction_opposee_nb( const obstacle_t obstacle ,
			  const direction_t direction ) ;

/*!
 * \fn direction_t direction_opposee_premier( const obstacle_t obstacle ,
 *                                            const direction_t direction )  ;
 * \brief Donne la premiere direction opposee 
 * \param[in] obstacle : obstacle sur lequel on butte
 * \param[in] direction : direction pour laquelle on cherche l'opposee
 */
extern direction_t direction_opposee_premier( const obstacle_t obstacle , 
					     const direction_t direction )  ;

/*!
 * \fn direction_t direction_opposee_random_suivante( const obstacle_t obstacle ,
 *					              const direction_t direction , 
 *					              const direction_t direction_opposee )
 * \brief Donne la direction opposee suivante pour une direction de depart aleatoire
 *
 * on repart au depbut de la liste quand on atteint la fin 
 * \param[in] obstacle : obstacle sur lequel on butte
 * \param[in] direction : direction pour laquelle on cherche l'opposee
 * \param[in] direction__opposee : direction opposee courante  
 */
direction_t direction_opposee_random_suivante( const obstacle_t obstacle ,
					       const direction_t direction , 
					       const direction_t direction_opposee ) ;

/*! @} */

#endif



