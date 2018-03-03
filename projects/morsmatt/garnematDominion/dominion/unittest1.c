/************************************************************************
  ## CS362-winter2018-assignment3
  ## Author: Matthew G. Morse
  ## ONID: morsatt
  ## Description: Test unit for the dominion.c updateCoins() function. (Appears
    on lines 1258-1286 of dominion.c)
**************************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include "cards.h" //refactored card functions
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <time.h>


void testUpdateCoins(){
  int passed, coinTotal, i, x, player, numPlayers = 2;
  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
              sea_hag, tribute, smithy, council_room};
  struct gameState G, testG;

  initializeGame(numPlayers, k, time(NULL), &G);

  //Coin total returned matches amount assigned to hand
  passed = 1;
  int handCardCount = 5;
  for (player = 0; player < numPlayers && passed == 1; player++) {
    coinTotal = 0;
    G.handCount[player] = handCardCount;
    for (i = 0; i < G.handCount[player]; i++) {
      G.hand[player][i] = gold;
      coinTotal += 3;
    }
		updateCoins(player, &G, 0); 
    if (G.coins != coinTotal)
      passed = 0;
  }
  if (passed == 1)
    printf("_updateCoins(): PASS updateCoins() == coins assigned to hand\n");
  else
    printf("_updateCoins(): FAIL updateCoins() == coins assigned to hand\n");

  //Total card count remains the same in player's hand after function runs
  initializeGame(numPlayers, k, time(NULL), &G);
  memcpy (&testG, &G, sizeof(struct gameState));
  passed = 1;
  for (player = 0; player < numPlayers && passed == 1; player++) {
    updateCoins(player, &testG, 0);
    if (testG.handCount[player] != G.handCount[player])
      passed = 0;
  }
  if (passed == 1)
    printf("_updateCoins(): PASS handCount is unchanged\n");
  else
    printf("_updateCoins(): FAIL handCount is unchanged\n");

  //Hand composition is unchanged by function
  initializeGame(numPlayers, k, time(NULL), &G);
  memcpy (&testG, &G, sizeof(struct gameState));
  passed = 1;
  for (player = 0; player < numPlayers && passed == 1; player++) {
    updateCoins(player, &testG, 0);
    for (x = 0; x < G.handCount[player]; x++) {
      if (testG.hand[player][i] != G.hand[player][i])
        passed = 0;
    }
  }
  if (passed == 1)
    printf("_updateCoins(): PASS hand composition is unchanged\n");
  else
    printf("_updateCoins(): FAIL hand composition is unchanged\n");


  //Check if running function causes change in supply card counts
  //Reset game values
  initializeGame(numPlayers, k, time(NULL), &G);
  //Save game state
  memcpy (&testG, &G, sizeof(struct gameState));
  passed = 1;
  for (player = 0; player < numPlayers; player++) { //Kingdom cards
      //Run function
      updateCoins(player, &testG, 0);
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
    printf("_updateCoins(): PASS supply card counts unchanged\n");
  else
    printf("_updateCoins(): FAIL supply card counts unchanged\n");

}


int main(int argc, char* argv[]) {
  testUpdateCoins();
  return 0;
}
