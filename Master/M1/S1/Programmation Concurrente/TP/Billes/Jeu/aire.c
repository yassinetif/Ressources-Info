#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>

#include <commun.h>
#include <aire.h>


/* 
 * =====
 * Gestion d'une aire 
 * =====
 */



/*
 * Methodes d'acces 
 */

extern  
dim_t aire_hauteur_lire( const aire_t * aire )  
{
  return( aire->hauteur) ;
}

extern  
dim_t aire_largeur_lire( const aire_t * aire )  
{
  return( aire->largeur) ;
}


extern
case_t ** aire_cases_lire( const aire_t * aire ) 
{
  return(aire->cases) ; 
} 

extern
case_t * aire_case_lire( const aire_t * aire ,
			 const dim_t ligne , 
			 const dim_t colonne ) 
{
  if( ( ligne > aire->hauteur-1 ) || ( colonne > aire->largeur-1 ) )
    {
      fprintf( stderr , "aire_case_lire: mauvaise coordonnees [%d,%d] (max = [%d,%d]) \n",
	       ligne , colonne , aire->hauteur-1 , aire->largeur-1 );
      return(CASE_NULL) ; 
    }
  
  return( (*(aire->cases+(aire->largeur*ligne)+colonne)) );
} 

/*
 * Nombre de billes dans l'aire 
 */
extern
bille_id_t aire_nb_billes_lire( const aire_t * aire ) 
{
  dim_t H = DIM_NULL ; 
  dim_t L = DIM_NULL ; 
  dim_t h = 0  ; 
  dim_t l = 0 ;
  bille_id_t nb = 0 ; 

 if( !aire_existe( aire ) ) 
    return(0) ;

 H = aire_hauteur_lire(aire) ; 
 L = aire_largeur_lire(aire) ;

  for( h=0 ; h<H ; h++ ) 
    for( l=0 ; l<L ; l++ )
      {
	if( case_bille( aire_case_lire( aire , h , l ) ) )
	  nb++ ;
      }
  return(nb) ; 
} 

/*
 * Liste des billes de l'aire 
 */
extern
liste_t * aire_billes_lire( const aire_t * aire ) 
{
  dim_t H = DIM_NULL ; 
  dim_t L = DIM_NULL ; 
  dim_t i = 0  ; 
  dim_t j = 0 ;
  liste_t * l = LISTE_NULL ; 

  if( (l=liste_creer(cb_bille_referencer, cb_bille_reference_effacer ) ) == NULL )
    return(NULL);

  if( !aire_existe( aire ) ) 
    return(0) ;
  
  H = aire_hauteur_lire(aire) ; 
  L = aire_largeur_lire(aire) ;

  for( i=0 ; i<H ; i++ ) 
    {
      for( j=0 ; j<L ; j++ )
	{
	  if( case_bille( aire_case_lire( aire , i , j ) ) )
	    if( (liste_enfiler( l , 
				case_bille_lire( aire_case_lire( aire , i , j ) ) ) ) )
	      return(NULL) ; 
	}
    }
  return(l) ; 
} 

/*
 * Tests
 */

extern 
booleen_t aire_existe( const aire_t * aire ) 
{
  if( aire == AIRE_NULL )
    return(FAUX) ; 
  else
    return(VRAI) ; 
}

/* 
 * Teste si une aire n'a plus de billes
 */
extern 
booleen_t aire_vide( const aire_t * aire ) 
{
  if( aire_nb_billes_lire(aire) == 0 )
    return(VRAI) ; 
  else
    return(FAUX) ; 
}

/* 
 * Teste si la case d'une aire est libre 
 */
extern 
booleen_t aire_case_libre( const aire_t * aire ,
			   const dim_t i , 
			   const dim_t j ) 
{
  if( case_libre( aire_case_lire( aire , i , j ) ) )
    return(VRAI) ; 
  else
    return(FAUX) ; 
}

/* 
 * Teste si la case d'une aire contient une bille 
 */
extern 
booleen_t aire_case_bille( const aire_t * aire ,
			   const dim_t i , 
			   const dim_t j ) 
{
  if( case_bille( aire_case_lire( aire , i , j ) ) )
    return(VRAI) ; 
  else
    return(FAUX) ; 
}



