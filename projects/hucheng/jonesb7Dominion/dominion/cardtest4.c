/* -----------------------------------------------------------------------
 * Test great_hall card in dominion.c
 * -----------------------------------------------------------------------
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>


int main() {
    printf("cardtest4.c -- result for testing great_hall:\n");

    int numPlayers = 2;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;;
    struct gameState G, testG;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room};
    initializeGame(numPlayers, k, 1000, &G);

    printf("TEST: +1 Card +1 Action\n");

    memcpy(&testG, &G, sizeof(struct gameState));

    cardEffect(great_hall, choice1, choice2, choice3, &testG, handpos, &bonus);

    if (testG.handCount[0] != G.handCount[0]) {
        printf("Fail: failed to draw a card or discard great_hall card\n");
    }
    if (testG.handCount[0] + testG.deckCount[0] + testG.discardCount[0] + testG.playedCardCount !=
        G.handCount[0] + G.discardCount[0] + G.deckCount[0] + G.playedCardCount) {
        printf("Fail: total cards in hand, deck, discard and played changed\n");
    }
    if (testG.numActions != G.numActions + 1) {
        printf("Fail: failed to increase action\n");
    }

    // test if other player's status has changed
    int statusOfOtherPlayerChanged = 0;
    if (G.handCount[1] != testG.handCount[1]) {
        statusOfOtherPlayerChanged = 1;
    }
    for (int i = 0; i < G.handCount[1]; i++) {
        if(G.hand[1][i] != testG.hand[1][i]) {
            statusOfOtherPlayerChanged = 1;
        }
    }
    if (G.deckCount[1] != testG.deckCount[1]) {
        statusOfOtherPlayerChanged = 1;
    }
    for (int i = 0; i < G.deckCount[1]; i++) {
        if(G.deck[1][i] != testG.deck[1][i]) {
            statusOfOtherPlayerChanged = 1;
        }
    }
    if (G.discardCount[1] != testG.discardCount[1]) {
        statusOfOtherPlayerChanged = 1;
    }
    for (int i = 0; i < G.discardCount[1]; i++) {
        if(G.discard[1][i] != testG.discard[1][i]) {
            statusOfOtherPlayerChanged = 1;
        }
    }
    if (statusOfOtherPlayerChanged == 1) {
        printf("Fail: the status of the other player has changed\n");
    }

    int gameStatusChanged = 0;
    for (int i = 0; i < 27; i++) {
        if (G.supplyCount[i] != testG.supplyCount[i]) {
            gameStatusChanged = 1;
        }
    }
    if (gameStatusChanged == 1) {
        printf("Fail: game status has changed\n");
    }

    if(testG.handCount[0] == G.handCount[0] &&
            testG.handCount[0] + testG.deckCount[0] + testG.discardCount[0] + testG.playedCardCount ==
            G.handCount[0] + G.discardCount[0] + G.deckCount[0] + G.playedCardCount &&
            testG.numActions == G.numActions + 1
            ) {
        if (statusOfOtherPlayerChanged == 0 && gameStatusChanged == 0) {
            printf("PASS: the player drew a card and the action increased by 1. "
                           "Status of the game and the other player did not change\n");
        }
    }
    return 0;
}


