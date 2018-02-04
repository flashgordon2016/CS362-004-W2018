/************************************************************************
 ## CS362-winter2018-assignment3
 ## Author: Matthew G. Morse
 ## ONID: morsatt
 ## Description: Test unit for the dominion.c fullDeckCount() function. (Appears
   on lines 325-345 of dominion.c)
**************************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include "cards.h" //refactored card functions
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include "rngs.h"

void testFullDeckCount() {
  int player, i, j, passed, cardCount;
  int numPlayers = 2;
  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
              sea_hag, tribute, smithy, council_room};
  struct gameState G, testG;

  initializeGame(numPlayers, k, time(NULL), &G);

  //Check that count matches assigned total for given card
  passed = 1;
  //Run test with each player
  for (player = 0; player < numPlayers && passed; player++) {
    for (i = 0; i < 10 && passed == 1; i++) { //Kingdom cards
      cardCount = 0; //Tracks assigned card total for comparison
      for (j = 0; j < 10 && passed == 1; j++) { //Add cards
        G.deck[player][G.deckCount[player]] = k[i];
        G.deckCount[player]++; //increment deck count
        G.discard[player][G.discardCount[player]] = k[i];
        G.discardCount[player]++; //increment discard pile count
        G.hand[player][G.handCount[player]] = k[i];
        G.handCount[player]++; //increment deck count
        cardCount += 3;
        if (fullDeckCount(player, k[i], &G) != cardCount)
          passed = 0;
      }
    }
  }
  if (passed == 1)
    printf("_fullDeckCount(): PASS assigned card count check\n");
  else
    printf("_fullDeckCount(): FAIL assigned card count check\n");

  //Check that game state is not changed for players
  //Reset game values
  initializeGame(numPlayers, k, time(NULL), &G);
  //Save game state
  memcpy (&testG, &G, sizeof(struct gameState));
  //Run test with each player
  passed = 1;
  for (player = 0; player < numPlayers && passed; player++) {
    for (i = 0; i < 10 && passed == 1; i++) { //Kingdom cards
        //Run function
        fullDeckCount(player, k[i], &testG);
        //Compare test game state to saved version
        //Pre and post deck comparisons for each player
        int p, x;
        for (p = 0; p < numPlayers && passed == 1; p++) {
          if (G.deckCount[p] == testG.deckCount[p]) {
            for (x = 0; x < G.deckCount[p] && passed == 1; x++) {
              if (testG.deck[p][x] != G.deck[p][x]) {
                passed = 0;
              }
            }
          } else {
            passed = 0;
          }
        }
        //Pre and post hand comparisons for each player
        for (p = 0; p < numPlayers && passed == 1; p++) {
          if (G.handCount[p] == testG.handCount[p]) {
            for (x = 0; x < G.handCount[p] && passed == 1; x++) {
              if (testG.hand[p][x] != G.hand[p][x]) {
                passed = 0;
              }
            }
          } else {
            passed = 0;
          }
        }
        //Pre and post discard pile comparison for each player
        for (p = 0; p < numPlayers && passed == 1; p++) {
          if (G.discardCount[p] == testG.discardCount[p]) {
            for (x = 0; x < G.discardCount[p] && passed == 1; x++) {
              if (testG.discard[p][x] != G.discard[p][x]) {
                passed = 0;
              }
            }
          } else {
            passed = 0;
          }
      	}
    }
  }
  if (passed == 1)
    printf("_fullDeckCount(): PASS player states unchanged check\n");
  else
    printf("_fullDeckCount(): FAIL player states unchanged check\n");

  //Check that card supply piles are not changed
  //Reset game values
  initializeGame(numPlayers, k, time(NULL), &G);
  //Save game state
  memcpy (&testG, &G, sizeof(struct gameState));
  passed = 1;
  for (player = 0; player < numPlayers && passed; player++) {
    for (i = 0; i < 10 && passed == 1; i++) { //Kingdom cards
        //Run function
        fullDeckCount(player, k[i], &testG);
        //Compare test game state to saved version
        //Pre and post deck comparisons for each player
        int x;
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
  }
  if (passed == 1)
    printf("_fullDeckCount(): PASS supply card counts unchanged check\n");
  else
    printf("_fullDeckCount(): FAIL supply card counts unchanged check\n");


}

int main(int argc, char* argv[]) {
  testFullDeckCount();
  return 0;
}
