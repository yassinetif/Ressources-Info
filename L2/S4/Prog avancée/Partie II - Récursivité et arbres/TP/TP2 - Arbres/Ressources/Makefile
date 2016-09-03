
CC=gcc
OPTS=-Wall -g
PROG=animaux
LIBS=arbre.o

all: ${PROG} ${LIBS}

${PROG}: animaux.c ${LIBS}
	${CC} animaux.c ${LIBS} ${OPTS} -o ${PROG}

arbre.o: arbre.c arbre.h
	${CC} -c arbre.c ${OPTS} 


clean:
	rm -f ${LIBS} ${PROG}


