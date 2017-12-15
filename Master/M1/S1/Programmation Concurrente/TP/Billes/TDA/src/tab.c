#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tab.h>
#include <tab_erreurs.h>

/*
 * Methodes d'acces 
 */

/* Nombre d'elements */

extern 
tab_id_t tab_nb_lire( const tab_t * tab )
{
  return(tab->nb );
} 

/* Acces a un element */
extern 
void * tab_lire( const tab_t * tab  , const tab_id_t ind )
{
  if( (ind < 0) || (ind > tab_nb_lire(tab)-1 ) )
    {
      fprintf( stderr , "tab_elem_lire: mauvais indice d'element [%ld] (devrait etre dans [%d..%ld])\n",
	       ind , 0 , tab_nb_lire(tab)-1 );
      return(NULL);
    }

  return( tab->tab[ind] ) ;
}


/* -- Acces au premier element */

extern 
void * tab_premier_lire( const tab_t * tab )
{
  return( tab->tab[0] ) ;
}

/* -- Acces au dernier element */

extern 
void * tab_dernier_lire( const tab_t * tab )
{
  return( tab->tab[tab->nb-1] ) ;
}


/*
 * Tests 
 */

extern 
booleen_t tab_existe( const tab_t * tab )
{
  if( tab == NULL )
    {
      return(FAUX) ; 
    }
  else
    {
      return(VRAI) ; 
    }
}

extern 
booleen_t tab_vide( const tab_t * tab )
{
  if( tab->nb == 0 )
    {
      return(VRAI) ; 
    }
  else
    {
      return(FAUX) ; 
    }
}

/*
 * Methodes d'affectation 
 */

/* -- Affectation d'un  element */
extern 
err_t tab_affecter( tab_t * tab , 
		    const void * elem ,
		    const tab_id_t ind ) 
{
  err_t noerr ;
  
#ifdef _DEBUG_
  if( (ind < 0) || (ind > tab_nb_lire(tab)-1 ) )
    {
      fprintf( stderr , "tab_elem_ecrire: mauvais indice d'element [%ld] (devrait etre dans [%d..%ld]\n",
	       ind , 0 , tab_nb_lire(tab)-1 );
      return(ERR_TAB_IND_ELEM);
    }
#endif
  if( tab->tab[ind] != NULL ) 
    {
      if( ( noerr = tab->detruire( &(tab->tab[ind]) ) ) )
	return(noerr) ;
    }

  if( (noerr = tab->affecter( &(tab->tab[ind]) ,
			      elem  )) )
	return(noerr);

  return(OK) ;
}

/* -- Insertion d'un element dans un tableau */
extern 
err_t tab_inserer( tab_t * tab , const void * elem , const tab_id_t ind ) 
{
  err_t noerr = OK ; 
  tab_id_t nb = 0 ; 
  tab_id_t i = 0 ;


  /* Assertions */
  if( ! tab_existe( tab ) ) 
    {
      return( ERR_TAB_IND_ELEM ) ;
    }

#ifdef _DEBUG_
  if( (ind < 0) || (ind > tab_nb_lire(tab) ) )
    {
      fprintf( stderr , "tab_inserer: mauvais indice d'element [%ld] (devrait etre dans [%d..%ld]\n",
	       ind , 0 , tab_nb_lire(tab) );
      return(ERR_TAB_IND_ELEM);
    }
#endif

  /* Mise a jour de la taille du tableau */
  nb = tab_nb_lire(tab) + 1 ;

  tab->nb = nb ; 

  if( nb == 1 ) 
    {
      if( ( tab->tab = malloc( sizeof(void *) ) ) == NULL ) 
	{
	  fprintf( stderr , "tab_inserer: debordement memoire %lu octets demandes\n" ,
		   sizeof(void *) ) ;
	  return(ERR_DEB_MEMOIRE) ; 
	} 
    }
  else
    {
      if( ( tab->tab = realloc( tab->tab , sizeof(void *) * nb ) ) == NULL ) 
	{
	  fprintf( stderr , "tab_inserer: debordement memoire %lu octets demandes\n" ,
		   sizeof(void *) * nb ) ;
	  return(ERR_DEB_MEMOIRE) ; 
	} 
    }
  /* Initialisation de la position ajoutee (en fin) */
  tab->tab[nb-1] = NULL ; 

  /* Decalage des pointeurs vers la fin a partir la position d'insertion*/
  for( i=nb-1 ; i>ind ; i-- ) 
    {
      tab->tab[i] = tab->tab[i-1] ;
    }

  /* Initialisation de la position d'insertion */
  tab->tab[ind] = NULL ; 

  /* Affectation du nouvel element a la position d'insertion */
  if( ( noerr = tab_affecter( tab , elem , ind ) ) )
	return(noerr) ;

  return(OK) ; 
}


