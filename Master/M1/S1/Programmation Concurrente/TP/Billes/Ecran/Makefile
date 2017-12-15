include ../Makefile.compilation 
include ../Makefile.dir         


#
# Objets
#

fich_obj_test_ecran_bille=test_ecran_bille.o \
	ecran.o \
	$(DirJeu)/coord.o $(DirJeu)/bille.o $(DirJeu)/case.o $(DirJeu)/aire.o $(DirJeu)/zone.o \
	$(DirMvt)/mvt_bille.o \
	$(DirCommun)/direction.o $(DirCommun)/erreur.o

fich_obj_test_ecran_billes=test_ecran_billes.o \
	ecran.o \
	$(DirJeu)/coord.o $(DirJeu)/bille.o $(DirJeu)/case.o $(DirJeu)/aire.o $(DirJeu)/zone.o \
	$(DirMvt)/mvt_bille.o \
	$(DirCommun)/direction.o $(DirCommun)/erreur.o


#
# Tests (executables+objets)
#

BIN = test_ecran_bille test_ecran_billes 

test_ecran_bille : $(fich_obj_test_ecran_bille) 
	$(CCLNK) $(CFLAGS) $(fich_obj_test_ecran_bille) -o test_ecran_bille $(LIB_CURSES) -ltda -L$(DirTDA)/lib

test_ecran_bille.o : test_ecran_bille.c ecran.h 
	$(CCOBJ) $(CFLAGS)  test_ecran_bille.c -o test_ecran_bille.o -I./ -I$(DirCommun) -I$(DirJeu) -I$(DirMvt) $(INC_CURSES) -I$(DirTDA)/inc

test_ecran_billes : $(fich_obj_test_ecran_billes) 
	$(CCLNK) $(CFLAGS) $(fich_obj_test_ecran_billes) -o test_ecran_billes $(LIB_CURSES) -ltda -L$(DirTDA)/lib

test_ecran_billes.o : test_ecran_billes.c ecran.h 
	$(CCOBJ) $(CFLAGS)  test_ecran_billes.c -o test_ecran_billes.o -I./ -I$(DirCommun) -I$(DirJeu) -I$(DirMvt) $(INC_CURSES) -I$(DirTDA)/inc

#
# Modules (objets)
#

OBJ =  ecran.o 

ecran.o : ecran.c ecran.h 
	$(CCOBJ) $(CFLAGS)  ecran.c -o ecran.o -I./ -I$(DirCommun) -I$(DirJeu) -I$(DirMvt) $(INC_CURSES) -I$(DirTDA)/inc

#
# Modules externes
#

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

#
# Headers 
#

ecran.h : $(DirJeu)/aire.h 
	touch ecran.h

#
#
#

all : $(BIN) $(OBJ)

clean :
	- rm  $(BIN) *.o *~

tests : 


