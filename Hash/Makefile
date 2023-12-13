CC=gcc
CFLAGS=-lm 
DEPS= main_idx.h hash.h forward_list.h node.h
OBJ=main_idx.o hash.o forward_list.o node.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main_idx: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
	echo "Compilado!"

clean:
	rm -rf *.o main

run:
	./main