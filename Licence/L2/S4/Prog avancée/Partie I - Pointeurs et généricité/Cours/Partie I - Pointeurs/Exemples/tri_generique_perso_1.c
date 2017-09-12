#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <copie.h>

/* FONCTION GENERIQUE DE TRI d'UN TABLEAU */

static 
void tri( void * T , /* Tableau de pointeurs sur des objets generiques */
	  const int N , /* Nombre d'objets dans le tableau  */ 
	  const int taille , /* Taille des elements du tableau */
	  int (*comparer)( void * e1 ,  void * e2) ) /* Fonction de comparaison de 2 objets generiques */ 
{
  int i = 0 ; 
  void * w = malloc(taille) ; 
  
  while( i < N-1 ) 
    {
      if( (*comparer)( T+(i*taille) , T+((i+1)*taille) ) > 0 )
	{
	  copie( w , T+(i*taille) , taille ) ; 
	  copie( T+(i*taille) , T+((i+1)*taille) , taille ) ; 
	  copie( T+((i+1)*taille) , w , taille ) ; 
	  i = 0 ; 
	}
      else
	i++ ; 
    }
  free(w) ; 
}


/* Fonction de comparaison de 2 pointeurs sur 2 entiers */
static 
int comparer_int(  int * i1 ,  int * i2 )
{
  return( (*i1) - (*i2) ) ;
}

/* Fonction d'affichage d'un tableau d'entiers */
static 
void afficher_int( int * T ,  int N )
{
  int i = 0 ; 
  for( i=0 ; i<N ; i++ ) 
      printf( "%d " , T[i] ) ;
  printf("\n" ); 
}


/* Fonction de comparaison de 2 pointeurs sur 2 chaines de car */
static 
int comparer_str(  char ** s1 ,  char ** s2 )
{
  return( strcmp( (*s1) , (*s2) ) ) ;
}

/* Fonction d'affichage d'un tableau de chaines de car */
static 
void afficher_str( char ** T ,  int N )
{
  int i = 0 ; 
  for( i=0 ; i<N ; i++ ) 
      printf( "%s " , T[i] ) ;
  printf("\n" ); 
}



/* Programme d'appel de la fonction generique */
int 
main()
{
  int tab_i[10] = { 9 , 2 , 5 , 4 , 8 , 0 , 7 , 1 , 3 , 6 } ; 
  char * tab_s[5] = { "DDDD" , "AAA" , "ZZZZ" , "UUUU" , "II" } ;

  printf( "\nTableau d'entiers AVANT tri:\n") ; 
  afficher_int( tab_i , 10 ) ;
  
  tri( tab_i , 10 , sizeof(int) , comparer_int ) ;

  printf( "Tableau d'entiers APRES tri:\n") ; 
  afficher_int( tab_i , 10 ) ;


  printf( "\nTableau de chaines de car AVANT tri:\n") ; 
  afficher_str( tab_s , 5 ) ;
  
  tri( tab_s , 5 , sizeof(char *) , comparer_str ) ;

  printf( "Tableau de chaines de car APRES tri:\n") ; 
  afficher_str( tab_s , 5 ) ;

  return(0);
}
