include ../Makefile.compilation 
include ../Makefile.dir         


#
# Objets
#

fich_obj_lancer_billes=lancer_billes.o \
	$(DirEcran)/ecran.o \
	$(DirJeu)/coord.o $(DirJeu)/bille.o $(DirJeu)/case.o $(DirJeu)/aire.o $(DirJeu)/zone.o\
	$(DirMvt)/mvt_bille.o \
	$(DirCommun)/direction.o $(DirCommun)/erreur.o

#
# Tests (executables+objets)
#

BIN = lancer_billes 

lancer_billes : $(fich_obj_lancer_billes) 
	$(CCLNK) $(CFLAGS) $(fich_obj_lancer_billes) -o lancer_billes $(LIB_CURSES) $(LIB_PTHREAD) $(MACRO_PTHREAD) -ltda -L$(DirTDA)/lib

lancer_billes.o : lancer_billes.c $(DirEcran)/ecran.h 
	$(CCOBJ) $(CFLAGS)  lancer_billes.c -o lancer_billes.o $(INC_CURSES) -I./ \
	-I$(DirCommun) \
	-I$(DirJeu) \
	-I$(DirMvt) \
	-I$(DirEcran) \
	-I$(DirTDA)/inc 

#
# Modules (objets)
#

OBJ =  

#
# Modules externes
#

$(DirCommun)/liste.o : $(DirCommun)/liste.h $(DirCommun)/liste.c
	cd $(DirCommun) ; make -f Makefile liste.o 

$(DirCommun)/erreur.o : $(DirCommun)/erreur.h $(DirCommun)/erreur.c
	cd $(DirCommun) ; make -f Makefile erreur.o 


$(DirJeu)/coord.o : $(DirJeu)/coord.c $(DirJeu)/coord.h 
	cd $(DirJeu) ; make -f Makefile coord.o

$(DirJeu)/bille.o : $(DirJeu)/bille.c $(DirJeu)/bille.h 
	cd $(DirJeu) ; make -f Makefile bille.o

$(DirJeu)/case.o : $(DirJeu)/case.c $(DirJeu)/case.h 
	cd $(DirJeu) ; make -f Makefile case.o

$(DirJeu)/zone.o : $(DirJeu)/zone.c $(DirJeu)/zone.h 
	cd $(DirJeu) ; make -f Makefile zone.o

$(DirJeu)/aire.o : $(DirJeu)/aire.c $(DirJeu)/aire.h 
	cd $(DirJeu) ; make -f Makefile aire.o

$(DirMvt)/mvt_bille.o : $(DirMvt)/mvt_bille.c $(DirMvt)/mvt_bille.h
	cd $(DirMvt) ; make -f Makefile mvt_bille.o 


$(DirEcran)/ecran.o : $(DirEcran)/ecran.c $(DirEcran)/ecran.h 
	cd $(DirEcran) ; make -f Makefile ecran.o 


#
# Headers 
#

#
#
#

all : $(BIN) $(OBJ)

clean :
	- rm  $(BIN) *.o *~

tests : 


