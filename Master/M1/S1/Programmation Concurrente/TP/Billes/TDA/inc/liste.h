#ifndef _LISTE_H_
#define _LISTE_H_

#include <stdio.h>
#include <liste_sdd.h>
#include <liste_erreurs.h>

/*! \file liste.h
  \brief Primitives du TDA liste
*/

/*
 * FONCTIONS
 */
/*!
 * @}
 * \name Tests 
 * @{
 */

/*! Teste si la liste existe */
extern booleen_t liste_existe( const liste_t * liste) ; 

/*! Teste si la liste est vide (aucun &eacute;l&eacute;ment dedans) */
extern booleen_t liste_vide( const liste_t * liste) ; 

/*!
 * \name Methodes d'acces 
 * @{
 */

/*! Acces au nombre d'&eacute;l&eacute;ments */
extern liste_id_t liste_taille( const liste_t * liste );

/*! Acces individuel a un &eacute;l&eacute;ment de la liste */
extern void * liste_acceder( const liste_t * liste , const liste_id_t position );

/* Acces a la position du debut de liste = position du premier element */
extern liste_id_t liste_debut( const liste_t * liste ) ; 

/*! Acces a la position de fin de liste: position situee apres le dernier element */
extern liste_id_t liste_sentinelle( const liste_t * liste ) ; 

/*! Acces au premier &eacute;l&eacute;ment de la liste */
extern void * liste_premier( const liste_t * liste ) ; 

/*! Acces au dernier &eacute;l&eacute;ment de la liste */
extern void * liste_dernier( const liste_t * liste ) ; 

/*! Position de l'&eacute;l&eacute;ment suivant */
extern liste_id_t liste_suivant( const liste_t * liste , const liste_id_t position );


/*!
 * @}
 * \name Methodes d'affectations 
 * @{
 */

/*! Ajout d'un element a une position */
extern err_t liste_inserer( liste_t * liste, 
			    const void * elem ,
			    const liste_id_t position ) ;

/*! Ajout d'un element en debut de liste */
extern err_t liste_empiler( liste_t * liste , const void * elem ) ;


/*! Ajout d'un element en fin de liste */
extern err_t liste_enfiler( liste_t * liste , const void * elem ) ; 


/*! Suppression d'un element a une position */
extern void * liste_supprimer( liste_t * liste, 
			       const liste_id_t position )  ;

/*! Depilement de l'element en debut de liste */
extern void * liste_depiler( liste_t * liste ) ;


/*! Defilement de l'element en fin de liste */
extern void * liste_defiler( liste_t * liste ) ; 



/*!
 * Copie d'une liste  
 * La liste cible est cr&eacute;&eacute;e par la fonction 
 */
extern err_t liste_copier( liste_t ** liste_cible , const liste_t * liste_source ) ;

/*!
 * @}
 * \name Primitives
 * @{
 */

/*!
 * Creation d'une liste 
 */
extern liste_t * liste_creer( err_t (*fonction_affectation)( void ** e1 , const void * e2 ) , 
			      err_t (*fonction_destruction)(void ** e) );

/*!
 * Destruction d'une liste 
 */

extern err_t liste_detruire( liste_t ** liste );


/*! 
 * \name Affichage
 * @{
 */

/*!
 * Affichage d'une liste sur la sortie standard
 */

extern void liste_afficher( const liste_t * liste , 
			    void (*fonction_affichage)(const void * e) , 
			    const char separateur );
/*!
 * Affichage d'une liste dans une chaine de caracteres
 */

extern 
char *  liste_string_afficher( const liste_t * liste ,
			       char * (*fonction_string_affichage)(const void * e) , 
			       const char separateur ) ;
/*!
 * @}
 */

/*!
 * \fn err_t liste_fd_charger( liste_t ** liste ,		
 *			       FILE * const fd ,
 *                             err_t (*fonction_chargement)(void ** e, FILE * const desc ),
 *                             err_t (*fonction_destruction)(void ** e) )
 * \brief Chargement d'une liste a partir d'un descripteur de fichier 
 * \param[out] liste: liste des obsevations &agrave; charger 
 * \param[in] fd : descripteur du fichier 
 * \param[in] fonction_chargement: fonction de chargement d'un element
 * \param[in] fonction_destruction : fonction de destruction d'un element 
 */
extern err_t liste_fd_charger( liste_t ** liste ,		
			       FILE * const fd , 
			       err_t (*fonction_chargement)(void ** e, FILE * const desc ),
			       err_t (*fonction_affectation)(void ** e1 , const void * e2 ) , 
			       err_t (*fonction_destruction)(void ** e) ) ;	

