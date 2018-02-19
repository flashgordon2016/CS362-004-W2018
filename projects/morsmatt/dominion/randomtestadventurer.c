/********************************************************
 * Course: CS362 - Software Engineering II - Winter 2018
 * Assignment: Assignment 4
 * Author: Matthew G. Morse
 * ONID: morsmatt
 * Date: 2/18/2018
 * Description: Random test unit for the refactored Adventurer 
 * card function from cards.c
********************************************************/
#include "dominion.h"
#include "cards.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h> //Remove if unused
#include <string.h>
#include "rngs.h"
#include <math.h>

//Write function to check for card in hand
//Return index of card if found. Otherwise, returns -1
int hasCard(int p, struct gameState *G, int card) {
	int i;
	for (i = 0; i < G->handCount[p]; i++) {
		if (G->hand[p][i] == smithy)
			return i;
	}
	return -1;
}


/*****************************************************************
 * Method under test: adventurerAction()
 * Dependencies: current player, current game state, and an array
 * for storing revealed cards
 ****************************************************************/
int checkAdventurerCard(int p, struct gameState *post, int *revealedCards, int handPos){
	//make copy of game state prior to test
	struct gameState pre;
	memcpy(&pre, post, sizeof(struct gameState));
	int r;
	
	//Run method under test
	r = adventurerAction(p, post, revealedCards); //Get return value
	//Check for successful function call
	if (r != 0) {
		printf("Test failed. Infinite loop in treasure search\n");
		return 1;
	}
	return 0;
}


int main (){
  int i, n, p, handPos;
	int testsFailed = 0, tests = 20000; 
	int revealedCards[MAX_DECK];
  struct gameState G;
  
  printf ("Testing Adventurer card function.\n");

  printf ("RANDOM TESTS.\n");

  SelectStream(2);
  PutSeed(3);

  for (n = 0; n < tests; n++) {
		//initialize game state w/ random values
    for (i = 0; i < sizeof(struct gameState); i++) {
      ((char*)&G)[i] = floor(Random() * 256);
    }
    p = floor(Random() * 2);
    G.deckCount[p] = floor(Random() * MAX_DECK);
		//initialize with random cards within possible range
		for (i = 0; i < G.deckCount[p]; i++) {
			G.deck[p][i] = floor(Random() * 26);
		}
    G.discardCount[p] = floor(Random() * MAX_DECK);
		//initialize with random cards within possible range
		for (i = 0; i < G.discardCount[p]; i++) {
			G.discard[p][i] = floor(Random() * 26);
		}
    G.handCount[p] = floor(Random() * MAX_HAND);
		G.playedCardCount = 0;
		//assign Adventurer to random position in hand
		handPos = floor(Random() * G.handCount[p]);
		testsFailed += checkAdventurerCard(p, &G, revealedCards, handPos);
  }
	if(testsFailed == 0)
  	printf ("ALL TESTS OK\n");
	else 
		printf("%d OUT OF %d TESTS FAILED\n", testsFailed, tests);
	return 0;
}
