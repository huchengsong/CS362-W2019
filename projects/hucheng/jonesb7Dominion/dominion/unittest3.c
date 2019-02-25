/* -----------------------------------------------------------------------
 * Test function isGameOver() in dominion.c
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
    printf("unittest3.c -- result for running isGameOver() tests:\n");

    int numPlayer = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine
            , remodel, smithy, village, baron, great_hall}; // this is not relevant in this test
    struct gameState G;
    srand(time(NULL));

    printf("Testing the situation where game is not over (none of the piles are empty):\n");
    memset(&G, 0, sizeof(struct gameState)); // reset G
    initializeGame(numPlayer, k, 1000, &G);
    int result = isGameOver(&G);
    if (result == 0) {
        printf("PASS. isGameOver() returns %d\n", result);
    } else{
        printf("FAIL. isGameOver() returns %d\n", result);
    }

    printf("Testing the situation where game is not over (only two of the supply piles are empty):\n");
    memset(&G, 0, sizeof(struct gameState)); // reset G
    initializeGame(numPlayer, k, 1000, &G);
    G.supplyCount[minion] = 0;
    G.supplyCount[steward] = 0;
    result = isGameOver(&G);
    if (result == 0) {
        printf("PASS. isGameOver() returns %d\n", result);
    } else{
        printf("FAIL. isGameOver() returns %d\n", result);
    }

    printf("Testing the situation where game is over (Province cards are empty):\n");
    memset(&G, 0, sizeof(struct gameState)); // reset G
    initializeGame(numPlayer, k, 1000, &G);
    G.supplyCount[province] = 0;
    result = isGameOver(&G);
    if (result == 1) {
        printf("PASS. isGameOver() returns %d\n", result);
    } else{
        printf("FAIL. isGameOver() returns %d\n", result);
    }

    printf("Testing the situation where game is over (three supply piles are empty but Province is not empty):\n");
    memset(&G, 0, sizeof(struct gameState)); // reset G
    initializeGame(numPlayer, k, 1000, &G);
    G.supplyCount[estate] = 0;
    G.supplyCount[village] = 0;
    G.supplyCount[treasure_map] = 0;
    result = isGameOver(&G);
    if (result == 1) {
        printf("PASS. isGameOver() returns %d\n", result);
    } else{
        printf("FAIL. isGameOver() returns %d\n", result);
    }

    return 0;
}