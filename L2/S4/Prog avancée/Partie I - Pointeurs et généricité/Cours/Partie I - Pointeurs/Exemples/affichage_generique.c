#include <stdio.h>
#include <stdlib.h>

/* FONCTION GENERIQUE D'AFFICHAGE d'UN TABLEAU */

static 
void afficher_tableau( void * T , /* Tableau de pointeurs sur des objets generiques */
		       const int N , /* Nombre d'objets dans le tableau  */ 
		       const int taille , /* Taille des elements du tableau */
		       void (*afficher_element)(const void * e) ) /* Fonction d'affichage d'un objet generique */ 
{
  int i = 0 ; 
  
  for( i=0 ; i < N ; i++ ) 
    {
      (*afficher_element)( T+(i*taille) ) ;
      printf(" ");
    }
  printf("\n" ) ;
}


/* ENTIER */

/* Fonction d'affichage d'un entier */
static 
void afficher_int( const int * i )
{
  printf("%d" , (*i) ) ;
}

static 
void afficher_int_cb( const void * v )
{
  const int * i = v ;

  return( afficher_int( i ) ) ;
}



/* STRUCTURE */
typedef struct S_s
{
  char * c ;
  int i ;
} S_t ;

/* Fonction d'affichage d'un entier */
static 
void afficher_struct( const S_t * s )
{
  printf("{ %s , %d }" , s->c , s->i ) ;
}

static 
void afficher_struct_cb( const void * v )
{
  const S_t * s = v ;

  return( afficher_struct( s ) ) ;
}

/* Programme d'appel de la fonction generique */
int 
main()
{
  int tab_i[10] = { 9 , 2 , 5 , 4 , 8 , 0 , 7 , 1 , 3 , 6 } ;
  S_t tab_s[3] = { { "abcd" , 11 } , { "efg" , 22 } , { "hijklmo" , 33 } } ;

  printf("Affichage du tableau d'entiers\n");
  afficher_tableau( tab_i , 10 , sizeof(int) , afficher_int_cb ) ;

  printf("Affichage du tableau de structures\n");
  afficher_tableau( tab_s , 3 , sizeof(S_t) , afficher_struct_cb ) ;

  return(0);
}
