#include <stdio.h>
#include <stdlib.h>

#include <commun.h>
#include <bille.h>


/*
 * Methodes d'acces 
 */

/* Acces aux coordonnees de la bille */
extern
coord_t * bille_coord_lire( const bille_t * bille ) 
{
  return(bille->coord) ; 
}

/* Acces a la direction de la bille */
extern
direction_t bille_direction_lire( const bille_t * bille ) 
{
  return(bille->direction) ; 
}


/* Acces a la vitesse de la bille */
extern
unsigned short int bille_vitesse_lire( const bille_t * bille ) 
{
  return(bille->vitesse) ; 
}

/* Acces au nombre de deplacements de la bille */
extern
unsigned int bille_nb_deplacements_lire( const bille_t * bille ) 
{
  return(bille->nb_deplacements) ; 
}


/* Acces a la marque de la bille */
extern
char bille_marque_lire( const bille_t * bille ) 
{
  return(bille->marque) ; 
}

/*
 * Tests 
 */

extern
booleen_t bille_existe( const bille_t * bille ) 
{
  if( bille == NULL )
    return(FAUX) ; 
  else
    return(VRAI);
}

extern
booleen_t bille_active( const bille_t * bille ) 
{
  if( ! bille_existe(bille) )
    return(FAUX) ; 

  if( bille_vitesse_lire(bille) == 0 )
    return(FAUX) ; 

  return(VRAI);
}



/*
 * Methodes d'affectations
 */

/* Affectation des coordonnees de la bille */
extern
err_t bille_coord_ecrire( bille_t * bille , const coord_t * coord ) 
{
  return( coord_copier( &(bille->coord) , coord ) ) ;
}


/* Affectation de la direction  de la bille */
extern
err_t bille_direction_ecrire( bille_t * bille , const direction_t direction ) 
{
  direction_affecter( &(bille->direction) , direction ) ; 
  return(OK) ; 
}

/* Affectation de la vitesse de la bille */
extern
err_t bille_vitesse_ecrire( bille_t * bille , const unsigned short int vitesse ) 
{
  bille->vitesse = vitesse ;
  return(OK) ; 
}

/* Affectation du nombre de deplacements de la bille */
extern
err_t bille_nb_deplacements_ecrire( bille_t * bille , const unsigned int nb ) 
{
  bille->nb_deplacements = nb ;
  return(OK) ; 
}

/* Affectation de la marque de la bille */
extern
err_t bille_marque_ecrire( bille_t * bille , const char marque ) 
{
  bille->marque = marque ;
  return(OK) ; 
}

/* Affectation globale d'une bille */
extern 
err_t bille_ecrire( bille_t * bille , 
		    const direction_t direction , 
		    const unsigned short int vitesse , 
		    const coord_t * coord , 
		    const char marque ) 
{
  err_t cr = OK ; 

  if( ! bille_existe(bille) )
    {
      fprintf( stderr , "bille_ecrire : tentative d'affectation d'une bille inexistante\n");
      return(ERR_BILLE_NULL);
    }

  if( (cr = bille_direction_ecrire( bille , direction) ) ) 
    return(cr) ; 
  if( (cr = bille_vitesse_ecrire( bille , vitesse ) ) )
    return(cr) ; 
  if( (cr = bille_coord_ecrire( bille , coord ) ) )
    return(cr) ; 
  if( (cr = bille_marque_ecrire( bille , marque ) ) )
    return(cr) ; 

  return(cr) ; 
}

/* Affectation d'une bille par une autre bille */
extern 
err_t bille_copier( bille_t ** b1 , const bille_t * b2 ) 
{
  err_t cr = OK ; 

  if( bille_existe((*b1)) ) 
    {
      if((cr=bille_detruire(b1) ) )
	return(cr); 
    }

  if( !bille_existe( b2 ) )
    return(OK) ; 

  if( ( (*b1) = bille_creer( bille_direction_lire(b2) ,
			     bille_vitesse_lire(b2) ,
			     bille_coord_lire(b2) , 
			     bille_marque_lire(b2) ) ) == BILLE_NULL )
    {
      return(ERR_DEB_MEMOIRE);
    }
  
  return(OK) ;
}