/* 
 * Teste si une case d'une aire est libre 
 * a partir de ses coordonnees
 */
extern 
booleen_t aire_coord_libre( const aire_t * aire ,
			    const coord_t * coord ) 
{

  if( ! coord_existe( coord ) ) 
    return(FAUX) ; 

  const dim_t i = coord_lig_lire(coord) ;
  const dim_t j = coord_col_lire(coord) ; 

  if( case_libre( aire_case_lire( aire , i , j ) ) )
    return(VRAI) ; 
  else
    return(FAUX) ; 
}


/* 
 * Teste si une case d'une aire contient une bille
 * a partir de ses coordonnees
 */
extern 
booleen_t aire_coord_bille( const aire_t * aire ,
			    const coord_t * coord ) 
{

  if( ! coord_existe( coord ) ) 
    return(FAUX) ; 

  const dim_t i = coord_lig_lire(coord) ;
  const dim_t j = coord_col_lire(coord) ; 

  if( case_bille( aire_case_lire( aire , i , j ) ) )
    return(VRAI) ; 
  else
    return(FAUX) ; 
}

/*
 * Teste si une coordonnee appartient a une aire 
 */

extern
booleen_t aire_coord_appartient( const aire_t * aire , 
				 const coord_t * coord  ,
				 obstacle_t * obstacle ) 
{
  const dim_t l = coord_lig_lire( coord ) ;
  const dim_t c = coord_col_lire( coord ) ;
  const dim_t H = aire_hauteur_lire( aire ) ;
  const dim_t L = aire_largeur_lire( aire ) ;

  (*obstacle) = INFORME; 

  if( ( l >= H ) && ( c >= L ) )
    {
      (*obstacle) = ANGLE_FERME ; 
      return(FAUX) ;
    }

  if( ( l < 0 ) && ( c >= L ) )
    {
      (*obstacle) = ANGLE_FERME ; 
      return(FAUX) ;
    }

  if( ( l < 0 ) && ( c < 0 ) )
    {
      (*obstacle) = ANGLE_FERME ; 
      return(FAUX) ;
    }

  if( ( l >= H ) && ( c < 0 ) )
    {
      (*obstacle) = ANGLE_FERME ; 
      return(FAUX) ;
    }

  if( ( l < 0 ) || ( l >= H ) )
    {
      (*obstacle) = HORIZONTAL ; 
      return(FAUX) ;
    }

  if( ( c < 0 ) || ( c>= L ) )
    {
      (*obstacle) = VERTICAL ; 
      return(FAUX) ;
    }

  return(VRAI) ;
}


/*
 * Methodes d'affectation
 */



/*
 * Affectation d'une case de l'aire par copie 
 */

extern
err_t aire_case_ecrire( aire_t * aire , 
			const dim_t ligne , 
			const dim_t colonne ,
			case_t * const contenu )
{
  err_t cr = OK ; 

  if( ( ligne > aire->hauteur-1 ) || ( colonne > aire->largeur-1 ) ) 
    {
      fprintf( stderr , "aire_case_ecrire: mauvaise coordonnees [%d,%d] (max = [%d,%d]) \n",
	       ligne , colonne , aire->hauteur-1 , aire->largeur-1 );
      return( ERR_AIRE_COORD) ; 
    }

  if( case_existe(contenu) )
    {    
      if( (cr = case_copier( &((*(aire->cases+(aire->largeur*ligne)+colonne))) , 
			     contenu ) ) )
	return(cr) ; 
    }
  else
    {
      (*(aire->cases+(aire->largeur*ligne)+colonne)) = CASE_NULL ;
    }

  return(OK) ; 
}



/*
 * Affectation d'une case de l'aire par reference
 */

