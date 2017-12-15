#ifndef _COMMUN_H_
#define _COMMUN_H_

#include <stdio.h>
#include <standard.h>
#include <tda.h>

/*! 
 * \file  commun.h
 * \brief Types et macros communes &agrave; tous les modules
 */
/*
 * TYPES 
 */

/*!
 * \typedef dim_t
 * \brief Type des Dimensions de damiers
 */
typedef short int dim_t ;

/*!
 * \def FICHIER_LG_NOM
 * \brief Longueur nom d'un fichier
 * \def DIR_LG_NOM
 * \brief Longueur chemin d'acces d'un fichier
 * \def DIM_NULL
 * \brief Valeur d'initialisation d'une variable dim_t
 * \def STRING_LG_MAX
 * \brief Longueur maximale d'une cha&icirc;ne de caract&egrave;res 
 */

#define FICHIER_LG_NOM 1024 
#define DIR_LG_NOM 2048 
#define DIM_NULL -1
#define STRING_LG_MAX 1024



#endif



