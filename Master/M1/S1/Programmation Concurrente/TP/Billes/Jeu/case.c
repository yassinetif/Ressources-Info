#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <case.h>


/* 
 * =====
 * Gestion d'une case 
 * =====
 */

/*
 * Methodes d'acces 
 */

extern
bille_t * case_bille_lire( const case_t * c ) 
{
  return(c->bille) ; 
}

extern 
liste_t * case_zones_lire( const case_t * c )
{
  return(c->zones) ;
}

/*
 * Methodes d'affectation
 */

extern 
err_t case_bille_poser( case_t * c  , bille_t * const bille ) 
{
  if( ! bille_existe( bille ) )
    return(OK) ; 

  c->bille = bille ;

  return(OK) ; 
}

extern 
err_t case_bille_enlever( case_t * c ) 
{
  c->bille = BILLE_NULL ;

  return(OK) ; 
}

extern 
err_t case_bille_deplacer( case_t * case_depart  , case_t * case_arrivee , const coord_t * coord_arrivee ) 
{
  err_t cr = OK ; 

  /* Assertions faites par aire_bille_deplacer */

  bille_t * bille = case_bille_lire(case_depart) ; 
  
  /* Mise a jour des cases */
  case_bille_poser( case_arrivee ,  bille ) ;
  case_bille_enlever( case_depart ) ;

  /* Mise a jour de la bille */
  if( ( cr =  bille_coord_ecrire( bille , coord_arrivee ) ) )
    return(cr) ;

  return(OK) ; 
}

extern 
err_t case_zones_ecrire( case_t * c  , const liste_t * zones ) 
{
  err_t cr = OK ; 

  if( ! liste_existe( zones ) )
    return(OK) ; 

  if( ( cr =  liste_copier( &(c->zones) , zones ) ) )
    return(cr) ;

  return(OK) ; 
}

extern 
err_t case_zone_ajouter( case_t * c , const zone_t * zone ) 
{
  err_t cr = OK ; 

  if( ( cr = liste_empiler( c->zones , zone ) ) )
    return(cr) ; 

  return(cr) ;
}

extern 
err_t case_ecrire( case_t * c , bille_t * const bille , const liste_t * zones ) 
{
  err_t cr = OK ; 
 
  /* Assertion */
  if( !case_existe(c) ) 
    return(ERR_CASE_NULL) ; 

  /* 
   * Affectation de la bille 
   * La case n'est pas proprietaire de la bille 
   */

  if( (cr = case_bille_poser( c , bille ) ) ) 
    return(cr) ;

  /* 
   * Affectation des zones 
   * La case n'est pas proprietaire des zones
   */
  if( ( cr = liste_copier( &(c->zones) , zones ) ) )
    return(cr) ; 

  return(cr) ; 
}


extern 
err_t case_copier( case_t ** c1 , const case_t * c2 )
{
  err_t cr = OK ; 

  if( case_existe( (*c1) ) )
    if( (cr = case_detruire(c1) ) )
      return(cr) ; 

  if( !case_existe(c2) )
    return(OK) ;

  if( ((*c1) = case_creer() ) == NULL ) 
    return(ERR_DEB_MEMOIRE) ;

  if( (cr = case_ecrire( (*c1) , 
			 case_bille_lire(c2),
			 case_zones_lire(c2)) ) )
    return(cr) ; 
  
  return(cr) ; 
}

extern
err_t cb_case_copier( void * * c1 , const void * c2 )
{
  return( case_copier( (case_t **)c1 , (case_t *) c2 ) ) ;
}

extern 
err_t case_referencer( case_t ** c1 , case_t * c2 )
{
  err_t cr = OK ; 

  (*c1) = c2 ;

  return(cr) ; 
}

extern
err_t cb_case_referencer( void * * c1 , const void * c2 )
{
  return( case_referencer( (case_t **)c1 , (case_t *) c2 ) ) ;
}

/*
 * Tests 
 */

extern 
booleen_t case_existe( const case_t * c ) 
{
  if( c == CASE_NULL ) 
    return(FAUX) ; 
  else
    return(VRAI) ; 
}

extern 
booleen_t case_libre( const case_t * c ) 
{
if( ! case_existe( c ) )
    return(FAUX); 

 if( c->bille == BILLE_NULL )
    return(VRAI) ; 
  else
    return(FAUX) ; 
}

extern 
booleen_t case_bille( const case_t * c ) 
{
  if( ! case_existe( c ) )
    return(FAUX); 

  if( c->bille == BILLE_NULL )
    return(FAUX) ; 
  else 
    return(VRAI) ; 
}

extern 
booleen_t case_zones( const case_t * c ) 
{
  if( ! case_existe( c ) )
    return(FAUX); 

  if( liste_taille(c->zones) > 0  )
    return(VRAI) ; 
  else
    return(FAUX) ; 
}

extern 
booleen_t case_aire_libre( const case_t * c ) 
{
  if( ! case_existe( c ) )
    return(FAUX); 

  return( case_libre(c) && (!case_zones(c)) ) ;
}

extern 
booleen_t case_aire_bille( const case_t * c )
{
 if( ! case_existe( c ) )
    return(FAUX); 

 return( case_bille(c) && (!case_zones(c)) ) ;
}

extern 
booleen_t case_zone_libre( const case_t * c ) 
{
  if( ! case_existe( c ) )
    return(FAUX); 

  return( case_libre(c) && case_zones(c) ) ;
}

