# Makefile for asgn7

all: xd bad_xd

xd: xd.o
	clang xd.o -o xd

xd.o: xd.c
	clang -c -gdwarf-4 xd.c

bad_xd: bad_xd.o
	clang bad_xd.o -o bad_xd

bad_xd.o: bad_xd.c
	clang -c -gdwarf-4 bad_xd.c

clean:
	rm -f *.o xd bad_xd
