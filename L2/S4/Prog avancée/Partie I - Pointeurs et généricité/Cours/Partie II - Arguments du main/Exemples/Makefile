include Makefile.compilation

#
# Objets
#

fich_obj_arguments_main=arguments_main.o 
fich_obj_arguments_main_map=arguments_main_map.o 
fich_obj_options_courtes=options_courtes.o
fich_obj_options_longues=options_longues.o 

#
# Tests (executables+objets)
#

BIN = arguments_main arguments_main_map options_courtes options_longues

arguments_main : $(fich_obj_arguments_main) 
	$(CCLNK) $(CFLAGS) $(LIBMATH) $(fich_obj_arguments_main) -o arguments_main 

arguments_main.o : arguments_main.c 
	$(CCOBJ) $(CFLAGS) $(LIBMATH) arguments_main.c -o arguments_main.o -I./ 

arguments_main_map : $(fich_obj_arguments_main_map) 
	$(CCLNK) $(CFLAGS) $(LIBMATH) $(fich_obj_arguments_main_map) -o arguments_main_map 

arguments_main_map.o : arguments_main_map.c 
	$(CCOBJ) $(CFLAGS) $(LIBMATH) arguments_main_map.c -o arguments_main_map.o -I./ 

options_courtes : $(fich_obj_options_courtes) 
	$(CCLNK) $(CFLAGS) $(LIBMATH) $(fich_obj_options_courtes) -o options_courtes 

options_courtes.o : options_courtes.c 
	$(CCOBJ) $(CFLAGS) $(LIBMATH) options_courtes.c -o options_courtes.o -I./ 

options_longues : $(fich_obj_options_longues) 
	$(CCLNK) $(CFLAGS) $(LIBMATH) $(fich_obj_options_longues) -o options_longues 

options_longues.o : options_longues.c 
	$(CCOBJ) $(CFLAGS) $(LIBMATH) options_longues.c -o options_longues.o -I./ 

#
# Modules
#

OBJ=getopt.o getopt1.o

getopt.o : getopt.c getopt.h
	$(CCOBJ) $(CFLAGS) $(LIBMATH) getopt.c -o getopt.o -I./

getopt1.o : getopt1.c getopt.h
	$(CCOBJ) $(CFLAGS) $(LIBMATH) getopt1.c -o getopt1.o -I./

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
	./arguments_main
	./arguments_main_map
	./options_courtes
	./options_longues

dist : 
	- rm Cours_2_Main.tar.gz
	tar cvfz Cours_2_Main.tar.gz cours_main.pdf Makefile Makefile.compilation \
	arguments_main.c arguments_main_map.c options_courtes.c options_longues.c \
	getopt.c getopt.h \
	getopt1.c 
