include ../Makefile.compilation
include ../Makefile.dir


#
# Objets
#

fich_obj_test_mvt_bille=test_mvt_bille.o mvt_bille.o \
	$(DirJeu)/coord.o $(DirJeu)/bille.o $(DirJeu)/case.o $(DirJeu)/zone.o $(DirJeu)/aire.o \
	$(DirCommun)/erreur.o $(DirCommun)/direction.o   

fich_obj_test_mvt_billes=test_mvt_billes.o mvt_bille.o \
	$(DirJeu)/coord.o $(DirJeu)/bille.o $(DirJeu)/case.o $(DirJeu)/zone.o $(DirJeu)/aire.o \
	$(DirCommun)/erreur.o $(DirCommun)/direction.o   

#
# Tests (executables+objets)
#

BIN = test_mvt_bille test_mvt_billes

test_mvt_bille : $(fich_obj_test_mvt_bille) 
	$(CCLNK) $(CFLAGS)  $(fich_obj_test_mvt_bille) -o test_mvt_bille -ltda -L$(DirTDA)/lib

test_mvt_bille.o : test_mvt_bille.c mvt_bille.h
	$(CCOBJ) $(CFLAGS)  test_mvt_bille.c -o test_mvt_bille.o -I./ -I$(DirCommun) -I$(DirTDA)/inc -I$(DirJeu) 

test_mvt_billes : $(fich_obj_test_mvt_billes) 
	$(CCLNK) $(CFLAGS)  $(fich_obj_test_mvt_billes) -o test_mvt_billes -ltda -L$(DirTDA)/lib

test_mvt_billes.o : test_mvt_billes.c mvt_bille.h
	$(CCOBJ) $(CFLAGS)  test_mvt_billes.c -o test_mvt_billes.o -I./ -I$(DirCommun) -I$(DirTDA)/inc -I$(DirJeu) 

#
# Modules (objets)
#

OBJ =  mvt_bille.o

mvt_bille.o : mvt_bille.c $(DirJeu)/aire.h 
	$(CCOBJ) $(CFLAGS)  mvt_bille.c -o mvt_bille.o -I./ -I$(DirCommun) -I$(DirTDA)/inc -I$(DirJeu) 

#
# Modules externes
#


#--- Commun 

$(DirCommun)/direction.o : $(DirCommun)/direction.c $(DirCommun)/direction.h
	cd $(DirCommun) ; make -f Makefile direction.o 

$(DirCommun)/vitesse.o : $(DirCommun)/vitesse.c $(DirCommun)/vitesse.h $(DirCommun)/commun.h
	cd $(DirCommun) ; make -f Makefile vitesse.o

$(DirCommun)/erreur.o : $(DirCommun)/erreur.c $(DirCommun)/erreur.h 
	cd $(DirCommun) ; make -f Makefile erreur.o

#--- Jeu 

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
