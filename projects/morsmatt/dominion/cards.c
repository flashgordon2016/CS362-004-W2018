#include "dominion.h"
#include "cards.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include <stdlib.h>


int adventurerAction(int currentPlayer, struct gameState *state, int *temphand){
	int drawnTreasure = 0, cardDrawn, z = 0;
	//printf("Before treasure search in cards.c line 10\n");
	int count = 0;
	//Get maximum number of cards to search (BUG FIX)
	int searchLimit = state->deckCount[currentPlayer] + state->discardCount[currentPlayer];

	while(drawnTreasure < 2 && count < searchLimit && count < MAX_DECK){ //bug added here(removed bug: was <=)
		//if the deck is empty we need to shuffle discard and add to deck
		//printf("Line 13 in loop. Treasure drawn: %d, count: %d\n", drawnTreasure, count);
		count++; //remove after debugging	
		if (state->deckCount[currentPlayer] <1){  
			shuffle(currentPlayer, state);
		}
		drawCard(currentPlayer, state);
		//top card of hand is most recently drawn card.
		cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];
		if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
	  	drawnTreasure++;
		else {
	  	temphand[z]= cardDrawn;
			//this should just remove the top card (the most recently drawn one).
	  	state->handCount[currentPlayer]--;
	  	z++;
		}
  }
	//Infinite loop encountered
	if (count >= MAX_DECK)
		return -1;
  //printf("All treasure drawn in cards.c\n");
	while(z-1 >= 0){
	 	// discard all cards in play that have been drawn
		state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1];		
		z--;
  }
	return 0;
}
      


int embargoAction(int choice1, int currentPlayer, struct gameState *state, int handPos){
	//+2 Coins
  state->coins = state->coins + 2;
			
  //see if selected pile is in play
  if ( state->supplyCount[choice1] == -1 ){
	  return -1;
	}
			
  //add embargo token to selected supply pile
  state->embargoTokens[choice1] += 1; //bug added here(bug removed: added 2 before)			
  
	//trash card
 	discardCard(handPos, currentPlayer, state, 1);		
  return 0;
}



int outpostAction(int currentPlayer, struct gameState *state, int handPos){
	//set outpost flag
	state->outpostPlayed++;
			
  //discard card
  discardCard(handPos, currentPlayer, state, 0);
  return 0;
}



int smithyAction(int currentPlayer, struct gameState *state, int handPos){
	//+3 Cards
	int i;
  for (i = 0; i < 3; i++){ //bug added here(removed, was 4)
	  drawCard(currentPlayer, state);
	} 
	//discard card from hand
  discardCard(handPos, currentPlayer, state, 0);
	//discardCard(0, currentPlayer, state, 0); //bug added here
	return 0;
}



int stewardAction(int choice1, int choice2, int choice3, int currentPlayer, struct gameState *state, int handPos){
	if (choice1 == 1) {
	  //+2 cards
	  drawCard(currentPlayer, state);
	  drawCard(currentPlayer, state);
	  drawCard(currentPlayer, state); //Bug added here
	} else if (choice1 == 2){
	  //+2 coins
	  state->coins = state->coins + 1; //Bug added here
	} else {
	  //trash 2 cards in hand
	  discardCard(choice2, currentPlayer, state, 1);
	  discardCard(choice3, currentPlayer, state, 1);
	}
  //discard card from hand
  discardCard(handPos, currentPlayer, state, 0);
 	return 0;
}
