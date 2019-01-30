/* -----------------------------------------------------------------------
 * Test council_room card in dominion.c
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
    printf("cardtest3.c -- result for testing council_room:\n");

    int numPlayers = 2;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;;
    struct gameState G, testG;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room};
    initializeGame(numPlayers, k, 1000, &G);

    printf("TEST: +4Cards, +1Buy. Each other player draws a card\n");

    memcpy(&testG, &G, sizeof(struct gameState));

    cardEffect(council_room, choice1, choice2, choice3, &testG, handpos, &bonus);

    if (testG.handCount[0] != G.handCount[0] + 3) {
        printf("Fail: drew less than four cards\n");
    }
    if (testG.handCount[0] + testG.deckCount[0] + testG.discardCount[0] + testG.playedCardCount !=
        G.handCount[0] + G.discardCount[0] + G.deckCount[0] + G.playedCardCount) {
        printf("Fail: total cards in hand, deck, discard and played changed\n");
    }
    if (testG.numBuys != G.numBuys + 1) {
        printf("Fail: number of buys did not increase by one\n");
    }

    // test if other player drew a card
    int otherPlayerDrew = 1;
    if (G.handCount[1] != testG.handCount[1] - 1) {
        printf("Fail: other player did not draw a card\n");
        otherPlayerDrew = 0;
    }

    int otherPlayerCardNumChanged = 0;
    if (testG.deckCount[1] + testG.discardCount[1] + testG.handCount[1]!= G.deckCount[1] + G.discardCount[1] + G.handCount[1]) {
        printf("Fail: other player's total card number changed\n");
        otherPlayerCardNumChanged = 1;
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

    if((testG.handCount[0] == G.handCount[0] + 3) && testG.numBuys == G.numBuys + 1 &&
       (testG.handCount[0] + testG.deckCount[0] + testG.discardCount[0] + testG.playedCardCount ==
        G.handCount[0] + G.discardCount[0] + G.deckCount[0] + G.playedCardCount)) {

        if (otherPlayerDrew  == 1 && gameStatusChanged == 0 && otherPlayerCardNumChanged == 0) {
            printf("PASS: the player drew four cards from deck and number of buys increased by one. "
                           "Each of other players drew one card\n");
        }
    }
    return 0;
}


