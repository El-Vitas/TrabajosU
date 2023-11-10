OBJ = main.o certamen.o
CFLAGS = -Wall
CC = gcc

certamen: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o certamen

main.o: main.c certamen.h
	$(CC) -c main.c

certamen.o: certamen.c certamen.h
	$(CC) -c certamen.c

clean:
	$(RM) -f *.o certamen core