extern 
err_t cb_bille_copier( void * * b1 , const void * b2 ) 
{
  return( bille_copier( (bille_t **)b1 , (bille_t *)b2 ) ) ;
}


extern 
err_t bille_referencer( bille_t ** b1 , bille_t * b2 ) 
{
  err_t cr = OK ; 

  if( bille_existe((*b1)) ) 
    {
      if((cr=bille_detruire(b1) ) )
	return(cr); 
    }

  (*b1) = b2 ;

  return(OK) ;
}

extern 
err_t cb_bille_referencer( void * * b1 , const void * b2 ) 
{
  return( bille_referencer( (bille_t **)b1 , (bille_t *)b2 ) ) ;
}

/*
 * Creation d'une bille 
 */
extern
bille_t * bille_creer( const direction_t direction , 
		       const unsigned short int vitesse, 
		       const coord_t * coord , 
		       const char marque ) 
{
  bille_t * bille ;
  err_t cr = OK ; 
 
  if( (bille=(bille_t *)malloc(sizeof(bille_t)) ) == NULL )
    {
      fprintf( stderr , "bille_creer: debordement memoire %lu octets demandes\n" , 
	       (long unsigned int)sizeof(bille_t) );
      return(NULL);
    }

  bille->direction = NULLE_PART ;
  bille->vitesse = 0 ; 
  bille->nb_deplacements = 0 ; 
  bille->coord = COORD_NULL ; 
  bille->marque = ' ' ; 

  if( ( cr = bille_direction_ecrire( bille , direction ) ) )
    {
      fprintf( stderr , "bille_creer: pb dans affectation de la direction, code erreur %d\n" ,cr  );
      return(BILLE_NULL) ;
    }


  if( ( cr =bille_vitesse_ecrire( bille , vitesse ) ) )
    {
      fprintf( stderr , "bille_creer: pb dans affectation de la vitesse, code erreur %d\n" ,cr  );
      return(BILLE_NULL) ;
    }

  if( ( cr = bille_coord_ecrire( bille , coord ) ) )
    {
      fprintf( stderr , "bille_creer: pb dans affectation des coodonnees, code erreur %d\n" ,cr  );
      return(BILLE_NULL) ;
    }


  if( ( cr = bille_marque_ecrire( bille , marque ) ) )
    {
      fprintf( stderr , "bille_creer: pb dans affectation de la marque, code erreur %d\n" ,cr  );
      return(BILLE_NULL) ;
    }

  return(bille) ; 
}


/* 
 * Destruction d'une bille 
 */

extern
err_t bille_detruire( bille_t ** bille ) 
{
  err_t cr = OK ; 

  if( (cr = coord_detruire( &((*bille)->coord) ) ) )
    return(cr) ; 

  free( (*bille) ) ;
  (*bille) = NULL ; 

  return(cr) ; 
}

extern
err_t cb_bille_detruire( void * * bille ) 
{
  return( bille_detruire( (bille_t **) bille ) ) ;
}

/*
 * Effacement des references 
 */

extern
err_t bille_reference_effacer( bille_t ** bille ) 
{
  err_t cr = OK ; 

  (*bille) = NULL ; 

  return(cr) ; 
}

extern
err_t cb_bille_reference_effacer( void * * bille ) 
{
  return( bille_reference_effacer( (bille_t **) bille ) ) ;
} 

/*
 * Affichage
 */

/* Dans une aire de jeu */
extern
void bille_afficher( const bille_t * bille )
{
  printf( "%c" , bille_marque_lire(bille) ) ;
  return ;
}

extern
void cb_bille_afficher( const void * bille )
{ 
  return(bille_afficher( (bille_t *) bille )) ;
}

/* Debuggage */

