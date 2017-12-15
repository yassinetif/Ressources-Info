#include <stdio.h>
#include <stdlib.h>

#include <coord.h>

#define N 10 


int
main( int argc , char * argv[] ) 
{
  coord_t * coord  = NULL ;
  coord_t * coord2 = NULL ;
  err_t cr = OK ; 

  printf("\n\n\n\t===========Debut %s==========\n\n" , argv[0] );

  printf("Creation d'une coordonne [1,2]\n") ;
  coord = coord_creer( 1 , 2 ) ;


  printf("Affichage:\n");
  printf("Coordonnee = "  ) ; fflush(stdout) ; 
  coord_afficher(coord) ; printf("\n") ;
 
  printf("\nAffectation de la coordonnee chargee dans une autre\n") ;
  if( (cr=coord_copier( &coord2 , coord ) ) )
    {
      printf("Pb coord_affecter avec cr =%d\n" , cr ) ;
    }

  printf("\nDestruction de la coord source..." ) ; fflush(stdout) ; 
  coord_detruire( &coord )  ; 
  printf("OK\n");

  printf("\tAffichage de la coordonnee affectee\n") ;
  coord_afficher( coord2 ) ;
  printf("\n");

  printf("\tDestruction de la coordonnee affectee\n" ) ; 
  coord_detruire( &coord2 )  ; 

  printf("\nSaisie d'une coordonnee (X pour arreter)\n" ) ; 
  while( (cr = coord_saisir( &coord) ) != FIN_SAISIE )
    {
      printf( "Code retour saisie = %d\n" , cr ) ;
      printf( "Coord saisie = " ) ; 
      coord_afficher(coord) ; 
      printf("\n\n") ; 
    }

  coord_detruire( &coord )  ; 

 printf("Creation d'une coordonne [9,9]\n") ;
 coord = coord_creer( 9 , 9 ) ;

 printf("Referencement de cette coord\n") ;
 coord_referencer( &coord2 , coord ) ;


 printf("\nAffichage coord source\n") ;
 coord_afficher(coord) ;
 printf("\nAffichage coord cible\n") ;
 coord_afficher(coord2) ;


 printf("\nModif de la coordonne [9,9] en [8,8]\n") ;
 coord_ecrire( coord , 8 , 8 ) ;

 printf("\nAffichage coord source\n") ;
 coord_afficher(coord) ;
 printf("\nAffichage coord cible\n") ;
 coord_afficher(coord2) ;

 

 printf("\n\nTests comparaisons coordonnees\n") ;
 coord_ecrire( coord , 2 , 3 ) ;
 coord2 = coord_creer( 3 , 2 ) ;
 if( coord_comparer( coord , coord2 ) == 0 )
   {
     coord_afficher(coord) ;
     printf(" == ") ;
     coord_afficher(coord2) ;
     printf( "--> KO !!! \n") ; 
   }
 else
   {
     coord_afficher(coord) ;
     printf(" != ") ;
     coord_afficher(coord2) ;
     printf( "--> OK\n") ; 
   }
 coord_ecrire( coord2 , 2 , 3 ) ;
 if( coord_comparer( coord , coord2 ) == 0 )
   {
     coord_afficher(coord) ;
     printf(" == ") ;
     coord_afficher(coord2) ;
     printf( "--> OK\n") ; 
   }
 else
   {
     coord_afficher(coord) ;
     printf(" != ") ;
     coord_afficher(coord2) ;
     printf( "--> KO !!!\n") ; 
   }
  
  printf("\n\n\t===========Fin %s==========\n\n" , argv[0] );

  return(0) ;
}

