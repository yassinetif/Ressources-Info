#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

#include <aire.h>

#define N 10 


int
main( int argc , char * argv[] ) 
{
  aire_t * A  = NULL ;
  aire_t * A_cible = NULL ; 
  err_t cr = OK ; 
  int i ; 

  printf("\n\n\n\t===========Debut %s==========\n\n" , argv[0] );

  srand(getpid());

  printf("Test existance sur aire inexistante ...") ;
  if( aire_existe(A) )
    printf("KO !!!!!\n" ) ;
  else
    printf("OK\n") ; 

  printf("Creation d'une aire de 20X10\n") ;
  if( ( A = aire_creer( 20 , 10 ) ) == AIRE_NULL )
    {
      printf("Erreur sur la creation de l'aire\n") ; 
      exit(-1);
    }

  printf("Test existance sur aire existante ...") ;
  if( aire_existe(A) )
    printf("OK\n") ;
  else
    printf("KO !!!!!\n" ) ;  

 printf("Test vide sur aire vide ...") ;
  if( aire_vide(A) )
    printf("OK\n") ;
  else
    printf("KO !!!!!\n" ) ;  

  printf("Affichage aire\n") ;
  aire_afficher(A) ;
 
  dim_t H = aire_hauteur_lire(A) ; 
  dim_t L = aire_largeur_lire(A) ; 
  printf("Lecture dimensions aire = %dX%d\n" , H , L ) ;
  
  bille_id_t nb_billes = (rand()%(H*L) ) ; 
  printf("Creation de %d billes\n" , nb_billes ) ; 
  bille_t ** tab_billes = (bille_t **)malloc(sizeof(bille_t*)*nb_billes) ;
  for( i=0 ; i<nb_billes ; i++ ) 
    {      
      if( ( tab_billes[i] = bille_creer( direction_random() ,
					 10+i , 
					 COORD_NULL ,
					 '*' ) ) == BILLE_NULL )
	{
	  printf("Erreur lors de la creation de la bille %d\n", i );
	}
      /* printf( "Bille %d : \n"  , i ); bille_struct_afficher(tab_billes[i]) ; printf("\n") ; */
    }

  printf("Positionnement des %d billes sur l'aire A\n" , nb_billes ) ; 
  for( i=0 ; i < nb_billes ; i++ ) 
    {
      if( (cr = aire_bille_positionner( A , tab_billes[i] ) ) )
	{
	  printf("Sortie erreur avec cr = %d\n", cr );
	  erreur_afficher(cr) ; 
	  printf("\n");
	  exit(-1) ; 
	}
    }
  printf("Les billes sont posees sur A mais n'appartiennent pas a A\n") ; 


  printf("Nombre de billes = %d \n" , aire_nb_billes_lire(A) ) ;
  aire_afficher(A) ;
 
  printf("Test vide sur aire pas vide ...") ;
  if( aire_vide(A) )
    printf("KO !!!!!\n" ) ; 
  else
    printf("OK\n") ;

  printf("Copie de l'aire A dans une aire A_cible \n");
  if( ( cr = aire_copier( &A_cible , A ) ) )
    {
      printf("Sortie erreur avec cr = %d\n", cr );
      erreur_afficher(cr) ; 
      printf("\n");
      exit(-1);
    }
  printf("Les billes sont partagees par A et A_cible\n") ; 

  printf("Destruction aire A (on ne detruit pas les billes)\n");
  if( ( cr = aire_detruire( &A) ) ) 
    {
      printf("Sortie erreur avec cr = %d\n", cr );
      erreur_afficher(cr) ; 
      exit(-1) ; 
    }
  
  printf("Affichage de l'aire A_cible (les billes existent encore)\n");
  aire_afficher(A_cible) ; 
 
  printf("Destruction aire A_cible (sans les billes)\n");
  if( ( cr = aire_detruire( &A_cible) ) ) 
    {
      printf("Sortie erreur avec cr = %d\n", cr );
    }

  printf("Destructions des %d billes\n" , nb_billes ) ; 
  for(i=0 ; i< nb_billes ; i++ )
    bille_detruire( &(tab_billes[i] ) ) ;
  free(tab_billes);


  A = aire_creer( H , L ) ; 
  nb_billes = (H*L)+1 ; 
  printf("Test aire pleine en posant 1 bille %d fois sur l'aire A (la bille est partagee par toutes les cases)\n" , nb_billes ) ; 
  bille_t * bille =  bille_creer( NORD , 1 , COORD_NULL , '*' ) ; 
  for( i=0 ; i<nb_billes ; i++ ) 
    {      
      if( (cr = aire_bille_positionner( A , bille ) ) )
	{
	  printf("Sortie erreur avec cr = %d\n", cr );
	  erreur_afficher(cr) ; 
	  printf("\n");
	}
    }
  aire_afficher(A) ;
 
  printf("Destruction de A (sans la bille)\n") ; 
  aire_detruire(&A) ; 

  printf("Creation d'une aire  A\n") ; 
  A = aire_creer( H , L ) ; 
  printf("Test deplacement d'une bille\n" ) ; 
  bille =  bille_creer( NORD , 1 , COORD_NULL , '*' ) ; 
  dim_t l = (dim_t)(H/2) ; 
  dim_t c = (dim_t)(L/2) ; 
  if( ( cr = aire_bille_poser( A , l , c , bille ) ) )
    {
      printf("Sortie erreur avec cr = %d\n", cr );
      erreur_afficher(cr) ; 
      printf("\n");
      exit(-1) ; 
    }
  printf("\t AVANT deplacement\n" ) ;
  aire_afficher(A) ;


  printf("\nExtraction liste des billes depuis l'aire\n");
  liste_t * liste_billes = LISTE_NULL ; 
  liste_billes = aire_billes_lire(A) ;
  liste_id_t nb_l_billes = liste_taille(liste_billes) ; 
  printf("Nombre de billes dans la liste = %ld\n" , nb_l_billes ); 
  printf("Liste des billes dans la liste:\n") ; 
  liste_afficher(liste_billes,cb_bille_struct_afficher,'\n') ;  
  printf("\n\n") ; 
  
  /* Deplacement vers le Sud */
  coord_t * coord_arrivee = coord_creer( l+1 , c ) ;
  if( (cr = aire_bille_deplacer( A , 
				 aire_case_lire( A , l , c ) , 
				 aire_case_lire( A , l+1 , c ) , 
				 coord_arrivee ) ) )
    {
      printf("Sortie erreur avec cr = %d\n", cr );
      erreur_afficher(cr) ; 
      printf("\n");
    }
  printf("\t APRES deplacement\n" ) ;
  aire_afficher(A) ;

  printf("\nExtraction liste des billes apres deplacement\n");
  liste_billes = aire_billes_lire(A) ;
  nb_l_billes = liste_taille(liste_billes) ; 
  printf("Nombre de billes dans la liste = %ld\n" , nb_l_billes ); 
  printf("Liste des billes dans la liste:\n") ; 
  liste_afficher(liste_billes,cb_bille_struct_afficher,'\n') ;  
  printf("\n\n") ; 

  printf("On enleve la bille de l'aire\n" ) ;
  aire_bille_enlever( A , bille ) ;

  printf("\t APRES enlevement de la bille\n" ) ;
  aire_afficher(A) ;

  printf("\nExtraction liste des billes apres enlevement\n");
  liste_billes = aire_billes_lire(A) ;
  nb_l_billes = liste_taille(liste_billes) ; 
  printf("Nombre de billes dans la liste = %ld\n" , nb_l_billes ); 
  printf("Liste des billes dans la liste:\n") ; 
  liste_afficher(liste_billes,cb_bille_struct_afficher,'\n') ;  
  printf("\n\n") ; 
  

  
  printf("Destructions de la bille\n" ) ; 
  bille_detruire( &bille ) ;

  printf( "Destruction de la coord d'arrivee\n") ; 
  coord_detruire( &coord_arrivee ) ; 



  
  printf("\n\n\t===========Fin %s==========\n\n" , argv[0] );

  return(0) ;
}

