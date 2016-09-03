include Makefile.compilation

#
# Objets
#

fich_obj_methode_argc_argv=methode_argc_argv.o 
fich_obj_methode_pile=methode_pile.o 
fich_obj_methode_pile_heterogene=methode_pile_heterogene.o 
fich_obj_methode_printf=methode_printf.o 


#
# Tests (executables+objets)
#

BIN = methode_argc_argv methode_pile methode_pile_heterogene methode_printf 

methode_argc_argv : $(fich_obj_methode_argc_argv) 
	$(CCLNK) $(CFLAGS) $(LIBMATH) $(fich_obj_methode_argc_argv) -o methode_argc_argv 

methode_argc_argv.o : methode_argc_argv.c 
	$(CCOBJ) $(CFLAGS) $(LIBMATH) methode_argc_argv.c -o methode_argc_argv.o -I./ 

methode_pile : $(fich_obj_methode_pile) 
	$(CCLNK) $(CFLAGS) $(LIBMATH) $(fich_obj_methode_pile) -o methode_pile 

methode_pile.o : methode_pile.c 
	$(CCOBJ) $(CFLAGS) $(LIBMATH) methode_pile.c -o methode_pile.o -I./ 

methode_pile_heterogene : $(fich_obj_methode_pile_heterogene) 
	$(CCLNK) $(CFLAGS) $(LIBMATH) $(fich_obj_methode_pile_heterogene) -o methode_pile_heterogene 

methode_pile_heterogene.o : methode_pile_heterogene.c 
	$(CCOBJ) $(CFLAGS) $(LIBMATH) methode_pile_heterogene.c -o methode_pile_heterogene.o -I./ 

methode_printf : $(fich_obj_methode_printf) 
	$(CCLNK) $(CFLAGS) $(LIBMATH) $(fich_obj_methode_printf) -o methode_printf 

methode_printf.o : methode_printf.c 
	$(CCOBJ) $(CFLAGS) $(LIBMATH) methode_printf.c -o methode_printf.o -I./ 



#
# Modules
#

OBJ=

#
# Headers 
#

#
#
#

all : $(BIN) $(OBJ)

clean :
	- rm  *.o

tests :
	./methode_argc_argv
	./methode_pile
	./methode_pile_heterogene
	./methode_printf

