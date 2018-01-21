#ifndef _CARDS_H
#define _CARDS_H
#include "dominion.h" //Needed for struct gameState definition
#include "dominion_helpers.h"


int adventurerAction(int currentPlayer, struct gameState *state, int *temphand);
int embargoAction(int choice1, int currentPlayer, struct gameState *state, int handPos);
int outpostAction(int currentPlayer, struct gameState *state, int handPos);
int smithyAction(int currentPlayer, struct gameState *state, int handPos);
int stewardAction(int choice1, int choice2, int choice3, int currentPlayer, struct gameState *state, int handPos);
#endif