extern
err_t aire_case_referencer( aire_t * aire , 
			    const dim_t ligne , 
			    const dim_t colonne ,
			    case_t * const contenu )
{

  if( ( ligne > aire->hauteur-1 ) || ( colonne > aire->largeur-1 ) ) 
    {
      fprintf( stderr , "aire_case_ecrire: mauvaise coordonnees [%d,%d] (max = [%d,%d]) \n",
	       ligne , colonne , aire->hauteur-1 , aire->largeur-1 );
      return( ERR_AIRE_COORD) ; 
    }

  if( case_existe(contenu) )
    {    
      (*(aire->cases+(aire->largeur*ligne)+colonne)) = contenu ;
    }
  else
    {
      (*(aire->cases+(aire->largeur*ligne)+colonne)) = CASE_NULL ;
    }

  return(OK) ; 
}




extern
err_t aire_case_libre_ecrire( aire_t * aire , 
				const dim_t ligne , 
				const dim_t colonne )
{
  err_t cr = OK ; 
  case_t * c ; 

  /* Creation de la case */
  if ( (c = case_creer() ) == NULL )
    return(ERR_DEB_MEMOIRE);

  if( (cr = aire_case_ecrire( aire , ligne ,colonne , c ) ) ) 
    return(cr) ;

  return(OK) ; 
}

/*
 * Affectation d'une copie de la bille sur l'aire 
 */

extern
err_t aire_bille_poser( aire_t * aire , 
			const dim_t ligne , 
			const dim_t colonne ,
			bille_t * const bille )
{
  err_t cr = OK ; 
  case_t * c ;

  /* Recherche de la case dans l'aire */
  if( ( c = aire_case_lire( aire , ligne , colonne ) ) == CASE_NULL )
    return(ERR_CASE_NULL) ;

  /* Affectation de la bille */
  if( (cr = case_bille_poser( c , bille ) ) ) 
    return(cr) ; 


  return(OK) ; 
}

/*
 * PRIMITIVES
 */

/*
 * Creation d'une aire
 */

extern 
aire_t * aire_creer( const dim_t hauteur , const dim_t largeur ) 
{
  aire_t * aire ;
  dim_t i = 0 ;
  dim_t j = 0 ;
 

  /* Assertions */
  if( ( hauteur < AIRE_HAUTEUR_MIN ) || ( hauteur  > AIRE_HAUTEUR_MAX ) ) 
    {
      fprintf( stderr , "aire_dim_ecrire: hauteur %d incorrecte\nElle doit etre entre %d et %d\n" , 
	       hauteur, AIRE_HAUTEUR_MIN ,  AIRE_HAUTEUR_MAX );
      return(AIRE_NULL) ; 
    }

  if( ( largeur < AIRE_LARGEUR_MIN ) || ( largeur  > AIRE_LARGEUR_MAX ) ) 
    {
      fprintf( stderr , "aire_dim_ecrire: largeur %d incorrecte\nElle doit etre entre %d et %d\n" , 
	       largeur, AIRE_LARGEUR_MIN ,  AIRE_LARGEUR_MAX );
      return(AIRE_NULL) ; 
    }

  /* Creation */
  if( (aire=(aire_t *)malloc(sizeof(aire_t)) ) == NULL )
    {
      fprintf( stderr , "aire_creer: debordement memoire\n" ) ;
      return(NULL) ; 
    }

  /* Affectation des dimensions */
  aire->hauteur = hauteur ;
  aire->largeur = largeur ; 
  
  /* Reservation de la place memoire de l'aire hauteur X largeur cases */
  if( (aire->cases=(case_t**)malloc(sizeof(case_t*)*hauteur*largeur) ) == NULL )
    {
      fprintf( stderr , "aire_dim_ecrire: debordement memoire lors de la reservation des cases de l'aire\n" ) ;
      return(AIRE_NULL) ; 
    }

  /* Initialisation de l'aire avec des cases libres */
  for( i=0 ; i<hauteur ; i++ ) 
    {
      for( j=0 ; j<largeur ; j++ ) 
	{
	  *(aire->cases+((aire->largeur*i)+j)) = case_creer() ; 
	}
    }

  /* 
   * Initialisation de la liste des zones: 
   * - l'aire est proprietaire des zones de la liste 
   * - les zones sont copiees dans la liste 
   */
  if( ( aire->zones = liste_creer( cb_zone_copier , cb_zone_detruire) ) == NULL )
    {
      fprintf( stderr , "aire_creer: debordement memoire lors de la creation de la liste des zones\n" ) ;
      return(NULL) ; 
    }


  return(aire) ; 
}

