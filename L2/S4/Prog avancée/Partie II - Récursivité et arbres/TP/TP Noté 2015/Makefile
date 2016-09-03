CC=gcc
OPTS=-Wall -g
PROG=abr_fibo
LIBS=arbre.o main.o

all: ${PROG} ${LIBS}

${PROG}: main.c arbre.c ${LIBS}
	${CC} main.c animaux.c ${LIBS} ${OPTS} -o ${PROG}

arbre.o: arbre.c arbre.h
	${CC} -c arbre.c ${OPTS} 

main.o: main.c
	${CC} -c main.c ${OPTS}

clean:
	rm -f ${LIBS} ${PROG}


