#ifndef _AIRE_H_
#define _AIRE_H_

#include <case.h>
#include <zone.h>
#include <liste.h>

/*! 
 * \file  aire.h
 * \brief Type et primitives d'une aire 
 */

/*
 * CONSTANTES
 */

/*!
 * \def AIRE_NULL
 * \brief Aire inexistant
 */
#define AIRE_NULL NULL 

/*!
 * \def AIRE_LARGEUR_MIN
 * \brief Largeur minimale  d'une aire
 */
#define AIRE_LARGEUR_MIN 3
/*!
 * \def AIRE_LARGEUR_MAX
 * \brief Largeur  maximale d'une aire
 */
#define AIRE_LARGEUR_MAX 123

/*!
 * \def AIRE_HAUTEUR_MIN
 * \brief Hauteur minimale  d'une aire
 */
#define AIRE_HAUTEUR_MIN 3
/*!
 * \def AIRE_HAUTEUR_MAX
 * \brief Hauteur  maximale d'une aire
 */
#define AIRE_HAUTEUR_MAX 40


/* Definition structure d'une aire */
 
/*!
 * \struct aire_t 
 * \brief Type d'une aire 
 */
typedef struct aire_s
{
  dim_t hauteur;		/*!< Hauteur de l'aire */
  dim_t largeur;		/*!< Largeur de l'aire */
  case_t ** cases ;		/*!< ensemble  des cases */
  liste_t * zones ;		/*!< liste des zones */
} aire_t ; 

/*!
 * \typedef case_id_t 
 * \brief Type d'index pour les  aires (indices, compteurs...)
 */
typedef unsigned int  aire_id_t  ;

/*
 * FONCTIONS 
 */

/*!
 * \name Methodes d'acces 
 * @{
 */
/*!
 * \fn dim_t aire_hauteur_lire( const aire * aire )
 * \brief Hauteur de l'aire 
¨* \param[in] aire : l'aire
 */
extern  dim_t aire_hauteur_lire( const aire_t * aire )  ;
/*!
 * \fn dim_t aire_largeur_lire( const aire_t * aire ) 
 * \brief Largeur de l'aire 
¨* \param[in] aire : l'aire
 */
extern  dim_t aire_largeur_lire( const aire_t * aire )  ;
/*!
 * \fn case_t ** aire_cases_lire( const aire_t * aire )
 * \brief Acces a la totalit&eacute; des cases (la surface de l'aire) 
¨* \param[in] aire : l'aire
 */
extern case_t ** aire_cases_lire( const aire_t * aire ) ;

/*!
 * \fn piece_id_t case_t * aire_case_lire( const aire_t * aire ,
 *					     const dim_t ligne , 
 *					     const dim_t colonne )
 * \brief Acces a une case de l'aire 
 * \param[in] aire : l'aire
 * \param[in] ligne : num&eacute;ro de ligne 
 * \param[in] colonne : num&eacute;ro de colonne
 */
extern case_t * aire_case_lire( const aire_t * aire ,
				const dim_t ligne , 
				const dim_t colonne ) ;

/*!
 * \fn piece_id_t aire_nb_billes_lire( const aire_t * aire )
 * \brief Donne le nombre de billes pr&eacute;sentes sur l'aire
 * \param[in] aire : l'aire
 */
extern bille_id_t aire_nb_billes_lire( const aire_t * aire ) ;

/*!
 * \fn  liste_t * aire_billes_lire( const aire_t * aire ) ;
 * \brief Donne la liste des billes pr&eacute;sentes sur l'aire
 * \param[in] aire : l'aire
 * \return une liste de references sur les billes 
 */
extern liste_t * aire_billes_lire( const aire_t * aire ) ;

/*!
 * @}
 * \name Methodes d'affectation
 * @{
 */

/*!
 * \fn err_t aire_case_ecrire( aire_t * aire , 
 *			         const dim_t ligne , 
 *			         const dim_t colonne ,
 *			         case_t * const contenu ) 
 * \brief Fonction generale de l'affectation par copie  d'une case dans une aire 
 * \param[in] aire : l'aire
 * \param[in] ligne : num&eacute;ro de ligne de la case
 * \param[in] colonne : num&eacute;ro de colonne de la case
 * \param[in] contenu : valeur &agrave; mettre dans la case =  couleur de case 
 */
