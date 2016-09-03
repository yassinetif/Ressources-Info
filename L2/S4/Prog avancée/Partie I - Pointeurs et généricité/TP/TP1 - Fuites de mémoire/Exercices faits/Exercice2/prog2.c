#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <obj2s.h>

#define MAX1 20
#define MAX2 100
#define BOUCLE 50

int
main()
{
  err_t noerr = OK ;
  obj2_t * objet = NULL ;
  obj2s_t * liste = NULL ;
  obj2s_t * copie_liste = NULL ;

  int i = 0 ;
  int taille = 0 ;
  int b = 0 ;

  printf( "Debut programme pour colmater les fuites memoire\n");
  srand( (unsigned int) getpid() ) ;

  liste = obj2s_creer(0) ;

  obj2s_detruire(&liste);

  for( b=0 ; b<BOUCLE ; b++ )
    {
      taille = rand() % MAX2 ;

      printf( "%3d : Creation + copie liste de %6d objets obj2_t..." , b , taille ) ; fflush(stdout ) ;

      liste = obj2s_creer(taille) ;
      for( i=0 ; i<taille ; i++ )
	{
	  objet = obj2_creer(rand()%MAX1) ;
	  if( ( noerr = obj2s_obj2_ecrire( liste, objet , i ) ) )
	    {
	      printf( "Sortie avec code erreur %d\n" , noerr ) ;
	      return(noerr) ;
	    }
	  obj2_detruire(&objet) ;
	}

      if( ( noerr = obj2s_copier( &copie_liste , liste ) ) )
	{
	  printf( "Sortie avec code erreur %d\n" , noerr ) ;
	  return(noerr) ;
	}
      printf("...OK\n" ) ;

      /* obj2s_afficher( copie_liste ) ; */

      if( ( noerr = obj2s_detruire( &liste ) ) )
	{
	  printf( "Sortie avec code erreur %d\n" , noerr ) ;
	  return(noerr) ;
	}

      if( ( noerr = obj2s_detruire( &copie_liste ) ) )
	{
	  printf( "Sortie avec code erreur %d\n" , noerr ) ;
	  return(noerr) ;
	}

    }

  printf("Compteurs :\n");
  printf("  obj1 : %i\n", obj1_compteur);
  printf("  obj1s : %i\n", obj1s_compteur);
  printf("  obj2 : %i\n", obj2_compteur);
  printf("  obj2s : %i\n", obj2s_compteur);

  printf( "Fin programme de colmatage\n");

  return(OK);
}
