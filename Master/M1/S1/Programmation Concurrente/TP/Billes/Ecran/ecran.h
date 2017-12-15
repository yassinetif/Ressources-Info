#ifndef _ECRAN_H_
#define _ECRAN_H_

#include <aire.h>
#include <ncurses.h>

/* 
 * Dans certain UBUNTU 
 * #include <ncurses/ncurses.h>
 */

/*! 
 * \file  ecran.h
 * \brief Structures et Primitives de l'&eacute;cran 
 * 
 * L'ecran est g&eacute;r&eacute; par les primitives de la biblioth&egrave;que "curses"  
 * L'ecran est divise en 2 zones : 
 * \li la zone d'affichage de l'aire
 * \li la zone d'affichage des messages
 */

/*
 * CONSTANTES
 */
/*!
 * \def ECRAN_NULL
 * \brief Valeur d'un ecran inexistant
 */
#define ECRAN_NULL NULL

/*!
 * \def ECRAN_LG_MESS
 * \brief Longueur max d'un message 
 */
#define ECRAN_LG_MESS 126

/*!
 * \def ECRAN_PAUSE_MESS
 * \brief Nombre de secondes minimum pendant lesquelles un message reste affiche 
 */
#define ECRAN_PAUSE_MESS 1

/*!
 * \def ECRAN_ATTENTE_MAX
 * \brief Nombre maximum de microsecondes entre deux deplacements d'une bille 
 * \def ECRAN_ATTENTE_MIN
 * \brief Nombre minimum de microsecondes entre deux deplacements d'une bille 
 */
#define ECRAN_ATTENTE_MAX 1000000
#define ECRAN_ATTENTE_MIN 50000
#define ECRAN_TEMPS_EXPLOSION 500000

/*
 * VARIABLES GLOBALES 
 */

/*!
 * \var Ecran_Nb_Ref
 * \brief Compteur de r&eacute;f&eacute;rences sur un objet fenetre de damier 
 */
int Ecran_Nb_Ref ; 

/*
 * TYPES
 */

/*!
 * \typedef ligne_id_t 
 * \brief type d'un index de ligne d'ecran 
 */
typedef unsigned int ligne_id_t ; 

/*!
 * \struct ecran_t 
 * \brief Type de la structure d'&eacute;cran d'un damier 
 */
typedef struct ecran_s
{
  WINDOW * aire ;		/*!< Fenetre de l'aire */
  WINDOW * messages ;		/*!< Fenetre des messages */
  ligne_id_t H_aire ;		/*!< Hauteur de la fenetre de l'aire */
  ligne_id_t L_aire ;		/*!< Largeur de la fenetre de l'aire */
  ligne_id_t y_messages ;	/*!< Ordonnee de la fenetre des messages */
  char * nom_err ;		/*!< Nom du fichier d'erreurs */
} ecran_t ; 

/*
 * FONCTIONS 
 */

/*!
 * \name Methodes d'acces 
 * @{
 */

/*!
 * \fn  WINDOWS * ecran_aire_lire( const ecran_t * ecran ) 
 * \brief Acces &agrave; la fenetre de l'aire
 * \param[in] ecran : ecran d'affichage 
 */
extern WINDOW * ecran_aire_lire( const ecran_t * ecran ) ;
/*!
 * \fn  WINDOW * ecran_messages_lire( const ecran_t * ecran ) 
 * \brief Acces &agrave; la fenetre des messages
 * \param[in] ecran : ecran d'affichage 
 */
extern WINDOW * ecran_messages_lire( const ecran_t * ecran ) ;
/*!
 * \fn ligne_id_t  ecran_hauteur_aire_lire( const ecran_t * ecran )
 * \brief Acces &agrave; la hauteur de la fenetre de l'aire
 * \param[in] ecran : ecran d'affichage 
 */
extern ligne_id_t  ecran_hauteur_aire_lire( const ecran_t * ecran ) ;
/*!
 * \fn ligne_id_t  ecran_largeur_aire_lire( const ecran_t * ecran )
 * \brief Acces &agrave; la largeur de la fenetre de l'aire
 * \param[in] ecran : ecran d'affichage 
 */
extern ligne_id_t  ecran_largeur_aire_lire( const ecran_t * ecran ) ;

/*!
 * \fn ligne_id_t  ecran_y_messages_lire( const ecran_t * ecran ) 
 * \brief Acces au numero de la ligne (l'ordonnee y) ou commence la fenetre des messages. 
 * \param[in] ecran : ecran d'affichage 
 */
extern ligne_id_t  ecran_y_messages_lire( const ecran_t * ecran ) ; 

/*! @} */

/*!
 * \name Tests 
 * @{
 */

/*!
 * \fn booleen_t  ecran_existe( const ecran_t * ecran ) 
 * \brief Test d'exsiatnce d'un ecran 
 * \param[in] ecran : un ecran
 */
extern booleen_t  ecran_existe( const ecran_t * ecran ) ; 
/*! @} */

  ;
