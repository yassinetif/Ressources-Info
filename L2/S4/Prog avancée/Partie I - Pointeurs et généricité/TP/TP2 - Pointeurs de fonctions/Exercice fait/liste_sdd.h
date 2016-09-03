#ifndef _LISTE_SDD_H_
#define _LISTE_SDD_H_

#include <commun.h>
#include <objet.h>


#define LISTE_NULL NULL
#define LISTE_ID_NULL -1


typedef struct liste_s
{
  int nb ;		/* Nombre d'objets dans la liste  */
  objet_t ** liste ;	/* liste  des objets */
} liste_t ;

typedef struct liste_objet_s
{
  int (* nb_lire) (struct liste_objet_s * const);
  objet_t * (* elem_lire) (struct liste_objet_s * const, const int);
  booleen_t (* vide) (struct liste_objet_s * const);
  err_t (* elem_ecrire) (struct liste_objet_s *, objet_t * const, const int); 
  err_t (*detruire) (struct liste_objet_s **);
  void (* afficher) (struct liste_objet_s * const, const char);
  
  int nb ;		/* Nombre d'objets dans la liste  */
  objet_t ** liste ;	/* liste  des objets */
} liste_objet_t ;

#endif
