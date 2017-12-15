include ../../Makefile.dir         
DirInc=../inc

#
# Modules (objets)
#

OBJ =  tab.o liste.o 

tab.o : tab.c $(DirInc)/tab.h
	gcc -c -Wall tab.c -o tab.o -I./ -I$(DirInc) 

liste.o : liste.c $(DirInc)/liste.h
	gcc -c -Wall  liste.c -o liste.o -I./ -I$(DirInc)

#
#
#

all : $(OBJ) 

clean :
	- rm $(OBJ) 
	- rm  *~

tests :
