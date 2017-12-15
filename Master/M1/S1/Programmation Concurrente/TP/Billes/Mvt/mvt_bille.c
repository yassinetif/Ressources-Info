#include <stdio.h>
#include <mvt_bille.h>
/*! 
 * \file  mvt_bille.c
 * \brief Corps des fonctions effectuant les d&eacute;placements d'une bille sur une aire
 */

/*
 * \fn err_t err_t mvt_bille_avancer( bille_t * bille ,
 *			              aire_t * aire , 
 *			              obstacle_t * obstacle ) 
 * \brief Avancement d'une bille dans a direction courante
 * \param[in,out] bille : bille avant/apres l'avancee
 * \param[in] aire : aire dans laquelle évolue la bille 
 * \param[out] obstacle : type de l'obstacle su rlequel on bute si on ne peut pas avancer
 * \return  
 * \|i OK : la bille a pu avancer, les coordonnées de la bille sont mises à jour 
 * \li ERR_MVT_BILLE_AVANCER : n'a pas pu avancer, les coordonnnées de la billes restent inchangées
 */

static
err_t  mvt_bille_avancer( bille_t * bille , 
			  aire_t * aire , 
			  obstacle_t * obstacle ) 
{
  err_t cr = OK ; 
  coord_t * coord_w = COORD_NULL ; 
  bille_t * bille_w = BILLE_NULL ;
 
  (*obstacle) = INFORME ; 

  if( ( cr = bille_copier( &bille_w , bille ) ) )
    return(cr) ; 

  if( ( cr = bille_deplacer( bille_w ) ) ) 
    return(cr) ;
  
  coord_w = bille_coord_lire( bille_w ) ;
  
  if( ! aire_coord_appartient(aire , coord_w , obstacle ) )
    {
      /* On deborde de l'aire : pas possible d'avancer */
      /* La bille ne change pas */

      /* Destruction variable de travail */
      if( ( cr = bille_detruire( &bille_w ) ) ) 
	return(cr) ;

      return( ERR_MVT_BILLE_AVANCER ) ;
    }
  
  if( aire_coord_bille(aire , coord_w) )
    {
      /* La prochaine case a deja une bille: impossible d'avancer */
      /* La bille ne change pas */
      
      (*obstacle) = ROND ; 

      /* Destruction variable de travail */
      if( ( cr = bille_detruire( &bille_w ) ) ) 
	return(cr) ;
      
      return( ERR_MVT_BILLE_AVANCER ) ;
    }
  
  if( ! aire_coord_libre(aire , coord_w) )
    {
      /* La prochaine case n'est pas une case libre : impossible d'avancer */
      /* La bille ne change pas */

      /* Destruction variable de travail */
      if( ( cr = bille_detruire( &bille_w ) ) ) 
	return(cr) ;

      return( ERR_MVT_BILLE_AVANCER ) ;
    }

  /* On a pu avancer: mise a jour des coordonnees de la bille */
  if( ( cr = bille_coord_ecrire( bille , bille_coord_lire(bille_w) ) ) )
    return(cr) ;

  /* Destruction variable de travail */
  if( ( cr = bille_detruire( &bille_w ) ) ) 
    return(cr) ;

  return(OK) ; 
}



/*
 * \fn err_t err_t mvt_bille_rebondir( bille_t * bille , 
 *				       aire_t * ,
 *				       const obstacle_t obstacle  )
 * \brief Rebondissement d'une bille sur un obstacle
 * \li limites de l'aire 
 * \li autre bille 
 * \param[in,out] bille : bille avant/apres rebondissement
 * \param[in] aire : aire dans laquelle évolue la bille
 * \param[in] obstacle : type de l'obstacle sur lequel on rebondit
 * \return  
 * \|i OK : la bille a pu rebondir , les coordonnées et la direction sont mises à jour 
 * \li ERR_MVT_BILLE_ETOUFFEMENT : la bille est encerclee et n'a pas pu rebondir, la bille reste inchangée
 */