/*
 * Destruction d'une case de l'aire 
 */

extern
err_t aire_case_detruire( aire_t * aire , 
			const dim_t ligne , 
			const dim_t colonne )
{
  err_t cr = OK ; 
  case_t * c = CASE_NULL ;

  if( ( ligne > aire->hauteur-1 ) || ( colonne > aire->largeur-1 ) ) 
    {
      fprintf( stderr , "aire_case_ecrire: mauvaise coordonnees [%d,%d] (max = [%d,%d]) \n",
	       ligne , colonne , aire->hauteur-1 , aire->largeur-1 );
      return( ERR_AIRE_COORD) ; 
    }

  /* Destruction de la case */
  /* 
   * free((*(aire->cases+(aire->largeur*ligne)+colonne)) ); 
   * (*(aire->cases+(aire->largeur*ligne)+colonne)) = CASE_NULL ;
   */
  c = aire_case_lire( aire , ligne , colonne ) ; 
  if( (cr = case_detruire(&c) ) )
    return(cr) ; 

  return(OK) ; 
}

/*
 * Destruction des billes d'une aire 
 */

extern 
err_t aire_billes_detruire( const aire_t * aire )
{
  err_t cr = OK ; 
  dim_t H = aire_hauteur_lire(aire) ; 
  dim_t L = aire_largeur_lire(aire) ; 
  dim_t i = 0 ; 
  dim_t j = 0 ;
  bille_t * bille = NULL ;

  for( i=0 ; i<H ; i++ ) 
    for( j=0; j<L ; j++ )
      {
	if( case_bille( aire_case_lire( aire , i , j ) ) )
	  {
	    bille = case_bille_lire( aire_case_lire( aire , i , j ) ) ;
	    if( (cr = bille_detruire( &bille ) ) )
	      return(cr) ;
	  }
      }
  return(OK) ;
}

/*
 * Destruction d'une bille d'une aire 
 */

extern 
err_t aire_bille_enlever( const aire_t * aire , 
			  bille_t * bille )
{
  err_t cr = OK ; 

  if( ! bille_existe( bille ) ) 
    {
      fprintf( stderr , "aire_bille_detruire: bille a detruire inexistante\n" ) ; 
      return(ERR_BILLE_NULL) ; 
    }

  /* La case devient libre */
  coord_t * coord = bille_coord_lire( bille ) ;
  dim_t i = coord_lig_lire(coord) ; 
  dim_t j = coord_col_lire(coord) ; 
  if( ( cr = case_bille_enlever( aire_case_lire( aire , i , j ) ) ) )
    return(cr) ; 

  /* Mise a jour bille */
  if( ( cr = bille_coord_ecrire( bille , COORD_NULL ) ) )
    return(cr) ; 

  return(OK) ;
}

/*
 * Destruction d'une aire
 */

extern 
err_t aire_detruire( aire_t ** aire ) 
{
  err_t cr = OK ; 
  const dim_t H = aire_hauteur_lire((*aire)) ; 
  const dim_t L = aire_largeur_lire((*aire)) ; 
  dim_t i = 0 ; 
  dim_t j = 0 ;

  if( ! aire_existe((*aire) ) )
    return(OK) ;

  for( i=0 ; i<H ; i++ ) 
    for( j=0 ; j<L ; j++ ) 
      if( ( cr = aire_case_detruire( (*aire) , i , j ) ) )
	return(cr) ; 

  free( (*aire)->cases ) ;

  free( (*aire) ) ;

  (*aire) = AIRE_NULL ; 

  return(OK);
}

extern 
err_t cb_aire_detruire( void * * aire ) 
{
  return(aire_detruire( (aire_t **) aire ) ) ; 
}




extern 
err_t aire_reference_effacer( aire_t ** aire ) 
{
  if( ! aire_existe((*aire) ) )
    return(OK) ;

  (*aire) = AIRE_NULL ; 

  return(OK);
}

