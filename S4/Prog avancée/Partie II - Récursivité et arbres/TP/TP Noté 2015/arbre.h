#ifndef __ARBRE_H__
#define __ARBRE_H__

#include<stdio.h>
#include<stdlib.h>

typedef struct noeud {
	int val;
	struct noeud *pere, *sag, *sad;
} t_noeud;

typedef struct noeud* t_arbre;

typedef enum type_parcours { PREFIXE, INFIXE, POSTFIXE } t_type_parcours;


/****************************************
 * primitives de modification de la structure de l'arbre
 ****************************************/
t_arbre creer_arbre(int val, t_arbre sag, t_arbre sad, t_arbre pere); /* renvoie l'arbre dont la racine vaut val, avec les sous-arbre sag et sad */
int supprimer_arbre(t_arbre*);		/* supprimer le sous-arbre dont la racine est donnee en parametre  */
t_arbre ajout_gauche(t_arbre, int);
t_arbre ajout_droit(t_arbre, int);

/****************************************
 * primitives d'accès à la structure de l'arbre
 ****************************************/
t_arbre pere(t_arbre); /* renvoie le pere s'il existe, NULL sinon */
t_arbre sag(t_arbre); /* renvoie le sous-arbre gauche s'il existe, NULL sinon */
t_arbre sad(t_arbre); /* renvoie le sous arbre droit s'il existe, NULL sinon */

/****************************************
 * primitives de vérification
 ****************************************/
int arbre_vide(t_arbre);			/* renvoie vrai si arbre vide, faux sinon */
int est_racine(t_arbre); /*renvoie vrai si le noeud est une racine */
int est_feuille(t_arbre); /*renvoie vrai si le noeud est une feuille */

/****************************************
 * primitives de modification de la valeur de la racine
 ****************************************/
int modif_racine(t_arbre, int);	/* modifie la valeur de la racine de l'arbre */
int val_racine(t_arbre, int*); 		/* renvoie la valeur de la racine de l'arbre */

/****************************************
 * primitives d'affichage
 ****************************************/
int afficher_arbre(t_arbre, t_type_parcours);
int afficher_arbre_prefixe(t_arbre, int);
int afficher_arbre_infixe(t_arbre, int );
int afficher_arbre_postfixe(t_arbre, int);

void afficher_ancetres(t_arbre a, char end);


int parcours_prefixe(t_arbre, void (*)(int*));

void init_arbre(t_arbre *);

#endif

