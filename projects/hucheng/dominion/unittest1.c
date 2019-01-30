/* -----------------------------------------------------------------------
 * Test function shuffle() in dominion.c
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
    printf("unittest1.c -- result for running shuffle() tests:\n");

    int numPlayer = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine
            , remodel, smithy, village, baron, great_hall}; // this is not relevant in this test
    struct gameState G;
    srand(time(NULL));

    if (initializeGame(numPlayer, k, 1000, &G)) {
        printf("Can't initialize game");
        return -1;
    }

    printf("Testing 0 cards in deck:\n");
    memset(&G, 0, sizeof(struct gameState)); // reset G
    G.deckCount[0] = 0;
    int result = shuffle(0, &G);
    if (result != 0) {
        printf("PASS. shuffle() returns %d\n", result);
    } else{
        printf("FAIL. shuffle() returns %d\n", result);
    }

    printf("Testing 10 cards in deck:\n");
    memset(&G, 0, sizeof(struct gameState)); // reset G
    // generate random deck
    G.deckCount[0] = 10;
    int originalDeck[MAX_DECK];
    for (int i = 0; i < G.deckCount[0]; i++) {
        int randNum = rand() % 27;
        G.deck[0][i] = randNum;
        originalDeck[i] =  randNum;
    }

    // test shuffle() result
    result = shuffle(0, &G);
    if (result != 0){
        printf("FAIL. shuffle() returns %d\n", result);
    }
    int shuffled = 0;
    int matchedNum = 0;
    for (int i = 0; i < G.deckCount[0]; i++) {
        for (int j = 0; j < G.deckCount[0]; j++) {
            if (originalDeck[j] == G.deck[0][i]) {
                if (i != j) shuffled = 1;
                originalDeck[j] = -1;
                matchedNum++;
                break;
            }
        }
    }

    if (shuffled && matchedNum == G.deckCount[0]) {
        printf("PASS. shuffle() shuffled the deck\n");
    }


    printf("Testing MAX_DECK cards in deck:\n");
    memset(&G, 0, sizeof(struct gameState)); // reset G
    // generate random deck
    G.deckCount[0] = MAX_DECK;
    for (int i = 0; i < G.deckCount[0]; i++) {
        int randNum = rand() % 27;
        G.deck[0][i] = randNum;
        originalDeck[i] =  randNum;
    }

    // test shuffle() result
    result = shuffle(0, &G);
    if (result != 0){
        printf("FAIL. shuffle() returns %d\n", result);
    }
    shuffled = 0;
    matchedNum = 0;
    for (int i = 0; i < G.deckCount[0]; i++) {
        for (int j = 0; j < G.deckCount[0]; j++) {
            if (originalDeck[j] == G.deck[0][i]) {
                if (i != j) shuffled = 1;
                originalDeck[j] = -1;
                matchedNum++;
                break;
            }
        }
    }

    if (shuffled && matchedNum == G.deckCount[0]) {
        printf("PASS. shuffle() shuffled the deck\n");
    }
    return 0;
}