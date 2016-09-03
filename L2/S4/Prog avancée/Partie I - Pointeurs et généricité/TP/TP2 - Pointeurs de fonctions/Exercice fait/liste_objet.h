#ifndef _liste_OBJET_H_
#define _liste_OBJET_H_

#include <liste_sdd.h>

extern unsigned long int liste_objet_cpt  ;

/*
 * FONCTIONS
 */

/*!
 * \name Methodes d'acces 
 * @{
 */

/*! Acces au nombre d'objets */
extern int liste_objet_nb_lire( liste_objet_t * const liste );

/*! Acces a un objets de la liste */
extern objet_t * liste_objet_elem_lire( liste_objet_t * const liste , const int ind );

/*!
 * @}
 * \name Tests 
 * @{
 */

/*! Teste si la liste existe */
extern booleen_t liste_objet_existe( liste_objet_t * const liste) ; 

/*! Teste si la liste est vide (aucun &eacute;l&eacute;ment dedans) */
extern booleen_t liste_objet_vide( liste_objet_t * const liste) ; 

/*!
 * @}
 * \name Methodes d'affectations 
 * @{
 */

/*! Affectation d'un objet */
extern err_t liste_objet_elem_ecrire( liste_objet_t * liste, 
				objet_t * const elem ,
				const int ind ) ;

/*!
 * @}
 * \name Primitives
 * @{
 */

/*!
 * Creation d'une liste 
 */
extern liste_objet_t * liste_objet_creer( const int nb);

/*!
 * Destruction d'une liste 
 */

extern err_t liste_objet_detruire( liste_objet_t ** liste );


/*! 
 * \name Affichage
 * @{
 */

/*!
 * Affichage d'une liste sur la sortie standard
 */

extern void liste_objet_afficher( liste_objet_t * const liste , 
			    const char separateur );

/*!
 * @}
 */

/*! @} */

#endif
