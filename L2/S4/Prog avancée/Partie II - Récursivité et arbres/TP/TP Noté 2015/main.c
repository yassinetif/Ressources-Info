#include <stdio.h>
#include <stdlib.h>

#include "arbre.h"

void supprimer_noeud(t_arbre * abr) {
    supprimer_arbre(abr);
}

void afficher_abr_actuel(t_arbre abr) {
    afficher_arbre(abr, PREFIXE);
}

void creer_abr_fibo(t_arbre * abr, int ordre) {
    // Suppression de l'arbre déjà existant
    while(!est_racine(*abr)) {
        *abr = pere(*abr);
    }

    supprimer_noeud(abr);

    int i = 0;
    t_arbre tmp_fg = malloc(sizeof(t_noeud));
    t_arbre tmp_racine = malloc(sizeof(t_noeud));
    int a1;
    int a2;

    init_arbre(abr);

    for(i = 3; i < ordre; i++) {
        tmp_fg = sad(*abr);

        val_racine(*abr, &a1);
        val_racine(tmp_fg, &a2);
        tmp_racine = creer_arbre(a1 + a2, tmp_fg, *abr, NULL);

        *abr = tmp_racine;
    }
}

void creer_abr(t_arbre * abr) {
    int ordre;
    printf("De quel ordre doit être la suite ? ");
    scanf("%i", &ordre);
    creer_abr_fibo(abr, ordre);
}

void augmenter_ordre(t_arbre * abr) {
    if(!arbre_vide(*abr)) {
        t_arbre nv_racine = malloc(sizeof(t_noeud));
        t_arbre nv_racine_fg = malloc(sizeof(t_noeud));

        int nb_racine;
        int nb_fg;

        nv_racine_fg = sad(*abr);

        val_racine(*abr, &nb_racine);
        val_racine(nv_racine_fg, &nb_fg);
        nv_racine = creer_arbre(nb_racine + nb_fg, nv_racine_fg, *abr, NULL);

        *abr = nv_racine;
    }
}

void diminuer_ordre(t_arbre * abr) {
    //Suppression du fils gauche
    free(&((*abr)->sag));

    t_arbre * tmp_abr = &((*abr)->sad);

    free(abr);

    *abr = *tmp_abr;
}

void quitter(t_arbre * abr) {
    supprimer_noeud(abr);
    printf("Au revoir !");
}

int main() {
    int choix = 0;
    t_arbre abr = NULL;

    init_arbre(&abr);
    while(choix != 5) {
        do {
            printf("----------\n");
            printf("Menu :\n");
            printf(" 1. Afficher l'arbre (parcours prefixe)\n");
            printf(" 2. Creer un nouvel arbre\n");
            printf(" 3. Augmenter l'ordre de la suite de Fibonacci\n");
            printf(" 4. Diminuer l'ordre de la suite de Fibonacci\n");
            printf(" 5. Quitter\n");
            printf("----------\n");

            scanf("%i", &choix);
        } while(choix < 1 || choix > 5);

        switch(choix) {
            case 1 :    afficher_abr_actuel(abr);
                        break;

            case 2 :    printf("\nCREATION ARBRE\n");
                        creer_abr(&abr);
                        break;

            case 3 :    printf("\nAUGMENTATION ORDRE\n");
                        augmenter_ordre(&abr);
                        break;

            case 4 :    printf("\DIMINUTION ORDRE\n");
                        diminuer_ordre(&abr);
                        break;

            case 5 :    quitter(&abr);
                        break;

            default :   printf("Erreur lors de l'execution du menu");
                        break;
        }
    }

    return 0;
}
