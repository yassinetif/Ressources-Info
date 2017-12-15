#ifndef _ERREURS_STANDARD_H_
#define _ERREURS_STANDARD_H_

/*! 
 * \file  erreurs_standard.h
 * \brief Liste des codes d'erreurs standard
 */
/*
 * TYPES 
 */

/*!
 * \typedef err_t 
 * \brief  Type code erreur 
 */
typedef int err_t ;

/*
 * CODES ERREURS 
 */

/*!
 * \def OK
 * \brief retour correct, sans erreur 
 */

#ifndef OK
#define OK 0
#endif

/*!
 * \name Erreurs standard [10..19]
 * @{
 */

#define ERR_DEB_MEMOIRE		-10	/*!< Debordement memoire */
#define ERR_EFF_MEMOIRE		-11	/*!< Erreur lors de la lib&eacute;ration de moire */
#define ERR_NOM_FICHIER		-12	/*!< Erreur sur nom d'un fichier */
#define ERR_PARAM_VIDE		-13	/*!< Une fonction a un parametre vide */
#define ERR_SAISIE		-14	/*!< Erreur dans la saisie au clavier d'un parametre */
#define FIN_SAISIE		-15	/*!< Indicateur de fin de saisie d'un parametre */
#define ERR_ERREUR_UNK		-19	/*!< Code erreur inconnu */

#endif