/* -- Ajout d'un element en debut de tableau */
extern 
err_t tab_debut_inserer( tab_t * tab , const void * elem ) 
{
  return( tab_inserer( tab , elem , 0 ) ) ;
}

/* -- Ajout d'un element en fin de tableau */
extern 
err_t tab_fin_inserer( tab_t * tab , const void * elem ) 
{
  return( tab_inserer( tab , elem , tab_nb_lire(tab) ) ) ;
}


/* -- Extraction d'un element depuis un tableau */
extern 
void * tab_extraire( tab_t * tab , const tab_id_t ind ) 
{
  tab_id_t nb = 0 ; 
  tab_id_t i = 0 ;
  void * elem ;

  /* --- Assertions --- */
  if( ! tab_existe( tab ) ) 
    {
      fprintf( stderr , "tab_inserer: tentative d'extraction dans un tableau inexistant\n");
      return(NULL) ;
    }

  if( tab_vide( tab ) )
    return(NULL) ; 

  if( (ind < 0) || (ind > tab_nb_lire(tab)-1 ) )
    {
      fprintf( stderr , "tab_inserer: mauvais indice d'element [%ld] (devrait etre dans [%d..%ld])\n",
	       ind , 0 , tab_nb_lire(tab)-1 );
      return(NULL);
    }

  /* ----------------- */

  /* Initialisation de l'element extrait */
  nb = tab_nb_lire(tab) ;
  elem = tab->tab[ind] ; 

  /* Decalage des pointeurs depuis la position d'extraction jusqu'a la fin */
  for( i=ind ; i<nb-1 ; i++ ) 
    {
      tab->tab[i] = tab->tab[i+1] ;
    }

 /* Mise a jour de la taille du tableau */
  nb-- ; 
  tab->nb = nb ; 
 
  if( nb == 0 ) 
    {
      free(tab->tab) ; 
      tab->tab = NULL ; 
    }
  else
    {
      if( ( tab->tab = realloc( tab->tab , sizeof(void *) * nb ) ) == NULL ) 
	{
	  fprintf( stderr , "tab_inserer: debordement memoire %lu octets demandes\n" ,
		   sizeof(void *) * nb ) ;
	  return(NULL) ; 
	} 
    }

  return(elem) ; 
}

extern 
void * tab_debut_extraire(  tab_t * tab ) 
{
  return( tab_extraire(tab,0) ) ; 
}

extern 
void * tab_fin_extraire(  tab_t * tab ) 
{
  return( tab_extraire(tab, tab_nb_lire(tab)-1 ) ) ; 
}



/*
 * Creation d'un tableau 
 */
extern
tab_t * tab_creer( const tab_id_t nb, 
		   err_t (*fonction_affectation)( void ** e1 , const void * e2 ) ,
		   err_t (*fonction_destruction)(void ** e) )
{
  tab_t * tab = NULL ;
  int i = 0 ; 

  if(( tab=(tab_t*)malloc(sizeof(tab_t))) == NULL )
    {
      fprintf( stderr , "tab_creer: debordement memoire lors de la creation d'un tableau\n");
      return((tab_t *)NULL);
    }

  tab->nb = nb ;
  tab->tab = (void **)NULL ;
  if( nb > 0 ) 
    {
      if( ( tab->tab = malloc( sizeof(void *) * nb ) ) == NULL )
	{
	  fprintf( stderr , "tab_creer: debordement memoire %lu octets demandes\n" ,
		   sizeof(void *) * nb ) ;
	  return(NULL) ; 
	}
    }

  for( i=0 ; i<nb ; i++ ) 
    tab->tab[i] = NULL ; 

  tab->affecter = fonction_affectation ;
  tab->detruire = fonction_destruction ; 

  return(tab);
}

