#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_

#include <erreur.h>

/*! 
 * \file  obstacle.h
 * \brief D&eacute;finition et Types des obstacles 
 */
/*
 * TYPES 
 */

/*! 
 * \enum obstacle_t
 * \brief Type d'un obstacle sur une aire
 *
 * Un obstacle peut &ecirc;tre:
 * \li VERTICAL
 * \li HORIZONTAL 
 * \li ROND
 * \le ANGLE_FERME
 * \le ANGLE_OUVERT
 * Les valeurs suivantes sont sp&eacute;ciales:
 * \li INFORME : sert d'initialisation &agrave; une variable de type obstacle 
 * \li FIN_OBSTACLE_T: sert de sentinelle lors du parcours de la liste des types d'obstacles existants
 */ 
typedef enum obstacle_s 
  { INFORME ,		/*!< Forme indefinie */
    VERTICAL ,		/*!< Forme verticale */
    HORIZONTAL ,	/*!< Forme horizontale */
    ROND ,		/*!< Forme ronde */
    ANGLE_FERME ,	/*!< A l'int&eacute;erieur d'un angle */
    ANGLE_OUVERT ,	/*!< A l'ext&eacute;rieur d'un angle */
    FIN_OBSTACLE_T	/*!< Fin liste des obstacles */
  } obstacle_t ; 
 
/*! 
 * \def OBSTACLE_PREMIER
 * \brief Premier obstacle de la liste des obstacles 
 * 
 * La premiere obstacle est arbitrairement celle du Nord-Ouest 
 */
#define OBSTACLE_PREMIER VERTICAL

/*! 
 * \def OBSTACLE_SENTINELLE
 * \brief Sentinelle de la liste des obstacles
 * 
 * C'est un obstacle fictif
 */
#define OBSTACLE_SENTINELLE FIN_OBSTACLE_T

/*! 
 * \def OBSTACLE_NB
 * \brief Nombre d'obstacles d&eacute;finis
 */
#define OBSTACLE_NB 5

/*! 
 * \fn  obstacle_t obstacle_suivant( obstacle_t d )
 * \brief Donne l'obstacle suivant dans la liste des obstacles
 * \param[in] d : obstacle courante 
 * \return obstacle suivant 
 */
extern obstacle_t obstacle_suivant( obstacle_t obst )  ;

/*! 
 * \fn  void obstacle_afficher( obstacle_t obst ) 
 * \brief Affiche sur la sortie standard le nom d'un obstacle
 * \param[in] obst : obstacle &agrave; afficher 
 */
extern void obstacle_afficher( obstacle_t obst ) ; 

/*! 
 * \fn  void obstacle_string_afficher( obstacle_t obst ) 
 * \brief Affiche dans une cha&icirc;ne de caract&egrave;res le nom d'un obstacle
 * \param[in] obst : obstacle &agrave; afficher 
 */
extern char * obstacle_string_afficher( obstacle_t obst ) ;

/*! 
 * \fn  void obstacle_affecter( obstacle_t * obst1 , const obstacle_t obst2 )
 * \brief Affectation d'un obstacle
 * \param[out] obst1 : obstacle cible
 * \param[in] obst2 : obstacle source 
 * \return resultat de l'affectation 
 */
extern obstacle_t obstacle_affecter( obstacle_t * obst1 , const obstacle_t obst2 ) ; 

/*! Fonction de callback */
extern err_t cb_obstacle_affecter( void ** obst1 , void * const obst2 ) ;

/*!
 * \fn obstacle_t obstacle_random()  
 * \brief Donne un obstacle au hasard
 */
extern obstacle_t obstacle_random()  ; 

/*! @} */

#endif



