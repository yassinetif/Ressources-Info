#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include <coord.h>


/* 
 * =====
 * Gestion d'une coordonnee 
 * =====
 */

/*
 * Methodes d'acces 
 */

/* Acces a l'ordonnee */
extern  
dim_t coord_lig_lire( const coord_t * coord )  
{
  return( coord->ligne) ;
}
/* Acces a l'abscisse */
extern  
dim_t coord_col_lire( const coord_t * coord )  
{
  return( coord->colonne) ;
}



/*
 * Methodes d'affectation
 */

/* Ecriture de l'ordonnee */
extern  
err_t coord_lig_ecrire( coord_t * coord , const dim_t ligne )  
{
  coord->ligne = ligne ;
  return(OK) ;
}

/* Ecriture de l'abscisse */
extern  
err_t coord_col_ecrire( coord_t * coord , const dim_t colonne )  
{
  coord->colonne = colonne ;
  return(OK) ;
}

/* Ecriture globale */
extern  
err_t coord_ecrire( coord_t * coord , const dim_t ligne , const dim_t colonne )  
{
  err_t noerr = OK ; 

  if( (noerr = coord_lig_ecrire( coord , ligne ) ) )
    return(noerr) ; 

  if( (noerr = coord_col_ecrire( coord , colonne ) ) )
    return(noerr) ; 

  return(OK) ;
}

/* Copie de coordonnees */
extern 
err_t coord_copier( coord_t ** coord_cible , 
		    const coord_t * coord_source )
{
  err_t cr = OK ;

  /* Destruction d'une coordonnee cible s'il existe deja */
  if( coord_existe( (*coord_cible) ) )
    {
      if( (cr=coord_detruire(coord_cible)) )
	return(cr);
    }

  /* Creation d'une coordonnee cible */
  if( !coord_existe( coord_source ) )
    return(OK) ; 

  if( ((*coord_cible) = coord_creer(coord_lig_lire(coord_source),
				    coord_col_lire(coord_source) )) == NULL )
    {
      fprintf( stderr , " coord_copier: pb lors de la creation d'une coordonnee cible\n");
      return(ERR_DEB_MEMOIRE) ;
    }

  return(OK);
}

extern 
err_t cb_coord_copier( void * * coord_cible , 
		       const void *  coord_source )
{
  return(coord_copier( (coord_t **)coord_cible , 
		       (coord_t *)coord_source ) ) ;
}


/* Reference d'une coordonnees */
extern 
err_t coord_referencer( coord_t ** coord_cible , 
			coord_t * coord_source )
{
  err_t cr = OK ;

  /* Destruction d'une coordonnee cible s'il existe deja */
  if( coord_existe( (*coord_cible) ) )
    {
      if( (cr=coord_detruire(coord_cible)) )
	return(cr);
    }

  /* Reference d'une coordonnee cible */
  (*coord_cible) = coord_source ;

  return(OK);
}

extern 
err_t cb_coord_referencer( void * * coord_cible , 
			   const void *  coord_source )
{
  return(coord_referencer( (coord_t **)coord_cible , 
			   (coord_t *)coord_source ) ) ;
}


/*
 * Creation d'une coordonnee
 */

extern 
coord_t * coord_creer( const dim_t ligne , const dim_t colonne ) 
{
  coord_t * coord ;

  if( (coord=(coord_t *)malloc(sizeof(coord_t)) ) == NULL )
    {
      fprintf( stderr , "coord_creer: debordement memoire\n" ) ;
      return(NULL) ; 
    }
  
  coord->ligne = DIM_NULL ; 
  coord->colonne = DIM_NULL  ;

  if( (coord_lig_ecrire( coord , ligne ) ) )
    return(NULL) ; 
 
  if( (coord_col_ecrire( coord , colonne ) ) )
    return(NULL) ; 

  return(coord) ; 
}

/*
 * Destruction d'une coordonnee
 */

extern 
err_t coord_detruire( coord_t ** coord ) 
{

  if( ! coord_existe((*coord) ) )
    return(OK) ;

  free( (*coord) ) ;
  (*coord) = NULL ; 

  return(OK);
}

extern 
err_t cb_coord_detruire( void * * coord ) 
{
  return(coord_detruire((coord_t**)coord) ) ; 
}

/* Effacement d'une reference */
extern 
err_t coord_reference_effacer( coord_t ** coord ) 
{

  if( ! coord_existe((*coord) ) )
    return(OK) ;

  (*coord) = NULL ; 

  return(OK);
}

