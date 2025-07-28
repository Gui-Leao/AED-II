all: programa

programa: main.o BTree.o BPlusTree.o queue.o
	gcc main.o BTree.o BPlusTree.o queue.o -o programa

main.o: main.c BTree.h BPlusTree.h queue.h
	gcc -c main.c

BTree.o: BTree.c BTree.h
	gcc -c BTree.c

BPlusTree.o: BPlusTree.c BPlusTree.h
	gcc -c BPlusTree.c

queue.o: queue.c queue.h BTree.h
	gcc -c queue.c

clean:
	rm -f *.o programa
