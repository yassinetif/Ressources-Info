#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
     
int
main (int argc, char **argv)
{
  int aflag = 0;
  int bflag = 0;
  char *cvalue = NULL;

  int i ;
  int opt;
     
  opterr = 0;
     
  while ((opt = getopt (argc, argv, "abc:")) != -1)
    switch (opt)
      {
      case 'a':
	aflag = 1;
	break;
      case 'b':
	bflag = 1;
	break;
      case 'c':
	cvalue = optarg;
	break;
      case '?':
	if (optopt == 'c')
	  fprintf (stderr, "Option -%c : il manque un argument.\n", optopt);
	else 
	  if (isprint (optopt))
	    fprintf (stderr, "Option inconnue `-%c'.\n", optopt);
	  else
	    fprintf (stderr, "Option inconnue et non affichable `\\x%x'.\n",
		     optopt);
	return 1;
      default:
	abort ();
      }
     
  printf ("aflag = %d, bflag = %d, cvalue = %s\n",
	  aflag, bflag, cvalue );
     
  for (i = optind; i < argc; i++)
    printf ("argv[%d] = %s\n", i , argv[i]);
  return 0;
}
