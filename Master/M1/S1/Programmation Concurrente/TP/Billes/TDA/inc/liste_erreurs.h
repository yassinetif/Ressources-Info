#ifndef _ERREUR_LISTE_H_
#define _ERREUR_LISTE_H_

/*! 
 * \file  erreurs_liste.h
 * \brief Liste des codes d'erreurs pour les listes
 */
/*
 * TYPES 
 */

#include <standard_erreurs.h>

/*
 * CODES ERREURS 
 */

/*!
 * @}
 * \name Erreurs sur les listes [30..39]
 * @{
 */

#define ERR_LISTE_MAX_LISTE	-30	/*!< Maximum de liste atteint */
#define ERR_LISTE_IND_ELEM	-31	/*<! Mauvais indice d'element dans une liste */
#define ERR_LISTE_SEEK_ELEM	-32	/*!< Recherche infructueuse d'un element dans une liste */
#define ERR_LISTE_END		-33	/*!< Fin de liste atteint avant le dernier element */
#define ERR_LISTE_NULL		-34	/*!< Liste inexistante alors qu'attendue */


/*! @} */


#endif

