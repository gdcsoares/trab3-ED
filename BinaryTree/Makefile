CC=gcc
CFLAGS=-lm 
DEPS= main.h binarytree.h node.h
OBJ=main.o binarytree.o node.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
	echo "Compilado!"

clean:
	rm -rf *.o main

run:
	./main