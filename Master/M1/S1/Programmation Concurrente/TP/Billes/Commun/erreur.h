#ifndef _ERREUR_H_
#define _ERREUR_H_

#include <standard_erreurs.h>

/*! 
 * \file  erreur.h
 * \brief Liste des codes d'erreurs
 */
/*
 * TYPES 
 */

/*
 * CODES ERREURS 
 */

/*!
 * @}
 * \name Erreurs sur les directions 20..25
 * @{
 */

#define ERR_DIRECTION_UNK	-20	/*!< Direction inconnue */

/*!
 * @}
 * \name Erreurs sur les coordonn&eacute;es 100..149
 * @{
 */

#define ERR_COORD_NULL		-100	/*!< Operation impossible sur une bille inexistante */

/*!
 * @}
 * \name Erreurs sur les billes 150..199
 * @{
 */

#define ERR_BILLE_NULL		-150	/*!< Operation impossible sur une bille inexistante */

/*!
 * @}
 * \name Erreurs sur une case 200..299
 * @{
 */

#define ERR_CASE_NULL		-200	/*!< Operation impossible sur une case inexistante */
#define ERR_CASE_TYPE		-201	/*!< Erreur sur le type d'une case */



/*!
 * @}
 * \name Erreurs sur une zone 300..399
 * @{
 */

#define ERR_ZONE_NULL		-300	/*!< Operation impossible sur une zone inexistante */
#define ERR_ZONE_COORD		-301	/*!< Delimitations incorrecte de la zone sur une aire */


/*!
 * @}
 * \name Erreurs sur une aire 400..499
 * @{
 */

#define ERR_AIRE_NULL		-400	/*!< Operation impossible sur une aire inexistante */
#define ERR_AIRE_VALIDE		-401	/*!< Aire non valide  */
#define ERR_AIRE_COORD		-402	/*!< Mauvaises coordonnees dans une aire  */
#define ERR_AIRE_PLEINE		-403	/*!< Ajout d'une bille dans une aire o&uacute; toutes les cases sont remplies  */

/*!
 * @}
 * \name Erreurs sur un  ecran 500..599
 * @{
 */

#define ERR_ECRAN_NULL		-500	/*!< Operation impossible sur un ecran inexistant */

/*!
 * @}
 * \name Erreurs sur les mpuvements d'une bille
 * @{
 */

#define ERR_MVT_BILLE_ETOUFFEMENT	-600	/*!< Une bille est encercl&eacute;e et ne peut se d&eacute;placer */
#define ERR_MVT_BILLE_AVANCER		-601	/*!< Une bille butte contre un obstacle et ne peut avancer        */


#define ERR_ERREUR_FIN		-999	/*!< Fin liste des codes erreurs */
/*! @} */

/*!
 * \fn void erreur_afficher( const err_t code ) ;
 * \brief Affiche sur la sortie erreur le message d'erreur correspondant &agrave; un code erreur 
 * \param[in] code : code de l'erreur 
 */
extern void erreur_afficher( const err_t code ) ; 

#endif