/*
 * Destruction d'un tableau 
 */

extern
err_t tab_detruire( tab_t ** tab )
{
  err_t noerr = OK ;
  tab_id_t nb ;
  tab_id_t i ;
  void * elem ;

  if( ! tab_existe((*tab)) )
    return(OK) ;

  nb = tab_nb_lire((*tab));

  for(i=0 ; i<nb ; i++)
    {
      elem = tab_lire( (*tab) , i ) ;
      if( elem == NULL )
	continue ;

      if( (noerr = (*tab)->detruire( (void **)&elem ) ) )
	return(noerr) ;

      (*tab)->tab[i] = NULL ;
    }
  free( (*tab)->tab ) ;
  free( (*tab) ) ;
  (*tab) = (tab_t *)NULL ;
  
  return(OK) ;
}


/*
 * Affichage d'un tableau sur la sortie standard
 */

extern 
void tab_afficher( const tab_t * tab ,
		   void (*fonction_affichage)(const void * e) , 
		   const char separateur )
{
  tab_id_t i ;
  tab_id_t nb ;

  if( ! tab_existe(tab) )
    {
      printf("(inexistante)" );
      return ;
    }
  
  if( tab_vide(tab) )
    {
      printf("(vide)" );
      return ;
    }
  
  nb = tab_nb_lire(tab) ; 
  for( i=0 ; i<nb ; i++ ) 
    {
      (*fonction_affichage)( tab_lire( tab , i ) ) ;
      printf("%c" , separateur ) ;
    } 
  printf( "(%ld elements)" , nb );
}


/*
 * Affichage d'un tableau dans une chaine de caracteres
 */

extern 
char *  tab_string_afficher( const tab_t * tab ,
			       char * (*fonction_string_affichage)(const void * e) , 
			       const char separateur )
{
  tab_id_t i ;
  tab_id_t nb ;
  char * str_p = NULL ; 
  char str_s[32] ; 
  char * string = (char *)malloc(LG_MAX_STRING) ; 
  size_t lg_string = 0 ; 

  if( ! tab_existe(tab) )
    {
      strcpy( string , "(inexistante)" );
      return(string) ;
    }
  
  if( tab_vide(tab) )
    {
      strcpy( string , "(vide)" );
      return(string) ;
    }

  string[0] = '\0' ; 
  nb = tab_nb_lire(tab) ; 
  for( i=0 ; i<nb ; i++ ) 
    {
      str_p = (*fonction_string_affichage)( tab_lire( tab , i ) ) ;
      strcat( string , str_p ) ;  
      free( str_p ) ;
      lg_string = strlen(string) ; 
      string[lg_string] = separateur ;
      string[lg_string+1] = '\0' ;
    }   
  sprintf( str_s , "(%ld elements)" , nb );
  strcat( string , str_s ) ; 

  return(string) ;
}

/*
 * Chargement d'un tableau a partir d'un fichier 
 */
