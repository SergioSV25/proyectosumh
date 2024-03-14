CC=gcc
CFLAGS=-I.
INC=sem.h 
OBJECTS=shared.o sem.o
semaforos: $(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) -o shared
semaforos.o: shared.c $(INC)
	$(CC) -c shared.c  $(CFLAGS)
sem.o: sem.c sem.h
	$(CC) -c sem.c  $(CFLAGS)
clean:
	rm shared $(OBJECTS)