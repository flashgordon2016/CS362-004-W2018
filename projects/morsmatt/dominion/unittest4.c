/************************************************************************
  ## CS362-winter2018-assignment3
  ## Author: Matthew G. Morse
  ## ONID: morsatt
  ## Description: Test unit for the dominion.c isGameOver() function. (Appears
    on lines 391-416 of dominion.c)
**************************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include "cards.h" //refactored card functions
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


void testIsGameOver(){
  int passed, x, numPlayers = 2;
  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
              sea_hag, tribute, smithy, council_room};
  struct gameState G, testG;

  initializeGame(numPlayers, k, time(NULL), &G);

  //Check that game ends when Province supply pile is completely depleted
  G.supplyCount[province] = 0;
  if (isGameOver(&G) == 1)
    printf("_isGameOver(): PASS Province supply empty\n");
  else
    printf("_isGameOver(): FAIL Province supply empty\n");

  //Check if game ends when 3 supply piles are depleted (less than 5 players)
  G.supplyCount[province] = 8; //reset province supply
  G.supplyCount[duchy] = 0;
  G.supplyCount[k[2]] = 0;
  G.supplyCount[gold] = 0;
  if (isGameOver(&G) == 1)
    printf("_isGameOver(): PASS 5 > players, 3 supplies piles empty\n");
  else
    printf("_isGameOver(): FAIL 5 > players, 3 supplies piles empty\n");

  initializeGame(5, k, time(NULL), &G); //Reset supply card values and increase player count
  //Check if game ends when 4 supply piles are depleted (more than 5 players)
  G.supplyCount[estate] = 0;
  G.supplyCount[k[2]] = 0;
  G.supplyCount[curse] = 0;
  G.supplyCount[k[6]] = 0;
  if (isGameOver(&G) == 1)
    printf("_isGameOver(): PASS 5 <= players, 4 supplies piles empty\n");
  else
    printf("_isGameOver(): FAIL 5 <= players, 4 supplies piles empty\n");

  //Check if running function causes change in supply card counts
  //Reset game values
  initializeGame(numPlayers, k, time(NULL), &G);
  //Save game state
  memcpy (&testG, &G, sizeof(struct gameState));
  passed = 1;
  for (i = 0; i < 10 && passed == 1; i++) { //Kingdom cards
      //Run function
      isGameOver(&testG);
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
    printf("_isGameOver(): PASS supply card counts unchanged check\n");
  else
    printf("_isGameOver(): FAIL supply card counts unchanged check\n");

}


int main(int argc, char* argv[]) {
  testIsGameOver();
  return 0;
}

//Broken testing procedure
/*for (pile1 = 0; pile1 < 17 && passed == 1; pile1++) {
  //Don't empty Province supply
  if (pile1 == 13)
    pile1 = 14;
  //Distinguish between kingdom cards and treasure/victory cards
  if (pile1 > 9)
    G.supplyCount[pile1 - 10] = 0;
  else
    G.supplyCount[k[pile1]] = 0;
  for (pile2 = pile1 + 1; pile2 < 17 && passed == 1; pile2++) {
    //Don't empty Province supply
    if (pile2 == 13)
      pile2 = 14;
    //Distinguish between kingdom cards and treasure/victory cards
    if (pile2 > 9)
      G.supplyCount[pile2 - 10] = 0;
    else
      G.supplyCount[k[pile2]] = 0;
    for (pile3 = pile2 + 1; pile3 < 17 && passed == 1; pile3++) {
      //Don't empty Province supply
      if (pile3 == 13)
        pile3 = 14;
      //Distinguish between kingdom cards and treasure/victory cards
      if (pile3 > 9)
        G.supplyCount[pile3 - 10] = 0;
      else
        G.supplyCount[k[pile3]] = 0;

      //3 piles empty, run function
      if (isGameOver(&G) == 0)
        passed = 0;
      //Reset supply pile counts
      initializeGame(numPlayers, k, time(NULL), &G);
    }
  }
}*/
