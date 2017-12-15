#ifndef _STANDARD_H_
#define _STANDARD_H_

#include <stdio.h>
#include <standard_erreurs.h>

/*! 
 * \file  standard.h
 * \brief Types et macros standards
 */
/*
 * TYPES 
 */

/*!
 * \enum booleen_t
 * \brief Type bool&eacute;en
 */
typedef enum booleen_s { FAUX , VRAI } booleen_t ;

/*!
 * \typedef index_t
 * \brief Type des indices
 */
typedef int index_t ;

/*!
 * \def LG_MAX_NOM_FICHIER
 * \brief Longueur maximale pour le nom d'un fichier
 * \def LG_MAX_NOM_DIR
 * \brief Longueur maximale chemin d'acces d'un fichier
 * \def LG_MAX_STRING
 * \brief Longueur maximale d'une cha&icirc;ne de caract&egrave;res 
 */

#define LG_MAX_NOM_FICHIER 1024 
#define LG_MAX_NOM_DIR 2048 
#define LG_MAX_STRING 1024

#endif



