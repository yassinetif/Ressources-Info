#include <stdio.h>
#include <stdlib.h>

#include <commun.h>
#include <zone.h>


/*
 * Methodes d'acces 
 */

/* Acces au coin supérieur gauche */
extern
coord_t * zone_coin_hg_lire( const zone_t * zone ) 
{
  return(zone->coin_hg) ; 
}

/* Acces au coin inférieur droit */
extern
coord_t * zone_coin_bd_lire( const zone_t * zone ) 
{
  return(zone->coin_bd) ; 
}

/*
 * Tests 
 */

extern
booleen_t zone_existe( const zone_t * zone ) 
{
  if( zone == NULL )
    return(FAUX) ; 
  else
    return(VRAI);
}

/*
 * Methodes d'affectations
 */

/* Affectation du coin en haut à gauche */
extern
err_t zone_coin_hg_ecrire( zone_t * zone , const coord_t * coin_hg ) 
{
  if( ! coord_existe(coin_hg) )
    return(OK) ; 

  return( coord_copier( &(zone->coin_hg) , coin_hg ) ) ;
}

/* Affectation du coin en bas à droite */
extern
err_t zone_coin_bd_ecrire( zone_t * zone , const coord_t * coin_bd ) 
{
  if( ! coord_existe(coin_bd) )
    return(OK) ; 

  return( coord_copier( &(zone->coin_bd) , coin_bd ) ) ;
}



/* Affectation globale d'une zone */
extern 
err_t zone_ecrire( zone_t * zone , 
		   const coord_t * coin_hg, 
		   const coord_t * coin_bd )
{
  err_t cr = OK ; 

  if( ! zone_existe(zone) )
    {
      fprintf( stderr , "zone_ecrire : tentative d'affectation d'une zone inexistante\n");
      return(ERR_ZONE_NULL);
    }

  if( (cr = zone_coin_hg_ecrire( zone , coin_hg ) ) )
    return(cr) ; 
  if( (cr = zone_coin_bd_ecrire( zone , coin_bd ) ) )
    return(cr) ; 

  return(cr) ; 
}

/* Copie profonde d'une zone */
extern 
err_t zone_copier( zone_t ** z1 , const zone_t * z2 ) 
{
  err_t cr = OK ; 

  if( zone_existe((*z1)) ) 
    {
      if((cr=zone_detruire(z1) ) )
	return(cr); 
    }
  
  if( !zone_existe(z2) )
    return(OK) ; 

  if( ( (*z1) = zone_creer( zone_coin_hg_lire(z2) ,
			    zone_coin_bd_lire(z2) ) ) == ZONE_NULL )
    {
      return(ERR_DEB_MEMOIRE);
    }
  
  return(OK) ;
}

extern 
err_t cb_zone_copier( void * * z1 , const void * z2 ) 
{
  return( zone_copier( (zone_t **)z1 , (zone_t *)z2 ) ) ;
}

/* Referencement d'une zone */
extern 
err_t zone_referencer( zone_t ** z1 , zone_t * z2 ) 
{
  err_t cr = OK ; 

  if( zone_existe((*z1)) ) 
    {
      if((cr=zone_detruire(z1) ) )
	return(cr); 
    }

  (*z1) = z2 ;

  return(OK) ;
}

extern 
err_t cb_zone_referencer( void * * z1 , const void * z2 ) 
{
  return( zone_referencer( (zone_t **)z1 , (zone_t *)z2 ) ) ;
}

/*
 * Creation d'une zone 
 */
extern
zone_t * zone_creer( const coord_t * coin_hg , 
		     const coord_t * coin_bd ) 
{
  zone_t * zone ;
  err_t cr = OK ; 
 
  if( (zone=(zone_t *)malloc(sizeof(zone_t)) ) == NULL )
    {
      fprintf( stderr , "zone_creer: debordement memoire %lu octets demandes\n" , 
	       (long unsigned int)sizeof(zone_t) );
      return(NULL);
    }

  zone->coin_hg = COORD_NULL ; 
  zone->coin_bd = COORD_NULL ; 

  if( ( cr =zone_coin_hg_ecrire( zone , coin_hg ) ) )
    {
      fprintf( stderr , "zone_creer: pb dans affectation du coin en haut a gauche, code erreur %d\n" ,cr  );
      return(ZONE_NULL) ;
    }

  if( ( cr =zone_coin_bd_ecrire( zone , coin_bd ) ) )
    {
      fprintf( stderr , "zone_creer: pb dans affectation du coin en bas a droite, code erreur %d\n" ,cr  );
      return(ZONE_NULL) ;
    }

  return(zone) ; 
}

/* 
 * Destruction physique d'une zone 
 */

extern
err_t zone_detruire( zone_t ** zone ) 
{
  err_t cr = OK ; 

  if( (cr = coord_detruire( &((*zone)->coin_hg) ) ) )
    return(cr) ; 

  if( (cr = coord_detruire( &((*zone)->coin_bd) ) ) )
    return(cr) ; 

  free( (*zone) ) ;
  (*zone) = NULL ; 

  return(cr) ; 
}

extern
err_t cb_zone_detruire( void * * zone ) 
{
  return( zone_detruire( (zone_t **) zone ) ) ;
}

/*
 * Effacement d'une reference sur une zone 
 */

extern
err_t zone_reference_effacer( zone_t ** zone ) 
{
  err_t cr = OK ; 

  (*zone) = NULL ; 

  return(cr) ; 
}

extern
err_t cb_zone_reference_effacer( void * * zone ) 
{
  return( zone_reference_effacer( (zone_t **) zone ) ) ;
} 

/*
 * Affichage
 */

/* Debuggage */

extern
void zone_struct_afficher( const zone_t * zone )
{
  printf("\n{\n") ; 
  printf(" Coin H-G: ") ;  coord_afficher(zone_coin_hg_lire(zone) ) ; 
  printf(" Coin B-G: ") ;  coord_afficher(zone_coin_bd_lire(zone) ) ; 
  printf(" \n}\n"); 
  return ;
}

extern
void cb_zone_struct_afficher( const void * zone )
{
  return(zone_struct_afficher( (zone_t *) zone )) ;
}

/* Dans une chaine de caracteres */
extern 
char * zone_string_afficher( const zone_t * zone )
{
  char * string = (char *)malloc(sizeof(char)*STRING_LG_MAX) ;

  sprintf( string , "{ Coin HG: %s Coin BD: %s } " ,
	   coord_string_afficher(zone_coin_hg_lire(zone)) ,
	   coord_string_afficher(zone_coin_bd_lire(zone)) ); 
  return(string) ;
}

/*
 * Comparaison de 2 zones
 */

extern 
int zone_comparer( const zone_t * z1 , const zone_t * z2 )
{
  int cmp = 0 ; 

  /* 1) Comparaison le coin Haut Gauche */
  if( ( cmp = coord_comparer( zone_coin_hg_lire(z1) , zone_coin_hg_lire(z2) ) ) )
    return(cmp) ; 

  /* 2) Comparaison le coin Bas Droit */
  if( ( cmp = coord_comparer( zone_coin_bd_lire(z1) , zone_coin_bd_lire(z2) ) ) )
    return(cmp) ; 

  return(cmp) ;
}

extern 
int cb_zone_comparer( const void * z1 , const void * z2 )
{
  return(zone_comparer( (zone_t *)z1 , (zone_t *)z2 ) ) ;
}
