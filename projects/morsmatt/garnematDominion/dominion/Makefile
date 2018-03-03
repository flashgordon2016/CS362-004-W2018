CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


##Generates and executes all unit tests
unittestresults.out: cardtest1.c cardtest2.c cardtest3.c cardtest4.c dominion.o rngs.o
	echo "Results for running dominion card function unit tests:" > unittestresults.out
	##Adventurer test unit
	echo "cardtest1.c" >> unittestresults.out
	gcc -o cardtest1 -g dominion.c rngs.c cardtest1.c $(CFLAGS)
	cardtest1 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	##Smith test unit
	echo "cardtest2.c" >> unittestresults.out
	gcc -o cardtest2 -g dominion.c rngs.c cardtest2.c $(CFLAGS)
	cardtest2 >> unittestresults.out
	gcov dominion.c >> unittestresults.out


#Generates and executes all random tests
randomtestcardresults.out: dominion.o rngs.o
	echo "Results for running random card function tests:" > randomtestcardresults.out
	#Adventurer card random test unit
	echo "randomtestadventurer.c" >> randomtestcardresults.out
	gcc -o randomtestadventurer -g dominion.c rngs.c randomtestadventurer.c $(CFLAGS)
	randomtestadventurer >> randomtestcardresults.out
	gcov dominion.c >> randomtestcardresults.out
	#Smith card random test unit
	echo "randomtestcard1.c" >> randomtestcardresults.out
	gcc -o randomtestcard1 -g dominion.c rngs.c randomtestcard1.c $(CFLAGS)
	randomtestcard1 >> randomtestcardresults.out
	gcov dominion.c >> randomtestcardresults.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out \
	testDrawCard testDrawCard.exe randomtestadventurer randomtestcard1 \
	cardtest1 cardtest2
