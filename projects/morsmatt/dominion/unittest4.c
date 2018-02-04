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
  int player, passed, pile1, pile2, pile3, pile4;
  int numPlayers = 2;
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
  passed = 1;
  G.supplyCount[province] = 8; //reset province supply
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
  G.supplyCount[duchy] = 0;
  G.supplyCount[k[2]] = 0;
  G.supplyCount[gold] = 0;
  if (isGameOver(&G) == 1)
    printf("_isGameOver(): PASS 5 > players, 3 supplies piles empty\n");
  else
    printf("_isGameOver(): FAIL 5 > players, 3 supplies piles empty\n");




  //Check if game ends when 4 supply piles are depleted (more than 5 players)

  //Check if running function causes change in supply card counts
}


int main(int argc, char* argv[]) {
  testIsGameOver();
  return 0;
}
