include Makefile.dirtop
include Makefile.compilation

clean : 
	- rm *~
	cd $(DirTDA) ; make $@
	cd $(DirCommun) ; make $@ 
	cd $(DirJeu) ; make $@
	cd $(DirMvt) ; make $@
	cd $(DirEcran) ; make $@
	cd $(DirEtu) ; make $@


all tests : 
ifeq ($(DEBUG),yes)
	@echo "Mode debug"
else
	@echo "Mode release"
endif
	cd $(DirTDA) ; make $@
	cd $(DirCommun) ; make $@ 
	cd $(DirJeu) ; make $@
	cd $(DirMvt) ; make $@
	cd $(DirEcran) ; make $@
	cd $(DirEtu) ; make $@


tags : 
	etags --language=c  */*.[ch] --output=BILLES.TAGS