extern 
err_t cb_aire_reference_effacer( void * * aire ) 
{
  return(aire_reference_effacer( (aire_t **) aire ) ) ; 
}



/*
 * Affichage d'une aire 
 */

extern 
void aire_afficher( const aire_t * aire ) 
{
  if( ! aire_existe(aire) )
    {
      printf("(inexistant)\n");
      return ;
    }
  const dim_t H = aire_hauteur_lire(aire) ;
  const dim_t L = aire_largeur_lire(aire) ;
  dim_t i = 0 ;
  dim_t j = 0 ; 

  printf( "Dimensions = %dX%d\n" ,  H , L ) ;

  /* Affichage des centaines */
  printf( "     ") ; for( j=0 ; j<100 && j<L ; j++ ) printf(" ") ; for( j=100 ; j<L ; j++ ) printf("%1d" , j/100) ; printf("\n"); 
  /* Affichage des dizaines */
  printf( "     ") ; for( j=0 ; j<10 && j<L ; j++ ) printf(" ") ; for( j=10 ; j<L ; j++ ) printf("%1d" , (j/10)%10) ; printf("\n"); 
  /* Affichage des unités */
  printf( "     ") ; for( j=0 ; j<L ; j++ ) printf("%1d" , j%10 )  ; printf("\n"); 
  /* Affichage du bord haut */
  printf( "    .") ; for( j=0 ; j<L ; j++ ) printf("-")            ; printf(".\n"); 
  for( i=0 ; i<H ; i++ ) 
    {
      /* Affichage du bord gauche */
      printf( "%3d |" , i ) ;
      /* Affichage d'une ligne */
      for( j=0 ; j<L ; j++ ) 
	{
	  case_afficher( aire_case_lire( aire , i , j ) ) ;
	}
      /* Affichage du bord droit */
      printf("|\n") ;      
    }
  /* Affichage du bord bas */
  printf( "    .") ; for( j=0 ; j<L ; j++ ) printf("-")      ; printf(".\n");
}

extern 
void cb_aire_afficher( const void * aire ) 
{
  aire_afficher( (aire_t *)aire )  ;
}

/*
 * Affectation d'une aire 
 */
extern 
err_t aire_copier( aire_t ** aire_cible , 
		     const aire_t * aire_source )
{
  err_t cr = OK ;
  dim_t l = 0 ; 
  dim_t c = 0 ; 
  
  /* Destruction du aire cible s'il existe deja */
  if( aire_existe( (*aire_cible) ) )
    {
      if( (cr=aire_detruire(aire_cible)) )
	return(cr);
    }

  if( ! aire_existe( aire_source ) )
    return(OK) ;

  /* Creation du aire cible */
  const dim_t H = aire_hauteur_lire( aire_source ) ;
  const dim_t L = aire_largeur_lire( aire_source ) ;
  if( ((*aire_cible) = aire_creer( H , L )) == AIRE_NULL )
    {
      fprintf( stderr , " aire_cases_affecter: pb lors de la creation du aire cible\n");
      return(ERR_DEB_MEMOIRE) ;
    }

  /* Copie des cases */
  for( l=0 ; l<H ; l++ ) 
    for( c=0 ; c<L ; c++ ) 
      if( (cr = aire_case_ecrire( (*aire_cible) , l , c , 				    
				  aire_case_lire(aire_source, l , c ) ) ) )
	return(cr) ; 

  return(OK) ; 
}

extern 
err_t cb_aire_copier( void * * aire_cible , 
			  const void * aire_source )
{
  return(aire_copier( (aire_t **)aire_cible , 
		      (aire_t *)aire_source )) ; 
}


/*
 * Affectation reference d'une aire 
 */
extern 
err_t aire_referencer( aire_t ** aire_cible , 
		       aire_t * aire_source )
{
  err_t cr = OK ;
  
  /* Destruction du aire cible s'il existe deja */
  if( aire_existe( (*aire_cible) ) )
    {
      if( (cr=aire_detruire(aire_cible)) )
	return(cr);
    }

  (*aire_cible) = aire_source ;

  return(OK) ; 
}

extern 
err_t cb_aire_referencer( void ** aire_cible , 
			  const void * aire_source )
{
  return(aire_referencer( (aire_t **)aire_cible , 
			  (aire_t *)aire_source )) ; 
}


