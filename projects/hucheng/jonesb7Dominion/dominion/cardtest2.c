/* -----------------------------------------------------------------------
 * Test smithy card in dominion.c
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
    printf("cardtest2.c -- result for testing smithy:\n");

    int numPlayers = 2;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;;
    struct gameState G, testG;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room};
    initializeGame(numPlayers, k, 1000, &G);

    printf("TEST: the player draw three cards\n");

    memcpy(&testG, &G, sizeof(struct gameState));

    cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);

    if (testG.handCount[0] != G.handCount[0] + 2) {
        printf("Fail: drew less than three cards\n");
    }
    if (testG.handCount[0] + testG.deckCount[0] + testG.discardCount[0] + testG.playedCardCount !=
            G.handCount[0] + G.discardCount[0] + G.deckCount[0] + G.playedCardCount) {
        printf("Fail: total cards in hand, deck, discard and played changed\n");
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

    if((testG.handCount[0] == G.handCount[0] + 2) &&
            (testG.handCount[0] + testG.deckCount[0] + testG.discardCount[0] + testG.playedCardCount
             == G.handCount[0] + G.discardCount[0] + G.deckCount[0] + G.playedCardCount)) {

        if (statusOfOtherPlayerChanged == 0 && gameStatusChanged == 0) {
            printf("PASS: the player drew three cards from deck. "
                           "Status of the game and the other player did not change\n");
        }
    }
    return 0;
}