extern 
err_t tab_fd_charger( tab_t ** tab  ,							/* tableau d'elements a charger */
		      FILE * const fd ,							/* descripteur fichier de chargement */
		      err_t (*fonction_affectation)( void ** e1 , const void * e2 ) ,   /* fonction d'affecation d'un element */ 
		      err_t (*fonction_destruction)(void ** e) ,                        /* fonction de destructiuon d'un element */
		      err_t (*fonction_chargement)(void * * e, FILE * const desc ) )	/* Fonction de chargement d'un element */
{
  tab_id_t i  ;
  err_t noerr ;
  tab_id_t nb ;

  /* Destruction de la tab si elle existe deja */
  if( !tab_existe( (*tab) )  )
    {
      if( (noerr = tab_detruire( tab ) ) )
	return(noerr) ; 
    }

  if( feof(fd) )
    return(OK) ; 

  /* Lecture du nombre d'elements */
  if( fscanf( fd , "%ld\n" , &nb ) != 1 )
    {
      /* Pas d'element a charger */
      return(OK)  ;
    }

  /* Creation de la tab */
  if( ((*tab) = tab_creer(nb , fonction_affectation , fonction_destruction ) ) == NULL )
    {
      fprintf( stderr , "tab_fd_charger: debordement memoire lors de la creation de la tab (%lu elements demades)\n" , 
	       nb );
      return(ERR_DEB_MEMOIRE) ; 
    }

  /* Chargement de elements */
  for( i=0 ; i<nb ; i++ )
    {
      if( (noerr = (*fonction_chargement)( &((*tab)->tab[i]) , 
					   fd ) ) ) 
	return(noerr);
    }

  return(OK) ;
}

extern 
err_t tab_charger( tab_t ** tab  ,							/* tableau d'elements a charger */
		   char * const nom_fichier ,							/* Nom du fichier de chargement */
		   err_t (*fonction_affectation)( void ** e1 , const void * e2 ) ,	/* fonction d'affecation d'un element */ 
		   err_t (*fonction_destruction)(void ** e) ,				/* fonction de destructiuon d'un element */
		   err_t (*fonction_chargement)(void * * e, FILE * const desc ) )	/* Fonction de chargement d'un element */
{
  err_t cr = OK ; 
  FILE * fd = NULL ; 

  /* Ouverture fichier en lecture */
  if( (fd = fopen( nom_fichier , "r" ) ) == NULL )
    {
      fprintf( stderr , "tab_charger: ouvrture en lecture du fichier %s impossible\n" , 
	       nom_fichier ) ; 
      return(ERR_NOM_FICHIER) ;
    }

  /* Chargement */
  if( (cr = tab_fd_charger( tab ,
			   fd ,	
			   fonction_affectation,
			   fonction_destruction,
			    fonction_chargement ) ) )
    return(cr) ; 

  /* Fermeture */
  fclose(fd) ; 

  return(cr) ; 
}

/*
 * Sauvegarde d'un tableau dans un fichier 
 */
extern 
err_t tab_fd_sauver( const tab_t * tab  ,		/* tab a sauvegarder */
		     FILE * const fd , 		/* descripteur fichier  */
		     err_t (*fonction_sauvegarde)(const void * e, FILE * const desc) , /* Fonction de sauvegarde d'un element */
		     const char separateur ) /* Separateur d'elements */
{
  tab_id_t l  ;
  err_t noerr ;
  tab_id_t nb ;

  if( ! tab_existe(tab) )
    {      
      return(OK) ; 
    }

  /* Ecriture du nombre de tab */
  nb= tab_nb_lire(tab) ; 
  fprintf( fd , "%ld\n" , nb )  ; 
  
  /* Ecriture des tab */
  for( l=0 ; l<nb ; l++ )
    {
      if( (noerr = (*fonction_sauvegarde)( tab_lire( tab , l ) ,
					   fd ) ) ) 
	return(noerr);
      fprintf( fd , "%c" , separateur ) ;
    }

  return(OK) ;
}

/*
 * Tri d'un tableau selon la methode du tri bulles ???
 */

extern 
err_t tab_trier( tab_t * tab,
		 int (*fonction_comparaison)(const void * e1 , const void * e2) )
{
  tab_id_t nb = 0 ; 

  /*-----*/

  /* Assertion */
  if( ! tab_existe(tab)  )
    return(OK) ;

  nb = tab_nb_lire(tab) ;

  if( nb < 2 ) 
    return(OK) ; 
  
  qsort( tab->tab , nb , sizeof(void *), fonction_comparaison );

  return(OK);
}

