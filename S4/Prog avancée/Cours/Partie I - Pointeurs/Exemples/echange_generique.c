#include <stdio.h>

static 
void echange_bad(void * p , void * q) 
{
  void * w ;
  w = p ; p = q ; q = w ;
}

static
void echange_good( void ** p , void ** q ) 
{
  void * w ;
  w = (*p) ; (*p) = (*q) ; (*q) = w ;
}

int
main()
{
  int i1 = 5 ;
  int i2 = 10 ;
  int * p_i1 = &i1 ; 
  int * p_i2 = &i2 ;

  float f1 = 6.6 ;
  float f2 = 77.77 ;
  float * p_f1 = &f1 ; 
  float * p_f2 = &f2 ;

  double d1 = 888888 ;
  double d2 = 999999 ;
  double * p_d1 = &d1 ; 
  double * p_d2 = &d2 ;

  printf( "\nAVANT : p_i1 = %d et p_i2 = %d\n" , *p_i1 , *p_i2 ) ; 
  echange_bad( p_i1 , p_i2) ; 
  printf( "APRES mauvais echange : p_i1 = %d et p_i2 = %d\n" , *p_i1 , *p_i2 ) ; 
  /* echange_good( &p_i1 , &p_i2 ) ; */
  echange_good( (void **)&p_i1 , (void **)&p_i2 ) ;
  printf( "APRES bon echange : p_i1 = %d et p_i2 = %d\n\n" , *p_i1 , *p_i2 ) ;


  printf( "AVANT : p_f1 = %f et p_f2 = %f\n" , *p_f1 , *p_f2 ) ; 
  echange_bad( p_f1 , p_f2) ; 
  printf( "APRES mauvais echange : p_f1 = %f et p_f2 = %f\n" , *p_f1 , *p_f2 ) ; 
  /* echange_good( &p_f1 , &p_f2 ) ; */
  echange_good( (void **)&p_f1 , (void **)&p_f2 ) ;
  printf( "APRES bon echange : p_f1 = %f et p_f2 = %f\n\n" , *p_f1 , *p_f2 ) ; 


  printf( "AVANT : p_d1 = %G et p_d2 = %G\n" , *p_d1 , *p_d2 ) ; 
  echange_bad( p_d1 , p_d2) ; 
  printf( "APRES mauvais echange : p_d1 = %G et p_d2 = %G\n" , *p_d1 , *p_d2 ) ; 
  /*   echange_good( &p_d1 , &p_d2 ) ; */
  echange_good( (void **)&p_d1 , (void **)&p_d2 ) ;
  printf( "APRES bon echange : p_d1 = %G et p_d2 = %G\n\n" , *p_d1 , *p_d2 ) ; 

  return(0) ; 
}
