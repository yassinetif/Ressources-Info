/* Mise en oeuvre par pointeurs d'un arbre binaire */

#include "abr.h"
#include<string.h>

t_elem creer_elem(t_type val){
	switch(TYPE_ELEM) {
		case CHAR : 	return creer_elem_char(val.chaine);
		case INT :		return creer_elem_int(val.nb);
		case EVENT :	return creer_elem_event(val.event);
		default : 		break;
	}
}

t_elem creer_elem_char(char * val) {
	t_elem elem;
	strcpy(elem.val.chaine, val);
	return elem;
}

t_elem creer_elem_int(int val) {
	t_elem elem;
	elem.val.nb = val;
	return elem;
}

t_elem creer_elem_event(t_event event) {
	t_elem elem;
	elem.val.event.date = event.date;
	strcpy(elem.val.event.intitule, event.intitule);

	return elem;
}

/****************************************
 * primitives de modification de la structure de l'arbre
 ****************************************/
/* renvoie un arbre dont la racine vaut val, le pere vaut p, et les sous-arbres sag et sad */
t_arbre creer_arbre(t_elem val, t_arbre sag, t_arbre sad, t_arbre pere){
	t_arbre a = malloc(sizeof(t_noeud));
	a->val = val;
	a->pere = pere;
	a->sag = sag;
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

/*  Suppression d'un noeud dans le cas d'un ARB */
int supprimer_feuille(t_arbre * arb) {
    if(arbre_vide(*arb))
		return 0;

    t_arbre p = pere(*arb);
	if(p){
		if(*arb == sag(p)){ p->sag = NULL; }
		else { //if (*pa == sad(p)){
			p->sad = NULL; }
	}

	free(*arb);
	*arb = NULL;
	return 1;
}

t_arbre valeur_inferieure(t_arbre arb) {
    if(sad(arb)) {
        return valeur_inferieure(sad(arb));
    }

    return arb;
}

t_arbre valeur_superieure(t_arbre arb) {
    if(sag(arb)) {
        return valeur_superieure(sag(arb));
    }

    return arb;
}

int supprimer_noeud(t_arbre * arb) {
    if(arbre_vide(*arb)) {
        return 0;
    }

    if(est_feuille(*arb)) {
        return supprimer_feuille(arb);
    }

    t_arbre arb_tmp;

    /* Trouver la valeur immediatement inferieure ... */
    if(sag(*arb)) {
        arb_tmp = valeur_inferieure(sag(*arb));
        (*arb)->val = arb_tmp->val;

        return supprimer_noeud(&arb_tmp);
    }

    /* ... Ou supérieure */
    if(sad(*arb)) {
        arb_tmp = valeur_superieure(sad(*arb));
        (*arb)->val = arb_tmp->val;

        return supprimer_noeud(&arb_tmp);
    }

    return 1;
}

t_arbre ajout_gauche(t_arbre a, t_elem v){
	if(arbre_vide(a))
		return NULL;
	a->sag = creer_arbre(v, NULL, NULL, a);
	return a->sag;
}

t_arbre ajout_droit(t_arbre a, t_elem v){

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
int val_racine(t_arbre a, t_elem* v){
	if(arbre_vide(a))
		return 0;
	*v = a->val;
	return 1;
}

/* modifie la valeur de la racine de l'arbre
 * renvoie vrai si modif effectueee, faux sinon */
int modif_racine(t_arbre a, t_elem val){
	if(a == NULL)
		return 0;
	if(cmp_elem(val.val, (sag(a))->val.val) <= 0 || cmp_elem(val.val, (sag(a))->val.val) >= 0) /* On verifie que la valeur peut etre ajoutee sans casser la structure de l'arbre */
		return 0;

	a->val = val;
	return 1;
}


/****************************************
 * primitives d'affichage
 ****************************************/

void afficher_val(t_arbre a, char end){
	switch(TYPE_ELEM) {
		case CHAR : 	printf("%s%c", a->val.val.chaine, end);
						break;
		case INT :		printf("%i%c", a->val.val.nb, end);
						break;
		case EVENT :	printf("%i : %s%c", a->val.val.event.date, a->val.val.event.intitule, end);
		default : 		break;
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

int parcours_prefixe(t_arbre a, void (*fonc)(t_elem*)){
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
	int i;
	if(arbre_vide(a)){
		printf("L'arbre est vide\n");
	} else{
		for(i=0; i<prof; i++) printf(" ");
		afficher_val(a, '\n');
		if(sag(a))
			afficher_arbre_prefixe(sag(a), prof+1);
		if(sad(a))
			afficher_arbre_prefixe(sad(a), prof+1);
	}
	return 0;
}

int afficher_arbre_infixe(t_arbre a, int prof){
	int i;
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
	int i;
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

/* Initialisation de l'arbre */
void init_arbre(t_arbre * abr) {
	t_elem el;
	t_type val;

	switch(TYPE_ELEM) {
		case INT :		val.nb = INITIALISATION_INT;
						break;

		case CHAR :		strcpy(val.chaine, INITIALISATION_CHAR);
						break;

		case EVENT :	val.event.date = INITIALISATION_EVENT_DATE;
						strcpy(val.event.intitule, INITIALISATION_EVENT_INTITULE);

		default :		break;
	}

	el = creer_elem(val);

	*abr = creer_arbre(el, NULL, NULL, NULL);
}

int max(int elem1, int elem2) {
	if(elem1 - elem2 < 0) {
		return elem2;
	} else {
		return elem1;
	}
}

/* Fonctions de comparaison */
int cmp_elem(t_type elem1, t_type elem2) {
	switch(TYPE_ELEM) {
		case CHAR : 	return cmp_elem_char(elem1.chaine, elem2.chaine);
		case INT :		return cmp_elem_int(&(elem1.nb), &(elem2.nb));
		case EVENT :	return cmp_elem_event(&(elem1.event), &(elem2.event));
		default : break;
	}
}

int cmp_elem_char(char * elem1, char * elem2) {
	return strcmp(elem1, elem2);
}

int cmp_elem_int(int * elem1, int * elem2) {
	return *elem1 - *elem2;
}

int cmp_elem_event(t_event * elem1, t_event * elem2) {
	int date_diff = cmp_elem_int(&(elem1->date), &(elem2->date));
	if(date_diff) {
		return date_diff;
	} else {
		return cmp_elem_char(elem1->intitule, elem2->intitule);
	}
}
