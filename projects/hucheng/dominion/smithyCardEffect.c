#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "smithyCardEffect.h"

int smithyCardEffect(struct gameState *state, int currentPlayer, int handPos) {
    //+3 Cards
    for (int i = 0; i < 3; i++)
    {
        // TODO: remove bug
        // drawCard(currentPlayer, state);
        drawCard(i, state);
    }

    //discard card from hand
    discardCard(handPos, currentPlayer, state, 0);
    return 0;
}