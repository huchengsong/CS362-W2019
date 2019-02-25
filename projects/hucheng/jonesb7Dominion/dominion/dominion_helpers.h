#ifndef _DOMINION_HELPERS_H
#define _DOMINION_HELPERS_H

#include "dominion.h"

int cardEffect(int card, int choice1, int choice2, int choice3, 
	       struct gameState *state, int handPos, int *bonus);
int drawCard(int player, struct gameState *state);
int discardCard(int handPos, int currentPlayer, struct gameState *state, 
		int trashFlag);
int gainCard(int supplyPos, struct gameState *state, int toFlag, int player);
int getCost(int cardNumber);
int updateCoins(int player, struct gameState *state, int bonus);

// Card Effect functions
int adventurerEffect(int currentPlayer, struct gameState *state, int drawntreasure, int* temphand, int z);
int councilroomEffect(int handPos, int currentPlayer, struct gameState *state);
int feastEffect();
int greathallEffect(int handPos, int currentPlayer, struct gameState *state);
int smithyEffect(int handPos, int currentPlayer, struct gameState *state);

#endif