static 
err_t mvt_bille_rebondir( bille_t * bille , 
			  aire_t * aire  ,
			  const obstacle_t obstacle)
{
  err_t cr = OK ;
  bille_t * bille_w = BILLE_NULL ;
  coord_t * coord_w = COORD_NULL ; 
  direction_t d_origine = bille_direction_lire(bille) ; 
  direction_t d_opposee = direction_opposee_random(obstacle,d_origine) ;
  int i = 0 ; 
  booleen_t trouve = FAUX ; 
  obstacle_t autre_obstacle = INFORME ; 


  /* Initialisation bille avec la bille d'origine ùais avec une direction opposee */
  if( ( cr = bille_copier( &bille_w , bille ) ) )
    return(cr) ; 

  if( ( cr = bille_direction_ecrire( bille_w , d_opposee ) ) )
    return(cr) ;
  
  for( i=0 ; i<direction_opposee_nb(obstacle,d_origine) && (!trouve) ; i++ )
    {
      /* Essai de deplacement de la bille */
      if( ( cr = bille_deplacer( bille_w ) ) ) 
	return(cr) ;

      coord_w = bille_coord_lire( bille_w ) ;

      /* Rebondissement sur un bord de l'aire */
      if(! aire_coord_appartient(aire , coord_w , &autre_obstacle) )
	{
	  if( ( cr = bille_coord_ecrire( bille_w , bille_coord_lire(bille) ) ) )
	    return(cr) ; 

	  d_opposee =direction_opposee_random_suivante(obstacle,d_origine,d_opposee) ;	  
	  if( ( cr = bille_direction_ecrire( bille_w , d_opposee ) ) )
	    return(cr) ;

	  continue ;
	}

      /* Rebondissement sur une autre bille */
      if( aire_coord_bille(aire , coord_w) )
	{
	  if( ( cr = bille_coord_ecrire( bille_w , bille_coord_lire(bille) ) ) )
	    return(cr) ; 

	  d_opposee =direction_opposee_random_suivante(obstacle,i,d_opposee) ;		  
	  if( ( cr = bille_direction_ecrire( bille_w , d_opposee ) ) )
	    return(cr) ;

	  continue ; 
	}
     
      /* On ne heurte aucun obstacle dans cette direction --> on a trouve une case libre */
      trouve = VRAI ; 	
    }


  /* Gestion du resultat */
  if( trouve )
    {
      /* On a pu rebondir: mise a jour de la bille avec ses nouvelles coordonnees et direction */
      if( ( cr = bille_coord_ecrire( bille , bille_coord_lire(bille_w) ) ) )
	return(cr) ; 

      if( ( cr = bille_direction_ecrire( bille , bille_direction_lire(bille_w) ) ) )
	return(cr) ;
    }
  else
    {
      /* On n'a pas pu rebondir: la bille reste inchagee  */      
    }

  /* Destruction variable de travail */
  if( ( cr = bille_detruire( &bille_w ) ) ) 
    return(cr) ;

  /* Gestion du retour */
  if( trouve )
    {
      return(OK) ;
    }
  else
    {
      return( ERR_MVT_BILLE_ETOUFFEMENT ) ;
    }

}


/*
 * \fn err_t  mvt_bille_deplacer( bille_t * bille ,
 *			          aire_t * aire )
 * \brief R&eacute;alisation de la fonction de d&eacute;placement d'une bille sur l'aire 
 * Le d&eacute;placement d'un pas d'une bille sur l'aire s'effectue en fonction
 * \li de la direction de la bille 
 * \li des limites de l'aire 
 * \param[in,out] aire  : aire dans laquelle la bille s'est d&eacute;plac&eacute;e
 * \param[in,out] bille : bille dont les coordonn&eacute;es ont &eacute;t&eacute; mises &agrave; jour
 */
extern
err_t  mvt_bille_deplacer( bille_t * bille ,
			   aire_t * aire ) 
{
  err_t cr = OK ; 
  obstacle_t obstacle = INFORME ; 

  if( ! aire_existe( aire ) )
    return(ERR_AIRE_NULL) ; 

  if( ! bille_existe( bille ) )
    return(ERR_BILLE_NULL) ; 

  /* Capture coord de depart */
  coord_t * coord_depart = COORD_NULL ; 
  coord_copier( &coord_depart , bille_coord_lire(bille) ) ;
  case_t * case_depart  = aire_case_lire( aire , coord_lig_lire(coord_depart) , coord_col_lire(coord_depart) ) ;

  /* Avancement  de la bille dans la meme direction */
  if( mvt_bille_avancer( bille , aire , &obstacle ) == ERR_MVT_BILLE_AVANCER )
    {
      /* Si ce n'est pas possible alors on essaie de rebondir */
      if( mvt_bille_rebondir( bille , aire , obstacle ) == ERR_MVT_BILLE_ETOUFFEMENT ) 
	{
	  /* Si ce n'est pas possible alors on ne fait rien */
	}
    }
 
  /* Capture coord d'arrivee */
  coord_t * coord_arrivee = COORD_NULL ; 
  coord_copier( &coord_arrivee , bille_coord_lire(bille) ) ; 
  case_t * case_arrivee = aire_case_lire( aire , coord_lig_lire(coord_arrivee) , coord_col_lire(coord_arrivee) ) ;
				
  /* Deplacement de la bille sur l'aire */
  if( coord_comparer( coord_depart , coord_arrivee ) )
    {	 
      if( ( cr = aire_bille_deplacer( aire , 
				      case_depart, 
				      case_arrivee ,
				      coord_arrivee ) ) ) 
	return(cr) ;
    } 

  /* Deplacement ou non, Mise a jour de la vitesse de la bille */
  unsigned int nb_deplacements =  bille_nb_deplacements_lire(bille) + 1 ;
  if( ( cr = bille_nb_deplacements_ecrire( bille , nb_deplacements ) ) )
    return(cr) ; 

  unsigned int vitesse = bille_vitesse_lire(bille) ;
  if( vitesse > 0 ) 
    {
      if( nb_deplacements%vitesse == 0 )
	{
	  if( ( cr = bille_vitesse_ecrire( bille , 
					  vitesse - 1 ) ) ) 
	    return(cr) ; 
	}
    }

  /* Destructions des variables de travail */
  coord_detruire( &coord_depart  ) ;
  coord_detruire( &coord_arrivee ) ; 

  return(OK) ; 
}
