#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include <ecran.h>
#include <mvt_bille.h>

/*
 * Methodes d'acces 
 */
extern 
WINDOW * ecran_aire_lire( const ecran_t * ecran ) 
{
  return( ecran->aire ) ; 
}

extern 
WINDOW * ecran_messages_lire( const ecran_t * ecran ) 
{
  return( ecran->messages ) ; 
}

extern 
ligne_id_t  ecran_hauteur_aire_lire( const ecran_t * ecran ) 
{
  return( ecran->H_aire ) ; 
}

extern 
ligne_id_t  ecran_largeur_aire_lire( const ecran_t * ecran ) 
{
  return( ecran->L_aire ) ; 
}

extern 
ligne_id_t  ecran_y_messages_lire( const ecran_t * ecran ) 
{
  return( ecran->y_messages ) ; 
}

/*
 * Creation fenetre du aire 
 */

extern 
ecran_t * ecran_creer( aire_t * const aire ) 
{
  ecran_t * ecran ;
  static booleen_t first = VRAI ; 

  if( first ) 
    {
      /* Initialisation compteur de references sur les objets ecran */
      Ecran_Nb_Ref = 0 ; 

      /* Initialisation de la bibliothèque curses */
      initscr() ;	/* Init de l'ecran */
      curs_set(0) ;	/* Curseur invisible (si supporte) */

      first = FAUX ; 
    }

  /* Incrementation des references sur un objet ecran  */
  Ecran_Nb_Ref++ ; 

  if( (ecran = (ecran_t *)malloc(sizeof(ecran_t))) == NULL )
    {
      fprintf( stderr , "ecran_creer: pd d'llaocation memoire (%lu octets demandes)\n",
	       (long unsigned int)sizeof(ecran_t) ) ;
      return(NULL) ; 	       
    }

  if( ! aire_existe(aire) )
    {
      fprintf( stderr , "ecran_creer: Warning aire inexistant\n");
      return(NULL) ;
    }

  const dim_t H = aire_hauteur_lire(aire) ;
  const dim_t L = aire_largeur_lire(aire) ;
  /*
   * Creation fenetre de l'aire 
   *
   * H = hauteur de l'aire 
   * L = Largeur de l'aire 
   *
   * Hauteur fenetre =  
   *   - ligne 0      : bord haut fenetre (.)
   *   - lignes 1 à 3 : numero (centaines+dizaines+unites)  
   *   - ligne 4      : cadre haut (-)
   *   - ligne 5      : debut fenetre aire 
   *   - ligne 5+H-1  : fin fenetre aire          
   *   - ligne 5+H    : cadre bas (-)
   *   - ligne 5+H+1  : bord bas fenetre (.)
   *
   * Largeur fenetre =  
   *   - col 0       : bord gauche fenetre (.)
   *   - col 1 à 5   : numero de ligne ( %3d ) 
   *   - col 6       : cadre gauche (|)
   *   - col 7       : debut fenetre aire
   *   - col 7+L-1   : fin fenetre aire 
   *   - col 7+L     : cadre droit (|)
   *   - col 7+L+1   : bord droit fenetre  (.)
   * 
   * Placement       = en haut et a gauche de l'ecran 
   */
  ecran->aire =  newwin( H+7 , L+9 , 0 , 0 );
  box( ecran->aire , '.' , '.' ) ;

  /* Initialisations hauteur et largeur de la fenetre de l'aire */
  ecran->L_aire = L+6 ;
  ecran->H_aire = H+5 ; 

  /* 
   * Creation fenetre des messages 
   * Hauteur fenetre = 1 ligne message 
   *                 + 2 lignes pour le cadre (bords haut et bas)
   * Largeur fenetre = nombre max longueur d'un message 
   *                 + 2 pour le cadre (bords gauche et droit) 
   *                 + 1 caractere entre bord gauche et debut message
   *                 + 1 caractere entre bord droit et fin message
   * Placement       = en dessous la fenetre du aire 
   */
   ecran->y_messages = ecran->H_aire+2  ;
  ecran->messages = newwin( 3 , ECRAN_LG_MESS+4 , ecran->y_messages , 0 );
  box( ecran->messages , '.' , '.' ) ;
  
  /* 
   * Redirection de la sortie erreur standard pour 
   * afficher les erreurs dans la fenetre des messages 
   */
  /* - creation fichier */
  char nom_err[1024] ; 
  int fd_err ; 
  sprintf( nom_err , "%d_stderr" , getpid() ) ;
  ecran->nom_err = (char*)malloc( strlen(nom_err)+1 * sizeof(char) ) ;
  strcpy( ecran->nom_err , nom_err );
  if( ( fd_err = open( nom_err , O_RDWR | O_CREAT , 0666 ) ) == -1 )
    {
      char mess[1024] ; 
      sprintf( mess , "ecran_creer: impossible d'ouvrir %s\n" , nom_err );
      perror( mess ) ; 
      return(ECRAN_NULL) ;
    }
  
  /* - redirection */
  close(2) ;
  dup(fd_err) ;
  close(fd_err) ; 

  return(ecran) ; 
}

