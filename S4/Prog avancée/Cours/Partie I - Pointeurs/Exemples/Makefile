include Makefile.compilation

#
# Objets
#
fich_obj_adressage_indirect=adressage_indirect.o 

fich_obj_arithm_pointeur_1=arithm_pointeur_1.o 
fich_obj_arithm_pointeur_2=arithm_pointeur_2.o 
fich_obj_arithm_pointeur_3=arithm_pointeur_3.o 

fich_obj_objets_statiques_pointeur_fou=objets_statiques_pointeur_fou.o 

fich_obj_attention_const=attention_const.o 

fich_obj_pointeurs_fonctions=pointeurs_fonctions.o 

fich_obj_parametres_resultat=parametres_resultat.o 

fich_obj_echange_generique=echange_generique.o 

fich_obj_tri_generique_perso_1=tri_generique_perso_1.o copie.o
fich_obj_tri_generique_perso_2=tri_generique_perso_2.o copie.o
fich_obj_tri_generique_qsort=tri_generique_qsort.o 
fich_obj_test_copie=test_copie.o copie.o
fich_obj_affichage_generique=affichage_generique.o 
fich_obj_affichage_objets=affichage_objets.o 
fich_obj_affichage_objets_2=affichage_objets_2.o 


#
# Tests (executables+objets)
#

BIN = adressage_indirect \
	arithm_pointeur_1 arithm_pointeur_2 arithm_pointeur_3 \
	objets_statiques_pointeur_fou \
	attention_const \
	pointeurs_fonctions \
	parametres_resultat \
	echange_generique \
	test_copie \
	tri_generique_perso_1 tri_generique_perso_2 tri_generique_qsort \
	affichage_generique affichage_objets affichage_objets_2

adressage_indirect : $(fich_obj_adressage_indirect) 
	$(CCLNK) $(CFLAGS) $(LIBMATH) $(fich_obj_adressage_indirect) -o adressage_indirect 

adressage_indirect.o : adressage_indirect.c 
	$(CCOBJ) $(CFLAGS) $(LIBMATH) adressage_indirect.c -o adressage_indirect.o -I./ 


arithm_pointeur_1 : $(fich_obj_arithm_pointeur_1) 
	$(CCLNK) $(CFLAGS) $(LIBMATH) $(fich_obj_arithm_pointeur_1) -o arithm_pointeur_1 

arithm_pointeur_1.o : arithm_pointeur_1.c 
	$(CCOBJ) $(CFLAGS) $(LIBMATH) arithm_pointeur_1.c -o arithm_pointeur_1.o -I./ 

arithm_pointeur_2 : $(fich_obj_arithm_pointeur_2) 
	$(CCLNK) $(CFLAGS) $(LIBMATH) $(fich_obj_arithm_pointeur_2) -o arithm_pointeur_2 

arithm_pointeur_2.o : arithm_pointeur_2.c 
	$(CCOBJ) $(CFLAGS) $(LIBMATH) arithm_pointeur_2.c -o arithm_pointeur_2.o -I./

arithm_pointeur_3 : $(fich_obj_arithm_pointeur_3) 
	$(CCLNK) $(CFLAGS) $(LIBMATH) $(fich_obj_arithm_pointeur_3) -o arithm_pointeur_3 

arithm_pointeur_3.o : arithm_pointeur_3.c 
	$(CCOBJ) $(CFLAGS) $(LIBMATH) arithm_pointeur_3.c -o arithm_pointeur_3.o -I./ 



objets_statiques_pointeur_fou : $(fich_obj_objets_statiques_pointeur_fou) 
	$(CCLNK) $(CFLAGS) $(LIBMATH) $(fich_obj_objets_statiques_pointeur_fou) -o objets_statiques_pointeur_fou 

objets_statiques_pointeur_fou.o : objets_statiques_pointeur_fou.c 
	$(CCOBJ) $(CFLAGS) $(LIBMATH) objets_statiques_pointeur_fou.c -o objets_statiques_pointeur_fou.o -I./ 


attention_const : $(fich_obj_attention_const) 
	$(CCLNK) $(CFLAGS) $(LIBMATH) $(fich_obj_attention_const) -o attention_const 

attention_const.o : attention_const.c 
	$(CCOBJ) $(CFLAGS) $(LIBMATH) attention_const.c -o attention_const.o -I./ 


pointeurs_fonctions : $(fich_obj_pointeurs_fonctions) 
	$(CCLNK) $(CFLAGS) $(LIBMATH) $(fich_obj_pointeurs_fonctions) -o pointeurs_fonctions 

