include ../../Makefile.dir         
DirSrc=../src

#
# Objets
#



#
# Tests (executables+objets)
#

LIB =  libtda.a



#
#--- Bibliotheque statique
#

obj_libtda = $(DirSrc)/tab.o $(DirSrc)/liste.o 
libtda.a : $(obj_libtda)
	ar -s -r libtda.a $(obj_libtda)

#
#
#



all : $(LIB) 

clean :
	- rm $(LIB) 
	- rm *~

tests :

