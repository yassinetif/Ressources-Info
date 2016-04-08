/* Menu du TP 3 - Arbre binaire de recherche */
#include<stdio.h>
#include<stdlib.h>


void afficher()
{
	printf("Ce traitement n'est pas encore disponible\n");
}

void hauteur()
{
	printf("Ce traitement n'est pas encore disponible\n");
}

void rechercher(void)
{	
	printf("Ce traitement n'est pas encore disponible\n");
}

void ajouter(void)
{
	printf("Ce traitement n'est pas encore disponible\n");
}


/* Programme principal */
int main(void)
{	
	int choix;	/* Choix de l'utilisateur */

	init_arbre();

	do
	{	/* Affichage du menu */
		printf("\nMenu :\n");
		printf(" 1 - Afficher les valeurs par ordre croissant\n");
        printf(" 2 - Afficher la hauteur de l'arbre\n");
		printf(" 3 - Ajouter une valeur\n");
		printf(" 4 - Chercher une valeur et ses ancêtres\n");
		printf(" 5 - Quitter\n");
		printf("Votre choix : ");
		scanf("%i",&choix);

		/* Traitement du choix de l'utilisateur */
		switch(choix)
		{	case 1:  afficher(); break;
			case 2:  hauteur(); break;
			case 3:  ajouter(); break;
			case 4:  rechercher(); break;
			case 5:  break;
			default: printf("Erreur: votre choix doit être compris entre 1 et 5\n");
		}
	}
	while(choix!=5);
	printf("Au revoir !\n");
}
