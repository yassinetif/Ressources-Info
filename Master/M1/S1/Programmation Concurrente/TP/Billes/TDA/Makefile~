include Makefile.dirtop

all clean : 
ifeq ($(DEBUG),yes)
	@echo "Mode debug"
else
	@echo "Mode release"
endif
	cd $(DirSrc) ; make $@
	cd $(DirLib) ; make $@

tests : 
