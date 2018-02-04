/************************************************************************
 ## CS362-winter2018-assignment3
 ## Author: Matthew G. Morse
 ## ONID: morsatt
 ## Description: Test unit for the dominion.c fullDeckCount() function. (Appears
   on lines 1221-1256 of dominion.c)
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

  //Check that card supply piles are not changed game

  //Check that state change hasn't occurred in other supply piles

  //Check that state change hasn't occured for other players
}

int main(int argc, char* argv[]) {
  testFullDeckCount();
  return 0;
}
