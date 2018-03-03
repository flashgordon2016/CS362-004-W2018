/************************************************************************
 ## CS362-winter2018-assignment3
 ## Author: Matthew G. Morse
 ## ONID: morsatt
 ## Description: Test unit for the adventurer cardEffect() function that was
    refactored to cards.c.
**************************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>


int main(int argc, char* argv[]){
  int passed, player, x, numPlayers = 2;
  int k[10] = {adventurer, adventurer, village, minion, mine, cutpurse,
              sea_hag, tribute, smithy, council_room};
  struct gameState G, testG;
  initializeGame(numPlayers, k, time(NULL), &G);

  //Check for infinite loop when less than 2 treasure cards are available
 /* player = G.whoseTurn;
  for (i = 0; i < G.deckCount[player]; i++) { //put just one treasure in deck
    if (i > 0)
      G.deck[player][i] = smithy;
    else
      G.deck[player][i] = gold;
  }
  for (i = 0; i < G.discardCount[player]; i++) { //make discard pile consist of only smithy cards
    G.discard[player][i] = smithy;
  }
  x = 1;
  time_t start = time(NULL);
  time_t finish = start + 5;
  while (start < finish) {
    if (x == 1)
      cardEffect(adventurer, 0, 0, 0, &G, 0, &bonus);
    x++;
    if (x == 2)
      break;
  }
  if (x > 1)
    printf("_adventurer(): PASS adventurer avoids infinite loop, less 2 treasure\n");
  else
    printf("_adventurer(): PASS adventurer avoids infinite loop, less 2 treasure\n");
*/

  //Test that card supply counts are not changed by adventurer
  //Reset game values
  initializeGame(numPlayers, k, time(NULL), &G);
  //Save game state
  memcpy (&testG, &G, sizeof(struct gameState));
  passed = 1;
  for (player = 0; player < numPlayers; player++) { //Kingdom cards
      //Run function
      cardEffect(adventurer, smithy, 0, 0, &G, 5, 0); //Add adventurer to smithy
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
    printf("_adventurer(): PASS supply card counts unchanged\n");
  else
    printf("_adventurer(): FAIL supply card counts unchanged\n");


  //Check that opposing player's cards are not changed by adventurer action
  //Reset game values
  initializeGame(numPlayers, k, time(NULL), &G);
  //Save copy of game state
  memcpy (&testG, &G, sizeof(struct gameState));
  passed = 1;
  //Determine opposing player index
  int p = 1;
  if (G.whoseTurn == 1)
    p = 0;
  //Run adventurer function
  cardEffect(adventurer, smithy, 0, 0, &G, 5, 0); //Add adventurer to smithy
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
    printf("_adventurer(): PASS opposing player cards unchanged\n");
  else
    printf("_adventurer(): FAIL opposing player cards unchanged\n");

  return 0;
}
