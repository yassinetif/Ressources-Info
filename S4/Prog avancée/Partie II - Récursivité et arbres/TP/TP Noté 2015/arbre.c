/* Mise en oeuvre par pointeurs d'un arbre binaire */

#include "arbre.h"

/****************************************
 * primitives de modification de la structure de l'arbre
 ****************************************/
/* renvoie un arbre dont la racine vaut val, le pere vaut p, et les sous-arbres sag et sad */
t_arbre creer_arbre(int val, t_arbre sag, t_arbre sad, t_arbre pere){
	t_arbre a = malloc(sizeof(t_noeud));
	a->val = val;
	a->pere = pere;
	a-> sag = sag;
	a->sad = sad;
	return a;
}

/* supprimer le sous-arbre  pointé par pa
 * renvoie vrai si opération effectuée, faux sinon */
int supprimer_arbre(t_arbre* pa){
	if(arbre_vide(*pa))
		return 0;
	if(sag(*pa)){
		t_arbre sa = sag(*pa);
		supprimer_arbre(&sa);
	}
	if(sad(*pa)){
		t_arbre sa = sad(*pa);
		supprimer_arbre(&sa);
	}


	/* mise à jour du pointeur du pere s'il existe */
	t_arbre p = pere(*pa);
	if(p){
		if(*pa == sag(p)){ p->sag = NULL; }
		else { //if (*pa == sad(p)){
			p->sad = NULL; }
	}

	free(*pa);
	*pa = NULL;
	return 1;
}

t_arbre ajout_gauche(t_arbre a, int v){
	if(arbre_vide(a))
		return NULL;
	a->sag = creer_arbre(v, NULL, NULL, a);
	return a->sag;
}

t_arbre ajout_droit(t_arbre a, int v){

	if(arbre_vide(a))
		return NULL;
	a->sad = creer_arbre(v, NULL, NULL, a);
	return a->sad;
}

/****************************************
 * primitives d'accès à la structure de l'arbre
 ****************************************/
/* renvoie le pere s'il existe, NULL sinon */
t_arbre pere(t_arbre a){
	if(arbre_vide(a))
		return NULL;
	return a->pere;
}

/* renvoie le sous-arbre gauche s'il existe, NULL sinon */
t_arbre sag(t_arbre a){
	if(arbre_vide(a))
		return NULL;
	return a->sag;
}

/* renvoie le sous arbre droit s'il existe, NULL sinon */
t_arbre sad(t_arbre a){
	if(arbre_vide(a))
		return NULL;
	return a->sad;
}

/****************************************
 * primitives de vérification
 ****************************************/
/* renvoie vrai si arbre vide, faux sinon */
int arbre_vide(t_arbre a){
	return a == NULL;
}
/*renvoie vrai si l'arbre est une racine
 * c-a-d s'il n'a pas de pere */
int est_racine(t_arbre a){
	if(arbre_vide(a))
		return 0;
	else if(arbre_vide(pere(a)))
		return 1;
	return 0;
}

/*renvoie vrai si le noeud est une feuille */
int est_feuille(t_arbre a){
	if(arbre_vide(a))
		return 0;
	else if(arbre_vide(sag(a)) && arbre_vide(sad(a)))
		return 1;
	return 0;
}

/****************************************
 * primitives de modification de la valeur de la racine
 ****************************************/
/* met la valeur de la racine de l'arbre dans v
 * renvoie vrai si affectation, faux sinon */
int val_racine(t_arbre a, int* v){
	if(arbre_vide(a))
		return 0;
	*v = a->val;
	return 1;
}

/* modifie la valeur de la racine de l'arbre
 * renvoie vrai si modif effectuée, faux sinon */
int modif_val(t_arbre a, int val){
	if(a == NULL)
		return 0;
	a->val = val;
	return 1;
}


/****************************************
 * primitives d'affichage
 ****************************************/

void afficher_val(t_arbre a, char end){
	int val;
	if(val_racine(a, &val)){
		printf("%d%c", val, end);
	}
}


int afficher_arbre(t_arbre a, t_type_parcours type){
	int res = 0;
	if(arbre_vide(a)){
		printf("L'arbre est vide\n");
	}
	else {
		if(type == PREFIXE)
			afficher_arbre_prefixe(a, 0);
		else if(type == INFIXE)
			afficher_arbre_infixe(a, 0);
		else if(type == POSTFIXE)
			afficher_arbre_postfixe(a, 0);
		else {
			printf("Mauvais type de parcours d'arbre\n");
			res = 1;
		}
	}
	printf("\n");
	return res;
}

int parcours_prefixe(t_arbre a, void (*fonc)(int*)){
	if(arbre_vide(a)){
		printf("L'arbre est vide\n");
	} else{
		fonc(&(a->val));
		if(sag(a))
			parcours_prefixe(sag(a), fonc);
		if(sad(a))
			parcours_prefixe(sad(a), fonc);
	}
	return 0;
}

int afficher_arbre_prefixe(t_arbre a, int prof){
	int val, i;
	if(arbre_vide(a)){
		printf("L'arbre est vide\n");
	} else{
		for(i=0; i<prof; i++) printf("  ");
		afficher_val(a, '\n');
		if(sag(a))
			afficher_arbre_prefixe(sag(a), prof+1);
		if(sad(a))
			afficher_arbre_prefixe(sad(a), prof+1);
	}
	return 0;
}

int afficher_arbre_infixe(t_arbre a, int prof){
	int val, i;
	if(arbre_vide(a)){
		printf("L'arbre est vide\n");
	} else{
		if(sag(a))
			afficher_arbre_infixe(sag(a), prof+1);
		for(i=0; i<prof; i++) printf(" ");
		afficher_val(a, '\n');
		if(sad(a))
			afficher_arbre_infixe(sad(a), prof+1);
	}
	return 0;
}

int afficher_arbre_postfixe(t_arbre a, int prof){
	int val, i;
	if(arbre_vide(a)){
		printf("L'arbre est vide\n");
	} else{
		if(sag(a))
			afficher_arbre_postfixe(sag(a), prof+1);
		if(sad(a))
			afficher_arbre_postfixe(sad(a), prof+1);
		for(i=0; i<prof; i++) printf(" ");
		afficher_val(a, '\n');
	}
	return 0;
}


void afficher_ancetres(t_arbre a, char end){
	a = pere(a);
	while(!arbre_vide(a)){
		afficher_val(a, ' ');
		a = pere(a);
	}
	printf("%c", end);
}

/*****
 * Primitives d'initialisation
 *****/

void init_arbre(t_arbre * abr) {
    *abr = creer_arbre(2, NULL, NULL, NULL);

    t_arbre fib_init = creer_arbre(1, NULL, NULL, *abr);

    (*abr)->sag = fib_init;
    (*abr)->sad = fib_init;
}