extern 
err_t cb_coord_reference_effacer( void * * coord ) 
{
  return(coord_reference_effacer((coord_t**)coord) ) ; 
}

/*
 * Affichage d'une coordonnee sur la sortie standard
 */

extern 
void coord_afficher( const coord_t * coord ) 
{
  if( ! coord_existe(coord) )
    {
      printf("(inexistante)");
      return ;
    }
  printf( "[%hd,%hd]" , 
	  coord_lig_lire(coord) , 
	  coord_col_lire(coord) ) ;
}

extern
void cb_coord_afficher( const void * coord ) 
{
  coord_afficher((coord_t *)coord) ;
}


/*
 * Affichage d'une coordonnee dans une chaines de caracteres
 */

extern 
char * coord_string_afficher( const coord_t * coord ) 
{
  char * s_p = (char *)malloc(sizeof(char)*STRING_LG_MAX);

  if( ! coord_existe(coord) )
    {
      strcpy(s_p , "(inexistante)");
      return(s_p) ;
    }
  sprintf( s_p , "[%hd,%hd]" , 
	   coord_lig_lire(coord) , 
	   coord_col_lire(coord) ) ;
  return(s_p) ; 
}

extern
char * cb_coord_string_afficher( const void * coord ) 
{
  return(coord_string_afficher((coord_t *)coord)) ;
}
 
/*
 * Tests
 */

extern 
booleen_t coord_existe( const coord_t * coord )
{
  if( coord == NULL )
    return(FAUX) ; 
  else
    return(VRAI) ; 
}


extern 
booleen_t coord_egal( const coord_t * coord1 , const coord_t * coord2 )
{
  /* Comparaison des pointeurs (test meme objet et NULL ) */
  if( coord1 == coord2 ) 
    return(VRAI) ; 

  if( coord_existe(coord1) && coord_existe(coord2) )
    {
      if( ( coord_lig_lire(coord1) == coord_lig_lire(coord2) ) &&
	  ( coord_col_lire(coord1) == coord_col_lire(coord2) )    )
	return(VRAI) ;
      else
	return(FAUX) ;
    }
  else
    return(FAUX) ;
}

extern 
int coord_comparer( const coord_t * coord1 , const coord_t * coord2 )
{
  if( !coord_existe(coord1) && !coord_existe(coord2) )
    return(0) ;
  
  if( coord_existe(coord1) && !coord_existe(coord2) )
    return(1) ; 
  
  if( !coord_existe(coord1) && coord_existe(coord2) )
    return(-1) ; 
  
  int cmp = coord_lig_lire(coord1) - coord_lig_lire(coord2) ;
  return( cmp ? cmp : coord_col_lire(coord1) - coord_col_lire(coord2) ) ;
}

extern 
int cb_coord_comparer( const void * coord1 , const void * coord2 )
{
  return(coord_comparer( (coord_t *) coord1 , (coord_t *) coord2 ) ) ;
}


/*
 * Saisie d'une coordonnee sur l'entree standard
 */

extern
err_t coord_saisir( coord_t ** coord ) 
{
  char s_lig[8] ;
  char s_col[8] ;
  dim_t lig = DIM_NULL ;
  dim_t col = DIM_NULL ;
  err_t cr = OK ; 

  /* Saisie au clavier */
  fprintf( stdout , "Ligne : ")   ; fflush(stdout) ; scanf( "%s" , s_lig ) ;

  if( s_lig[0] == 'X'  )
    return( FIN_SAISIE ) ;
 
  if ( sscanf( s_lig , "%hu" , &lig ) != 1 )
    {
      fprintf( stderr , "coord_saisir: ligne incorrecte\n") ;
      return(ERR_SAISIE) ; 
    }


  fprintf( stdout , "Colonne : ") ; fflush(stdout) ; scanf( "%s" , s_col ) ;
  if(  s_col[0] == 'X' ) 
    return( FIN_SAISIE ) ;
 
  if ( sscanf( s_col , "%hu" , &col ) != 1 ) 
    {
      fprintf( stderr , "coord_saisir: colonne incorrecte\n") ;
      return(ERR_SAISIE) ; 
    }

  /* Creation de la coordonnee */
  if( coord_existe( (*coord) ) )
    {
      if( (cr=coord_detruire(coord)) )
	return(cr) ;
    }
  
  if( ((*coord) = coord_creer(lig,col)) == COORD_NULL )
    {
      fprintf( stderr , "coord_saisir: pb lors de la creation d'une coordonnee saisie\n");
      return(ERR_DEB_MEMOIRE) ;
    }
  
  return(OK) ; 
}
