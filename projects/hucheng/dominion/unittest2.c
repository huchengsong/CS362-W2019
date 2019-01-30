/* -----------------------------------------------------------------------
 * Test fullDeckCount() in dominion.c
 * -----------------------------------------------------------------------
 */

#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"


int main() {
    printf("unittest2.c -- result for running fullDeckCount() tests:\n");

    int numPlayer = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine
            , remodel, smithy, village, baron, great_hall}; // this is not relevant in this test
    struct gameState G;
    srand(time(NULL));

    if (initializeGame(numPlayer, k, 1000, &G)) {
        printf("Can't initialize game");
        return -1;
    }

    printf("Testing empty deck, hand and discard:\n");
    memset(&G, 0, sizeof(struct gameState)); // reset G
    G.deckCount[0] = 0;
    G.handCount[0] = 0;
    G.discardCount[0] = 0;
    int card = rand() % 27; // generate random card
    int result = fullDeckCount(0, card, &G);
    if (result == 0) {
        printf("PASS. fullDeckCount() returns %d\n", result);
    } else{
        printf("FAIL. fullDeckCount() returns %d\n", result);
    }

    printf("Testing a total of 30 same cards out of 30 cards in deck, hand and discard:\n");
    G.deckCount[0] = 10;
    G.handCount[0] = 10;
    G.discardCount[0] = 10;
    card = rand() % 27; // generate random card
    for (int i = 0; i < G.deckCount[0]; i++){
        G.deck[0][i] = card;
    }
    for (int i = 0; i < G.handCount[0]; i++){
        G.hand[0][i] = card;
    }
    for (int i = 0; i < G.discardCount[0]; i++){
        G.discard[0][i] = card;
    }
    result = fullDeckCount(0, card, &G);
    if (result == G.deckCount[0] + G.handCount[0] + G.discardCount[0]) {
        printf("PASS. fullDeckCount() returns %d\n", result);
    } else{
        printf("FAIL. fullDeckCount() returns %d\n", result);
    }

    printf("Testing a total of 6 same cards out of 30 cards in deck, hand and discard:\n");
    G.deckCount[0] = 10;
    G.handCount[0] = 10;
    G.discardCount[0] = 10;
    card = 26;
    for (int i = 0; i < G.deckCount[0] - 2; i++){
        G.deck[0][i] = rand() % 26;
    }
    for (int i = 0; i < G.handCount[0] - 2; i++){
        G.hand[0][i] = rand() % 26;
    }
    for (int i = 0; i < G.discardCount[0] - 2; i++){
        G.discard[0][i] = rand() % 26;
    }
    G.deck[0][G.deckCount[0] - 2] =  card;
    G.deck[0][G.deckCount[0] - 1] =  card;
    G.hand[0][G.handCount[0] - 2] =  card;
    G.hand[0][G.handCount[0] - 1] =  card;
    G.discard[0][G.discardCount[0] - 2] =  card;
    G.discard[0][G.discardCount[0] - 1] =  card;

    result = fullDeckCount(0, card, &G);
    if (result == 6) {
        printf("PASS. fullDeckCount() returns %d\n", result);
    } else{
        printf("FAIL. fullDeckCount() returns %d\n", result);
    }

    return 0;
}