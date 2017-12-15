#include <stdio.h>
#include <erreur.h>
#include <standard_erreurs.h>
#include <tda_erreurs.h>

extern
void erreur_afficher( const err_t code )
{
  switch( code ) 
    {   
    case ERR_DEB_MEMOIRE		:	fprintf( stderr , " Debordement memoire \n"); break ; 
    case ERR_EFF_MEMOIRE		:	fprintf( stderr , " Erreur lors de la liberation de la memoire \n"); break ; 
    case ERR_NOM_FICHIER		:	fprintf( stderr , " Erreur sur ouverture nom d'un fichier liste \n"); break ; 
    case ERR_PARAM_VIDE			:	fprintf( stderr , " Une fonction a un parametre vide \n"); break ; 
    case ERR_SAISIE			:	fprintf( stderr , " Erreur dans la saisie au clavier d'un parametre \n"); break ; 
    case FIN_SAISIE			:	fprintf( stderr , " Indicateur de fin de saisie d'un parametre \n"); break ; 

    case ERR_DIRECTION_UNK		:	fprintf( stderr , " Direction inconnue \n"); break ; 

    case ERR_LISTE_MAX_LISTE		:	fprintf( stderr , " Maximum de liste atteint \n"); break ; 
    case ERR_LISTE_IND_ELEM		:	fprintf( stderr , " Mauvais indice d'element dans une liste \n"); break ; 
    case ERR_LISTE_SEEK_ELEM		:	fprintf( stderr , " Recherche infructueuse d'un element dans une liste \n"); break ; 
    case ERR_LISTE_END			:	fprintf( stderr , " Fin de liste atteint avant le dernier element \n"); break ; 
    case ERR_LISTE_NULL			:	fprintf( stderr , " Liste inexistante alors qu'attendue \n"); break ; 

    case ERR_COORD_NULL			:	fprintf( stderr , " Operation impossible sur une coordonnee inexistante \n"); break ; 

    case ERR_BILLE_NULL			:	fprintf( stderr , " Operation impossible sur une bille inexistante \n"); break ; 

    case ERR_CASE_NULL			:	fprintf( stderr , " Operation impossible sur une case inexistante \n"); break ;
    case ERR_CASE_TYPE			:	fprintf( stderr , " Erreur sur le type d'une case \n"); break ;

    case ERR_ZONE_NULL			:	fprintf( stderr , " Operation impossible sur une zone inexistante\n"); break ;

    case ERR_AIRE_NULL			:	fprintf( stderr , " Operation impossible sur une aire inexistante \n"); break ; 
    case ERR_AIRE_VALIDE		:	fprintf( stderr , " Aire non valide \n"); break ; 
    case ERR_AIRE_COORD			:	fprintf( stderr , " Mauvaises coordonnees dans une aire \n"); break ; 
    case ERR_AIRE_PLEINE		:	fprintf( stderr , " Ajout d'une bille dans une aire ou toutes les cases sont remplies \n"); break ; 
    case ERR_ECRAN_NULL			:	fprintf( stderr , " Operation impossible sur un ecran inexistant\n"); break ; 

    case ERR_MVT_BILLE_ETOUFFEMENT	:	fprintf( stderr , " Une bille est encerclee et ne peut se deplacer\n"); break ; 
    case ERR_MVT_BILLE_AVANCER		:	fprintf( stderr , " Une bille butte contre un obstacle et ne peut avancer\n"); break ; 

    default : 
      fprintf( stderr , "Code message inconnu : %d\n" , code ) ;  break ;
    }

  return  ; 
}

