all:generer showrank.cgi lowestscore.cgi insertrank.cgi test wordgame
wordgame:wordgame.o grille.o random.o
	gcc -Wall -o wordgame wordgame.o grille.o random.o `pkg-config --cflags --libs gtk+-2.0 gmodule-2.0`
wordgame.o:wordgame.c
	gcc -Wall -c wordgame.c `pkg-config --cflags --libs gtk+-2.0 gmodule-2.0`
test:test.o grille.o random.o
	gcc -Wall -o test test.o grille.o random.o
test.o:test.c
	gcc -Wall -c test.c
generer:grille.o random.o generer.o
	gcc -Wall -o generer.cgi random.o grille.o generer.o
generer.o:generer.c
	gcc -Wall -c generer.c
random.o:random.c random.h
	gcc -Wall -c random.c
grille.o:grille.c grille.h
	gcc -Wall -c grille.c
insertrank.cgi:insertrank.o score.o
	gcc -Wall -o insertrank.cgi insertrank.o score.o
insertrank.o:insertrank.c
	gcc -Wall -c insertrank.c
showrank.cgi:score.o score.cgi.o
	gcc -Wall -o showrank.cgi score.o score.cgi.o
lowestscore.cgi:score.o lowestscore.o
	gcc -Wall -o lowestscore.cgi score.o lowestscore.o
score.o:score.c
	gcc -Wall -c score.c
score.cgi.o:score.cgi.c
	gcc -Wall -c score.cgi.c
lowestscore.o:lowestscore.c
	gcc -Wall -c lowestscore.c
clean:
	rm *.o