extern
void bille_struct_afficher( const bille_t * bille )
{
  printf("{-----\n"); 
  printf(" Direction....: ") ;     direction_afficher(bille_direction_lire(bille))  ; printf("\n"); 
  printf(" Vitesse......: %u \n" , bille_vitesse_lire(bille) ) ; 
  printf(" Coordonnees..: ")     ; coord_afficher(bille_coord_lire(bille) ) ; printf("\n"); 
  printf(" Marque.......: %c\n " , bille_marque_lire(bille) ) ; 
  printf("-----}\n"); 
  return ;
}

extern
void cb_bille_struct_afficher( const void * bille )
{
  return(bille_struct_afficher( (bille_t *) bille )) ;
}


extern 
char * bille_struct_string_afficher( const bille_t * bille )
{
  char * string = (char *)malloc(sizeof(char)*STRING_LG_MAX) ;

  sprintf( string , "{ Direction: %s Vitesse: %u Coord: %s Marque: %c } " ,
	   direction_string_afficher(bille_direction_lire(bille)),
	   bille_vitesse_lire(bille) ,
	   coord_string_afficher(bille_coord_lire(bille)) ,
	   bille_marque_lire(bille) ); 
  return(string) ;
}

/*
 * Comparaison de 2 billes
 */

extern 
int bille_comparer( const bille_t * b1 , const bille_t * b2 )
{
  int cmp = 0 ; 

  /* 1) Comparaison de la marque */
  if( (cmp = bille_marque_lire(b1) - bille_marque_lire(b2) ) )
    return(cmp) ;

  /* 2) Comparaison des coordonnees */
  cmp = coord_comparer( bille_coord_lire(b1) , bille_coord_lire(b2) ) ;

  return(cmp) ;
}

extern 
int cb_bille_comparer( const void * b1 , const void * b2 )
{
  return(bille_comparer( (bille_t *)b1 , (bille_t *)b2 ) ) ;
}


/*
 * Deplacement d'une bille d'un pas en fonction 
 * en fonction de sa direction courante.
 * Cette fonction met a jour les coordonnees de la bille 
 * san tenir compte de l'aire sur laquelle elle evolue 
 */
extern 
err_t bille_deplacer( bille_t * bille ) 
{
  err_t cr = OK ;

  if( ! bille_existe(bille) )
      return(ERR_BILLE_NULL) ;

  direction_t d = bille_direction_lire(bille) ; 
  coord_t * coord = bille_coord_lire( bille ) ; 
  dim_t l = coord_lig_lire(coord) ; 
  dim_t c = coord_col_lire(coord) ; 
  dim_t new_l = DIM_NULL ;
  dim_t new_c = DIM_NULL ;
  coord_t * new_coord = COORD_NULL ; 

  switch( d ) 
    {
    case NULLE_PART	: new_l = l   ; new_c = c   ; break ;
    case NORD		: new_l = l-1 ; new_c = c   ; break ;
    case NORD_EST	: new_l = l-1 ; new_c = c+1 ; break ;
    case EST		: new_l = l   ; new_c = c+1 ; break ;
    case SUD_EST	: new_l = l+1 ; new_c = c+1 ; break ;
    case SUD		: new_l = l+1 ; new_c = c   ; break ;
    case SUD_OUEST	: new_l = l+1 ; new_c = c-1 ; break ;
    case OUEST		: new_l = l   ; new_c = c-1 ; break ;
    case NORD_OUEST	: new_l = l-1 ; new_c = c-1 ; break ;
    default : 
      fprintf( stderr , "bille_un_pas_deplacer: direction inconnue = %d\n" , d ) ;
      return(ERR_DIRECTION_UNK ) ;
    }


  if( ( new_coord = coord_creer( new_l , new_c ) ) == COORD_NULL )
    return(ERR_COORD_NULL) ;
  if( ( cr = bille_coord_ecrire( bille , new_coord ) ) ) 
    return(cr) ; 
  if( ( cr = coord_detruire( &new_coord ) ) ) 
    return(cr) ; 
  
  return(OK) ; 
}