/*
 * Destruction fenetre de l'aire 
 */

extern 
err_t ecran_detruire( ecran_t ** ecran ) 
{
  if( ecran_existe((*ecran)) )
    {
      /* Destrcution des fenetres */
      delwin((*ecran)->aire) ;
      delwin((*ecran)->messages) ;

   /* Retablissement de la sortie erreur standard a l'ecran */
      close(2) ; 
      dup(1) ; 
      unlink( (*ecran)->nom_err) ;
      free( (*ecran)->nom_err ) ;

      /* Liberation structure ecran */
      free((*ecran)) ; 

      (*ecran) = NULL ;
    }
 /* Decrementation compteur de references */
  Ecran_Nb_Ref-- ; 

  /* Fermeture bibliotheque curses */
  if( Ecran_Nb_Ref == 0 )
    {
      endwin() ; 
    }
 
  return(OK) ; 
}
 
/*
 * Affichage d'un message en bas de la fenetre
 */
extern
void ecran_message_afficher( const ecran_t * ecran , char * const mess )
{
  size_t lg_mess = strlen(mess) ; 

  if( lg_mess > ECRAN_LG_MESS ) 
    {
      /* Affichage du message directement */
      mvwprintw( ecran->messages , 1 , 2 , mess ) ; 
    }
  else
    {
      /* Effacement d'un eventuel message precedent */
      ecran_message_effacer( ecran ) ; 

      /* Affichage sur la fenetre */
      mvwprintw( ecran->messages , 1 , 2 , mess ) ; 
    }
  wrefresh( ecran->messages ) ; 
}

extern
void ecran_message_pause_afficher( const ecran_t * ecran , char * const mess )
{
  ecran_message_afficher( ecran , mess ) ;
  sleep(ECRAN_PAUSE_MESS) ;
}

/*
 * Effacement d'un message
 */
extern
void ecran_message_effacer( const ecran_t * ecran )
{  
  /* Affichage du message directement */
  werase( ecran->messages ) ; 
  box( ecran->messages ,  '.' , '.' ) ;

  wrefresh( ecran->messages ) ; 
}


/*
 * Affichage d'une case libre
 */

/* -- en dehors d'une zone */
static 
void ecran_case_libre_afficher( WINDOW * fenetre ) 
{
   wprintw( fenetre, " " );
}

/* -- dans une zone */
static 
void ecran_case_zone_libre_afficher( WINDOW * fenetre ) 
{
  wprintw( fenetre, "." );
}

/* 
 * Affichage d'une case de type inconnu 
 */
static 
void ecran_case_unk_afficher( WINDOW * fenetre ) 
{
   wprintw( fenetre, "?" );
}

/*
 * AFFICHAGE BILLES 
 */

/*
 * Affichage d'une bille
 */

