all: game1 game2

game1: game1.c
	gcc -Wall -lm game1.c -o game1

game2: game2.c
	gcc -Wall -lm game2.c -o game2

clean:
	rm -f *.o game1 game2

zipfile: 
	tar cvf Bot_Games.tar Makefile *.c
	gzip Bot_Games.tar