/* -----------------------------------------------------------------------
 * Test adventure card in dominion.c
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
    printf("cardtest1.c -- result for testing adventure:\n");

    int numPlayers = 2;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;;
    struct gameState G, testG;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room};
    initializeGame(numPlayers, k, 1000, &G);

    printf("TEST: there are less than two treasure cards in the deck pile\n");
    // there is no card on deck and there are two treasure cards in discard
    G.deckCount[0] = 0;
    G.discardCount[0] = 10;
    for (int i = 0; i < G.discardCount[0] - 2; i++) {
        G.discard[0][i] = estate;
    }
    G.discard[0][G.discardCount[0] - 2] = copper;
    G.discard[0][G.discardCount[0] - 1] = copper;
    memcpy(&testG, &G, sizeof(struct gameState));
    
    // number of Treasure in hand before play
    int numTreasureOnHandBefore = 0;
    for (int i = 0; i < testG.handCount[0]; i++) {
        if (testG.hand[0][i] == copper || testG.hand[0][i]  == silver || testG.hand[0][i]  == gold) {
            numTreasureOnHandBefore++;
        }
    }

    cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

    // number of Treasure in hand after play
    int numTreasureOnHandAfter = 0;
    for (int i = 0; i < testG.handCount[0]; i++) {
        if (testG.hand[0][i] == copper || testG.hand[0][i]  == silver || testG.hand[0][i]  == gold) {
            numTreasureOnHandAfter++;
        }
    }

    if (testG.handCount[0] != G.handCount[0] + 2) {
        printf("Fail: drew less than two cards\n");
    } else if (numTreasureOnHandAfter != numTreasureOnHandBefore + 2) {
        printf("Fail: two cards are not treasure cards\n");
    } else if (testG.deckCount[0] + testG.discardCount[0] != G.discardCount[0] + G.deckCount[0] - 2) {
        printf("Fail: total cards in hand, deck and discard changed\n");
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

    if(testG.handCount[0] == G.handCount[0] + 2 &&
            testG.deckCount[0] + testG.discardCount[0] == G.discardCount[0] + G.deckCount[0] - 2 &&
            numTreasureOnHandAfter == numTreasureOnHandBefore + 2
            ) {
        if (statusOfOtherPlayerChanged == 0 && gameStatusChanged == 0) {
            printf("PASS: the player drew two treasure cards from deck and discarded other cards. "
                           "Status of the game and the other player did not change\n");
        }
    }


    return 0;
}


