CC=gcc
CFLAGS=-lm 
DEPS= main_idx.h index.h hash.h forward_list.h node.h vector.h
OBJ=main_idx.o index.o hash.o forward_list.o node.o vector.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main_idx: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
	echo "Compilado!"

clean:
	rm -rf *.o main

run:
	./main