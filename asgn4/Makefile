#makefile for asgn4
all: unique unittests

unique: unique.o tree.o
	clang unique.o tree.o -o unique

unittests: unittests.o tree.o
	clang unittests.o tree.o -o unittests

unique.o: unique.c tree.h
	clang -c -gdwarf-4 unique.c

tree.o : tree.c tree.h
	clang -c -gdwarf-4 tree.c

unittests.o: unittests.c tree.h
	clang -c -gdwarf-4 unittests.c

clean:
	rm -f *.o unique unittests