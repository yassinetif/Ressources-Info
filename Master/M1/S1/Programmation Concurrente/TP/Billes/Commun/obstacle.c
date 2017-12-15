#include <commun.h>
#include <obstacle.h>
#include <stdlib.h>
#include <time.h>

/*
 * VARIABLES GLOBALES PRIVEES 
 */

/*
 * Fonction sur les obstacles 
 */
extern
obstacle_t obstacle_affecter( obstacle_t * obst1 , const obstacle_t obst2 ) 
{
  return( (*obst1) = obst2 ) ; 
}

extern 
err_t cb_obstacle_affecter( void ** obst1 , void * const obst2 ) 
{
  return( obstacle_affecter( (obstacle_t *)obst1 , (obstacle_t)obst2 ) ) ;
}

extern
obstacle_t obstacle_suivant( obstacle_t obst ) 
{
  return( obst+1 ) ;
}

extern
void obstacle_afficher( obstacle_t obst ) 
{
  switch( obst )
    {
    case INFORME : printf("Informe") ;
      break ; 
    case VERTICAL : printf("Vertical") ;
      break ; 
    case HORIZONTAL : printf("Horizontal") ;
      break ; 
    case ROND : printf("Rond") ;
      break ; 
    case ANGLE_FERME : printf("Angle Ferme") ;
      break ; 
    case ANGLE_OUVERT : printf("Angle Ouvert") ;
      break ; 
    default : printf("???") ;
      break ; 
    }
}

extern
char * obstacle_string_afficher( obstacle_t obst ) 
{
  switch( obst )
    {
    case INFORME : return("Informe") ;
      break ; 
    case VERTICAL : return("Vertical") ;
      break ; 
    case HORIZONTAL : return("Horizontal") ;
      break ; 
    case ROND : return("Rond") ;
      break ; 
    case ANGLE_FERME : return("Angle Ferme") ;
      break ; 
    case ANGLE_OUVERT : return("Angle Ouvert") ;
      break ; 
    default : return("???") ;
      break ; 
    }
}

/*
 * Donne une obstacle au hasard
 */
extern
obstacle_t obstacle_random() 
{
  unsigned int seed = (unsigned int)time(NULL) ;
  return((obstacle_t)((rand_r(&seed)%OBSTACLE_NB)+1)) ;
}