extern err_t aire_case_ecrire( aire_t * aire , 
				 const dim_t ligne , 
				 const dim_t colonne ,
				 case_t * contenu ) ;

/*!
 * \fn err_t aire_case_referencer( aire_t * aire , 
 *			         const dim_t ligne , 
 *			         const dim_t colonne ,
 *			         case_t * const contenu ) 
 * \brief Fonction generale de l'affectation par reference d'une case dans une aire 
 * \param[in] aire : l'aire
 * \param[in] ligne : num&eacute;ro de ligne de la case
 * \param[in] colonne : num&eacute;ro de colonne de la case
 * \param[in] contenu : valeur &agrave; mettre dans la case =  couleur de case 
 */
extern err_t aire_case_referencer( aire_t * aire , 
				   const dim_t ligne , 
				   const dim_t colonne ,
				   case_t * contenu ) ;

/*!
 * \fn err_t aire_case_libre_ecrire( aire_t * aire , 
 *			             const dim_t ligne , 
 *			             const dim_t colonne ) 
 * \brief Fonction d'ecriture d'une case libre dans une aire 
 * \param[in] aire : l'aire
 * \param[in] ligne : num&eacute;ro de ligne de la case
 * \param[in] colonne : num&eacute;ro de colonne de la case
 */
extern err_t aire_case_libre_ecrire( aire_t * aire , 
				     const dim_t ligne , 
				     const dim_t colonne ) ; 

/*!
 * \fn err_t aire_bille_poser( aire_t * aire , 
 *			        const dim_t ligne , 
 *			        const dim_t colonne ,
 *                              bille_t * const bille ) 
 * \brief Affectation de la reference d'une bille dans la case d'une aire
 * \param[in] aire : l'aire
 * \param[in] ligne : num&eacute;ro de ligne de la case
 * \param[in] colonne : num&eacute;ro de colonne de la case
 * \param[in] bille : bille &agrave; mettre sur la case
 */
extern err_t aire_bille_poser( aire_t * aire , 
				const dim_t ligne , 
				const dim_t colonne ,
				bille_t * const bille ) ;

/*!
 * @}
 */

/*!
 * @}
 * \name Tests
 * @{
 */

/*!
 * \fn booleen_t aire_existe( const aire_t * aire )
 * \brief Teste si l'aire existe (a &eacute;t&eacute; cr&eacute;&eacute;)
 * \param[in] aire : l'aire
 * \return 
 * \li VRAI si l'aire existe
 * \li FAUX sinon 
 */
extern booleen_t aire_existe( const aire_t * aire ) ;

/*!
 * \fn booleen_t aire_vide( const aire_t * aire )
 * \brief Teste si l'aire contient des billes
 * \param[in] aire : l'aire
 * \return 
 * \li VRAI si aucune bille sur l'aire
 * \li FAUX sinon 
 */
extern booleen_t aire_vide( const aire_t * aire ) ;


/*!
 * \fn booleen_t aire_case_libre( const aire_t * aire ,
 *				  const dim_t i , 
 *				  const dim_t j ) ;
 * \brief Teste si la case d'une aire est libre 
 * \param[in] aire : l'aire
 * \param[in] i : num&eacute;ro de ligne de la case 
 * \param[in] j : num&eacute;ro de colonne de la case 
 * \return 
 * \li VRAI si la case est libre 
 * \li FAUX sinon 
 */
extern booleen_t aire_case_libre( const aire_t * aire ,
				  const dim_t i , 
				  const dim_t j ) ;

/*!
 * \fn booleen_t aire_case_bille( const aire_t * aire ,
 *				  const dim_t i , 
 *				  const dim_t j ) ;
 * \brief Teste si la case d'une aire contient une bille  
 * \param[in] aire : l'aire
 * \param[in] i : num&eacute;ro de ligne de la case 
 * \param[in] j : num&eacute;ro de colonne de la case 
 * \return 
 * \li VRAI si la case contient une bille  
 * \li FAUX sinon 
 */
extern booleen_t aire_case_bille( const aire_t * aire ,
				  const dim_t i , 
				  const dim_t j ) ;


