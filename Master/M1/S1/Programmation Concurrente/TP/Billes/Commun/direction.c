#include <commun.h>
#include <direction.h>
#include <stdlib.h>
#include <time.h>

/*
 * VARIABLES GLOBALES PRIVEES 
 */

/* 
 * Tableau des directions opposees 
 */


static int tab_dir_opp[6][9][6] = { 

  /* Pour obstacle INFORME */
  {
    /* NULLE_PART */
    { 1 , NULLE_PART } ,
    /* NORD */
    { 1 , NULLE_PART } ,
    /* NORD_EST */
    { 1 , NULLE_PART } ,
    /* EST */
    { 1 , NULLE_PART } ,
    /* SUD_EST */
    { 1 , NULLE_PART } ,
    /* SUD */
    { 1 , NULLE_PART } ,
    /* SUD_OUEST */
    { 1 , NULLE_PART } ,
    /* OUEST */
    { 1 , NULLE_PART } ,
    /* NORD_OUEST */
    { 1 , NULLE_PART } ,
  } ,

  /* Pour obstacle VERTICAL */
  {
    /* NULLE_PART */
    { 1 , NULLE_PART } ,
    /* NORD */
    { 1 , NULLE_PART } ,
    /* NORD_EST */
    { 2 , OUEST , NORD_OUEST } ,
    /* EST */
    { 3 , NORD_OUEST , OUEST , SUD_OUEST } , 
    /* SUD_EST */
    { 2 , OUEST , SUD_OUEST } , 
    /* SUD */
    { 1 , NULLE_PART } , 
    /* SUD_OUEST */
    { 2 , EST , SUD_EST } , 
    /* OUEST */
    { 3 , NORD_EST , EST , SUD_EST } , 
    /* NORD_OUEST */
    { 2 , EST , NORD_EST }  
  } ,

 /* Pour obstacle HORIZONTAL */
  {
    /* NULLE_PART */
    { 1 , NULLE_PART } ,
    /* NORD */
    { 3 , SUD_OUEST , SUD , SUD_EST  } ,
    /* NORD_EST */
    { 2 , SUD_EST , SUD } ,
    /* EST */
    { 1 , NULLE_PART } , 
    /* SUD_EST */
    { 2 , NORD_EST , NORD } , 
    /* SUD */
    { 3 , NORD_OUEST , NORD , NORD_EST } , 
    /* SUD_OUEST */
    { 2 , NORD_OUEST , NORD } , 
    /* OUEST */
    { 1 , NULLE_PART } , 
    /* NORD_OUEST */
    { 2 , SUD_OUEST , SUD }  
  } ,

 /* Pour obstacle ROND */
  {
    /* NULLE_PART */
    { 1 , NULLE_PART } ,
    /* NORD */
    { 5 , OUEST , SUD_OUEST , SUD , SUD_EST , EST } ,
    /* NORD_EST */
    { 5 , NORD_OUEST , OUEST , SUD_OUEST , SUD , SUD_EST } ,
    /* EST */
    { 5 , NORD , NORD_OUEST , OUEST , SUD_OUEST , SUD } , 
    /* SUD_EST */
    { 5 , NORD_EST , NORD , NORD_OUEST , EST , SUD_OUEST } , 
    /* SUD */
    { 5 , EST , NORD_EST , NORD , NORD_OUEST , OUEST } , 
    /* SUD_OUEST */
    { 5 , SUD_EST , EST , NORD_EST , NORD , NORD_OUEST } , 
    /* OUEST */
    { 5 , SUD , SUD_EST , EST , NORD_EST , NORD } , 
    /* NORD_OUEST */
    { 5 , SUD_OUEST , SUD , SUD_EST , EST , NORD_EST }  
  } ,

 /* Pour obstacle ANGLE FERME */
  {
    /* NULLE_PART */
    { 1 , NULLE_PART } ,
    /* NORD */
    { 1 , NULLE_PART } ,
    /* NORD_EST */
    { 5 , NORD_OUEST , OUEST , SUD_OUEST , SUD , SUD_EST } ,
    /* EST */
    { 1 , NULLE_PART } , 
    /* SUD_EST */
    { 5 , NORD_EST , NORD , NORD_OUEST , EST , SUD_OUEST } , 
    /* SUD */
    { 1 , NULLE_PART } , 
    /* SUD_OUEST */
    { 5 , SUD_EST , EST , NORD_EST , NORD , NORD_OUEST } , 
    /* OUEST */
    { 1 , NULLE_PART } , 
    /* NORD_OUEST */
    { 5 , SUD_OUEST , SUD , SUD_EST , EST , NORD_EST }  
  } ,

 /* Pour obstacle ANGLE OUVERT */
  {
    /* NULLE_PART */
    { 1 , NULLE_PART } ,
    /* NORD */
    { 1 , NULLE_PART } ,
    /* NORD_EST */
    { 3 , EST , SUD_OUEST , SUD } ,
    /* EST */
    { 1 , NULLE_PART } , 
    /* SUD_EST */
    { 3 , NORD , NORD_OUEST , OUEST } , 
    /* SUD */
    { 1 , NULLE_PART } , 
    /* SUD_OUEST */
    { 3 , NORD , NORD_OUEST , EST } , 
    /* OUEST */
    { 1 , NULLE_PART } , 
    /* NORD_OUEST */
    { 3 , SUD , SUD_EST , EST }  
  } 

}  ;

