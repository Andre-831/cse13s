
#makefile for asgn3, lcr executable

lcr: lcr.o game.o randi.o
	clang lcr.o game.o randi.o -o lcr

lcr.o: lcr.c game.h randi.h
	clang -c lcr.c

game.o: game.c game.h randi.h
	clang -c game.c

randi.o: randi.c randi.h
	clang -c randi.c

clean:
	rm -f *.o lcr