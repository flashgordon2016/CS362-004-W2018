/********************************************************
 * Course: CS362 - Software Engineering II - Winter 2018
 * Assignment: Assignment 4
 * Author: Matthew G. Morse
 * ONID: morsmatt
 * Date: 2/18/2018
 * Description: Random test unit for the refactored Smithy
 * card function 
********************************************************/
#include "dominion.h"
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
 * Method under test: Smithy Card Effect
 * Dependencies: current player, current game state, and hand 
 * position of Smithy card of current player
 ****************************************************************/
int checkSmithyCard(int p, struct gameState *post, int handPos){
	//make copy of game state prior to test
	struct gameState pre;
	memcpy(&pre, post, sizeof(struct gameState));

	int r;

	//	printf("post.handcount: %d, post.deckCount: %d, post.discardCount: %d\n", post->handCount[p], post->deckCount[p], post->discardCount[p]);
	//Run method under test
	r = smithyCard(p, post, handPos); //Get return value
	//Alter pre struct in same fashion as Smithy should when
	//functioning as expected
	if (pre.deckCount[p] >= 3) {
		//Draw 3 cards from player's deck and add them to the player's hand
		int i;
		for (i = 0; i < 3; i++) {
			pre.handCount[p]++;
			pre.hand[p][pre.handCount[p] - 1] = pre.deck[p][pre.deckCount[p] - 1];
			pre.deckCount[p]--;
		}
		//Discard the Smithy card and add it to the discard pile
		discardCard(handPos, p, &pre, 0);
	} else if (pre.discardCount[p] > 0) { //deck had to be reshuffled
		//Copy deck of post to pre
    memcpy(pre.deck[p], post->deck[p], sizeof(int) * (pre.discardCount[p] + 2));
    //Copy any additional post hand cards up to 2
    //(3 cards are added but Smithy is removed)
   /*( int count = 0;
		while (pre.handCount[p] < post->handCount[p] && count < 2) {
			pre.hand[p][post->handCount[p]-1] = post->hand[p][post->handCount[p]-1];
    	pre.handCount[p]++;
			count++;
		}
		//Copy card at Smithy's old index from post hand 
		pre.hand[p][handPos] = post->hand[p][handPos];*/
    pre.deckCount[p] = post->deckCount[p];//pre.discardCount[p] - count;
    pre.discardCount[p] = 0;
		//Smithy should be only card in discard pile
		pre.discard[p][0] = smithy;
	}
	if (r != 0) {
		printf("Function failed\n");
		return 1;
	}

	//Check that game state responds according to expectations
	if (memcmp(&pre, post, sizeof(struct gameState)) != 0) {
		printf("Game state changed unexpectedly\n");
		/*printf("Pre.handCount: %d, pre.deckCount: %d, pre.discardCount: %d\n", pre.handCount[p], pre.deckCount[p], pre.discardCount[p]);
		printf("post.handcount: %d, post.deckCount: %d, post.discardCount: %d\n", post->handCount[p], post->deckCount[p], post->discardCount[p]);
		*/	
		return 1;
	}
	return 0;
}


int main (){
  int i, n, p, handPos;
	int testsFailed = 0, tests = 20000;
  struct gameState G;
  
  printf ("Testing Smithy card function.\n");

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
    G.discardCount[p] = floor(Random() * MAX_DECK);
    G.handCount[p] = floor(Random() * MAX_HAND);
		G.playedCardCount = 0;
		//assign Smithy to random position in hand
		handPos = floor(Random() * G.handCount[p]);
		testsFailed += checkSmithyCard(p, &G, handPos);
  }
	if (testsFailed == 0) 
 		printf("ALL TESTS OK\n");
	else
		printf("%d OUT OF %d TESTS FAILED\n", testsFailed, tests);


	return 0;
}
