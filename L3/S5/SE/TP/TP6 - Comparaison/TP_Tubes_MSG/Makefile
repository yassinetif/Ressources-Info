# MAKEFILE pour TP IPC
#
#

#
# Directories
#

#
# Object files
#

fich_obj_test_msg_messages = test_msg_messages.o msg_messages.o
fich_obj_msg_emetteur = msg_emetteur.o msg_messages.o
fich_obj_msg_recepteur = msg_recepteur.o msg_messages.o

fich_obj_test_pipe_messages = test_pipe_messages.o pipe_messages.o
fich_obj_pipe_emetteur = pipe_emetteur.o pipe_messages.o
fich_obj_pipe_recepteur = pipe_recepteur.o pipe_messages.o

fich_obj_test_file_messages = test_file_messages.o file_messages.o
fich_obj_file_emetteur = file_emetteur.o file_messages.o
fich_obj_file_recepteur = file_recepteur.o file_messages.o

#
# Options for compilation
#

GCCOBJ = gcc -c 
GCCLNK = gcc 


# Option for debugger
# -- pour versions des programmes en debuggage
opt = -g -Wall -D_DEBUG_ -D_MAC_
# -- pour versions finales des programmes  
#opt = -O2 -Wall
#
#
#

#
#-------- Mains ---------------
#

test_msg_messages : $(fich_obj_test_msg_messages)
	$(GCCLNK) $(fich_obj_test_msg_messages) $(opt) -o test_msg_messages -I ./

test_msg_messages.o : test_msg_messages.c msg_messages.h
	$(GCCOBJ) $(opt) test_msg_messages.c -o test_msg_messages.o -I ./

msg_emetteur : $(fich_obj_msg_emetteur)
	$(GCCLNK) $(fich_obj_msg_emetteur) $(opt) -o msg_emetteur -I ./

msg_emetteur.o : msg_emetteur.c msg_messages.h
	$(GCCOBJ) $(opt) msg_emetteur.c -o msg_emetteur.o -I ./

msg_recepteur : $(fich_obj_msg_recepteur)
	$(GCCLNK) $(fich_obj_msg_recepteur) $(opt) -o msg_recepteur -I ./

msg_recepteur.o : msg_recepteur.c msg_messages.h
	$(GCCOBJ) $(opt) msg_recepteur.c -o msg_recepteur.o -I ./



test_pipe_messages : $(fich_obj_test_pipe_messages)
	$(GCCLNK) $(fich_obj_test_pipe_messages) $(opt) -o test_pipe_messages -I ./

test_pipe_messages.o : test_pipe_messages.c pipe_messages.h
	$(GCCOBJ) $(opt) test_pipe_messages.c -o test_pipe_messages.o -I ./

pipe_emetteur : $(fich_obj_pipe_emetteur)
	$(GCCLNK) $(fich_obj_pipe_emetteur) $(opt) -o pipe_emetteur -I ./

pipe_emetteur.o : pipe_emetteur.c pipe_messages.h
	$(GCCOBJ) $(opt) pipe_emetteur.c -o pipe_emetteur.o -I ./

pipe_recepteur : $(fich_obj_pipe_recepteur)
	$(GCCLNK) $(fich_obj_pipe_recepteur) $(opt) -o pipe_recepteur -I ./

pipe_recepteur.o : pipe_recepteur.c pipe_messages.h
	$(GCCOBJ) $(opt) pipe_recepteur.c -o pipe_recepteur.o -I ./


test_file_messages : $(fich_obj_test_file_messages)
	$(GCCLNK) $(fich_obj_test_file_messages) $(opt) -o test_file_messages -I ./

test_file_messages.o : test_file_messages.c file_messages.h
	$(GCCOBJ) $(opt) test_file_messages.c -o test_file_messages.o -I ./

file_emetteur : $(fich_obj_file_emetteur)
	$(GCCLNK) $(fich_obj_file_emetteur) $(opt) -o file_emetteur -I ./

file_emetteur.o : file_emetteur.c file_messages.h
	$(GCCOBJ) $(opt) file_emetteur.c -o file_emetteur.o -I ./

file_recepteur : $(fich_obj_file_recepteur)
	$(GCCLNK) $(fich_obj_file_recepteur) $(opt) -o file_recepteur -I ./

file_recepteur.o : file_recepteur.c file_messages.h
	$(GCCOBJ) $(opt) file_recepteur.c -o file_recepteur.o -I ./


#
# --- Tests ---
#

#
#-------- Modules -------------
#

msg_messages.o : msg_messages.c msg_messages.h 
	$(GCCOBJ) $(opt) msg_messages.c -o msg_messages.o -I ./

pipe_messages.o : pipe_messages.c pipe_messages.h 
	$(GCCOBJ) $(opt) pipe_messages.c -o pipe_messages.o -I ./

file_messages.o : file_messages.c file_messages.h 
	$(GCCOBJ) $(opt) file_messages.c -o file_messages.o -I ./

#
#-------- Headers -------------
#

msg_messages.h : messages.h
	touch msg_messages.h

pipe_messages.h : messages.h
	touch pipe_messages.h

file_messages.h : messages.h
	touch file_messages.h

#
#-------- Clean objects -------
#

clean : 
	- rm *.o 
	- rm *~ 
	- rm msg_recepteur ; 
	- rm msg_emetteur ; 
	- rm pipe_recepteur ; 
	- rm file_emetteur ; 
	- rm test_msg_messages ; 
	- rm test_pipe_messages ; 
	- rm test_file_messages ; 

dist : clean
	cd .. ;  mv Etudiant TP_Tubes_MSG ; tar cvfz TP_Tubes_MSG.tar.gz TP_Tubes_MSG ; mv TP_Tubes_MSG Etudiant 

#
#-------- All executables -------
#

all : msg_emetteur msg_recepteur test_msg_messages   pipe_emetteur pipe_recepteur test_pipe_messages  file_emetteur file_recepteur test_file_messages

#
#-------- All tests -------
#
tests : 
	./test_msg_messages
	./test_pipe_messages
	./test_file_messages

#
#-------- Tags -------
#

tags :
	etags *.c 
