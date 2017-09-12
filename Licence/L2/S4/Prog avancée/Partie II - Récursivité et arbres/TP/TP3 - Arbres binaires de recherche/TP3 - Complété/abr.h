#ifndef __ARBRE_H__
#define __ARBRE_H__

#include<stdio.h>
#include<stdlib.h>

// taille maximum pour le texte dans l'arbre
#define TAILLE_MAX 100

/* Type des elements de l'arbre */
#define TYPE_ELEM EVENT
#define INITIALISATION_INT				50
#define INITIALISATION_CHAR				"Test"
#define INITIALISATION_EVENT_DATE		1204
#define INITIALISATION_EVENT_INTITULE	"4e Croisade"

/* OS */
#define OS  WINDOWS

typedef struct t_event {
	int date;
	char intitule[TAILLE_MAX];
} t_event;

typedef union {
	char chaine[TAILLE_MAX] ;
	int nb ;
	t_event event;
} t_type ;

typedef struct elem { t_type val; } t_elem;

typedef struct noeud {
	t_elem val;
	struct noeud *pere, *sag, *sad;
} t_noeud;

typedef struct noeud* t_arbre;

typedef enum type_parcours { PREFIXE, INFIXE, POSTFIXE } t_type_parcours;

typedef enum type_element { CHAR, INT, EVENT } t_type_element;

typedef enum os { WINDOWS, LINUX } t_os;


/****************************************
 * Primitives de modification de la structure de l'arbre
 ****************************************/
t_arbre creer_arbre(t_elem val, t_arbre sag, t_arbre sad, t_arbre pere); /* renvoie l'arbre dont la racine vaut val, avec les sous-arbre sag et sad */
int supprimer_arbre(t_arbre*);		/* supprimer le sous-arbre dont la racine est donnee en parametre  */
t_arbre ajout_gauche(t_arbre, t_elem);
t_arbre ajout_droit(t_arbre, t_elem);

/****************************************
 * Primitives d'accès à la structure de l'arbre
 ****************************************/
t_arbre pere(t_arbre); /* renvoie le pere s'il existe, NULL sinon */
t_arbre sag(t_arbre); /* renvoie le sous-arbre gauche s'il existe, NULL sinon */
t_arbre sad(t_arbre); /* renvoie le sous arbre droit s'il existe, NULL sinon */
t_arbre valeur_inferieure(t_arbre arb);
t_arbre valeur_superieure(t_arbre arb);

/****************************************
 * Primitives de vérification
 ****************************************/
int arbre_vide(t_arbre);			/* renvoie vrai si arbre vide, faux sinon */
int est_racine(t_arbre); /*renvoie vrai si le noeud est une racine */
int est_feuille(t_arbre); /*renvoie vrai si le noeud est une feuille */

/****************************************
 * Primitives de modification de la valeur de la racine
 ****************************************/
int modif_racine(t_arbre, t_elem);	/* modifie la valeur de la racine de l'arbre */
int val_racine(t_arbre, t_elem*); 		/* renvoie la valeur de la racine de l'arbre */

/****************************************
 * Primitives d'affichage
 ****************************************/
void afficher_val(t_arbre, char);
int afficher_arbre(t_arbre, t_type_parcours);
int afficher_arbre_prefixe(t_arbre, int);
int afficher_arbre_infixe(t_arbre, int );
int afficher_arbre_postfixe(t_arbre, int);
void afficher_ancetres(t_arbre a, char end);

/****************************************
 * Primitives de parcours d'arbre
 ****************************************/
int parcours_prefixe(t_arbre, void (*)(t_elem*));

/****************************************
 * Primitives de comparaison
 ****************************************/
int cmp_elem(t_type, t_type);
int cmp_elem_int(int *, int *);
int cmp_elem_char(char *, char *);
int cmp_elem_event(t_event *, t_event *);

/****************************************
 * Primitives de recherche
 ****************************************/
void rechercher(t_arbre);
t_arbre rechercher_valeur(t_arbre, t_type);

/****************************************
 * Primitives de creation d'elements
 ****************************************/
t_elem creer_elem(t_type);
t_elem creer_elem_char(char *);
t_elem creer_elem_int(int);
t_elem creer_elem_event(t_event);

/****************************************
 * Primitives de suppression
 ****************************************/
void supprimer(t_arbre abr);
void supprimer_valeur(t_arbre abr, t_type el);
int supprimer_feuille(t_arbre * arb);
int supprimer_arbre(t_arbre* pa);
int supprimer_noeud(t_arbre * arb);

/****************************************
 * Primitives diverses
 ****************************************/
void init_arbre(t_arbre *);
int max(int, int);
void pause();
void effacer_ecran();

#endif
