#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>
#include "messages.h"

int main(int argc, char * argv[]) {
	if(argc != 2) {
		printf("%s : <cle externe>\n", argv[0]);
		exit(-1);
	}
	
	key_t cleExterne = atoi(argv[1]);
	
	/* Création requête */
	requete_t requete;
	requete.corps.dossard = getpid();
	requete.type = PC_COURSE;
	
	/* Création réponse */
	reponse_t reponse;
	reponse.corps.etat = EN_COURSE;
	
	int idMsg = msgget(cleExterne, 0);
	
	messages_initialiser_attente();
	
	while(reponse.corps.etat == EN_COURSE) {
		msgsnd(idMsg, &requete, sizeof(corps_requete_t), 0);
	
		msgrcv(idMsg, &reponse, sizeof(corps_reponse_t), getpid(), 0);
	
		/* Affichage de l'etat d'un coureur */
		messages_afficher_etat(reponse.corps.etat) ;

		/* Affichage d'un message de requete d un coureur au PC Course */
		messages_afficher_requete(&requete);

		/* Affichage d'un message de reponse du PC Course */
		messages_afficher_reponse(&reponse);

		/* Affichage du parcours de la course */
		messages_afficher_parcours(&reponse);

		/* Attente entre 2 envois de message vers le PC Course */
		messages_attendre_tour();
	}
}