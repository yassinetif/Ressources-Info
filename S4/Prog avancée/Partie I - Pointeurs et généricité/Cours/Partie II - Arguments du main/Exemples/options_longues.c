#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <getopt.h>


/* ------------------------------ */
/* ----- long options array ----- */
/* ------------------------------ */

static struct option longopts[] =
{
  {"verbose", required_argument, NULL, (int)'v'},
  {"help", no_argument, NULL, (int)'h'},
  {"option-a", no_argument, NULL, (int)'a'},
  {"option-b", no_argument, NULL, (int)'b'},
  {"option-c", required_argument, NULL, (int)'c'},
  {0, 0, 0, 0}
};


/*
 * Usage 
 */
static 
void usage( char * nomprog )
{
      fprintf( stdout , "Programme de test des options requerant 3 arguments (quelconques) \n");
      fprintf( stdout , "usage : %s [options]  argument1 argument2 argument3" , nomprog );
      fprintf( stdout , "Options:\n"); 
      fprintf( stdout , "  -v, --verbose <niveau>        niveau de la trace de l'execution\n");
      fprintf( stdout , "                 0              pas de trace\n");
      fprintf( stdout , "                 1              trace des actions principales\n");
      fprintf( stdout , "                 2              trace detaillee\n");
      fprintf( stdout , "  -h, --help                    affiche cette aide\n");
      fprintf( stdout , "  -a, --option-a                positionne le flag 'a'\n");
      fprintf( stdout , "  -b, --option-b                positionne le flag 'b'\n");
      fprintf( stdout , "  -c, --option-c <valeur>       affecte l'option 'c'\n");
}

int
main( int argc , char * argv[] ) 
{
  int opt;
  char nomprog[512] ; 
  int i ;
  int verbose = 0 ;

  int aflag = 0;
  int bflag = 0;
  char *cvalue = NULL;

  /* Section options */
  strcpy( nomprog , argv[0] ) ;
  while ((opt = getopt_long(argc, argv, "v:habc:", longopts, NULL)) != -1 )
    {
      switch(opt)
	{
	case 'v': /* --verbose */
	  verbose = atoi(optarg) ;
	  switch(verbose) 
	    {
	    case 0 : 
	      break ;
	    case 1 : printf("Trace niveau 1 : principales actions\n");
	      break ;
	    case 2 : printf("Trace niveau 2 : ttrace detaillee\n");
	      break ;
	    default : printf("%s : niveau de trace invalide [%d]\n", nomprog , verbose );
	      usage(nomprog) ;
	      exit(0);
	    }
	  break;

	case 'h': /* --help */
	  usage(nomprog) ;
	  exit(0);
	  break;

	case 'a' :
	  aflag = 1;
	  break;

	case 'b' :
	  bflag = 1;
	  break;

	case 'c':
	  cvalue = malloc( strlen(optarg)+1 ) ; 
	  strcpy( cvalue , optarg ) ; 
	  break;

	case '?':
	  usage(nomprog) ;
	  exit(0);
	  break;

	default:
	  usage(nomprog) ;
	  exit(0);
	  break;
	}
    }
  argc -= optind ;
  argv += optind ;

  /* argc == nb de parametres sans le nom de la commande */
  /* argv[0] --> 1er parametre */ 


  /* Section parametre */
  if( argc != 3 )
    {
      fprintf( stderr , "Erreur sur le nombre de parametres: 3 attendus au lieu de %d\n" , argc );
      usage(nomprog) ; 
      exit(0) ; 
    }

  for (i = 0; i < argc; i++)
    printf ("argv[%d] = %s\n", i , argv[i]);

  printf("\nOptions :\n" );
  printf("\t- verbose activee avec le niveau %d \n" , verbose );
  printf("\t- aflag  :  %d \n" , aflag  );
  printf("\t- bflag  :  %d \n" , bflag  );
  printf("\t- cvalue :  %s \n" , cvalue );
  
  return(0) ;
}