/*
 * Fonction sur les directions 
 */
extern
direction_t direction_affecter( direction_t * d1 , const direction_t d2 ) 
{
  return( (*d1) = d2 ) ; 
}

extern 
err_t cb_direction_affecter( void * * d1 , void * const d2 ) 
{
  return( direction_affecter( (direction_t *)d1 , (direction_t)d2 ) ) ;
}

extern
direction_t direction_suivante( direction_t d ) 
{
  return( d+1 ) ;
}

extern
void direction_afficher( direction_t d ) 
{
  switch( d )
    {
    case NORD : printf("Nord") ;
      break ; 
    case NORD_EST : printf("Nord-Est") ;
      break ; 
    case EST : printf("Est") ;
      break ; 
    case SUD_EST : printf("Sud-Est") ;
      break ; 
    case SUD : printf("Sud") ;
      break ; 
    case SUD_OUEST : printf("Sud-Ouest") ;
      break ; 
    case OUEST : printf("Ouest") ;
      break ; 
    case NORD_OUEST : printf("Nord-Ouest") ;
      break ; 
    default : printf("???") ;
      break ; 
    }
}

extern
char * direction_string_afficher( direction_t d ) 
{
  switch( d )
    {
    case NORD : return("Nord") ;
      break ; 
    case NORD_EST : return("Nord-Est") ;
      break ; 
    case EST : return("Est") ;
      break ; 
    case SUD_EST : return("Sud-Est") ;
      break ; 
    case SUD : return("Sud") ;
      break ; 
    case SUD_OUEST : return("Sud-Ouest") ;
      break ; 
    case OUEST : return("Ouest") ;
      break ; 
    case NORD_OUEST : return("Nord-Ouest") ;
      break ; 
    default : return("???") ;
      break ; 
    }
}

/*
 * Donne une direction au hasard
 */
extern
direction_t direction_random() 
{
  unsigned int seed = (unsigned int) time(NULL) ;
  return((direction_t)((rand_r(&seed)%DIR_NB)+1)) ;
}

/*
 * Donne une direction opposee au hasard 
 */
extern
direction_t direction_opposee_random( const obstacle_t obstacle ,
				      const direction_t direction ) 
{
  unsigned int seed = (unsigned int)time(NULL) ;
  return( (direction_t)(tab_dir_opp[obstacle][direction][(rand_r(&seed)%tab_dir_opp[obstacle][direction][0])+1]) ) ;
}


extern
direction_t direction_opposee_suivante( const obstacle_t obstacle, 
					const direction_t direction , 
					const direction_t direction_opposee ) 
{
  int i ; 
  for( i=1 ; (i<=tab_dir_opp[obstacle][direction][0]) && (direction_opposee!=tab_dir_opp[obstacle][direction][i]) ; i++ ) ;
  
  if( i<tab_dir_opp[obstacle][direction][0] )
    return( tab_dir_opp[obstacle][direction][i+1] ) ;
  else
    return(DIR_SENTINELLE);
}

extern
int direction_opposee_nb( const obstacle_t obstacle ,
			  const direction_t direction ) 
{
  return( tab_dir_opp[obstacle][direction][0] ) ;
}


extern
direction_t direction_opposee_premier( const obstacle_t obstacle ,
				       const direction_t direction ) 
{
  return( tab_dir_opp[obstacle][direction][1] ) ;
}


extern
direction_t direction_opposee_random_suivante( const obstacle_t obstacle ,
					       const direction_t direction , 
					       const direction_t direction_opposee ) 
{
  int i ; 
  for( i=1 ; (i<=tab_dir_opp[obstacle][direction][0]) && (direction_opposee!=tab_dir_opp[obstacle][direction][i]) ; i++ ) ;

 if( i<tab_dir_opp[obstacle][direction][0] )
    return( tab_dir_opp[obstacle][direction][i+1] ) ;
  else
    return( tab_dir_opp[obstacle][direction][1]);  
}
