#ifndef _ERREUR_TAB_H_
#define _ERREUR_TAB_H_

/*! 
 * \file  tab_erreurs.h
 * \brief Liste des codes d'erreurs pour les tableaux
 */
/*
 * TYPES 
 */

/*
 * CODES ERREURS 
 */

/*!
 * @}
 * \name Erreurs sur les tableaux [20..29]
 * @{
 */

#define ERR_TAB_MAX_TAB		-20	/*!< Maximum de tableaux atteint */
#define ERR_TAB_IND_ELEM	-21	/*!< Mauvais indice d'element dans un tableau */
#define ERR_TAB_SEEK_ELEM	-22	/*!< Recherche infructueuse d'un element dans un tableau */
#define ERR_TAB_END		-23	/*!< Fin de tableau atteint avant le dernier element */
#define ERR_TAB_NULL		-24	/*!< Tableau inexistant alors qu'attendu */


/*! @} */


#endif

