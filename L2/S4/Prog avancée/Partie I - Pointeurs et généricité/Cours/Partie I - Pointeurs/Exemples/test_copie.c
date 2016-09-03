#include <stdio.h>
#include <stdlib.h>

#include <copie.h>

/* Programme d'appel de la fonction generique */
typedef struct S_s
{
  char * c ;
  int i ;
} S_t ;

static 
void afficher_tabi( int * tabi , int n )
{
  int i = 0 ; 
  printf( "{ " ) ; 
  for(i=0; i<n ; i++) printf("%d " , tabi[i]) ; 
  printf( "}\n" ) ; 
  
}
int 
main()
{
  int i1 = 11 ;
  int i2 = 0 ;
  int * pt_i = NULL ; 
  float f1 = 12.34 ; 
  float f2 = 0.0 ;
  float * pt_f = NULL ;
  double d1 = 999.99 ;
  double d2 = 0 ; 
  double * pt_d = NULL; 
  S_t s1 = { "abc" , 12 } ;
  S_t s2 = { "-" , 0 } ;
  S_t * pt_s = NULL ; 
  int tabi1[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 } ; 
  int tabi2[10] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1} ; 
  

  printf( "AVANT i1 = %d , i2 = %d\n" , i1 , i2 ) ;
  pt_i = copie( &i2 , &i1 , sizeof(int) ) ;
  printf( "APRES i1 = %d , i2 = %d\n\n" , i1 , i2 ) ;

  printf( "AVANT f1 = %f , f2 = %f\n" , f1 , f2 ) ;
  pt_f = copie( &f2 , &f1 , sizeof(float) ) ;
  printf( "APRES f1 = %f , f2 = %f\n\n" , f1 , f2 ) ;
  
  printf( "AVANT d1 = %g , d2 = %g\n" , d1 , d2 ) ;
  pt_d = copie( &d2 , &d1 , sizeof(double) ) ;
  printf( "APRES d1 = %g , d2 = %g\n\n" , d1 , d2 ) ;

  printf( "AVANT s1 = {%s,%d} , f2 = {%s,%d}\n" , s1.c , s1.i , s2.c , s2.i ) ;
  pt_s = copie( &s2 , &s1 , sizeof(S_t) ) ;
  printf( "APRES s1 = {%s,%d} , f2 = {%s,%d}\n\n" , s1.c , s1.i , s2.c , s2.i ) ;

  printf( "AVANT tabi1 = ") ; afficher_tabi(tabi1 , 10) ; 
  printf( "      tabi2 = ") ; afficher_tabi(tabi2 , 10) ; 
  pt_i = copie( tabi2 , tabi1 , 10*sizeof(int) ) ;
  printf( "APRES tabi1 = ") ; afficher_tabi(tabi1 , 10) ; 
  printf( "      tabi2 = ") ; afficher_tabi(tabi2 , 10) ; 
  printf("\n") ;

  return(0);
}
