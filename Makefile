all: programa

programa: main.o BTree.o queue.o
	gcc main.o BTree.o queue.o -o programa

# Compilação de main.o
main.o: main.c BTree.h queue.h
	gcc -c main.c

# Compilação de BTree.o
BTree.o: BTree.c BTree.h
	gcc -c BTree.c

# Compilação de queue.o
queue.o: queue.c queue.h BTree.h
	gcc -c queue.c

# Limpeza
clean:
	rm -f *.o programa
