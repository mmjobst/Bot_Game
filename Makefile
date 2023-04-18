all: game

game: game.c
	gcc -Wall -lm game.c -o game

clean:
	rm -f *.o game

zipfile: 
	tar cvf Bot_Game.tar Makefile *.c
	gzip Bot_Game.tar