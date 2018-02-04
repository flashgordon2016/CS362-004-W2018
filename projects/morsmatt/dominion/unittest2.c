/************************************************************************
 ## CS362-winter2018-assignment3
 ## Author: Matthew G. Morse
 ## ONID: morsatt
 ## Description: Test unit for the dominion.c getCost() function. (Appears
   on lines 584-645 of dominion.c)
**************************************************************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include "cards.h" //refactored card functions
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"


void testGetCost() {
  int i, passed;
  int distinctCards = 27;

  //Check that getCost() returns nonnegative values for all valid cards
  passed = 1; //Test is assumed successful until proven otherwise
  for (i = 0; i < distinctCards && passed == 1; i++) {
    if (getCost(i) < 0)
      passed = 0;
  }
  if (passed == 1)
    printf("_getCost(): PASS negative cost check\n");
  else
    printf("_getCost(): FAIL negative cost check\n");

  //Check that getCost() returns invalid value (negative) when called
  //to find non-existent card
  passed = 1;
  if (getCost(-1) < 0 || getCost(30) < 0)
    printf("_getCost(): PASS invalid card enum check\n");
  else
    printf("_getCost(): FAIL invalid card enum check\n");

  //Check that the state of the players in a game is not altered by
  //calling getCost()

  //Check that the state of the supply decks is not altered by
  //calling getCost()

  //Check that no card costs more than 8 coins
  passed = 1; //Test is assumed successful until proven otherwise
  for (i = -1; (i < (distinctCards + 1)) && passed == 1; i++) {
    if (getCost(i) <= 8)
      passed = 0;
  }
  if (passed == 1)
    printf("_getCost(): PASS maximum cost check\n");
  else
    printf("_getCost(): FAIL maximum cost check\n");
}


int main(int argc, char *argv[]) {
  testGetCost();
  return 0;
}