extern 
err_t tab_sauver( const tab_t * tab  ,							/* tableau a sauvegarder */
		  char * const nom_fichier ,						/* Nom fichier sauvegarde */
		  err_t (*fonction_sauvegarde)(const void * e, FILE * const desc) ,	/* Fonction de sauvegarde d'un element */
		  const char separateur )						/* Separateur d'elements */
{
  err_t cr = OK ; 
  FILE * fd = NULL ; 

  /* Ouverture fichier en ecriture */
  if( (fd = fopen( nom_fichier , "w" ) ) == NULL )
    {
      fprintf( stderr , "tab_charger: ouvrture en ecriture du fichier %s impossible\n" , 
	       nom_fichier ) ; 
      return(ERR_NOM_FICHIER) ;
    }

  /* Sauvegarde */
  if( ( cr = tab_fd_sauver( tab  ,
			    fd ,
			    fonction_sauvegarde, 
			    separateur ) )  )
    return(cr) ; 
  
  /* Fermeture */
  fclose(fd) ; 

  return(cr) ; 
}

/*
 * Recherche d'un element dans un tableau 
 */

extern 
booleen_t tab_rechercher( const tab_t * tab,
			  const void * element,
			  int (*fonction_comparaison)(const void * e1 , const void * e2) ,
			  tab_id_t * indice )
{
  tab_id_t nb = 0 ; 
  tab_id_t i = 0 ; 
  booleen_t trouve = FAUX ; 

  /*-----*/

  /* Initialisations */
  (*indice) = -1 ; 
  
  /* Assertions */
  if( ! tab_existe( tab ) )
    return(FAUX) ;

  /* Recherche */
  nb = tab_nb_lire(tab) ;

  while( (i<nb) && (!trouve) ) 
    {
      if( (*fonction_comparaison)(&(tab->tab[i]) , &element ) == 0 )
	trouve = VRAI ;
      else
	i++ ;
    }
  
  if( trouve ) 
    (*indice) = i ; 
  
  return(trouve);
}


/*
 * Copie d'un tableau
 */

extern
err_t tab_copier( tab_t ** tab_cible , const tab_t * tab_source )
{
  err_t cr = OK ; 
 if( ! tab_existe( tab_source ) )
    return(OK) ; 

  tab_id_t nb = tab_nb_lire(tab_source) ;
  tab_id_t i = 0 ; 

  if( tab_existe( (*tab_cible) ) )
    {
      if( (cr = tab_detruire( tab_cible ) ) )
	return(cr) ; 
    }

  if( ( (*tab_cible) = tab_creer(nb , 
				 tab_source->affecter , 
				 tab_source->detruire ) ) == NULL )
    return(ERR_DEB_MEMOIRE) ;

  for( i=0 ; i< nb ; i++ )
    {
      if( (cr = tab_affecter( (*tab_cible) , 
			      tab_lire( tab_source , i ) ,
			      i ) ) ) 
	return(cr); 
    }

  return(cr) ; 
}

/*
 * Permutation de 2 cases d'un tableau
 */
extern 
err_t tab_permuter( tab_t * const tab , const tab_id_t ind1 , const tab_id_t ind2 )
{
  err_t cr = OK ;
  void * w = NULL ; 

 /* Assertions */
  if( ! tab_existe( tab ) )
    return(ERR_TAB_NULL) ;

#ifdef _DEBUG_
  if( (ind1 < 0) || (ind1 > tab_nb_lire(tab)-1 ) )
    {
      fprintf( stderr , "tab_permuter: mauvais indice d'element [%ld] (devrait etre dans [%d..%ld]\n",
	       ind1 , 0 , tab_nb_lire(tab)-1 );
      return(ERR_TAB_IND_ELEM);
    }

  if( (ind2 < 0) || (ind2 > tab_nb_lire(tab)-1 ) )
    {
      fprintf( stderr , "tab_permuter: mauvais indice d'element [%ld] (devrait etre dans [%d..%ld]\n",
	       ind1 , 0 , tab_nb_lire(tab)-1 );
      return(ERR_TAB_IND_ELEM);
    }
#endif

  w = tab->tab[ind1] ;
  tab->tab[ind1] = tab->tab[ind2] ;
  tab->tab[ind2] = w ; 

  return(cr) ; 
}