static 
void ecran_bille_afficher( WINDOW * fenetre , const bille_t *bille )
{
 /*  char mess[2] ; */
/*   mess[0] = bille_marque_lire(bille) ; */
/*   mess[1] = '\0' ; */
/*   wprintw(  fenetre , mess ) ; */
  wprintw(  fenetre , "%c" , bille_marque_lire(bille) ) ;
}

/*
 *---------
 * Affichage generique d'une case 
 *---------
 */
static
void ecran_case_afficher( WINDOW * fenetre , case_t * const c ) 
{
  /* Case vide n'appartenant pas a une zone */
  if( case_aire_libre(c) )
    {
      ecran_case_libre_afficher(fenetre) ;
      return ;
    }

  /* Case vide appartenant a une zone */
  if( case_zone_libre(c) )
    {
       ecran_case_zone_libre_afficher(fenetre) ; 
       return ;
    }

  /* Case contenant une bille */
  if( case_bille(c) )
    {
      ecran_bille_afficher(fenetre , case_bille_lire(c) ) ;
      return ;
    }

  ecran_case_unk_afficher(fenetre) ;
  return ; 
}

/*
 * Affichage d'un mouvement de bille 
 */
static 
err_t ecran_mvt_bille_afficher( ecran_t * ecran  ,
				const aire_t * aire ,
				const bille_t * bille , 
				const coord_t * coord_depart ,
				const coord_t * coord_arrivee ) 
{
  char ch ;
  case_t * case_depart = CASE_NULL ; 

  /* Deplacement sur la case de depart de la bille */
  wmove( ecran->aire , 
	 coord_lig_lire(coord_depart)+5 ,
	 coord_col_lire(coord_depart)+6 ) ; 

  case_depart = aire_case_lire( aire , 
				coord_lig_lire(coord_depart) , 
				coord_col_lire(coord_depart) ) ;

  /* Capture de la marque de la bille */
  ch = winch( ecran->aire ) ;
  
  /* Effacement marque bille depart */
  /* waddch( ecran->aire , ' ' ) ;*/

  if( case_zones(case_depart) )
    {
      ecran_case_zone_libre_afficher(ecran->aire) ;
    }
  else
    {
      ecran_case_libre_afficher(ecran->aire) ;
    }
  
  /* Deplacement sur la case d'arrivee de la bille */
  wmove( ecran->aire , 
	 coord_lig_lire(coord_arrivee)+5 ,
	 coord_col_lire(coord_arrivee)+6 ) ;

  /* Ecriture bille arrivee */
  waddch( ecran->aire , ch ) ;

  /* Rafraissement ecran */
  wrefresh(ecran->aire) ; 

  /* Deplacement du curseur dans la zone des messages (pour faire plus joli dans l'affichage) */
  wmove( ecran->messages , 1 , ECRAN_LG_MESS ) ;
  wrefresh(ecran->messages) ;

  return(OK) ; 
}


