CFLAGS = -std=c99 -Wall -fpic -coverage -lm -g

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to enter: ./playdom <any integer number> like ./playdom 10*/

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player

clean:
	rm -f *.o playdom.exe playdom player player.exe randomcardtest1 randomcardtest2 randomcardtest3 *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe unittestresults.out

randomcardtest1: dominion.o rngs.o
	echo "randomcardtest1.c:" >> randomcardtest1.out
	gcc -o randomcardtest1 randomcardtest1.c dominion.o rngs.o $(CFLAGS)
	./randomcardtest1 >> randomcardtest1.out
	gcov -b -c -f dominion.c >> randomcardtest1.out
	
randomcardtest2: dominion.o rngs.o
	echo "randomcardtest2.c:" >> randomcardtest2.out
	gcc -o randomcardtest2 randomcardtest2.c dominion.o rngs.o $(CFLAGS)
	./randomcardtest2 >> randomcardtest2.out
	gcov -b -c -f dominion.c >> randomcardtest2.out
	
randomcardtest3: dominion.o rngs.o
	echo "randomcardtest3.c:" >> randomcardtest3.out
	gcc -o randomcardtest3 randomcardtest3.c dominion.o rngs.o $(CFLAGS)
	./randomcardtest3 >> randomcardtest3.out
	gcov -b -c -f dominion.c >> randomcardtest3.out