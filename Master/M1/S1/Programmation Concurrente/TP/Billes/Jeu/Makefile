include ../Makefile.compilation 
include ../Makefile.dir         

#
# Objets
#

fich_obj_test_coord=test_coord.o coord.o \
	$(DirCommun)/erreur.o

fich_obj_test_coords=test_coords.o coord.o \
	 $(DirCommun)/erreur.o


fich_obj_test_bille=test_bille.o coord.o bille.o \
	$(DirCommun)/direction.o $(DirCommun)/erreur.o

fich_obj_test_billes=test_billes.o coord.o bille.o \
	$(DirCommun)/direction.o $(DirCommun)/erreur.o


fich_obj_test_case=test_case.o coord.o bille.o case.o zone.o \
	$(DirCommun)/direction.o $(DirCommun)/erreur.o

fich_obj_test_cases=test_cases.o coord.o bille.o case.o zone.o \
	 $(DirCommun)/direction.o $(DirCommun)/erreur.o


fich_obj_test_zone=test_zone.o coord.o zone.o \
	$(DirCommun)/erreur.o

fich_obj_test_zones=test_zones.o coord.o zone.o \
	 $(DirCommun)/direction.o $(DirCommun)/erreur.o


fich_obj_test_aire=test_aire.o coord.o bille.o case.o zone.o aire.o \
	$(DirCommun)/direction.o $(DirCommun)/erreur.o

fich_obj_test_aires=test_aires.o coord.o bille.o case.o zone.o aire.o \
	 $(DirCommun)/direction.o $(DirCommun)/erreur.o

fich_obj_test_aire_zone=test_aire_zone.o coord.o bille.o case.o zone.o aire.o \
	 $(DirCommun)/direction.o $(DirCommun)/erreur.o

#
# Tests (executables+objets)
#

BIN = test_coord test_coords test_bille test_billes test_case test_cases test_zone test_aire test_aires test_aire_zone

test_coord : $(fich_obj_test_coord) 
	$(CCLNK) $(CFLAGS)  $(fich_obj_test_coord) -o test_coord 

test_coord.o : test_coord.c coord.h 
	$(CCOBJ) $(CFLAGS)  test_coord.c -o test_coord.o -I./ -I$(DirCommun) -I$(DirTDA)/inc 

test_coords : $(fich_obj_test_coords) 
	$(CCLNK) $(CFLAGS)  $(fich_obj_test_coords) -o test_coords -ltda -L$(DirTDA)/lib 

test_coords.o : test_coords.c  coord.h 
	$(CCOBJ) $(CFLAGS)  test_coords.c -o test_coords.o -I./ -I$(DirCommun) -I$(DirTDA)/inc


test_bille : $(fich_obj_test_bille) 
	$(CCLNK) $(CFLAGS)  $(fich_obj_test_bille) -o test_bille 

test_bille.o : test_bille.c bille.h 
	$(CCOBJ) $(CFLAGS)  test_bille.c -o test_bille.o -I./ -I$(DirCommun) -I$(DirTDA)/inc

test_billes : $(fich_obj_test_billes) 
	$(CCLNK) $(CFLAGS)  $(fich_obj_test_billes) -o test_billes -ltda -L$(DirTDA)/lib 

test_billes.o : test_billes.c bille.h 
	$(CCOBJ) $(CFLAGS)  test_billes.c -o test_billes.o -I./ -I$(DirCommun) -I$(DirTDA)/inc


test_case : $(fich_obj_test_case) 
	$(CCLNK) $(CFLAGS)  $(fich_obj_test_case) -o test_case -ltda -L$(DirTDA)/lib 

test_case.o : test_case.c case.h 
	$(CCOBJ) $(CFLAGS)  test_case.c -o test_case.o -I./ -I$(DirCommun) -I$(DirTDA)/inc


test_zone : $(fich_obj_test_zone) 
	$(CCLNK) $(CFLAGS)  $(fich_obj_test_zone) -o test_zone 

test_zone.o : test_zone.c zone.h 
	$(CCOBJ) $(CFLAGS)  test_zone.c -o test_zone.o -I./ -I$(DirCommun) -I$(DirTDA)/inc

