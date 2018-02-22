CFLAGS = -Wall -fpic -coverage -lm

#refactored card functions
cards.o: cards.h cards.c
	gcc -c cards.c dominion.c -g $(CFLAGS)

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o cards.o
	gcc -c dominion.c cards.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o cards.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o cards.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o cards.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o cards.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o cards.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o cards.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

#Generates and executes all random unit tests
randomtestcardresults.out: randomtestcard1.c dominion.o rngs.o
	echo "Results for running random card function tests:" > randomtestcardresults.out
	#Smith card random test unit
	echo "randomtestcard1.c" >> randomtestcardresults.out
	gcc -o randomtestcard1 -g dominion.c cards.c rngs.c randomtestcard1.c $(CFLAGS)
	randomtestcard1 >> randomtestcardresults.out
	gcov cards.c >> randomtestcardresults.out
	#Embargo card random test unit
	echo "randomtestcard2.c" >> randomtestcardresults.out
	gcc -o randomtestcard2 -g dominion.c cards.c rngs.c randomtestcard2.c $(CFLAGS)
	randomtestcard2 >> randomtestcardresults.out
	gcov cards.c >> randomtestcardresults.out
	#Adventurer card random test unit
	echo "randomtestadventurer.c" >> randomtestcardresults.out
	gcc -o randomtestadventurer -g dominion.c cards.c rngs.c randomtestadventurer.c $(CFLAGS)
	randomtestadventurer >> randomtestcardresults.out
	gcov cards.c >> randomtestcardresults.out

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard \
	testDrawCard.exe badTestDrawCard randomtestcard1 randomtestcard2 randomtestadventurer
