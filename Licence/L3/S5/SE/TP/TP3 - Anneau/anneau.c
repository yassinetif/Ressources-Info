#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char * argv[]) {

	// Gestion des arguments
	if(argc != 3) {
		printf("Utilisation : anneau nb_processus commande\n");
		
		exit(-1);
	}
	
	int nbProc = atoi(argv[1]);
	
	if(nbProc <= 1) {
		printf("Le nombre de processus doit etre superieur ou egal a deux\n");
		
		exit(-1);
	}
	
	// Creation et redirection des entrees et sorties du pere
	int tube[2];
	pipe(tube);
	
	close(0);
	dup(tube[0]);
	close(tube[0]);
	close(1);
	dup(tube[1]);
	close(tube[1]);
	
	int nbFils;
	int pidFils;
	
	for(nbFils = 1; nbFils < nbProc; nbFils++) {
		// Creation d'un nouveau pipe pour chaque fils
		pipe(tube);
		
		switch(pidFils = fork()) {
			case -1:	// Erreur
				printf("Erreur de fork\n");
				exit(-1);
		
			case 0:		// Fils
				close(0);
				dup(tube[0]);
				close(tube[0]);
				break;
		
			default:		// Pere
				close(1);
				dup(tube[1]);
				close(tube[1]);
		}
		
		// Sinon chaque processus jeton est cree deux fois
		if(pidFils) {
			break;
		}
	}
	
	execl(argv[2], argv[2], NULL);
	
	printf("Erreur lors de l'execution du processus %s\n", argv[2]);
	return -1;
}