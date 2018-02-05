#include "dominion.h"
#include "cards.h" //Refactored card function implementations
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>


int main(int argc, char* argv[]){
  int passed, player, count, i, x, numPlayers = 2, bonus = 0;
  int choice1 = 0, choice2 = 0, choice3 = 0;
  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
              sea_hag, tribute, smithy, council_room};
  struct gameState G, testG;

  initializeGame(numPlayers, k, time(NULL), &G);

  //Test that 3 cards are added to current player's hand
  player = G.whoseTurn;
  //Get player's handCount before playing smithy
  count = G.handCount[player];
  //Get player's discard count before playing smithy
  x = G.discardCount[player];
  //Run Smithy function
  cardEffect(smithy, choice1, choice2, choice3, &testG, 0, &bonus);
  if (x + 1 == G.discardCount[player] && G.handCount[player] == count + 2)
    printf("_smithy(): PASS correct number of cards drawn\n");
  else
    printf("_smithy(): FAIL correct number of cards drawn\n");

  //Test that 3 cards came from current player's pile
  

  //Test that only one card is discarded
  //Reset game values
  initializeGame(numPlayers, k, time(NULL), &G);
  player = G.whoseTurn;
  //Get player's discardCount before playing smithy
  count = G.discardCount[player];
  //Run Smithy function
  cardEffect(smithy, choice1, choice2, choice3, &testG, 0, &bonus);
  if (count + 1 == G.discardCount[player])
    printf("_smithy(): PASS correct number of discards\n");
  else
    printf("_smithy(): FAIL correct number of discards\n");


  //Test that no state change occurs for other players
  //Reset game values
  initializeGame(numPlayers, k, time(NULL), &G);
  //Save copy of game state
  memcpy (&testG, &G, sizeof(struct gameState));
  passed = 1;
  //Determine opposing player index
  int p = 1;
  if (G.whoseTurn == 1)
    p = 0;
  //Run Smithy function
  cardEffect(smithy, choice1, choice2, choice3, &testG, 0, &bonus);
  if (G.deckCount[p] == testG.deckCount[p]) {
    for (x = 0; x < G.deckCount[p] && passed == 1; x++) {
      if (testG.deck[p][x] != G.deck[p][x]) {
        passed = 0;
      }
    }
  } else {
    passed = 0;
  }
  //Pre and post hand comparisons for opposing player
  if (G.handCount[p] == testG.handCount[p]) {
    for (x = 0; x < G.handCount[p] && passed == 1; x++) {
      if (testG.hand[p][x] != G.hand[p][x]) {
        passed = 0;
      }
    }
  } else {
    passed = 0;
  }
  //Pre and post discard pile comparison for opposing player
  if (G.discardCount[p] == testG.discardCount[p]) {
    for (x = 0; x < G.discardCount[p] && passed == 1; x++) {
      if (testG.discard[p][x] != G.discard[p][x]) {
        passed = 0;
      }
    }
  } else {
    passed = 0;
  }
  if (passed == 1)
    printf("_smithy(): PASS opposing player cards unchanged\n");
  else
    printf("_smithy(): FAIL opposing player cards unchanged\n");



  //Check if running function causes change in supply card counts
  //Reset game values
  initializeGame(numPlayers, k, time(NULL), &G);
  //Save copy of game state
  memcpy (&testG, &G, sizeof(struct gameState));
  passed = 1;
  for (i = 0; i < 10 && passed == 1; i++) { //Kingdom cards
      //Run function
      cardEffect(smithy, choice1, choice2, choice3, &testG, 0, &bonus);
      //Compare test game state to saved version
      //Check that kingdom card supply counts match
      for (x = 0; x < 10 && passed == 1; x++) {
        if (testG.supplyCount[k[x]] != G.supplyCount[k[x]]) {
          passed = 0;
        }
      }
      //Check that victory and treasure card supply counts match
      for (x = curse; x <= gold && passed == 1; x++) {
        if (testG.supplyCount[x] != G.supplyCount[x]) {
          passed = 0;
        }
      }
  }
  if (passed == 1)
    printf("_smithy(): PASS supply card counts unchanged check\n");
  else
    printf("_smithy(): FAIL supply card counts unchanged check\n");
	
	return 0;
}