/*
 * Comparaison de deux aires
 * La comparaison s'effectue uniquement sur les cases du aire
 */

extern
int aire_comparer( const aire_t * D1 , const aire_t * D2 )
{

  if( (! aire_existe(D1) ) && (! aire_existe(D2) ) )
    return(0) ;

  if( aire_existe(D1) && (! aire_existe(D2) ) )
    return(1) ;

  if( (! aire_existe(D1) ) && aire_existe(D2) )
    return(-1) ;

  int cmp = 0 ; 

  dim_t H = aire_hauteur_lire(D1) ;
  if( ( cmp = H - aire_hauteur_lire(D2) ) )
    return(cmp) ; 
    
  dim_t L = aire_largeur_lire(D1) ;
  if( ( cmp = H - aire_largeur_lire(D2) ) )
    return(cmp) ; 

  dim_t i = 0 ;
  dim_t j = 0 ; 

  for( i=0 ; i<H ; i++ ) 
    {
      for( j=0 ; j<L ; j++ ) 
	{
	  if( ( cmp = case_comparer( aire_case_lire( D1 , i , j ) ,
				     aire_case_lire( D2 , i , j ) ) ) )
	    return(cmp) ; 
	}
    }

  return(0) ;
}


extern
int cb_aire_comparer( const void *  D1 , const void * D2 )
{
  return(aire_comparer( (aire_t *) D1 , (aire_t *)D2 ) ) ; 
}



/*
 * Positionnement initial au hasard d'une bille sur une aire 
 */

extern
err_t aire_bille_positionner( aire_t * aire , 
			      bille_t * bille ) 
{
  err_t cr = OK ; 
  dim_t H = DIM_NULL ;
  dim_t L = DIM_NULL ;
  dim_t i = 0 ; 
  dim_t j = 0 ; 
  struct timeval start ;
  
  /* Assertion */
  if( !aire_existe(aire) )
    {
      fprintf( stderr, "aire_bille_demarrer: Warning , l'aire n'existe pas\n") ;
      return(OK) ; 
    }

  H = aire_hauteur_lire(aire) ;
  L = aire_largeur_lire(aire) ;
  
  /* Positionnement de la bille au hasard */  
  gettimeofday(&start, NULL);
  unsigned int seed = (unsigned int)start.tv_usec ;
  dim_t init_H = rand_r(&seed)%H ; 
  dim_t init_L = rand_r(&seed)%L ; 
  booleen_t trouve = FAUX ;
  booleen_t fin_H = FAUX ; 
  booleen_t fin_L = FAUX ;


  i=init_H ; 
  fin_H = FAUX ;
  while( (!fin_H) && (!trouve) )
    {
      j=init_L ; 
      fin_L = FAUX ;
      while( (!fin_L) && (!trouve) )
	{
	  if( aire_case_libre( aire , i , j ) )
	    trouve = VRAI ;
	  else
	    {
	      j = (j+1)%L ; 
	      if( j == init_L ) 
		fin_L = VRAI ;
	    }
	}
      /* Passage ligne suivante */
      if( ! trouve ) 
	{
	  i = (i + 1)%H;
	  if( i == init_H ) 
	    fin_H = VRAI ;
	} 
    }

  if( !trouve )
    return( ERR_AIRE_PLEINE ); 

  /* Affectation des coordonnees de la bille */
  coord_t * coord_bille = COORD_NULL ;
  if( ( coord_bille = coord_creer( i , j ) ) == COORD_NULL )
    return(ERR_DEB_MEMOIRE) ; 
  
  if( ( cr = bille_coord_ecrire( bille , coord_bille ) ) ) 
    return(cr) ;

  /* Affectation de la bille sur l'aire */
  if( (cr = aire_bille_poser( aire , i , j , bille ) ) ) 
    return(cr) ; 
  
  return(OK) ;
}


/*
 * Transfert de la bille posee sur la case de depart vers la case d'arrivee
 */

