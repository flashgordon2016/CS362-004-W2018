/********************************************************
 * Course: CS362 - Software Engineering II - Winter 2018
 * Assignment: Assignment 4
 * Author: Matthew G. Morse
 * ONID: morsmatt
 * Date: 2/18/2018
 * Description: Random test unit for the refactored Outpost
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

/*
int outpostAction(int currentPlayer, struct gameState *state, int handPos){
	//set outpost flag
	state->outpostPlayed++;
			
  //discard card
  discardCard(handPos, currentPlayer, state, 0);
  return 0;
}
*/

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
 * Method under test: outpostAction()
 * Dependencies: current player, current game state, and the 
 * position of the Outpost card in the players's hand.
 ****************************************************************/
int checkOutpostCard(int p, struct gameState *post, int handPos){
	//make copy of game state prior to test
	struct gameState pre;
	memcpy(&pre, post, sizeof(struct gameState));
	int r;
	//Run method under test
	r = outpostAction(p, post, handPos); //Get return value
	
	//Update pre state with expected values
	pre.outpostPlayed++;
	//Add card to played pile
	discardCard(handPos, p, &pre, 0);
	
	//Check for successful function call
	if (r != 0) {
		printf("Function failed.\n");
		return 1;
	}
	if (memcmp(&pre, post, sizeof(struct gameState)) != 0) {
		printf("Game state changed unexpectedly\n");
		return 1;
	}
	return 0;
}


int main (){
  int i, n, p, handPos;
  int testsFailed = 0, tests = 20000; 
	struct gameState G;
  
  printf ("Testing Outpost card function.\n");

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
		G.outpostPlayed = 0;
		//assign Adventurer to random position in hand
		handPos = floor(Random() * G.handCount[p]);
		testsFailed += checkOutpostCard(p, &G, handPos);
  }
	if (testsFailed == 0) 
  	printf ("ALL TESTS OK\n");
	else
		printf("%d OUT OF %d TESTS FAILED\n", testsFailed, tests);

	return 0;
}