pointeurs_fonctions.o : pointeurs_fonctions.c 
	$(CCOBJ) $(CFLAGS) $(LIBMATH) pointeurs_fonctions.c -o pointeurs_fonctions.o -I./ 


parametres_resultat : $(fich_obj_parametres_resultat) 
	$(CCLNK) $(CFLAGS) $(LIBMATH) $(fich_obj_parametres_resultat) -o parametres_resultat 

parametres_resultat.o : parametres_resultat.c 
	$(CCOBJ) $(CFLAGS) $(LIBMATH) parametres_resultat.c -o parametres_resultat.o -I./ 


echange_generique : $(fich_obj_echange_generique) 
	$(CCLNK) $(CFLAGS) $(LIBMATH) $(fich_obj_echange_generique) -o echange_generique 

echange_generique.o : echange_generique.c 
	$(CCOBJ) $(CFLAGS) $(LIBMATH) echange_generique.c -o echange_generique.o -I./ 



tri_generique_perso_1 : $(fich_obj_tri_generique_perso_1) 
	$(CCLNK) $(CFLAGS) $(LIBMATH) $(fich_obj_tri_generique_perso_1) -o tri_generique_perso_1 

tri_generique_perso_1.o : tri_generique_perso_1.c 
	$(CCOBJ) $(CFLAGS) $(LIBMATH) tri_generique_perso_1.c -o tri_generique_perso_1.o -I./ 

tri_generique_perso_2 : $(fich_obj_tri_generique_perso_2) 
	$(CCLNK) $(CFLAGS) $(LIBMATH) $(fich_obj_tri_generique_perso_2) -o tri_generique_perso_2 

tri_generique_perso_2.o : tri_generique_perso_2.c 
	$(CCOBJ) $(CFLAGS) $(LIBMATH) tri_generique_perso_2.c -o tri_generique_perso_2.o -I./ 

tri_generique_qsort : $(fich_obj_tri_generique_qsort) 
	$(CCLNK) $(CFLAGS) $(LIBMATH) $(fich_obj_tri_generique_qsort) -o tri_generique_qsort 

tri_generique_qsort.o : tri_generique_qsort.c 
	$(CCOBJ) $(CFLAGS) $(LIBMATH) tri_generique_qsort.c -o tri_generique_qsort.o -I./ 

test_copie : $(fich_obj_test_copie) 
	$(CCLNK) $(CFLAGS) $(LIBMATH) $(fich_obj_test_copie) -o test_copie 

test_copie.o : test_copie.c 
	$(CCOBJ) $(CFLAGS) $(LIBMATH) test_copie.c -o test_copie.o -I./ 

affichage_generique : $(fich_obj_affichage_generique) 
	$(CCLNK) $(CFLAGS) $(LIBMATH) $(fich_obj_affichage_generique) -o affichage_generique 

affichage_generique.o : affichage_generique.c 
	$(CCOBJ) $(CFLAGS) $(LIBMATH) affichage_generique.c -o affichage_generique.o -I./

affichage_objets : $(fich_obj_affichage_objets) 
	$(CCLNK) $(CFLAGS) $(LIBMATH) $(fich_obj_affichage_objets) -o affichage_objets 

affichage_objets.o : affichage_objets.c 
	$(CCOBJ) $(CFLAGS) $(LIBMATH) affichage_objets.c -o affichage_objets.o -I./ 

affichage_objets_2 : $(fich_obj_affichage_objets_2) 
	$(CCLNK) $(CFLAGS) $(LIBMATH) $(fich_obj_affichage_objets_2) -o affichage_objets_2 

affichage_objets_2.o : affichage_objets_2.c 
	$(CCOBJ) $(CFLAGS) $(LIBMATH) affichage_objets_2.c -o affichage_objets_2.o -I./ 

#
# Modules
#

OBJ=copie.o

copie.o : copie.c 
	$(CCOBJ) $(CFLAGS) $(LIBMATH) copie.c -o copie.o -I./ 
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
	./adressage_indirect
	./arithm_pointeur_1
	./arithm_pointeur_2
	./arithm_pointeur_3
	./objets_statiques_pointeur_fou
	./attention_const
	./pointeurs_fonctions
	./parametres_resultat
	./echange_generique
	./tri_generique_perso_1
	./tri_generique_perso_2
	./tri_generique_qsort
	./test_copie
	./affichage_generique
	./affichage_objets
	./affichage_objets_2
