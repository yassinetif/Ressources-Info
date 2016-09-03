CC = gcc
OBJ = abr.o tp_ABR.o
FLAGS = -g -Wall
EXEC = abr

$(EXEC): $(OBJ)
	$(CC) -o $(EXEC) $(OBJ) $(FLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(FLAGS)

clean:
	rm -i *.o
	rm -i *.*~