test_zones : $(fich_obj_test_zones) 
	$(CCLNK) $(CFLAGS)  $(fich_obj_test_zones) -o test_zones -ltda -L$(DirTDA)/lib 

test_zones.o : test_zones.c zone.h 
	$(CCOBJ) $(CFLAGS)  test_zones.c -o test_zones.o -I./ -I$(DirCommun) -I$(DirTDA)/inc

test_cases : $(fich_obj_test_cases) 
	$(CCLNK) $(CFLAGS)  $(fich_obj_test_cases) -o test_cases -ltda -L$(DirTDA)/lib 

test_cases.o : test_cases.c case.h 
	$(CCOBJ) $(CFLAGS)  test_cases.c -o test_cases.o -I./ -I$(DirCommun) -I$(DirTDA)/inc


test_aire : $(fich_obj_test_aire) 
	$(CCLNK) $(CFLAGS)  $(fich_obj_test_aire) -o test_aire -ltda -L$(DirTDA)/lib 

test_aire.o : test_aire.c aire.h 
	$(CCOBJ) $(CFLAGS)  test_aire.c -o test_aire.o -I./ -I$(DirCommun) -I$(DirTDA)/inc

test_aires : $(fich_obj_test_aires) 
	$(CCLNK) $(CFLAGS)  $(fich_obj_test_aires) -o test_aires -ltda -L$(DirTDA)/lib 

test_aires.o : test_aires.c  aire.h 
	$(CCOBJ) $(CFLAGS)  test_aires.c -o test_aires.o -I./ -I$(DirCommun) -I$(DirTDA)/inc


test_aire_zone : $(fich_obj_test_aire_zone) 
	$(CCLNK) $(CFLAGS)  $(fich_obj_test_aire_zone) -o test_aire_zone -ltda -L$(DirTDA)/lib 

test_aire_zone.o : test_aire_zone.c  aire.h 
	$(CCOBJ) $(CFLAGS)  test_aire_zone.c -o test_aire_zone.o -I./ -I$(DirCommun) -I$(DirTDA)/inc



#
# Modules (objets)
#

OBJ =  coord.o bille.o case.o zone.o aire.o  

coord.o : coord.c coord.h 
	$(CCOBJ) $(CFLAGS)  coord.c -o coord.o -I./ -I$(DirCommun) -I$(DirTDA)/inc

bille.o : bille.c bille.h 
	$(CCOBJ) $(CFLAGS)  bille.c -o bille.o -I./ -I$(DirCommun) -I$(DirTDA)/inc

case.o : case.c case.h 
	$(CCOBJ) $(CFLAGS)  case.c -o case.o -I./ -I$(DirCommun) -I$(DirTDA)/inc

zone.o : zone.c zone.h 
	$(CCOBJ) $(CFLAGS)  zone.c -o zone.o -I./ -I$(DirCommun) -I$(DirTDA)/inc

aire.o : aire.c aire.h 
	$(CCOBJ) $(CFLAGS)  aire.c -o aire.o -I./ -I$(DirCommun) -I$(DirTDA)/inc

#
# Modules externes
#

$(DirCommun)/direction.o : $(DirCommun)/direction.c $(DirCommun)/direction.h
	cd $(DirCommun) ; make -f Makefile direction.o 

$(DirCommun)/erreur.o : $(DirCommun)/erreur.c $(DirCommun)/erreur.h
	cd $(DirCommun) ; make -f Makefile erreur.o

#
# Headers 
#

coord.h : $(DirCommun)/commun.h  
	touch coord.h

bille.h : coord.h $(DirCommun)/direction.h 
	touch bille.h

case.h : bille.h
	touch case.h

zone.h : coord.h
	touch zone.h

aire.h : case.h 
	touch aire.h

#
#
#

all : $(BIN) $(OBJ)

clean :
	- rm  $(BIN) *.o *~

tests :
	./test_bille
	./test_billes
	./test_case
	./test_zone
	./test_aire
	./test_aires
	./test_aire_zone
	./test_coord < stdin_test_coord
	./test_coords
