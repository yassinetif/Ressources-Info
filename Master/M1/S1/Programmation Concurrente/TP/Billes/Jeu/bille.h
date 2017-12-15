#ifndef _BILLE_H_
#define _BILLE_H_

#include <coord.h>
#include <direction.h>

/*! 
 * \file  bille.h
 * \brief Type et primitives d'une bille
 */


/*
 * CONSTANTES 
 */
/*!
 * \def BILLE_NULL 
 * \brief Bille inexistante
 */
#define BILLE_NULL NULL

/*!
 * \def BILLE_VITESSE_MAX
 * \brief Vitesse maximale d'une bille 
 * Sert de base pour la valeur d'initialisation de la vitesse d'une bille 
 */
#define BILLE_VITESSE_MAX 50

/*
 * TYPES 
 */

/*!
 * \struct bille_t 
 * \brief Type d'une pi&egrave;ce d'un damier
 */
typedef struct bille_s 
{
  direction_t direction ;		/*!< Direction dans laquelle va la bille */
  unsigned short int vitesse ;		/*!< Vitesse de la bille */
  unsigned int nb_deplacements ;	/*!< Nombre de d&eacute;placements de la bille */
  coord_t * coord ;			/*!< Coordonnees de la bille sur l'aire */
  char marque;				/*!< Marque caract&eacute;risant la bille */
} bille_t ; 

/*!
 * \typedef bille_id_t 
 * \brief Type d'index pour les  pi&egrave;ces (indices, compteurs...)
 */
typedef unsigned int bille_id_t  ;

/*
 * FONCTIONS 
 */

/*!
 * \name Methodes d'acces 
 * @{
 */

/*! Acces aux coordonnees de la bille */
extern coord_t * bille_coord_lire( const bille_t * bille ) ; 

/*! Acces a la direction de la bille */
extern direction_t bille_direction_lire( const bille_t * bille )  ; 

/*! Acces a la vitesse de la bille */
extern unsigned short int bille_vitesse_lire( const bille_t * bille ) ;

/*! Acces a la marque de la bille */
extern char bille_marque_lire( const bille_t * bille ) ;

/*! Acces au nombre de deplacements de la bille */
extern unsigned int bille_nb_deplacements_lire( const bille_t * bille ) ;

/*!
 * @}
 * \name Tests 
 * @{
 */

/*! si une une bille existe */
extern booleen_t bille_existe( const bille_t * bille ) ;

/*! si une bille est active: une bille est consid&eacute;r&eacute;e comme active quand sa vitesse n'est pas nulle */
extern booleen_t bille_active( const bille_t * bille ) ;

/*!
 * @}
 * \name Methodes d'affectations
 * @{
 */

/*! Affectation aux coordonnees de la bille */
extern err_t bille_coord_ecrire( bille_t * bille , const coord_t * coord ) ;

/*! Affectation de la direction  de la bille */
extern err_t bille_direction_ecrire( bille_t * bille , const direction_t direction ) ;

/*! Affectation de la vitesse de la bille */
extern err_t bille_vitesse_ecrire( bille_t * bille , const unsigned short int vitesse ) ;

/*! Affectation du nombre de deplacements de la bille */
extern err_t bille_nb_deplacements_ecrire( bille_t * bille , const unsigned int nb ) ;

/*! Affectation de la marque de la bille */
extern err_t bille_marque_ecrire( bille_t * bille , const char marque )  ; 

/*! Affectation globale d'une bille */
extern err_t bille_ecrire( bille_t * bille , 
			   const direction_t direction , 
			   const unsigned short int vitesse , 
			   const coord_t * coord , 
			   const char marque ) ;

/*! 
 * \name Affectation d'une bille par une autre  bille 
 * @{
 */

/*! Fonction standard */
extern err_t bille_copier( bille_t ** b1 , const bille_t * b2 ) ; 

/*! Fonction de callback */
extern  err_t cb_bille_copier( void * * b1 , const void * b2 ) ;

/*! 
 * \name Affectation d'une reference d'une bille 
 * @{
 */

/*! Fonction standard */
extern err_t bille_referencer( bille_t ** b1 , bille_t * b2 ) ;

/*! Fonction de callback */
extern err_t cb_bille_referencer( void * * b1 , const void * b2 ) ;

/*!
 * @}
 */

/*! 
 * @}
 * \name Primitives 
 * @{
 */

/*!
 * \fn bille_t * bille_creer( const direction_t direction , const unsigned short int vitesse , const coord_t * coord , const char marque )
 * \brief  Creation d'une bille 
 * \param[in] direction : direction de la bille 
 * \param[in] vitesse : vitesse de la bille
 * \param[in] coord : coordonnees de la bille sur l'aire
 * \param[in] marque : marque de la bille sur l'aire
 * \return la bille cr&e&ee
 */
extern 
bille_t * bille_creer(const direction_t direction , 
		      const unsigned short int vitesse , 
		      const coord_t * coord ,
		      const char marque ) ;


/*! 
 * \name Destruction d'une bille 
 * @{
 */
/*! Fonction standard */
extern err_t bille_detruire( bille_t ** bille ) ;

/*! Fonction de callback */
extern err_t cb_bille_detruire( void * * bille ) ;

/*! 
 * \name Destruction d'une reference sur une bille  
 * @{
 */
/*! Fonction standard */
extern err_t bille_reference_effacer( bille_t ** bille ) ;

/*! Fonction de callback */
extern err_t cb_bille_reference_effacer( void * * bille ) ;

/*!
 *@}
 */

/*! 
 * \name Affichage d'une bille 
 * @{
 */

/*! standard, pour une aire de jeu  */
extern void bille_afficher( const bille_t * bille ); 

/*! Fonction de callback pour une aire de jeu */
extern void cb_bille_afficher( const void * bille ) ;

/*!  Standard, pour afficher tous les attributs */
extern void bille_struct_afficher( const bille_t * bille ) ;

/*!  Fonction de callback, pour afficher tous les attributs */
extern void cb_bille_struct_afficher( const void * bille );

/*! Affichage de tous les attributs dans une cha&icirc;ne de caract&egrave;res */
extern char * bille_struct_string_afficher( const bille_t * bille ) ;

/*!
 *@}
 */

/*!
 * @}
 * \name M&eacute;thode de Sauvegarde/Restauration
 * @{
 */

/*!
 * @}
 * \name M&eacute;thode de Comparaison
 * @{
 */

/*!
 * \fn int bille_comparer( const bille_t * b1 , const bille_t * b2 )
 * \brief Comparaison de 2 pi&egrave;ces
 * 
 * La comparaison s'effectue uniquement sur les cases du bille 
 * \param[in] b1 : bille 1 
 * \param[in] b2 : bille 2
 * \return 
 * \li valeur < 0 si b1 < b2 
 * \li 0 si b1 = b2
 * \li valeur > 0 si b1 > b2
 */
extern int bille_comparer( const bille_t * b1 , const bille_t * b2 ) ;

/*! Fonction de callback */
extern int cb_bille_comparer( const void * b1 , const void * b2 ) ;




/*!
 * \fn err_t bille_deplacer( bille_t * bille )
 * 
 * \brief Deplacement d'une bille d'un pas en fonction 
 * en fonction de sa direction courante.
 * Cette fonction met a jour les coordonnees de la bille 
 * san tenir compte de l'aire sur laquelle elle evolue 
 * \param[in,out] bille : la bille &agrave; d&eacute;placer
 */
extern err_t bille_deplacer( bille_t * bille ) ;

/*! @} */

#endif
