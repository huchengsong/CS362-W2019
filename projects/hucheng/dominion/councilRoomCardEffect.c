#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "councilRoomCardEffect.h"

int councilRoomCardEffect(struct gameState *state, int currentPlayer, int handPos) {

    //+4 Cards
    for (int i = 0; i < 4; i++)
    {
        drawCard(currentPlayer, state);
    }

    // TODO: remove bug
    //+1 Buy
    // state->numBuys++;

    //Each other player draws a card
    for (int i = 0; i < state->numPlayers; i++)
    {
        if ( i != currentPlayer )
        {
            drawCard(i, state);
        }
    }

    //put played card in played card pile
    discardCard(handPos, currentPlayer, state, 0);

    return 0;
}