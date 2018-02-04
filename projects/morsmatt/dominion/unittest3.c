/************************************************************************
 ## CS362-winter2018-assignment3
 ## Author: Matthew G. Morse
 ## ONID: morsatt
 ## Description: Test unit for the dominion.c gainCard() function. (Appears
   on lines 1221-1256 of dominion.c)
**************************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include "cards.h" //refactored card functions
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

void testGainCard() {
  int i, passed;
  int numPlayers = 2;
  int k1[] = {
   adventurer,
   /* If no/only 1 treasure found, stop when full deck seen */
   council_room,
   feast, /* choice1 is supply # of card gained) */
   gardens,
   mine, /* choice1 is hand# of money to trash, choice2 is supply# of
	    money to put in hand */
   remodel, /* choice1 is hand# of card to remodel, choice2 is supply# */
   smithy,
   village,

   baron, /* choice1: boolean for discard of estate */
   /* Discard is always of first (lowest index) estate */
   great_hall};
  int k2[] = {
    minion, /* choice1:  1 = +2 coin, 2 = redraw */
    steward, /* choice1: 1 = +2 card, 2 = +2 coin, 3 = trash 2 (choice2,3) */
    tribute,

    ambassador, /* choice1 = hand#, choice2 = number to return to supply */
    cutpurse,
    embargo, /* choice1 = supply# */
    outpost,
    salvager, /* choice1 = hand# to trash */
    sea_hag,
    treasure_map};
    struct gameState g;

  //Check that players can't gain a card from an empty pile






  //Check that gained card is added to the discard pile

  //Check that supply is decremented when a card is gained

  //Check that state change hasn't occurred in other supply piles

  //Check that state change hasn't occured for other players
}

int main(int argc, char* argv[]) {
  testGainCard();
  return 0;
}