/*!
 * \fn ecran_t * ecran_creer( aire_t * const aire )
 * \brief Creation fenetre de l'aire 
 *
 * La sortie erreur standard est redirig&eacute;e dans un fichier pour 
 * afficher les erreurs dans la fenetre des messages et ne pas polluer l'affichage de l'ecran
 * \param[in] aire : aire a afficher
 * \return une fenetre dans laquelle on peut afficher le aire
 */
extern ecran_t * ecran_creer( aire_t * const aire ) ;

/*!
 * \fn err_t ecran_detruire( ecran_t ** ecran )
 * \brief Destruction fenetre de l'aire 
 * \param[in,out] ecran:  fenetre &agrave; d&eacute;truire
 */
extern err_t ecran_detruire( ecran_t ** ecran )  ; 

/*!
 * \fn err_t ecran_afficher( const ecran_t * ecran  , aire_t * const aire)
 * \brief Affichage d'un aire 
 *
 * Affiche dans l'ecran: 
 * \li le aire courant
 * \li une animation des mouvements avec un message
 * \li une animation des prises avec un message 
 * \param[in] aire : aire a afficher
 * \param[in] ecran : fenetre de l'ecran dans laquelle on affichera le aire
 */
extern err_t ecran_afficher( const ecran_t * ecran  , aire_t * const aire )  ; 

/*!
 * \fn void ecran_message_afficher( const ecran_t * ecran , char * const mess ) 
 * \brief Affichage d'un message dans la fenetre des messages
 * \param[in] ecran : ecran dans lequel on affiche
 * \param[in] mess : message a afficher
 */
extern void ecran_message_afficher( const ecran_t * ecran , char * const mess ) ; 

/*!
 * \fn void ecran_message_pause_afficher( const ecran_t * ecran , char * const mess ) 
 * \brief Affichage d'un message avec une pause de ECRAN_PAUSE_MESS seconde(s) avant qu'il ne soit &eacute;ventuellment effac&eacute; 
 * dans la fenetre des messages
 * \param[in] ecran : ecran dans lequel on affiche
 * \param[in] mess : message a afficher
 */
extern void ecran_message_pause_afficher( const ecran_t * ecran , char * const mess ) ; 

/*!
 * \fn void ecran_message_effacer( const ecran_t * ecran ) 
 * \brief Efface le contenu de la fenetre des messages
 * \param[in] ecran : ecran dans lequel on affiche
 */
extern void ecran_message_effacer( const ecran_t * ecran ) ; 


/*!
 * \fn err_t ecran_bille_deplacer( ecran_t * ecran , 
 *			           aire_t * aire ,
 *			           bille_t * bille )
 * \brief Calcul et affichage d'un mouvement de bille en fonction 
 * \li de sa direction
 * \li de sa vitesse
 *
 * \param[in] ecran : ecran dans lequel on affiche
 * \param[in] aire  : aire dans laquelle la bille se d&eacute;place
 * \param[in] bille : bille &agrave; d&eacute;placer
 */
extern err_t ecran_bille_deplacer( ecran_t * ecran , 
				   aire_t * aire ,
				   bille_t * bille ) ;

/*!
 * \fn err_t err_t ecran_bille_desintegrer( ecran_t * ecran , 
 *				            bille_t * bille )
 * \brief Affichage sur l'ecran de l'explosion d'une bille 
 * l'aire n'est pas modifi&eacute;e
 * 
 * Si la variable d'environnement _DEBUG_ est d&eacute;finie alors un message de debuggage est affich&eacute;
 * ( Attributs de la bille desint&eacute;gr&ecaute;e )
 * \param[in] ecran : ecran dans lequel on affiche
 * \param[in] bille : bille &agrave; d&eacute;placer
 */
extern err_t ecran_bille_desintegrer( ecran_t * ecran , 
				      bille_t * bille ) ;


/*!
 * \fn err_t ecran_bille_positionner( ecran_t * ecran , 
 *				      aire_t * aire ,
 *				      bille_t *bille ) 
 * \brief Pose aleatoire d'une bille sur un ecran d&eacute;j&agrave; affich&eacute;
 *
 * Il faut que la bille soit d&eacute;j&agrave; positionn&eacute;e dans l'aire 
 * \param[in,out] ecran : &eacute;cran o&ugrave; on pose la bille
 * \param[in] aire : aire dans laquelle est positionn&eacute;e la bille
 * \param[in] bille: bille &agrave; poser sur l'&eacute;cran 
 */

extern err_t ecran_bille_positionner( ecran_t * ecran , 
				      aire_t * aire ,
				      bille_t *bille ) ;
  
/*!
 * \fn void ecran_stderr_afficher( ecran_t * ecran ) 
 * \brief Affichage de la sortie standard d'erreurs sur l'ecran 
 * dans la fenetre des messages 
 * \param[in] ecran : ecran dans lequel on affiche
 */

extern void ecran_stderr_afficher( ecran_t * ecran )  ; 

/*!
 * \fn  void ecran_bille_temporiser( const bille_t *bille ) 
 * \brief Temporisation du mouvement d'une bille 
 * La dur&eacute;e de la temporisation est inversement proportionnelle &agrave; la vitesse de la bille 
 *
 * \param[in] bille : bille  &agrave; afficher 
 */

extern void ecran_bille_temporiser( const bille_t * bille ) ;

#endif
