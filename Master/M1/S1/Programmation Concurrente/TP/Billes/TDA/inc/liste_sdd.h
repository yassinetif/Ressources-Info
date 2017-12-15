#ifndef _LISTE_SDD_H_
#define _LISTE_SDD_H_

/*! 
 * \file liste_sdd.h
 * \brief R&eacute;alisation d'une liste.
 *
 * Structure de Donn&eacute;es utilis&eacute;e pour repr&eacute;senter une liste
 * Ces listes contiennent des &eacute;l&eacute;ments avec un type g&eacute;n&eacute;rique, c'est &agrave; dire qui peut &ecirc:tre remplac&eacute; par un autre type. 
 * Les &eacute;l&eacute;ments d'une m&ecirc;me liste doivent &ecirc;tre du m&ecirc;me type
 */

#include <standard.h>
#include <tab.h>


/*!
 * \def LISTE_NULL 
 * \brief valeur d'une liste inexistante.
 * NB : une liste vide != liste inexistante
 */ 
#define LISTE_NULL NULL

/*!
 * \def LISTE_ID_NULL
 * \brief valeur d'initialisation d'un indice de liste
 */ 
#define LISTE_ID_NULL -1

/*!
 * \typedef liste_id_t 
 * \brief Type de l'indice d'une liste 
 */

typedef tab_id_t liste_id_t ;


/*!
 * \struct liste_t
 * \brief Type d'une liste. 
 *
 * Le stockage des &eacute;l&eacute;ments est indirect. 
 */
typedef tab_t liste_t ;

#endif
