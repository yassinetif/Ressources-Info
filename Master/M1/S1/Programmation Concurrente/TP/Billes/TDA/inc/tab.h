#ifndef _TAB_H_
#define _TAB_H_

#include <tab_sdd.h>

/*! 
  \file tab.h
  \brief Primitives du TDA tableau

  Un tableau contient les elements en stockage indirect: chaque case contient un pointeur sur l'element 
  Selon les fonctions d'affectation et de destruction des elements on peut choisir de faire 
*/

/*
 * FONCTIONS
 */

/*!
 * \name Methodes d'acces 
 * @{
 */

/*! 
  \brief Acces au nombre d'&eacute;l&eacute;ments 
  \fn tab_id_t tab_nb_lire( const tab_t * tab )
  \param[in] tab : tableau 
 */
extern tab_id_t tab_nb_lire( const tab_t * tab );

/*! 
  \brief Acces a un &eacute;l&eacute;ment situ&eacute; &agrave; un indice du tableau 
  \fn  void * tab_lire( const tab_t * tab , const tab_id_t ind )
  \param[in] tab : tableau 
  \param[ind] : indice 
 */
extern void * tab_lire( const tab_t * tab , const tab_id_t ind );

/*! 
  \brief Acces au premier &eacute;l&eacute;ment du tableau 
  \fn void * tab_premier_lire( const tab_t * tab )
  \param[in] tab : tableau 
 */
extern void * tab_premier_lire( const tab_t * tab ) ; 

/*! 
  \brief Acces au dernier &eacute;l&eacute;ment du tableau 
  \fn void * tab_dernier_lire( const tab_t * tab )
  \param[in] tab : tableau 
*/
extern void * tab_dernier_lire( const tab_t * tab ) ; 

/*!
 * @}
 * \name Tests 
 * @{
 */

/*!
  \brief Teste si le tableau existe 
  \fn booleen_t tab_existe( const tab_t * tab) 
  \param[in] tab : tableau 
 */
extern booleen_t tab_existe( const tab_t * tab) ; 

/*! 
  \brief Teste si le tableau est vide (aucun &eacute;l&eacute;ment dedans) 
  \fn booleen_t tab_vide( const tab_t * tab)
  \param[in] tab : tableau 
 */
extern booleen_t tab_vide( const tab_t * tab) ; 

/*!
 * @}
 * \name Methodes d'affectations 
 * @{
 */

/*! 
  \brief Affectation d'un element dans une case du tableau 
  La case doit &ecirc;tre cr&eacute;&eacute;e 
  \fn tab_affecter( tab_t * tab, 
                    const void * elem ,
		    const tab_id_t ind )
  \param[in,out] tab : tableau
  \param[in] elem : element &agrave; affecter
  \pram[in] ind : indice du tableau où l'on doit affecter l'&eacute;l&eacute;ment
 */
extern err_t tab_affecter( tab_t * tab, 
			   const void * elem ,
			   const tab_id_t ind ) ;

/*!
 * @}
 * \name Methodes d'insertion
 * La taille du tableau est incrment&eacute;e apr&egrave;s ces fonctions 
 * @{
 */

/*! 
  \brief Insertion d'un element &agrave; un indice du tableau 
  \fn err_t tab_inserer( tab_t * tab, 
			  const void * elem ,
			  const tab_id_t ind )
  \param[in] tab : tableau 
  \param[in] elem : : element &agrave; affecter
  \pram[in] ind : indice du tableau où l'on doit inserer l'&eacute;l&eacute;ment
 */
extern err_t tab_inserer( tab_t * tab, 
			  const void * elem ,
			  const tab_id_t ind ) ;

/*! 
  \brief Insertion au d&eacute;but du tableau 
  \fn tab_debut_inserer( tab_t * tab , const void * elem ) 
  \param[in] tab : tableau 
  \param[in] elem : : element &agrave; ins&eacute;rer
 */
extern err_t tab_debut_inserer( tab_t * tab , const void * elem ) ;


/*! 
  \brief Insertion &agrave; la fin du tableau
  \fn err_t tab_fin_inserer( tab_t * tab , const void * elem )
  \param[in] tab : tableau 
  \param[in] elem : : element &agrave; ins&eacute;rer
 */
extern err_t tab_fin_inserer( tab_t * tab , const void * elem ) ; 

/*!
 * @}
 * \name Methodes d'extraction
 * La taille du tableau est d&eacute;cr&eacute;ment&eacute;e apr&egrave;s ces fonctions 
 * @{
 */