extern
err_t ecran_bille_desintegrer( ecran_t * ecran , 
			       bille_t * bille ) 
{

  coord_t * coord = bille_coord_lire(bille) ; 
  dim_t l = coord_lig_lire(coord) ; 
  dim_t c = coord_col_lire(coord) ; 
  char ch1 , ch2 , ch3 , ch4 , ch5 , ch6 , ch7 , ch8 ;   

  /* Effacement bille sur l'ecran */
  wmove( ecran->aire , l+5 , c+6 ) ; 
  waddch( ecran->aire , ' ' ) ; 

  /* Explosion 1er cercle */  
  wmove( ecran->aire , l+5-1 , c+6-1 ) ; ch1 = winch( ecran->aire ) ; waddch( ecran->aire , '\\' ) ;
  wmove( ecran->aire , l+5-1 , c+6   ) ; ch2 = winch( ecran->aire ) ; waddch( ecran->aire , '|' ) ;
  wmove( ecran->aire , l+5-1 , c+6+1 ) ; ch3 = winch( ecran->aire ) ; waddch( ecran->aire , '/' ) ;
  wmove( ecran->aire , l+5   , c+6-1 ) ; ch4 = winch( ecran->aire ) ; waddch( ecran->aire , '-' ) ;
  wmove( ecran->aire , l+5   , c+6+1 ) ; ch5 = winch( ecran->aire ) ; waddch( ecran->aire , '-' ) ;
  wmove( ecran->aire , l+5+1 , c+6-1 ) ; ch6 = winch( ecran->aire ) ; waddch( ecran->aire , '/' ) ;
  wmove( ecran->aire , l+5+1 , c+6   ) ; ch7 = winch( ecran->aire ) ; waddch( ecran->aire , '|' ) ;
  wmove( ecran->aire , l+5+1 , c+6+1 ) ; ch8 = winch( ecran->aire ) ; waddch( ecran->aire , '\\' ) ;
  
  wrefresh( ecran->aire ) ; 
  usleep(ECRAN_TEMPS_EXPLOSION) ;

  wmove( ecran->aire , l+5-1 , c+6-1 ) ; waddch( ecran->aire , ch1 ) ;
  wmove( ecran->aire , l+5-1 , c+6   ) ; waddch( ecran->aire , ch2 ) ;
  wmove( ecran->aire , l+5-1 , c+6+1 ) ; waddch( ecran->aire , ch3 ) ;
  wmove( ecran->aire , l+5   , c+6-1 ) ; waddch( ecran->aire , ch4 ) ;
  wmove( ecran->aire , l+5   , c+6+1 ) ; waddch( ecran->aire , ch5 ) ;
  wmove( ecran->aire , l+5+1 , c+6-1 ) ; waddch( ecran->aire , ch6 ) ;
  wmove( ecran->aire , l+5+1 , c+6   ) ; waddch( ecran->aire , ch7 ) ;
  wmove( ecran->aire , l+5+1 , c+6+1 ) ; waddch( ecran->aire , ch8 ) ;

  wrefresh( ecran->aire ) ; 

  return(OK) ;
}

extern 
err_t ecran_bille_deplacer( ecran_t * ecran , 
			    aire_t * aire ,
			    bille_t * bille ) 
{
  err_t cr = OK ; 

  if( ! ecran_existe( ecran ) )
    {
      ecran_message_pause_afficher( ecran , "ecran_bille_deplacer: ecran inexistant") ; 
      return(ERR_ECRAN_NULL) ;
    }

  if( ! aire_existe( aire ) ) 
    {
      ecran_message_pause_afficher( ecran , "ecran_bille_deplacer: aire inexistante") ; 
      return(ERR_AIRE_NULL) ;
    }

 if( ! bille_existe( bille ) ) 
    {
      ecran_message_pause_afficher( ecran , "ecran_bille_deplacer: bille inexistante") ; 
      return(ERR_BILLE_NULL) ;
    }
  
 /* Sauvegarde positon depart */
 coord_t * coord_depart = COORD_NULL ; 
 if( ( cr = coord_copier( &coord_depart , bille_coord_lire(bille) ) ) )
   {
     ecran_message_pause_afficher( ecran , "ecran_bille_deplacer: Pb lors de la copie des coordonnees de depart ") ; 
     return(cr) ;
   }
  
  /* Calcul position d'arrivee */
  if( ( cr = mvt_bille_deplacer( bille , aire ) ) )
    {
      ecran_message_pause_afficher( ecran , "ecran_bille_deplacer: Pb lors du calcul du deplacement d'une bille") ; 
      return(cr) ;
    }

  /* Sauvegarde position d'arrivee */
  coord_t * coord_arrivee = bille_coord_lire(bille) ; 

  /* Affichage deplacement entre positions de depart et d'arrivee */
  if( ( cr = ecran_mvt_bille_afficher( ecran  ,
				       aire , 
				       bille , 
				       coord_depart ,
				       coord_arrivee ) ) )
    {
      ecran_message_pause_afficher( ecran , "ecran_bille_deplacer: Pb lors de l'affichage du deplacement d'une bille") ;
      return(cr) ;
    }
 
  return(OK) ; 
}