/*!
 * \fn booleen_t aire_coord_libre( const aire_t * aire ,
 *				   coord_t * const coord ) 
 * \brief Teste si une case d'une aire est libre a partir de ses coordonnees
 * \param[in] aire : l'aire
 * \param[in] coord : coordonnnees de la case 
 * \return 
 * \li VRAI si la case est libre 
 * \li FAUX sinon 
 */
extern booleen_t aire_coord_libre( const aire_t * aire ,
				   const coord_t * coord ) ;

/*!
 * \fn booleen_t aire_coord_bille( const aire_t * aire ,
 *				   coord_t * const coord ) 
 * \brief Teste si une case d'une aire contient une bille  a partir de ses coordonnees
 * \param[in] aire : l'aire
 * \param[in] coord : coordonnnees de la case 
 * \return 
 * \li VRAI si la case contient une bille 
 * \li FAUX sinon 
 */
extern booleen_t aire_coord_bille( const aire_t * aire ,
				   const coord_t * coord ) ;

/*
 * Teste si une coordonnee appartient a une aire 
 */
/*!
 * \fn booleen_t aire_coord_appartient( const aire_t * aire , 
 *					coord_t * const coord,
 *				        obstacle_t * obstacle   ) 
 * \brief Teste si case appartient a une aire a partir de ses coordonnees
 * \param[in] aire : l'aire
 * \param[in] coord : coordonnnees de la case 
 * \param[out] obstacle : type de l'obstacle rencontr&eacute; (un bord, un coin ...)
 * \return 
 * \li VRAI si la case est dans l'aire
 * \li FAUX sinon 
 */
extern booleen_t aire_coord_appartient( const aire_t * aire , 
					const coord_t * coord ,
					obstacle_t * obstacle   ) ;

/*!
 * @}
 * \name Primitives 
 * @{
 */

/*!
 * \fn aire_t * aire_creer(const dim_t hauteur , const dim_t largeur)
 * \brief Creation d'une aire
 * \param[in] hauteur : hauteur de l'aire (nombre de lignes)
 * \param[in] largeur : largeur de l'aire (nombre de colonnes)
 */
extern aire_t * aire_creer(const dim_t hauteur , const dim_t largeur) ;

/*!
 * \name Destructions
 * @{
 */

/*!
 * \fn err_t aire_detruire( aire_t ** aire )
 * \brief Destruction d'une aire
 * \param[in,out] aire : l'aire &agrave; d&eacute;truire
 */
extern err_t aire_detruire( aire_t ** aire )  ; 

/*! Fonction de callback */
extern err_t cb_aire_detruire( void * * aire ) ;

/*!
 * \fn err_t aire_reference_effacer( aire_t ** aire )
 * \brief Destruction d'une aire
 * \param[in,out] aire : l'aire &agrave; d&eacute;truire
 */
extern err_t aire_reference_effacer( aire_t ** aire )  ; 

/*! Fonction de callback */
extern err_t cb_aire_reference_effacer( void * * aire ) ;


/*!
 * \fn err_t aire_billes_detruire( const aire_t * aire ) 
 * \brief Destruction de toutes les billes d'une aire
 * \param[in,out] aire : l'aire d&eacute;gag&eacute;e de ses billes 
 */
extern err_t aire_billes_detruire( const aire_t * aire ) ;

/*
 * \fn  err_t aire_bille_enlever( const aire_t * aire , 
 *				   bille_t * bille ) 
 * \brief Enleve une bille de l'aire (ne detruit pas la bille)
 * \param[in,out] bille : bille a detruire 
 * \param[in,out] aire : l'aire d&eacute;gag&eacute;e  de cette bille 
 * 
 */

extern err_t aire_bille_enlever( const aire_t * aire , 
				 bille_t * bille ) ;

/*
 * \fn err_t aire_case_detruire( aire_t * aire , 
 *				 const dim_t ligne , 
 *				 const dim_t colonne ) 
 * \brief Destruction d'une case de l'aire 
 * \param[in,out] aire : l'aire avec une case en moins
 * \param[in] ligne , colonne : coordonn&eacute;es de la case 
 */
extern err_t aire_case_detruire( aire_t * aire , 
				 const dim_t ligne , 
				 const dim_t colonne ) ;

/*!
 * @}
 */

/*!
 * \name Affichage d'une aire 
 * @{
 */

