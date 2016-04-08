#include <stdio.h>
#include <individu.h>
#include <fraction.h>
#include <mystring.h>
#include <liste_objet.h>

int
main() 
{
  err_t noerr = OK; 
  individu_t * indiv_1 = individu_creer( "Roger" , "Waters" ) ; 
  individu_t * indiv_2 = individu_creer( "David" , "Gilmour" ) ; 
  fraction_t * frac_1 = fraction_creer( 3 , 5 ) ;
  fraction_t * frac_2 = fraction_creer( 9 , 13 ) ;
  string_t * str_1 = string_creer( "azertyuiop" ) ; 
  string_t * str_2 = string_creer( "qsdfghjklm" ) ;
  string_t * str_3 = string_creer( "wxcvbn" ) ; 

  liste_objet_t * liste_objet = NULL ;

  printf( "Debut du programme des test sur les objets de type liste_objet_t\n" ) ; 

  printf( "Test d'existance sur une liste_objet_t inexistant\n" ) ;
  ( liste_objet_existe(liste_objet) ? printf("-->KO\n") : printf ("-->OK\n") )  ;
  printf( "\n");
  
  printf( "Test creation liste_objet_t\n" ) ;
  liste_objet = liste_objet_creer(8) ;
  (liste_objet->elem_ecrire)(liste_objet, (objet_t *)indiv_1 , 0 );
  (liste_objet->elem_ecrire)(liste_objet, (objet_t *)indiv_2 , 1 );
  (liste_objet->elem_ecrire)(liste_objet, (objet_t *)frac_1 , 2 );
  (liste_objet->elem_ecrire)(liste_objet, (objet_t *)frac_2 , 3 );
  (liste_objet->elem_ecrire)(liste_objet, (objet_t *)str_1 , 4 );
  (liste_objet->elem_ecrire)(liste_objet, (objet_t *)str_2 , 5 );
  (liste_objet->elem_ecrire)(liste_objet, (objet_t *)str_3 , 7 );
  printf( "\n");
  
  printf( "Test affichage liste_objet \n" ) ;
  (liste_objet->afficher)(liste_objet,' '); 
  printf( "\n");
  
  printf( "Test d'existance sur une liste_objet_t existant\n" ) ;
  ( liste_objet_existe(liste_objet) ? printf("-->OK\n") : printf ("-->KO\n") )  ;
  
  printf( "Test destruction liste_objet\n" ) ;
  if( ( noerr = (liste_objet->detruire)(&liste_objet) ) )
    { 
      printf("Sortie avec code erreur = %d\n" , noerr ) ;
      return(noerr) ; 
    }
  
  printf( "Fin du programme des test sur les objets de type liste_objet_t\n" ) ; 
  
  printf( "Nombre de liste_objet_t  = %lu\n" , liste_objet_cpt ) ;
  
  return(0) ; 
}