/*! 
  \brief Extraction d'un element &agrave; un indice du tableau 
  \fn void * tab_extraire( tab_t * tab, 
			   const tab_id_t ind ) 
 \param[in,out] tab : tableau 
  \pram[in] ind : indice du tableau où l'on doit inserer l'&eacute;l&eacute;ment
 */
extern void * tab_extraire( tab_t * tab, 
			   const tab_id_t ind ) ;

/*! 
  \brief Extraction du premier &eacute;l&eacute;ment du tableau 
  \fn void * tab_debut_extraire( tab_t * tab  )
  \param[in,out] tab : tableau 
 */
extern void * tab_debut_extraire( tab_t * tab  ) ;


/*! 
  \brief Extraction d'un element en fin de tableau 
  \fn void * tab_fin_extraire( tab_t * tab )
  \param[in] tab : tableau 
*/
extern void * tab_fin_extraire( tab_t * tab ) ; 

/*!
 * @}
 * \name Primitives
 * @{
 */

/*!
  \brief Creation d'un tableau 
  \fn tab_t * tab_creer( const tab_id_t nb, 
			 err_t (*fonction_affectation)( void ** e1 , const void * e2 ) ,
			 err_t (*fonction_destruction)( void ** e) )
 \param[in] nb : nombre d'elements du tableau
 \param[in] fonction_affectation : 
 \param[in] fonction_destruction : 
 \return : le tableau 
 */
extern tab_t * tab_creer( const tab_id_t nb, 
			  err_t (*fonction_affectation)( void ** e1 , const void * e2 ) ,
			  err_t (*fonction_destruction)( void ** e) );

/*!
 * Destruction d'un tableau 
 * \fn err_t tab_detruire( tab_t ** tab )
 * \param[in,out] tab : tableau 
 */

extern err_t tab_detruire( tab_t ** tab );


/*! 
 * \name Affichage
 * @{
 */

/*!
 * Affichage d'un tableau sur la sortie standard
 * \fn 
 * \param[in] tab : tableau 
 */

extern void tab_afficher( const tab_t * tab , 
			  void (*fonction_affichage)(const void * e) , 
			  const char separateur );
/*!
 * Affichage d'un tableau dans une chaine de caracteres
 * \fn 
 * \param[in] tab : tableau 
 */

extern 
char *  tab_string_afficher( const tab_t * tab ,
			     char * (*fonction_string_affichage)(const void * e) , 
			     const char separateur ) ;
/*!
 * @}
 */

/*!
 * \fn err_t tab_fd_charger( tab_t ** tab ,
 *			     FILE * const fd ,
 *                           err_t (*fonction_affectation)( void ** e1 , const void * e2 ) ,	
 *                           err_t (*fonction_destruction)(void ** e) ,	
 *                           err_t (*fonction_chargement)(void ** e, FILE * const desc ) )
 * \brief Chargement d'un tableau a partir d'un descripteur de fichier
 * \param[out] tab: tab des obsevations &agrave; charger 
 * \param[in] fonction_affectation : fonction d'affectation d'un element
 * \param[in] fonction_destruction : fonction de destruction d'un element
 * \param[in] fd : descripteur du fichier 
 * \param[in] fonction_chargement: fonction de chargement d'un element
 */
extern 
err_t tab_fd_charger( tab_t ** tab ,
		      FILE * const fd , 
		      err_t (*fonction_affectation)( void ** e1 , const void * e2 ) ,   
		      err_t (*fonction_destruction)(void ** e) ,                        		
		      err_t (*fonction_chargement)(void ** e, FILE * const desc ) ) ;	

/*!
 * \fn err_t tab_charger( tab_t ** tab ,
 *			  char * const nom_fichier ,
 *                        err_t (*fonction_affectation)( void ** e1 , const void * e2 ) ,	
 *                        err_t (*fonction_destruction)(void ** e) ,	
 *                        err_t (*fonction_chargement)(void ** e, FILE * const desc ) )
 * \brief Chargement d'un tableau a partir d'un fichier 
 * \param[out] tab: tab des obsevations &agrave; charger 
 * \param[in] fonction_affectation : fonction d'affectation d'un element
 * \param[in] fonction_destruction : fonction de destruction d'un element
 * \param[in] nom_fichier : nom du fichier 
 * \param[in] fonction_chargement: fonction de chargement d'un element
 */
extern 
err_t tab_charger( tab_t ** tab  ,
		   char * const nom_fichier ,
		   err_t (*fonction_affectation)( void ** e1 , const void * e2 ) ,
		   err_t (*fonction_destruction)(void ** e) ,	
		   err_t (*fonction_chargement)(void * * e, FILE * const desc ) ) ;

