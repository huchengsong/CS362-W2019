/* -----------------------------------------------------------------------
 * Test function supplyCount() in dominion.c
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
    printf("unittest4.c -- result for running supplyCount() tests:\n");

    int numPlayer = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine
            , remodel, smithy, village, baron, great_hall}; // this is not relevant in this test
    struct gameState G;
    initializeGame(numPlayer, k, 1000, &G);
    srand(time(NULL));

    printf("Testing the situation where a card is not chosen in the game:\n");
    int result = supplyCount(tribute, &G);
    if (result == -1) {
        printf("PASS. supplyCount() returns %d; expecting -1\n", result);
    } else{
        printf("FAIL. supplyCount() returns %d\n; expecting -1\n", result);
    }

    printf("Testing the situation where a card has 10 in the pile:\n");
    G.supplyCount[smithy] = 10;
    result = supplyCount(smithy, &G);
    if (result == 10) {
        printf("PASS. supplyCount() returns %d; expecting 10\n", result);
    } else{
        printf("FAIL. supplyCount() returns %d; expecting 10\n", result);
    }


    return 0;
}