extern
err_t aire_bille_deplacer( aire_t * aire , 
			   case_t * case_depart, 
			   case_t * case_arrivee ,
			   const coord_t * coord_arrivee )
{
  err_t cr = OK ; 
  
  /* Assertions */

  if( ! case_existe( case_depart ) )
    { 
      fprintf( stderr, "aire_bille_transferer: case de depart inexistante\n") ;
      return(ERR_AIRE_COORD) ; 
    }

  if( ! case_existe( case_arrivee ) )
    { 
      fprintf( stderr, "aire_bille_transferer: case de d'arrivee inexistante\n") ;
      return(ERR_AIRE_COORD) ; 
    }
  
  if( ! case_bille(case_depart) )
    {
      fprintf( stderr , "aire_bille_transferer: la case de depart ne comporte pas de bille\n" ) ;
      return( ERR_AIRE_COORD) ; 
    }

  if( ! case_libre(case_arrivee) )
    {
      fprintf( stderr , "aire_bille_transferer: la case d'arrivee n'est pas libre\n" ) ;
      return( ERR_AIRE_COORD) ; 
    }

  /* Transfert de la bille */
  if( (cr = case_bille_deplacer( case_depart , case_arrivee , coord_arrivee) ) ) 
    return(cr) ; 
  
 return(OK) ; 
}

/*
 * Gestion des zones 
 */

extern
err_t aire_zone_creer( aire_t * aire , 
		       const coord_t * coin_hg , 
		       const coord_t * coin_bd ) 
{
  err_t cr = OK ; 
  zone_t * zone = ZONE_NULL ; 

  /* Assertions */
  const dim_t H = aire_hauteur_lire(aire) ; 
  const dim_t L = aire_largeur_lire(aire) ; 
  const dim_t H_hg = coord_lig_lire(coin_hg) ;
  const dim_t L_hg = coord_col_lire(coin_hg) ; 
  const dim_t H_bd = coord_lig_lire(coin_bd) ;
  const dim_t L_bd = coord_col_lire(coin_bd) ; 

  if( ( H_hg > H ) || ( L_hg > L )  )
    {
      printf( "aire_zone_creer: delimitation incorrecte du coin haut-gauche de la zone\n\t" );
      coord_afficher(coin_hg) ; 
      printf( " devrait etre contenu dans %dX%d\n" , H , L ) ; 
      return(ERR_ZONE_COORD) ;
    }

 if( ( H_bd > H ) || ( L_bd > L ) )
    {
      printf( "aire_zone_creer: delimitation incorrecte du coin bas-droit de la zone\n\t" );
      coord_afficher(coin_bd) ; 
      printf( " devrait etre contenu dans %dX%d\n" , H , L ) ; 
      return(ERR_ZONE_COORD) ;
    }

  /* Creation de la zone */
  if( (zone = zone_creer( coin_hg , 
			  coin_bd ) ) == ZONE_NULL )
    {
      fprintf( stderr , "aire_zone_creer: Pb creation zone \n");
      return(ERR_ZONE_NULL) ; 
    }

  /* Ajout d'une copie de cette zone en tete de la liste des zones de l'aire */
  if ( ( cr = liste_empiler( aire->zones , zone ) ) )
    return(cr) ; 

  /* Destruction de la zone */
  if( ( cr = zone_detruire( &zone ) ) )
    return(cr) ; 

  /* Recuperation de la copie de la zone (en tete de liste) */
  zone = liste_premier( aire->zones ) ;

  /* Marquage des cases appartenant a cette zone */
  const dim_t L_deb = coord_lig_lire(coin_hg) ;
  const dim_t L_fin = coord_lig_lire(coin_bd) ;
  const dim_t C_deb = coord_col_lire(coin_hg) ;
  const dim_t C_fin = coord_col_lire(coin_bd) ;
  dim_t i = 0 ;
  dim_t j = 0 ; 
  for( i=L_deb ; i<=L_fin ; i++ ) 
    {
      for( j=C_deb ; j<=C_fin ; j++ ) 
	{
	  if( ( cr = case_zone_ajouter( aire_case_lire( aire , i , j ) ,
					zone ) ) )
	    return(cr) ; 
	}
    }
  
  return(cr) ; 
}