/*!
 * \fn err_t tab_fd_sauver( const tab_t * tab  ,
 *			    FILE * const fd ,
 *                          err_t (*fonction_sauvegarde)(const void * e, FILE * const desc) , 
 *		            const char separateur )
 * \brief Sauvegarde d'un tableau a partir d'un descripteur de fichier 
 *
 * Le descripteur doit correspondre a un fichier ouvert en ecriture
 * \param[in] tab : tab &agrave; sauver
 * \param[in] fd : descripteur du fichier de sauvegarde (r&eacute;sultat d'un <code>fopen(...,w...)</code>)
 * \param[in] fonction_sauvegarde : fonction de sauvegarde d'un element
 * \param[in] separateur : caractere de separation entre deux elements dans le fichier de sauvegarde
 */
extern 
err_t tab_fd_sauver( const tab_t * tab  ,
		     FILE * const fd ,
		     err_t (*fonction_sauvegarde)(const void * e,  FILE * const desc) , 
		     const char separateur ) ;	
/*!
 * \fn err_t tab_sauver( const tab_t * tab  ,
 *			 char * const fd ,
 *                       err_t (*fonction_sauvegarde)(const void * e, FILE * const desc) , 
 *		         const char separateur )
 * \brief Sauvegarde d'un tableau dans un fichier 
 *
 * \param[in] tab : tab &agrave; sauver
 * \param[in] nom_fichier: nom  du fichier de sauvegarde
 * \param[in] fonction_sauvegarde : fonction de sauvegarde d'un element
 * \param[in] separateur : caractere de separation entre deux elements dans le fichier de sauvegarde
 */
extern 
err_t tab_sauver( const tab_t * tab  ,
		  char * const nom_fichier ,
		  err_t (*fonction_sauvegarde)(const void * e, FILE * const desc) ,
		  const char separateur ) ;

/*!
 * \fn err_t tab_trier( tab_t * tab,
 *		        int (*fonction_comparaison)(const void * e1 , const void * e2) ) 
 * \brief Tri d'un tableau selon a methode du tri bulles
 * \param[in,out] tab : tableau à trier
 * \param[in] fonction_comparaison :  comparaison de 2 elements e1 et e2 
 * cette fonction doit retourner  
 * \li une valeur < 0 si e1 < e2
 * \li 0 si e1 = e2 
 * \li une valeur > 0 si e1 > e2 
 */

extern 
err_t tab_trier( tab_t * tab,
		 int (*fonction_comparaison)(const void *  e1 , const void *  e2) ) ;



/*!
 * \fn booleen_t tab_rechercher( const tab_t * tab,
 *				 const void * element,
 *				 int (*fonction_comparaison)(const void * e1 , const void * e2) ,
 *				 tab_id_t * indice ) 
 * \brief Recherche d'un element dans un tableau 
 * \param[in] tab : tabeau (tri&eacute;e ou non)
 * \param[in] element : l'&eacute;l&eacute;ment recherch&eacute;  
 * \param[in] fonction_comparaison :  comparaison de 2 elements e1 et e2 
 * cette fonction doit retourner  
 * \li une valeur < 0 si e1 < e2
 * \li 0 si e1 = e2 
 * \li une valeur > 0 si e1 > e2 
 * \param[out] indice : 
 * \li si l'&eacute;l&eacute;ment  appartient &agrave; la lise alors indice de &eacute;l&eacute;ment recherch&eacute; dans le tableau 
 * \li sinon -1 
 * \return 
 * \li VRAI si l'&eacute;l&eacute;ment  &agrave; &eacute;t&eacute; trouv &eacute; dans le tableau
 * \li FAUX sinon 
 */
/*
 * 
 */

extern 
booleen_t tab_rechercher( const tab_t * tab,
			  const void * element,
			  int (*fonction_comparaison)(const void *  e1 , const void * e2) ,
			  tab_id_t * indice ) ;


/*!
 * \fn err_t tab_copier( tab_t ** tab_cible , tab_t * tab_source )
 * \brief Copie d'un tableau source dans un tableau cible 
 * Le tableau cble est cree
 * \param[out] tab_cible : tableau cible 
 * \param[in]  tab_source : tableau source
 */

extern 
err_t tab_copier( tab_t ** tab_cible , const tab_t * tab_source ) ; 


/*!
 * Permutation de 2 cases d'un tableau
 */
extern 
err_t tab_permuter( tab_t * const tab , const tab_id_t ind1 , const tab_id_t ind2 ) ;

/*! @} */
#endif
