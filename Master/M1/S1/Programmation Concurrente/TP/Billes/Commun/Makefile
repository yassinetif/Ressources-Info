include ../Makefile.compilation 
include ../Makefile.dir         

#
# Objets
#

fich_obj_test_obstacle=test_obstacle.o obstacle.o 
fich_obj_test_direction=test_direction.o direction.o obstacle.o
fich_obj_test_vitesse=test_vitesse.o vitesse.o 
fich_obj_test_erreur=test_erreur.o erreur.o  

#
# Tests (executables+objets)
#

BIN = test_obstacle test_direction test_vitesse  test_erreur 

test_obstacle : $(fich_obj_test_obstacle) 
	$(CCLNK) $(CFLAGS) $(fich_obj_test_obstacle) -o test_obstacle 

test_obstacle.o : test_obstacle.c commun.h obstacle.h
	$(CCOBJ) $(CFLAGS) test_obstacle.c -o test_obstacle.o -I./ -I$(DirTDA)/inc

test_direction : $(fich_obj_test_direction) 
	$(CCLNK) $(CFLAGS) $(fich_obj_test_direction) -o test_direction 

test_direction.o : test_direction.c direction.h obstacle.h commun.h
	$(CCOBJ) $(CFLAGS) test_direction.c -o test_direction.o -I./ -I$(DirTDA)/inc

test_vitesse : $(fich_obj_test_vitesse) 
	$(CCLNK) $(CFLAGS) $(fich_obj_test_vitesse) -o test_vitesse 

test_vitesse.o : test_vitesse.c vitesse.h commun.h
	$(CCOBJ) $(CFLAGS) test_vitesse.c -o test_vitesse.o -I./ -I$(DirTDA)/inc


test_erreur : $(fich_obj_test_erreur) 
	$(CCLNK) $(CFLAGS)  $(fich_obj_test_erreur) -o test_erreur 

test_erreur.o : test_erreur.c
	$(CCOBJ) $(CFLAGS)  test_erreur.c -o test_erreur.o -I./ -I$(DirTDA)/inc

#
# Modules (objets)
#

OBJ = obstacle.o direction.o vitesse.o

obstacle.o : obstacle.c obstacle.h commun.h
	$(CCOBJ) $(CFLAGS)  obstacle.c -o obstacle.o -I./ -I$(DirTDA)/inc

direction.o : direction.c direction.h obstacle.h commun.h
	$(CCOBJ) $(CFLAGS)  direction.c -o direction.o -I./ -I$(DirTDA)/inc

vitesse.o : vitesse.c vitesse.h commun.h
	$(CCOBJ) $(CFLAGS)  vitesse.c -o vitesse.o -I./ -I$(DirTDA)/inc

erreur.o : erreur.c erreur.h 
	$(CCOBJ) $(CFLAGS)  erreur.c -o erreur.o -I./ -I$(DirTDA)/inc

#
# Modules externes
#

#
# Headers 
#

HDR = direction.h

direction.h : obstacle.h
	touch direction.h

#
#
#

all : $(BIN) $(OBJ) $(HDR) 

clean :
	- rm  $(BIN) *.o *~

tests :
	./test_obstacle
	./test_direction
	./test_vitesse
	./test_erreur
