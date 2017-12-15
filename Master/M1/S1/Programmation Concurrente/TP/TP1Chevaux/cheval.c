/*
BIARDEAU
Tristan
M1
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#include <commun.h>
#include <liste.h>
#include <piste.h>


static struct sembuf Op_P = {0,-1,0};
static struct sembuf Op_V = {0,1,0};

static
void P(int Sem_id){
  semop(Sem_id, &Op_P, 1);
}

static
void V(int Sem_id){
  semop(Sem_id, &Op_V, 1);
}


/*pose de sémaphore sur une cellule particulière*/
static
void P2(int Sem_id, int i) { 
  struct sembuf Op_P2 = {i,-1,0}; 
  semop(Sem_id,&Op_P2,1); 
} 

/*levée de sémaphore sur une cellule particulière*/
static
void V2(int Sem_id, int i) { 
  struct sembuf Op_V2 = {i,1,0}; 
  semop(Sem_id,&Op_V2,1); 
}

int 
main( int nb_arg , char * tab_arg[] )
{     
  /* cle_piste -> shm_cle/sem_cle */
  int cle_piste ;
  piste_t * piste = NULL ;

  /* cle_liste -> shm_cle/sem_cle */
  int cle_liste ;
  liste_t * liste = NULL ;

  char marque ;

  booleen_t fini = FAUX ;
  piste_id_t deplacement = 0 ;
  piste_id_t depart = 0 ;
  piste_id_t arrivee = 0 ;

  int index = 0;

  cell_t cell_cheval ;


  elem_t elem_cheval ;




  /*Recuperation des arguments*/

  if( nb_arg != 4 )
    {
      fprintf( stderr, "usage : %s <cle de piste> <cle de liste> <marque>\n" , tab_arg[0] );
      exit(-1);
    }
  
  if( sscanf( tab_arg[1] , "%d" , &cle_piste) != 1 )
    {
      fprintf( stderr, "%s : erreur , mauvaise cle de piste (%s)\n" , 
	       tab_arg[0]  , tab_arg[1] );
      exit(-2);
    }


  if( sscanf( tab_arg[2] , "%d" , &cle_liste) != 1 )
    {
      fprintf( stderr, "%s : erreur , mauvaise cle de liste (%s)\n" , 
	       tab_arg[0]  , tab_arg[2] );
      exit(-2);
    }

  if( sscanf( tab_arg[3] , "%c" , &marque) != 1 )
    {
      fprintf( stderr, "%s : erreur , mauvaise marque de cheval (%s)\n" , 
	       tab_arg[0]  , tab_arg[3] );
      exit(-2);
    }
     

  /*Récuperation des id de memoires partagées et sémaphore de la liste / piste*/
  int shmid_piste = shmget(cle_piste, PISTE_LONGUEUR*sizeof(cell_t), IPC_CREAT | 0666);
  piste = shmat(shmid_piste,0,0);
  int semid_piste = semget(cle_piste,PISTE_LONGUEUR,0666);

  int shmid_liste = shmget(cle_liste, LISTE_MAX*sizeof(elem_t), IPC_CREAT | 0666);
  liste = shmat(shmid_liste,0,0);
  int semid_liste = semget(cle_liste,1,0666);
  

  /* Init de l'attente */
  commun_initialiser_attentes() ;


  /* Init de la cellule du cheval pour faire la course */
  cell_pid_affecter( &cell_cheval  , getpid());
  cell_marque_affecter( &cell_cheval , marque );

  /* Init de l'element du cheval pour l'enregistrement */
  elem_cell_affecter(&elem_cheval , cell_cheval ) ;
  elem_etat_affecter(&elem_cheval , EN_COURSE ) ;

  /* 
   * Enregistrement du cheval dans la liste
   */

  if(elem_sem_creer(&elem_cheval) == -1) {
    perror("Pb création sémaphore du cheval");
    exit(-1);
  }


  /*Avant d'ajouter un cheval dans la liste, on prend le sémaphore pour pouvoir y écrire sans problème*/
  P(semid_liste);
  if((liste_elem_ajouter(liste, elem_cheval)) != 0){
    perror("Pb ajout cheval à la liste");
    exit(-2);
  }
  V(semid_liste);


  /*On récupère l'index d'où est placé le cheval dans la liste*/
  if(!liste_elem_rechercher(&index, liste, elem_cheval)) {
    perror("Le cheval n'a pas été ajouté à la liste");
    exit(-2);
  }


  while( ! fini )
    {
      /*On attend son tour*/
      commun_attendre_tour();

      P(semid_liste);
       /* 
       * On vérifie si notre cheval n'a pas été décanillé
       */
      if(elem_decanille(elem_cheval)){

        fini = VRAI;

        /*Modification de la piste, on doit s'assurer qu'on est le seul à la modifier*/
        P(semid_piste);
        piste_cell_effacer(piste, index);
        V(semid_piste);

        if(!liste_elem_rechercher(&index, liste, elem_cheval)){
          perror("Notre propre cheval n'a pas été trouvé dans la liste");
          exit(-2);
        }

        if (liste_elem_supprimer(liste, index) != 0) {
          perror("Erreur suppression cheval");
          exit(-2);
        }

        /*Les opérations sur la liste sont finies, on peut la liberer*/
        V(semid_liste);

        if (elem_sem_deverrouiller(&elem_cheval) == -1) {
          perror("Pb elem_cheval supp sem");
          exit(-2);
        }

      /* Destruction du sémaphore du cheval */
      elem_sem_detruire(&elem_cheval);
      exit(0);

      }else{
        V(semid_liste);
      }


      /*
       * Avancee sur la piste
       */

      /* Coup de de */
      deplacement = commun_coup_de_de() ;

#ifdef _DEBUG_
      printf(" Lancement du De --> %d\n", deplacement );
#endif

      arrivee = depart+deplacement ;

      if( arrivee > PISTE_LONGUEUR-1 )
	{
	  arrivee = PISTE_LONGUEUR-1 ;
	  fini = VRAI ;
	}

      if( depart != arrivee )
	{

	  /* 
	   * Si case d'arrivee occupee alors on decanille le cheval existant 
	   */

    elem_sem_verrouiller(&elem_cheval);

	  if(piste_cell_occupee(piste,arrivee)){ 
      cell_t cellChevalADeca;
      elem_t chevalADeca;
      int indexCheval;
      
      if(piste_cell_lire(piste,arrivee,&cellChevalADeca) != 1) {
        perror("propbleme lecture piste");
        exit(-2);
      } 

      elem_cell_affecter(&chevalADeca, cellChevalADeca); //decanillage de l'adversaire 

      /*On veut pas que la liste soit changée quand on fait des recherches*/
      P(semid_liste); 

         liste_elem_rechercher(&indexCheval,liste,chevalADeca); 

         elem_sem_verrouiller(&chevalADeca); 
            if(liste_elem_decaniller(liste,indexCheval) == -1) {
              perror("erreur quand on veut décaniller le cheval");
              exit(-2);
            } 
         elem_sem_deverrouiller(&chevalADeca);

      V(semid_liste);
    }

    
     //on bloque la case de depart et d'arrivee du cheval pour ne pas être dérangé sur les cases sur lesquels on fait du traitement 
     P2(semid_piste, arrivee);
     P2(semid_piste, depart);

       /*On effece notre cheval de la cellule de depart*/
       piste_cell_effacer(piste,depart);
       commun_attendre_fin_saut(); 
       elem_sem_deverrouiller(&elem_cheval); // on dévérouille notre cheval une fois qu'on a sauté

       /*On place notre cheval sur la cellule d'arrivee*/
       piste_cell_affecter(piste,arrivee,cell_cheval); 

       /*On débloque la case depart*/
       V2(semid_piste, depart);
       /*On débloque la case d'arrivee*/
    V2(semid_piste, arrivee);

#ifdef _DEBUG_
	  printf("Deplacement du cheval \"%c\" de %d a %d\n",
		 marque, depart, arrivee );
#endif

	  
	} 
      /* Affichage de la piste  */
      piste_afficher_lig( piste );
     
      depart = arrivee ;
    }

  printf( "Le cheval \"%c\" A FRANCHIT LA LIGNE D ARRIVEE\n" , marque );

 
     
  /* 
   * Suppression du cheval de la liste 
   */

  P(semid_piste);
    piste_cell_effacer(piste, depart);
  V(semid_piste);

  P(semid_liste);
    if(liste_elem_supprimer(liste, index) != 0) {
      perror("Probleme supprimer element apres victoire");
      exit(-2);
    }
  V(semid_liste);


  exit(0);
}