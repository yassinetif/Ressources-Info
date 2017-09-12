/* Menu du TP 3 - Arbre binaire de recherche */
#include<stdio.h>
#include<stdlib.h>

#include "abr.h"
#include<string.h>

void pause() {
   int c;
   while((c = getchar()) != '\n' && c != EOF);getchar();
}

void effacer_ecran() {
    switch(OS) {
        case WINDOWS :  system("cls");
                        break;

        case LINUX :    system("clear");
                        break;

        default :       break;
    }
}

void afficher_types() {
    switch(TYPE_ELEM) {
        case INT :		printf("Int\n");
                        break;

        case CHAR :		printf("Char\n");
                        break;

        case EVENT :	printf("Event\n");
                        break;

        default :		printf("Erreur\n");
                        break;
    }
}

/* Fonction renvoyant un t_type correspondant */
t_type creer_t_type() {
	t_type val;
	switch(TYPE_ELEM) {
		case CHAR :		scanf("%[^\n]", val.chaine);
						break;

		case INT :		scanf("%i", &(val.nb));
						break;

		case EVENT : 	scanf("%i ", &(val.event.date));
						scanf("%[^\n]", val.event.intitule);
						break;

		default :		break;
	}

	return val;
}

/* Fonctions d'affichage */
void afficher(t_arbre abr)
{
	afficher_arbre(abr, INFIXE);
}

/* Fonctions de calcul de la hauteur */
int calcul_hauteur(t_arbre abr) {
	if(est_feuille(abr)) {
		return 1;
	} else if(arbre_vide(abr)) {
		return 0;
	} else {
		return 1 + max(calcul_hauteur(sag(abr)), calcul_hauteur(sad(abr)));
	}
}

void hauteur(t_arbre abr)
{
	int haut = 0;
	haut = calcul_hauteur(abr);

	printf("L'arbre a une hauteur de %i\n", haut);
}

/* Fonctions d'ajout */
int ajouter_valeur(t_arbre abr, t_elem elem) {
	if(!(cmp_elem(abr->val.val, elem.val))) { /* Valeur deja presente dans l'arbre */
		return 0;
	}

	if(arbre_vide(abr)) {
		return 1;
	} else {
		if(cmp_elem(abr->val.val, elem.val) < 0) { /* Ajout a droite */
			if(arbre_vide(sad(abr))) {
				ajout_droit(abr, elem);
			} else {
				ajouter_valeur(sad(abr), elem);
			}
		} else if(cmp_elem(abr->val.val, elem.val) > 0) { /* Ajout a gauche */
			if(arbre_vide(sag(abr))) {
				ajout_gauche(abr, elem);
			} else {
				ajouter_valeur(sag(abr), elem);
			}
		}

		return 1;
	}

	return 1;
}

void ajouter(t_arbre abr)
{
	t_type val;

	printf("Que voulez-vous ajouter dans l'arbre ? ");

	val = creer_t_type();

	t_elem elem = creer_elem(val);

	if(!ajouter_valeur(abr, elem)) {
		printf("La valeur etait deja presente dans l'arbre\n");
	}
}

/* Fonctions de recherche */
void rechercher(t_arbre abr)
{
	t_type val;

	printf("Quelle valeur souhaitez-vous rechercher ? ");

	val = creer_t_type();

	t_arbre a = rechercher_valeur(abr, val);

	if(a) {
		afficher_val(a, ' ');
		afficher_ancetres(a, ' ');
	} else {
		switch(TYPE_ELEM) {
			case CHAR :		printf("La valeur recherchee, %s, n'est pas dans l'arbre\n", val.chaine);
							break;

			case INT :		printf("La valeur recherchee, %i, n'est pas dans l'arbre\n", val.nb);
							break;

			case EVENT : 	printf("L'evenement recherche, %i : %s, n'est pas dans l'arbre\n", val.event.date, val.event.intitule);
							break;

			default :		break;
		}

	}
}

t_arbre rechercher_valeur(t_arbre abr, t_type val) {
	int comparaison;

	if(arbre_vide(abr)) {
		return 0;
	}

	comparaison = cmp_elem(abr->val.val, val);
	if(!comparaison) {
		return abr;
	} else if(comparaison > 0) {
		return rechercher_valeur(sag(abr), val);
	} else {
		return rechercher_valeur(sad(abr), val);
	}
}

/* Suppression d'un noeud */
void supprimer(t_arbre abr) {
    printf("Quelle valeur souhaitez-vous supprimer ? ");
    t_type el = creer_t_type();
    t_arbre abr_tmp;
    abr_tmp = rechercher_valeur(abr, el);
    if(abr_tmp) {
        supprimer_valeur(abr_tmp, el);
        printf("Supprime\n");
    } else {
        printf("%i : %s n'est pas dans l'arbre\n", el.event.date, el.event.intitule);
    }
}

void supprimer_valeur(t_arbre abr, t_type el) {
    if(!(cmp_elem(abr->val.val, el))) {
        supprimer_noeud(&abr);
    } else if(cmp_elem(abr->val.val, el) > 0) {
        supprimer_valeur(sag(abr), el);
    } else {
        supprimer_valeur(sad(abr), el);
    }
}
/* Fin du programme */
void quitter(t_arbre * arb) {
    supprimer_arbre(arb);
}

/* Programme principal */
int main(int argc, char * argv[])
{
	int choix;	/* Choix de l'utilisateur */

	if(argc > 1) {
        if(!strcmp(argv[1], "-t")) {
            afficher_types();
        }
	}


	t_arbre abr;
	init_arbre(&abr);

	do
	{	/* Affichage du menu */
		printf("----------");
		printf("\nMenu :\n");
		printf(" 1 - Afficher les valeurs par ordre croissant\n");
        printf(" 2 - Afficher la hauteur de l'arbre\n");
		printf(" 3 - Ajouter une valeur\n");
		printf(" 4 - Chercher une valeur et ses ancetres\n");
		printf(" 5 - Supprimer une valeur\n");
		printf(" 6 - Quitter\n");
		printf("----------\n");
		printf("Votre choix : ");
		scanf("%i",&choix);

		/* Traitement du choix de l'utilisateur */
		switch(choix)
		{	case 1:  afficher(abr); 	break;
			case 2:  hauteur(abr); 		break;
			case 3:  ajouter(abr); 		break;
			case 4:  rechercher(abr);	break;
			case 5:  supprimer(abr);    break;
			case 6:  quitter(&abr);		break;
			default: printf("Erreur: votre choix doit etre compris entre 1 et 6\n");
		}

		pause();
		effacer_ecran();
	}
	while(choix!=6);
	printf("Au revoir !\n");

	return 0;
}