/*!
 * \fn void aire_afficher( const aire_t * aire )
 * \brief Affichage d'un aire 
 * \param[in] aire : l'aire 
 */
extern void aire_afficher( const aire_t * aire ) ;

/*! Fonction de callback */
extern void cb_aire_afficher( const void * aire );

/*! 
 * @}
 */

/*! 
 * \name Affectation d'une aire 
 * @{
 */

/*!
 * \fn err_t aire_copier( aire_t ** aire_cible , 
 *		            const aire_t * aire_source ) ; 
 * \brief Affectation de l'aire source dans une aire cible 
 * 
 * \param[out] aire_cible : aire cible 
 * \param[in] aire_source : aire source  
 */
extern err_t aire_copier( aire_t ** aire_cible , 
			  const aire_t * aire_source ) ; 

/*! Fonction de callback */
extern err_t cb_aire_copier( void * * aire_cible , 
			     const void * aire_source ) ;
/*!
 * \fn  err_t aire_referencer( aire_t ** aire_cible , 
 *			       aire_t * aire_source )
 * \brief Affectation globale d'un aire 
 * \param[out] aire_cible : aire cible de l'affectation 
 * \param[in] aire_source : aire source de l'affectation
 */
extern  err_t aire_referencer( aire_t ** aire_cible , 
			       aire_t * aire_source ) ; 

/*! Fonction de callback */
extern err_t cb_aire_referencer( void * * aire_cible , 
				 const void * aire_source ) ; 
/*!
 * @}
 */

/*! 
 * \name Comparaisons
 * @{
 */

/*!
 * \fn int aire_comparer( const aire_t * D1 , const aire_t * D2 )
 * \brief Comparaison de 2 aires
 * 
 * La comparaison s'effectue uniquement sur les cases du aire 
 * \param[in] D1 : aire 1 
 * \param[in] D2 : aire 2
 * \return 
 * \li valeur < 0 si D1 < D2 
 * \li 0 si D1 = D2
 * \li valeur > 0 si D1 > D2
 */
extern int aire_comparer( const aire_t * D1 , const aire_t * D2 ) ; 

/*! Fonction de callback */
extern int cb_aire_comparer( const void *  D1 , const void * D2 ) ;

/*!
 * @}
 */
/*! 
 * \name Poses d'une bille sur l'aire
 * @{
 */

/*!
 * \fn  err_t aire_bille_positionner( aire_t * aire , 
 *			             bille_t * bille )
 * \brief Positionnement initial au hasard d'une bille sur une aire 
 * \param[in,out] aire : aire vec une bille de plus
 * \param[in] bille : bille &agrave; mettre sur l'aire 
 */

extern
err_t aire_bille_positionner( aire_t * aire , 
			     bille_t * bille )  ; 

/*!
 * \fn err_t aire_bille_deplacer( aire_t * aire , 
 *			          case_t * case_depart, 
 *				  case_t * case_arrivee ,
 *                                coord_t * const coord_arrivee ) 
 * \brief Fonction qui d&eacute;place une bille sur une aire. Les coordonn&eacute;es de la bille sont mises &agrave; jour  
 * \param[in] aire : l'aire
 * \param[in] case_depart : case de d&eacute;part 
 * \param[in] case_arrivee : case d'arriv&eacute;e 
 * \param[in] coord_arrivee : coordonn&eacute;es de la case d'arrivee
 */
extern err_t aire_bille_deplacer( aire_t * aire , 
				  case_t * case_depart, 
				  case_t * case_arrivee ,
				  const coord_t * coord_arrivee ) ; 
/*!
 * @}
 */

/*! 
 * \name Gestion des zones 
 * @{
 */

/*!
 * \fn err_t aire_zone_creer( aire_t * aire , 
 *			      const coord_t * coin_hg , 
 *			      const coord_t * coin_bd ) ;
 * \brief Creation d'une zone sur l'aire. 
 * \param[in] aire : l'aire
 * \param[in] coin_hg : coordonnee du coin en haut a gauche de la zone 
 * \param[in] coin_bd : coordonnee du coin en bas a droite de la zone 
 */

extern err_t aire_zone_creer( aire_t * aire , 
			      const coord_t * coin_hg , 
			      const coord_t * coin_bd ) ;
/*! @} */

/*! @} */

#endif