/*
 * Affichage de l'aire (juste les cases)
 */

static 
err_t ecran_cases_afficher( const ecran_t * ecran , aire_t * const aire ) 
{
  if( ! aire_existe(aire) )
    return( ERR_AIRE_NULL)  ;

  
  dim_t H = aire_hauteur_lire(aire) ;
  dim_t L = aire_largeur_lire(aire) ;
  dim_t i = 0 ;
  dim_t j = 0 ; 
  WINDOW * fenetre = ecran_aire_lire(ecran) ;
  /* 
   * Affichage entete de l'aire 
   */
  /* - affichage des centaines */
  mvwprintw( fenetre , 1 , 1 , "     ") ; 
  for( j=0 ; j<100 && j<L ; j++ ) wprintw( fenetre , " ") ; 
  for( j=100 ; j<L ; j++ ) wprintw( fenetre , "%1d" , j/100) ; 
  /* - affichage des dizaines */
  mvwprintw( fenetre , 2 , 1 , "     ") ; 
  for( j=0 ; j<10 && j<L ; j++ ) wprintw( fenetre , " ") ; 
  for( j=10 ; j<L ; j++ ) wprintw( fenetre , "%1d" , (j/10)%10) ; 
  /* - affichage des unites */
  mvwprintw( fenetre , 3 , 1 , "     ") ; 
  for( j=0 ; j<L ; j++ ) wprintw( fenetre , "%1d" , j%10 )  ; 
  /* - affichage du bord haut */
  mvwprintw( fenetre , 4 , 1 , "    .") ; 
  for( j=0 ; j<L ; j++ ) wprintw( fenetre , "-")            ; 
  wprintw( fenetre , ".");

  /* 
   * Affichage corps de l'aire 
   */
  for( i=0 ; i<H ; i++ ) 
    {	  
      /* Affichage une ligne */
      mvwprintw( fenetre ,  i+5 , 1 , "%3d |" , i ) ;

      for(j=0 ; j<L ; j++ ) 
	{
	  /* Affichage une case */
	  ecran_case_afficher( fenetre , aire_case_lire(aire , i , j ) ) ;
	}
      wprintw( fenetre , "|") ;
    }
  /* 
   * Affichage pied de l'aire 
   */
  mvwprintw( fenetre , H+5 , 1 , "    .") ; 
  for( j=0 ; j<L ; j++ ) wprintw( fenetre , "-")      ; 
  wprintw( fenetre , ".");

  /*
   * Rafraichissement fenetre 
   */
  wrefresh(fenetre) ;

  return(OK) ;
}

/*
 * Affichage de la structure de l'aire 
 */

extern 
err_t ecran_afficher( const ecran_t * ecran , aire_t * const aire ) 
{
  err_t cr = OK ;

  /* Affichage de l'aire  dans la fenetre principale */
  if( (cr = ecran_cases_afficher( ecran , aire ) ) )
    return(cr) ; 

  ecran_message_effacer(ecran) ;

  return(OK) ; 

}

/*
 * Tests
 */

extern 
booleen_t  ecran_existe( const ecran_t * ecran ) 
{
  if( ecran == NULL )
    return(FAUX) ; 
  else
    return(VRAI) ; 
}


/* 
 * Affichage de la sortie standard d'erreurs sur l'ecran 
 * dans la fenetre des messages 
 */

