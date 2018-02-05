/************************************************************************
 ## CS362-winter2018-assignment3
 ## Author: Matthew G. Morse
 ## ONID: morsatt
 ## Description: Test unit for the outpost cardEffect() function that was
    refactored to cards.c.
**************************************************************************/
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
  int passed, player, x, numPlayers = 2;
  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
              sea_hag, tribute, smithy, council_room};
  struct gameState G, testG;
  initializeGame(numPlayers, k, time(NULL), &G);


  //Check that Outpost triggers flag in game state
  //Save game state
  memcpy (&testG, &G, sizeof(struct gameState));
  cardEffect(outpost, 0, 0, 0, &G, 5, 0);
  if ((G.outpostPlayed + 1) == testG.outpostPlayed)
    printf("_outpost(): PASS outpost flag triggered in game state\n");
  else
    printf("_outpost(): FAIL outpost flag triggered in game state\n");


  //Check that supply cards aren't affected by Outpost function
  //Reset game values
  initializeGame(numPlayers, k, time(NULL), &G);
  //Save game state
  memcpy (&testG, &G, sizeof(struct gameState));
  passed = 1;
  for (player = 0; player < numPlayers; player++) { //Kingdom cards
      //Run function
      cardEffect(outpost, 0, 0, 0, &G, 5, 0);
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
    printf("_outpost(): PASS supply card counts unchanged\n");
  else
    printf("_outpost(): FAIL supply card counts unchanged\n");

  //Check that opposing player's cards are not changed by Outpost
  //Reset game values
  initializeGame(numPlayers, k, time(NULL), &G);
  //Save copy of game state
  memcpy (&testG, &G, sizeof(struct gameState));
  passed = 1;
  //Determine opposing player index
  int p = 1;
  if (G.whoseTurn == 1)
    p = 0;
  //Run outpost function
  cardEffect(outpost, 0, 0, 0, &G, 5, 0);
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
    printf("_outpost(): PASS opposing player cards unchanged\n");
  else
    printf("_outpost(): FAIL opposing player cards unchanged\n");

  return 0;
}