/*!
 * \fn err_t liste_charger( liste_t ** liste ,		
 *			    char * const nom_fichier ,
 *                          err_t (*fonction_chargement)(void ** e, FILE * const desc ),
 *                          err_t (*fonction_destruction)(void ** e) )
 * \brief Chargement d'une liste a partir d'un fichier 
 * \param[out] liste: liste des obsevations &agrave; charger 
 * \param[in] fd : descripteur du fichier 
 * \param[in] fonction_chargement: fonction de chargement d'un element
 * \param[in] fonction_destruction : fonction de destruction d'un element 
 */
extern err_t liste_charger( liste_t ** liste ,		
			    char * const nom_fichier , 
			    err_t (*fonction_chargement)(void ** e, FILE * const desc ),
			    err_t (*fonction_affectation)( void ** e1 , const void *  e2 ) , 
			    err_t (*fonction_destruction)(void ** e) ) ;	


/*!
 * \fn err_t liste_fd_sauver( const liste_t * liste  ,
 *			       FILE * const fd ,
 *                             err_t (*fonction_sauvegarde)(const void *  e, FILE * const desc) , 
 *		               const char separateur )
 * \brief Sauvegarde d'une liste a partir d'un descripteur de fichier 
 * 
 * Le fichier doit etre ouvert en ecriture
 * \param[in] liste : liste &agrave; sauver
 * \param[in] fd : descripteur du fichier de sauvegarde (r&eacute;sultat d'un <code>fopen(...,w...)</code>)
 * \param[in] fonction_sauvegarde : fonction de sauvegarde d'un element
 * \param[in] separateur : caractere de separation entre deux elements dans le fichier de sauvegarde
 */
extern 
err_t liste_fd_sauver( const liste_t * liste  ,
		       FILE * const fd ,
		       err_t (*fonction_sauvegarde)(const void * e, FILE * const desc) , 
		       const char separateur ) ;	

/*!
 * \fn err_t liste_sauver( const liste_t * liste  ,
 *			   char * const nom_fichier ,
 *                         err_t (*fonction_sauvegarde)(const void * e, FILE * const desc) , 
 *		           const char separateur )
 * \brief Sauvegarde d'une liste dans un fichier 
 * 
 * Le fichier doit etre ouvert en ecriture
 * \param[in] liste : liste &agrave; sauver
 * \param[in] nom_fichier : nom du fichier de sauvegarde 
 * \param[in] fonction_sauvegarde : fonction de sauvegarde d'un element
 * \param[in] separateur : caractere de separation entre deux elements dans le fichier de sauvegarde
 */
extern 
err_t liste_sauver( const liste_t * liste  ,
		    char * const nom_fichier ,
		    err_t (*fonction_sauvegarde)(const void * e, FILE * const desc) , 
		    const char separateur ) ;	

/*!
 * \fn err_t liste_trier( liste_t * liste,
 *		          int (*fonction_comparaison)(const void * e1 , const void * e2) ) 
 * \brief Tri d'une liste selon a methode du tri bulles
 * \param[in,out] liste : 
 * \li in : liste non tri&eacute;e 
 * \li in : liste tri&eacute;e 
 * \param[in] fonction_comparaison :  comparaison de 2 elements e1 et e2 
 * cette fonction doit retourner  
 * \li une valeur < 0 si e1 < e2
 * \li 0 si e1 = e2 
 * \li une valeur > 0 si e1 > e2 
 */

extern 
err_t liste_trier( liste_t * liste,
		   int (*fonction_comparaison)(const void *  e1 , const void * e2) ) ;



/*!
 * \fn booleen_t liste_rechercher( const liste_t * liste,
 *				   const void * element,
 *				   int (*fonction_comparaison)(const void * e1 , const void * e2) ,
 *				   liste_id_t * indice ) 
 * \brief Recherche d'un element dans une liste 
 * \param[in] liste : liste (tri&eacute;e ou non)
 * \param[in] element : l'&eacute;l&eacute;ment recherch&eacute;  
 * \param[in] fonction_comparaison :  comparaison de 2 elements e1 et e2 
 * cette fonction doit retourner  
 * \li une valeur < 0 si e1 < e2
 * \li 0 si e1 = e2 
 * \li une valeur > 0 si e1 > e2 
 * \param[out] indice : 
 * \li si l'&eacute;l&eacute;ment  appartient &agrave; la lise alors indice de &eacute;l&eacute;ment recherch&eacute; dans la liste 
 * \li sinon -1 
 * \return 
 * \li VRAI si l'&eacute;l&eacute;ment  &agrave; &eacute;t&eacute; trouv &eacute; dans la liste
 * \li FAUX sinon 
 */
/*
 * 
 */

extern 
booleen_t liste_rechercher( const liste_t * liste,
			    const void * element,
			    int (*fonction_comparaison)(const void * e1 , const void * e2) ,
			    liste_id_t * position ) ;


/*! @} */
#endif