extern 
void ecran_stderr_afficher( ecran_t * ecran ) 
{
  int fd_err ; 
  char buffer[ECRAN_LG_MESS+1] ;
  int nb_lus ;

  /* Ouverture fichier erreurs */
  if(  ( fd_err = open( ecran->nom_err , O_RDONLY , 0666 ) ) == -1 ) 
    {
      char mess[1024] ; 
      sprintf( mess , "Impossible d'ouvrir le fichier %s" , ecran->nom_err ) ;
      ecran_message_pause_afficher( ecran , mess ) ;
      return ; 
    }

  /* Affichage du contenu */
  while( ( nb_lus = read( fd_err , buffer , ECRAN_LG_MESS ) ) )
    {
      buffer[nb_lus-1] = '\0' ;
      ecran_message_pause_afficher( ecran , buffer ) ;
    }

  /* Fermeture fichier erreurs */
  close(fd_err) ; 
}


/*
 * Temporisation du mouvement d'une bille 
 * La duree de la temporisation est inversement proportionnelle a la vitesse de la bille 
 */

extern 
void ecran_bille_temporiser( const bille_t *bille ) 
{
  if( ! bille_existe( bille ) )
    return ; 

   unsigned int vitesse = bille_vitesse_lire(bille) ; 
   unsigned int attente = (ECRAN_ATTENTE_MAX/vitesse < ECRAN_ATTENTE_MIN ? ECRAN_ATTENTE_MIN : ECRAN_ATTENTE_MAX/vitesse  ) ;

   usleep(attente) ;
}


/*
 * Pose d'une bille sur un ecran deja affiche
 * Il faut que la bille ait des coordonnees valides dans l'aire avant de la poser sur l'ecran
 */

static
err_t ecran_bille_poser( ecran_t * ecran , 
			 aire_t * const aire ,
			 const bille_t * bille )
{  
  coord_t * coord = bille_coord_lire(bille) ; 
  dim_t lig = coord_lig_lire(coord); 
  dim_t col = coord_col_lire(coord) ; 


  case_t * c = aire_case_lire( aire , lig , col ) ;
  if( ! case_bille( c ) )
    {
      ecran_message_pause_afficher(ecran , "ecran_bille_poser: la bille n'est pas positionnee dans l'aire");
      return(ERR_BILLE_NULL) ;
    }

  if( bille_comparer( bille , case_bille_lire(c) ) != 0 )
    {
      ecran_message_pause_afficher(ecran , "ecran_bille_poser: la bille est positionnee sur uen autre bille dans l'aire");
      return(ERR_BILLE_NULL) ;
    }

  /* Calcul déplacement du curseur à la case de la bille */
  dim_t i = lig + 5 ;
  dim_t j = col + 6 ;

  /* Pose de la bille dans cette case de l'ecran */
  WINDOW * fenetre_aire = ecran_aire_lire(ecran) ;
  mvwprintw( fenetre_aire ,  i , j , "%c" , bille_marque_lire(bille) ) ;

  /* Déplacement du curseur dans la zone des messages (pour faire plus joli dans l'affichage) */
  WINDOW * fenetre_messages = ecran_messages_lire(ecran) ;
  wmove( fenetre_messages , 1 , 2 ) ;

  /* Rafraichissement de la fenetre de l'aire */
  wrefresh( fenetre_aire ) ;

  return(OK) ;
}

/*
 * Positionnment aleatoire d'une bille sur l'ecran d'affichage d'une aire 
 */

extern
err_t ecran_bille_positionner( ecran_t * ecran , 
			       aire_t * aire ,
			       bille_t * bille )
{
  err_t cr = OK ;

  /* Assertions */
  if( ! ecran_existe(ecran) )
    return(ERR_ECRAN_NULL) ; 
  
  if( ! aire_existe(aire) )
    return(ERR_AIRE_NULL) ; 
  
  if( ! bille_existe(bille) )
    return(ERR_BILLE_NULL) ; 

  /* Recherche d'une place pour la bille sur l'aire */
  if( ( cr = aire_bille_positionner( aire , bille ) ) )
    return(cr) ; 

  /* Affichage de la bille sur l'ecran */
  if( ( cr = ecran_bille_poser( ecran , aire , bille ) ) )
    return(cr) ; 

  return(cr) ; 
}
