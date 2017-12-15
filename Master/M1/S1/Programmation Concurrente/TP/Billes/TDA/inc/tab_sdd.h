#ifndef _TAB_SDD_H_
#define _TAB_SDD_H_

/*! 
 * \file tab_sdd.h
 * \brief R&eacute;alisation d'un tableau.
 *
 * Structure de Donn&eacute;es utilis&eacute;e pour repr&eacute;senter un tableau
 * Ces tableaux contiennent des &eacute;l&eacute;ments avec un type g&eacute;n&eacute;rique, c'est &agrave; dire qui peut &ecirc:tre remplac&eacute; par un autre type. 
 * Les &eacute;l&eacute;ments d'un m&ecirc;me tableau doivent &ecirc;tre du m&ecirc;me type
 */

#include <standard.h>

/*!
 * \def TAB_NULL 
 * \brief valeur d'un tableau inexistant.
 * NB : un tableau vide != tab inexistant
 */ 
#define TAB_NULL NULL

/*!
 * \def TAB_ID_NULL
 * \brief valeur d'initialisation d'un indice de tab
 */ 
#define TAB_ID_NULL -1

/*!
 * \typedef tab_id_t 
 * \brief Type de l'indice d'un tableau 
 */

typedef long int tab_id_t ;


/*!
 * \struct tab_t
 * \brief Type d'un tableau. 
 *
 * Le stockage des &eacute;l&eacute;ments est indirect. 
 */
typedef struct tab_s
{
  tab_id_t nb ;	/*!< Nombre d'&eacute;l&eacute;ments  */
  void ** tab ;	/*!< Tab des &eacute;l&eacute;ments; c'est un tableau d'elements generiques */
  /*! Fonctions invariables applicables sur tous les elements de la tab */
  err_t (*affecter)( void ** e1 , const void * e2 ) ; /*!< Fonction d'affectation d'un element */
  err_t (*detruire)( void ** e) ; /*!< Fonction de destruction d'un element */
} tab_t ;

#endif
