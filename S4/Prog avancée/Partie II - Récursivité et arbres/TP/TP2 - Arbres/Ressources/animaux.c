

//#include "ab.h"
#include "arbre.h"
#include <string.h>

#define TAILLE 500

static int id = 0;

void affiche(t_arbre r){
	// VOTRE CODE ICI
}


/*
 Fonction qui cherche et renvoie le noeud d'id id à partir de la racine r
 Renvoie NULL si non trouve
 */
t_arbre cherche(t_arbre r, int id)
{
	t_arbre res = NULL;
	t_elem el;
    if(!arbre_vide(r)) {
		val_racine(r, &el);
        if(el.id == id) {
            res = r;
        }
        else if(est_feuille(r)) {
            res = NULL;
        }
        else {
            if(sag(r)){
                res = cherche(sag(r), id);
            }
            if(!res && sad(r)){ // si on n'a pas trouvé, on cherche à droite
                res = cherche(sad(r), id);
            }
        }
    }
	return res;
}


/*
Fonction qui se positionne sur le noeud d'id = pere et ajoute le fils gauche d'id id et de valeur q
*/
t_arbre ajout(t_arbre r, int pere, t_elem el)
{
	t_arbre res = cherche(r, pere);
	fprintf(stderr, "ajout: pere=%d id=%d, ch='%s'\n", pere, el.id, el.val);
	if(res){
		if(!sag(res))
			ajout_gauche(res, el);
		else if(!sad(res))
			ajout_droit(res, el);
		else {
			fprintf(stderr, "Le noeud %d a déjà un fg et un fd, problème dans le fichier !!\n", pere);
			res=0;
		}
	}
	else {
		fprintf(stderr, "Impossible d'ajouter %d, %s car le noeud d'id %d est introuvable !\n",el.id, el.val, pere);
	}
	return res;
}

/*
 Fonction qui charge le fichier contenant l'arborescence de la classification
 */
t_arbre loadClassification(char *fn)
{
    t_arbre r = NULL;
	t_elem el;
	char line[TAILLE], q[TAILLE];
	int _id, pere;
	FILE* fd = fopen(fn, "r");
	if (fd==NULL){ 
		perror ("Error opening file");
		return 0;
	}

	while(!feof(fd)){
		if(fgets(line, TAILLE, fd) != NULL){
			if(sscanf(line, "%d %d %[^\n]", &_id, &pere, q) == 3){
				el = creer_elem(_id, q);
				if( arbre_vide(r) ){
					r = creer_arbre(el, NULL, NULL, NULL);
				} else if(!ajout(r, pere, el)) {
					exit(0);
				}
				// mise à jour de la valeur de id (var globale)
				if(_id > id) id = _id;
			}
		}
	}
	fclose(fd);
	return r;
}



/*
 Fonction principale
 */
int main(int argc, char **argv)
{

	if(argc < 2)
	{
		printf("Usage : %s <fic>\n", argv[0]);
		printf("<fic> doit contenir la classification sous forme d'arbre\n");
		exit(EXIT_SUCCESS);
	}
	char *fn = argv[1];

	t_arbre classif = loadClassification(fn);
	fprintf(stderr, "Classification chargée ...\n");
	affiche(classif); //affichage de la classification


	// VOTRE CODE ICI


	return 0;
}

