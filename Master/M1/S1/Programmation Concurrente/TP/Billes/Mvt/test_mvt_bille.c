#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

#include <mvt_bille.h>


int
main( int argc , char * argv[] ) 
{
  aire_t * A  = AIRE_NULL ;
  err_t cr = OK ; 
  int i ;
  /*   int j ;  */
  bille_t * bille = BILLE_NULL ; 
  bille_t * bille2 = BILLE_NULL ; 
  liste_t * liste_billes = NULL ; 

  printf("\n\n\n\t===========Debut %s==========\n\n" , argv[0] );

  srand(getpid());


  printf("Creation d'une aire de 5X10\n") ;
  if( ( A = aire_creer( 5 , 10 ) ) == AIRE_NULL )
    {
      printf("Erreur sur la creation de l'aire\n") ; 
      exit(-1);
    }

  printf("Affichage aire\n") ;
  aire_afficher(A) ;

  printf("Creation d'une bille\n" ) ; 
  if( ( bille = bille_creer( NORD ,
			     10, 
			     COORD_NULL ,
			     '*' ) ) == BILLE_NULL )
    {
      printf( "Pb sur creation de la bille\n");
      exit(-1) ; 
    }
  
  printf("Positionnement de la bille sur l'aire \n" ) ;   
  if( (cr = aire_bille_positionner( A , bille ) ) )
    {
      printf("Sortie erreur avec cr = %d\n", cr );
      erreur_afficher(cr) ;
      printf("\n");
      exit(-1) ;
    }
  
  printf("Nombre de billes dans aire = %d \n" , aire_nb_billes_lire(A) ) ;

  /* Recuperation de la liste des  billes de l'aire */
  liste_billes = aire_billes_lire( A ) ;
  int nb_billes = liste_taille(liste_billes) ; 
  printf("Nombre de billes dans liste = %d \n" , nb_billes ) ;
  

  /* Verif reference bille */
  bille2 = liste_premier( liste_billes ) ;
  /* bille2 est normalement une reference sur bille */
  if( bille_comparer( bille , bille2 ) )
    {
      bille_struct_afficher(bille) ;
      printf( "\n != \n" );
      bille_struct_afficher(bille2) ;
      printf( "--> KO\n" );
      exit(-1) ;
    }
  else
    {
      bille_struct_afficher(bille) ;
      printf( "\n == \n" );
      bille_struct_afficher(bille2) ;
      printf( "--> OK\n" );
    }
  if( bille != bille2 ) 
     {
       printf( "\n reference bille 1 %p != reference bille 2 %p --> KO \n" ,
	       bille , bille2 );
       exit(-1) ;
    }
  else
    {
      printf( "\n reference bille 1 %p == reference bille 2 %p --> OK \n" ,
	      bille , bille2 );
    }
  
  bille_marque_ecrire( bille , '#' ) ;

  aire_afficher(A) ;

  /* Deplacement de la bille  */
  printf( "\n\nTest 20 deplacements de la bille\n");
  for( i=0 ; i<20 ; i++ )
    {
      if( (cr = mvt_bille_deplacer( bille , A ) ) )
  	{
  	  printf("Sortie erreur avec cr = %d\n", cr );
  	  erreur_afficher(cr) ;
  	  printf("\n");
  	}
      printf("Deplacement %d\n" , i ) ;
      aire_afficher(A) ;
      printf("Bille:\n");
      bille_struct_afficher(bille) ;
      printf("\n");
    }

  printf( "Destruction de la bille\n");
  if( ( cr = bille_detruire( &bille ) ) )
     {
      printf("Sortie erreur avec cr = %d\n", cr );
      erreur_afficher(cr) ; 
      exit(-1) ; 
    }

  printf("Destruction aire A \n");
  if( ( cr = aire_detruire( &A) ) ) 
    {
      printf("Sortie erreur avec cr = %d\n", cr );
      erreur_afficher(cr) ; 
      exit(-1) ; 
    }
 
  printf("\n\n\t===========Fin %s==========\n\n" , argv[0] );

  return(0) ;
}