extern 
booleen_t case_zone_bille( const case_t * c )
{
 if( ! case_existe( c ) )
    return(FAUX); 

  return( case_bille(c) && case_zones(c) ) ;
}


/*
 * Primitives
 */

extern
case_t * case_creer() 
{
  case_t * c ;

  if( (c=(case_t *)malloc(sizeof(case_t)) ) == NULL )
    {
      fprintf( stderr , "case_creer: debordement memoire %lu octets demandes\n" , 
	       (long unsigned int)sizeof(case_t) ) ;
      return(NULL) ;
    }
  
  /* Pas de bille sur la case */
  c->bille = BILLE_NULL ;

  /* 
   * Initialisation liste des zones: 
   * - la liste est vide 
   * - la case n'est PAS proprietaire des zones (references sur les zones)
   */
  if( ( c->zones = liste_creer( cb_zone_referencer , cb_zone_reference_effacer ) ) == NULL )
    return(NULL) ; 

  return(c) ; 
}


extern
err_t case_detruire( case_t ** c ) 
{
  err_t cr = OK ; 

  if( !case_existe((*c)) )
    return(OK) ;

  /*
   * Attention: risque de fuite memoire
   * on ne detruit pas la bille sur cette case 
   * car la case n'est pas proprietaire de la bille
   */

  /* Destruction liste des zones (destruction uniquement du conteneur) */
  if( ( cr = liste_detruire( &((*c)->zones) ) ) )
    return(cr) ; 

  free( (*c) ) ;
  (*c) = NULL ;

  return(cr) ; 
}

extern
err_t cb_case_detruire( void ** c ) 
{
  return( case_detruire( (case_t **) c ) ) ;
} 

extern
err_t case_reference_effacer( case_t ** c ) 
{
  (*c) = NULL ;

  return(OK) ; 
}

extern
err_t cb_case_reference_effacer( void * * c ) 
{
  return( case_reference_effacer( (case_t **) c ) ) ;
} 

/*
 * Affichage d'une case sur la sortie standard 
 */

extern
void case_afficher( const case_t * c ) 
{
  /* Case vide n'appartenant pas a une zone */
  if( case_aire_libre(c) )
    {
      printf( " " ) ; 
      return ;
    }

  /* Case vide appartenant a une zone */
  if( case_zone_libre(c)  )
    {
       printf( "." ) ; 
       return ;
    }

  /* Case contenant une bille n'appartenant pas a une zone */
  if( case_aire_bille(c) )
    {
      bille_afficher( c->bille ) ;
      return ;
    }

  /* Case contenant une bille appartenant a une zone */
  if( case_zone_bille(c) )
    {
       printf( "X" ) ; 
       return ;
    }

  printf("?") ; 
  return ; 
}

extern
void cb_case_afficher( const void * c )
{ 
  return(case_afficher( (case_t *) c )) ;
}

extern
void case_struct_afficher( const case_t * c ) 
{
  printf("[") ; 
  if( case_libre(c) )
    {
      printf( "CASE_LIBRE\n" ) ; 
    }
  else
    {
      printf( "CASE_BILLE\n" ) ; 
      bille_struct_afficher( c->bille ) ;
    }

  if( case_zones(c) )
    {
      printf( "APPARTIENT AU(X) ZONE(S)\n" ) ; 
      liste_afficher( c->zones , cb_zone_struct_afficher , '\n' ) ; 
    }
  else
    {
      printf("n'APPARTIENT A AUCUNE ZONE\n");
    }
  printf("]\n");

}

extern
void cb_case_struct_afficher( const void * c )
{ 
  return(case_struct_afficher( (case_t *) c )) ;
}

/*
 * Affichage d'une case dans une chaine de caracteres
 */

extern
char * case_string_afficher( const case_t * c ) 
{
  char * s = (char *)malloc(sizeof(char)*4);

  /* Case vide n'appartenant pas a une zone */
  if( case_aire_libre(c) )
    {
      strcpy( s , " " ) ; 
      return(s) ;
    }

  /* Case vide appartenant a une zone */
  if( case_zone_libre(c) )
    {
      strcpy( s , "." ) ; 
      return(s) ;
    }

  /* Case contenant une bille n'appartenant pas a une zone */
  if( case_aire_bille(c) )
    {
      sprintf( s , "%c" , bille_marque_lire( c->bille ) );
      return(s) ;
    }

  /* Case contenant une bille appartenant a une zone */
  if( case_zone_bille(c) )
    {
      sprintf( s , "X" ) ; 
      return(s) ;
    }

  strcpy( s , "?" ) ; 
  return(s) ; 
}


/*
 * Comparaison du contenu de 2 cases  
 */

extern 
int case_comparer( const case_t * c1 , const case_t * c2 )
{

  if( !case_bille(c1) && !case_bille(c2) ) return(0) ; 

  if( case_bille(c1) && !case_bille(c2) ) return(1) ; 

  if( !case_bille(c1) && case_bille(c2) ) return(-1) ; 
    
  if( case_bille(c1) && case_bille(c2) )
    {
      /* Comparaison des billes sur ces cases (arbitraire) */
      return(bille_comparer( case_bille_lire(c1) , 
			      case_bille_lire(c2) ) ) ;
    }

  return(0) ;
}

extern 
int cb_case_comparer( const void * c1 , const void * c2 )
{
  return( case_comparer( (case_t *)c1 , (case_t *)c2 ) ) ;
}
